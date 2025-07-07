# Paths
secrets_dir = secrets
wifi_env_file = $(secrets_dir)/set_wifi_env.sh

# Initialization targets
init-secrets: init-wifi-secrets
	@echo "Secrets initialization completed successfully."

init-wifi-secrets:
	@echo "Starting Wi-Fi secrets initialization..."
	@read -p "SSID: " ssid; \
	read -s -p "PASS: " pass; echo; \
	mkdir -p $(secrets_dir); \
	echo "#!/bin/bash" > $(wifi_env_file); \
	echo "export WIFI_SSID=\"$$ssid\"" >> $(wifi_env_file); \
	echo "export WIFI_PASS=\"$$pass\"" >> $(wifi_env_file); \
	echo "echo \"Environment variables set:\"" >> $(wifi_env_file); \
	echo "echo \"WIFI_SSID=\$$WIFI_SSID\"" >> $(wifi_env_file); \
	echo "echo \"WIFI_PASS=\$$WIFI_PASS\"" >> $(wifi_env_file); \
	chmod +x $(wifi_env_file)
	@echo "Wi-Fi secrets initialization completed successfully."

# Load secrets
load-secrets:
	@if [ ! -f "$(wifi_env_file)" ]; then \
		echo "Warning: secrets not initialized. Run 'make init-secrets' first."; \
		exit 1; \
	fi
	@echo "Secrets file exists at '$(wifi_env_file)'"
	@echo "To load secrets into your shell environment, run:"
	@echo "  source $(wifi_env_file)"
	@echo "Secrets not loaded automatically - manual sourcing required."

# Build and upload
build:
	@echo "Starting build..."
	pio run
	@echo "Build completed successfully."

upload:
	@echo "Starting upload (build will run if necessary)..."
	pio run --target upload
	@echo "Upload completed successfully."

fs:
	@echo "Starting filesystem upload (build will run if necessary)..."
	pio run --target uploadfs
	@echo "Filesystem upload completed successfully."

monitor:
	@echo "Starting monitor..."
	pio device monitor
	@echo "Monitor session ended."

# Cleanup targets
clean-wifi-secret:
	@echo "Starting Wi-Fi secret cleanup..."
	rm -f $(wifi_env_file)
	@echo "Wi-Fi secret cleanup completed successfully."

clean-secrets:
	@echo "Starting secrets directory cleanup..."
	rm -rf $(secrets_dir)
	@echo "Secrets directory cleanup completed successfully."

clean-all: clean-wifi-secret clean-secrets
	@echo "Full cleanup completed successfully."

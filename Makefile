# System Python (для создания venv)
python ?= python3.10
# python / venv
venv_dir = venv
venv_bin = $(venv_dir)/bin
pip = $(venv_bin)/pip
pio = $(venv_bin)/pio
venv_python = $(venv_bin)/python
# Paths
secrets_dir = secrets
wifi_env_file = $(secrets_dir)/set_wifi_env.sh

# Initialization targets
init-venv:
	@echo "Initializing virtual environment..."
	$(python) -m venv $(venv_dir)
	@echo "Installing dependencies..."
	$(pip) install --upgrade pip
	$(pip) install -r requirements.txt
	@echo "Virtual environment initialized successfully."

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

# Validation targets
check-venv:
	@if [ ! -f "$(pio)" ]; then \
		echo "Error: venv not initialized or PlatformIO missing. Run 'make init-venv' first."; \
		exit 1; \
	fi

# Build and upload
build: check-venv
	@echo "Starting build..."
	$(pio) run
	@echo "Build completed successfully."

upload: check-venv
	@echo "Starting upload (build will run if necessary)..."
	$(pio) run --target upload
	@echo "Upload completed successfully."

fs: check-venv
	@echo "Starting filesystem upload (build will run if necessary)..."
	$(pio) run --target uploadfs
	@echo "Filesystem upload completed successfully."

monitor: check-venv
	@echo "Starting monitor..."
	$(pio) device monitor
	@echo "Monitor session ended."

# Cleanup targets
clean-venv:
	@echo "Starting virtual environment cleanup..."
	rm -rf $(venv_dir)
	@echo "Virtual environment cleanup completed successfully."

clean-wifi-secret:
	@echo "Starting Wi-Fi secret cleanup..."
	rm -f $(wifi_env_file)
	@echo "Wi-Fi secret cleanup completed successfully."

clean-secrets:
	@echo "Starting secrets directory cleanup..."
	rm -rf $(secrets_dir)
	@echo "Secrets directory cleanup completed successfully."

clean-all: clean-venv clean-wifi-secret clean-secrets
	@echo "Full cleanup completed successfully."

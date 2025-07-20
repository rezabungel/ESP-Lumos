#include "LittleFSConfig.h"
#include "LittleFSService.h"

bool LittleFSService::begin()
{
#if LITTLEFS_SHOULD_FORMAT == 0
    Serial.println("Mounting LittleFS...");
    if (!LittleFS.begin(false))
    {
        Serial.println("Failed to mount LittleFS.");
        return false;
    }
    Serial.println("LittleFS mounted successfully.");
    return true;
#elif LITTLEFS_SHOULD_FORMAT == 1
    Serial.println("Formatting LittleFS...");
    if (!LittleFS.format())
    {
        Serial.println("Failed to format LittleFS.");
        return false;
    }
    Serial.println("LittleFS formatted successfully.");
    Serial.println("Rebooting into mounted mode (LITTLEFS_SHOULD_FORMAT = 0)...");
    esp_deep_sleep_start();
    return false; // Unreachable: esp_deep_sleep_start() halts execution.
#endif
}

void LittleFSService::ls(const char *path)
{
    if (!LittleFS.exists(path))
    {
        Serial.printf("No such file or directory: %s\n", path);
        return;
    }

    Serial.printf("Listing files in: %s\n", path);
    File root = LittleFS.open(path);
    if (!root)
    {
        Serial.printf("Failed to open path: %s\n", path);
        return;
    }
    else if (!root.isDirectory())
    {
        Serial.printf("FILE: %s (%u bytes)\n", root.name(), root.size());
        root.close();
        return;
    }

    File file = root.openNextFile();
    while (file)
    {
        if (file.isDirectory())
        {
            Serial.printf("DIR: %s\n", file.name());
        }
        else
        {
            Serial.printf("FILE: %s (%u bytes)\n", file.name(), file.size());
        }
        file.close();
        file = root.openNextFile();
    }
    root.close();
}

bool LittleFSService::exists(const char *path)
{
    return LittleFS.exists(path);
}

bool LittleFSService::isDir(const char *path)
{
    if (!exists(path))
    {
        return false;
    }

    File f = LittleFS.open(path);
    if (!f)
    {
        return false;
    }

    bool result = f.isDirectory();
    f.close();
    return result;
}

bool LittleFSService::isFile(const char *path)
{
    if (!exists(path))
    {
        return false;
    }

    File f = LittleFS.open(path);
    if (!f)
    {
        return false;
    }

    bool result = !f.isDirectory();
    f.close();
    return result;
}

bool LittleFSService::checkPathsExist(const char *paths[], const int count)
{
    for (int i = 0; i < count; ++i)
    {
        if (exists(paths[i]))
        {
            Serial.printf("OK: Path exists: %s\n", paths[i]);
        }
        else
        {
            Serial.printf("Error: Path does not exist: %s\n", paths[i]);
            return false;
        }
    }
    return true;
}

bool LittleFSService::checkDirsExist(const char *dirs[], const int count)
{
    for (int i = 0; i < count; ++i)
    {
        if (isDir(dirs[i]))
        {
            Serial.printf("OK: Directory exists: %s\n", dirs[i]);
        }
        else
        {
            Serial.printf("Error: Directory does not exist: %s\n", dirs[i]);
            return false;
        }
    }
    return true;
}

bool LittleFSService::checkFilesExist(const char *files[], const int count)
{
    for (int i = 0; i < count; ++i)
    {
        if (isFile(files[i]))
        {
            Serial.printf("OK: File exists: %s\n", files[i]);
        }
        else
        {
            Serial.printf("Error: File does not exist: %s\n", files[i]);
            return false;
        }
    }
    return true;
}

bool LittleFSService::verifyFilesystem(
    const char *required_paths[], const int paths_count,
    const char *required_dirs[], const int dirs_count,
    const char *required_files[], const int files_count)
{
    Serial.println("Verifying filesystem...");

    Serial.println("Verifying required paths...");
    if (checkPathsExist(required_paths, paths_count))
    {
        Serial.println("All required paths exist.");
    }
    else
    {
        Serial.println("Error: Not all required paths exist.");
        return false;
    }

    Serial.println("Verifying required directories...");
    if (checkDirsExist(required_dirs, dirs_count))
    {
        Serial.println("All required directories exist.");
    }
    else
    {
        Serial.println("Error: Not all required directories exist.");
        return false;
    }

    Serial.println("Verifying required files...");
    if (checkFilesExist(required_files, files_count))
    {
        Serial.println("All required files exist.");
    }
    else
    {
        Serial.println("Error: Not all required files exist.");
        return false;
    }

    Serial.println("Filesystem verification passed.");
    return true;
}

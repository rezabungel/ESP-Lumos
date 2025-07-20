#pragma once
#ifndef _LITTLEFS_SERVICE_H_
#define _LITTLEFS_SERVICE_H_

#include <LittleFS.h>

class LittleFSService
{
public:
    bool begin();
    void ls(const char *path = "/");
    bool exists(const char *path);
    bool isDir(const char *path);
    bool isFile(const char *path);
    bool checkPathsExist(const char *paths[], const int count);
    bool checkDirsExist(const char *dirs[], const int count);
    bool checkFilesExist(const char *files[], const int count);
    bool verifyFilesystem(
        const char *required_paths[], const int paths_count,
        const char *required_dirs[], const int dirs_count,
        const char *required_files[], const int files_count);
};

#endif // _LITTLEFS_SERVICE_H_

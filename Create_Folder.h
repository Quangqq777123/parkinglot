#pragma once
#include <iostream>
#include <fstream>
#ifdef _WIN32
#include <Windows.h>  // Để sử dụng các hàm của Windows
#else
#include <sys/stat.h> // Để sử dụng hàm stat trên UNIX-like systems
#endif
bool directoryExists(const std::string& path) {
#ifdef _WIN32
    // Hệ điều hành Windows
    DWORD attributes = GetFileAttributesA(path.c_str());
    return (attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY));
#else
    // Hệ điều hành UNIX-like (bao gồm Linux, macOS)
    struct stat info;
    return (stat(path.c_str(), &info) == 0 && S_ISDIR(info.st_mode));
#endif
}
bool createDirectory(const std::string& path) {
    // Kiểm tra xem thư mục đã tồn tại hay chưa
    if (directoryExists(path)) {
        return false;
    }
#ifdef _WIN32
    // Hệ điều hành Windows
    if (CreateDirectoryA(path.c_str(), nullptr)) {
        return true;
    }
    else {
        return false;
    }
#else
    // Hệ điều hành UNIX-like (bao gồm Linux, macOS)
    if (mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0) {
        return true;
    }
    else {
        return false;
    }
#endif
}


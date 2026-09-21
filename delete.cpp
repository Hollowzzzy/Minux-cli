#include "delete.h"
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

bool delete_file(const std::string& filename) {
    return unlink(filename.c_str()) == 0;
}

bool delete_folder(const std::string& foldername, const bool recursive) {
    if (!recursive) {
        return rmdir(foldername.c_str()) == 0;
    }

    DIR* dir = opendir(foldername.c_str());
    if (!dir) return false;

    struct dirent* entry;
    bool success = true;

    while ((entry = readdir(dir)) != nullptr) {
        std::string name = entry->d_name;
        if (name == "." || name == "..") continue;

        std::string full_path = foldername + "/" + name;

        struct stat st;
        stat(full_path.c_str(), &st);

        if (S_ISDIR(st.st_mode)) {
            if (!delete_folder(full_path, true)) {
                success = false;
            }
        } else {
            if (unlink(full_path.c_str()) != 0) {
                success = false;
            }
        }
    }

    closedir(dir);

    if (!success) return false;
    return rmdir(foldername.c_str()) == 0;
}

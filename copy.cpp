#include "copy.h"
#include "delete.h"
#include "open.h"
#include "create.h"
#include <cstdio>
#include <dirent.h>
#include <sys/stat.h>

bool copy_file(const std::string& oldfilename, const std::string& newfilename, const bool destructive) {
    std::string content;
    if (!read_file(oldfilename, content)) {
        printf("Error: could not open file '%s'\n", oldfilename.c_str());
        return false;
    }

    if (!create_file(newfilename, content)) {
        return false;   // copy failed — do NOT touch the original
    }

    if (destructive) {
        return delete_file(oldfilename);
    }

    return true;
}

bool copy_folder(const std::string& oldfoldername, const std::string& newfoldername, const bool recursive, const bool destructive) {
    if (!recursive) {
        return create_folder(newfoldername);   // just make the (empty) destination dir
    }

    if (!create_folder(newfoldername)) {
        return false;
    }

    DIR* dir = opendir(oldfoldername.c_str());
    if (!dir) return false;

    struct dirent* entry;
    bool success = true;

    while ((entry = readdir(dir)) != nullptr) {
        std::string name = entry->d_name;
        if (name == "." || name == "..") continue;

        std::string src_path = oldfoldername + "/" + name;
        std::string dst_path = newfoldername + "/" + name;

        struct stat st;
        stat(src_path.c_str(), &st);

        if (S_ISDIR(st.st_mode)) {
            if (!copy_folder(src_path, dst_path, true, destructive)) {
                success = false;
            }
        } else {
            if (!copy_file(src_path, dst_path, destructive)) {
                success = false;
            }
        }
    }

    closedir(dir);

    if (destructive && success) {
        return delete_folder(oldfoldername, true);
    }

    return success;
}

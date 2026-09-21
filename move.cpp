#include <cstdio>
#include <cerrno>
#include "move.h"
#include "copy.h"

bool move_file(const std::string& oldpath, const std::string& newpath) {
    if (rename(oldpath.c_str(), newpath.c_str()) == 0) {
        return true;
    }

    if (errno == EXDEV) {
        return copy_file(oldpath, newpath, true);
    }

    return false;   // some other real error (permissions, etc.)
}

bool move_folder(const std::string& oldpath, const std::string& newpath) {
    if (rename(oldpath.c_str(), newpath.c_str()) == 0) {
        return true;
    }

    if (errno == EXDEV) {
        return copy_folder(oldpath, newpath, true, true);  // always recursive AND destructive for a move
    }

    return false;
}

#ifndef MOVE_H
#define MOVE_H

#include <string>

bool move_file(const std::string& oldpath, const std::string& newpath);
bool move_folder(const std::string& oldpath, const std::string& newpath);

#endif

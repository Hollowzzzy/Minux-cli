#ifndef DELETE_H
#define DELETE_H

#include <string>

bool delete_file(const std::string& filename);
bool delete_folder(const std::string& foldername, const bool recursive = false);

#endif

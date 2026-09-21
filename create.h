#ifndef CREATE_H
#define CREATE_H

#include <string>

bool create_file(const std::string& filename, const std::string& content = "");
bool create_folder(const std::string& foldername);

#endif

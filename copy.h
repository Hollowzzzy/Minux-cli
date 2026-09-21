#ifndef COPY_H
#define COPY_H

#include <string>

bool copy_file(const std::string& oldfilename, const std::string& newfilename, bool destructive = false);
bool copy_folder(const std::string& oldfoldername, const std::string& newfoldername, bool recursive = false, bool destructive = false);

#endif

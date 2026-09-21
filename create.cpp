#include "create.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

bool create_file(const std::string& filename, const std::string& content) {
    int fd = open(filename.c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        return false;
    }

    write(fd, content.c_str(), content.size());
    close(fd);
    return true;
}

bool create_folder(const std::string& foldername) {
    return mkdir(foldername.c_str(), 0755) == 0;
}

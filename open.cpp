#include "open.h"
#include <fcntl.h>
#include <unistd.h>

bool read_file(const std::string& filename, std::string& content) {
    int fd = open(filename.c_str(), O_RDONLY);
    if (fd == -1) {
        return false;
    }
    char buffer[4096];
    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        content.append(buffer, bytes_read);
    }

    close(fd);
    return true;
}

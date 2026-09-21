#include "open.h"
#include "delete.h"
#include "create.h"
#include "copy.h"
#include "move.h"
#include <cstdio>
#include <string>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <command> <argument>\n", argv[0]);
        return 1;
    }

    std::string command = argv[1];

    if (command == "open") {
        if (argc < 3) {
            printf("Usage: %s open <filename>\n", argv[0]);
            return 1;
        }
        std::string content;
        if (read_file(argv[2], content)) {
            printf("%s\n", content.c_str());
            return 0;
        } else {
            printf("Error: could not open file '%s'\n", argv[2]);
            return 1;
        }

    } else if (command == "delete") {
        if (argc < 3) {
            printf("Usage: %s delete <filename>\n", argv[0]);
            return 1;
        }
        if (delete_file(argv[2])) {
            printf("The file has been deleted successfully!\n");
        } else {
            printf("Error: could not delete file '%s'\n", argv[2]);
        }

    } else if (command == "rmdir") {
        if (argc < 3) {
            printf("Usage: %s rmdir <foldername> [recursive]\n", argv[0]);
            return 1;
        }
        bool recursive = (argc >= 4 && std::string(argv[3]) == "recursive");
        if (delete_folder(argv[2], recursive)) {
            printf("The folder has been deleted successfully!\n");
        } else {
            printf("Error: could not delete folder '%s', this may be because the folder is not empty or does not exist.\n", argv[2]);
        }

    } else if (command == "crfi") {
        if (argc < 3) {
            printf("Usage: %s crfi <filename> [content]\n", argv[0]);
            return 1;
        }
        std::string content = (argc >= 4) ? argv[3] : "";
        if (create_file(argv[2], content)) {
            printf("The file has been created successfully!\n");
        } else {
            printf("Error: could not create file.\n");
        }

    } else if (command == "crfo") {
        if (argc < 3) {
            printf("Usage: %s crfo <foldername>\n", argv[0]);
            return 1;
        }
        if (create_folder(argv[2])) {
            printf("The folder has been created successfully!\n");
        } else {
            printf("Error: could not create folder.\n");
        }

    } else if (command == "copy") {
        if (argc < 4) {
            printf("Usage: %s copy <source> <destination> [recursive] [destructive]\n", argv[0]);
            return 1;
        }

        struct stat st;
        if (stat(argv[2], &st) != 0) {
            printf("Error: source '%s' does not exist.\n", argv[2]);
            return 1;
        }

        bool recursive = false;
        bool destructive = false;
        for (int i = 4; i < argc; i++) {
            std::string flag = argv[i];
            if (flag == "recursive") recursive = true;
            if (flag == "destructive") destructive = true;
        }

        if (S_ISDIR(st.st_mode)) {
            if (copy_folder(argv[2], argv[3], recursive, destructive)) {
                printf("The folder has been copied successfully!\n");
            } else {
                printf("Error: could not copy folder.\n");
            }
        } else {
            if (copy_file(argv[2], argv[3], destructive)) {
                printf("The file has been copied successfully!\n");
            } else {
                printf("Error: could not copy file.\n");
            }
        }
    } else if (command == "mv") {
        if (argc < 4) {
            printf("Usage: %s mv <oldpath> <newpath>\n", argv[0]);
            return 1;
        }

        struct stat st;
        if (stat(argv[2], &st) != 0) {
            printf("Error: source '%s' does not exist.\n", argv[2]);
            return 1;
        }

        if (S_ISDIR(st.st_mode)) {
            if (move_folder(argv[2], argv[3])) {
                printf("The folder has been moved successfully!\n");
            } else {
                printf("Error: could not move folder.\n");
            }
        } else {
            if (move_file(argv[2], argv[3])) {
                printf("The file has been moved successfully!\n");
            } else {
                printf("Error: could not move file.\n");
            }
        }

    } else {
        printf("Unknown command: %s\n", command.c_str());
        return 1;
    }

    return 0;
}

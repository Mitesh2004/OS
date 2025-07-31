#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int openf(const char *);

int main() {
    DIR *dir;
    struct dirent *entry;
    int fd, fd_out;
    char ch;

    // Open output file
    fd_out = openf("op.txt");

    // Open the ./test directory
    dir = opendir("./test");
    if (dir == NULL) {
        perror("opendir error");
        return 1;
    }

    // Loop through directory entries
    while ((entry = readdir(dir)) != NULL) {
        int len = strlen(entry->d_name);

        // Check if filename ends with ".txt"
        if (len >= 4 && strcmp(&entry->d_name[len - 4], ".txt") == 0) {
            // Build full path for the file in ./test directory
            char filepath[256];
            snprintf(filepath, sizeof(filepath), "./test/%s", entry->d_name);

            // Open the input file
            fd = openf(filepath);
            if (fd < 0) continue;

            // Copy contents to new.txt
            while (read(fd, &ch, 1) > 0)
                write(fd_out, &ch, 1);

            close(fd);
        }
    }

    closedir(dir);
    close(fd_out);
    printf("All .txt files merged into new.txt successfully.\n");
    return 0;
}

// Function to open file with error checking
int openf(const char *s) {
    int fd = open(s, O_RDWR | O_CREAT, 0666);
    if (fd < 0)
        perror("open error");
    else
        printf("File opened successfully: %s (fd = %d)\n", s, fd);
    return fd;
}


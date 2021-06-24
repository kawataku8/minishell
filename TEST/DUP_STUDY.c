#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
        int file_fd;

        if (argc != 2) {
                fprintf(stderr, "Usage: %s file_name\n", argv[0]);
                exit(1);
        }

        file_fd = open(argv[1], O_RDONLY);
        if (file_fd < 0) {
                perror("open");
                exit(1);
        }

        // close(0);
        if (dup2(file_fd, 0) < 0) {
                perror("dup2");
                close(file_fd);
                exit(1);
        }
        close(file_fd);

        execlp("wc", "wc", NULL);

        return 1;
}
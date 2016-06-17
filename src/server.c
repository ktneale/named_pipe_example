#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int fd = 0, len = 0, ret = 0;

    struct stat fileStat;

    if(stat("./tmp_file",&fileStat) != 0) {
        // Create a named pipe.
        system("mkfifo ./tmp_file");
    }

    char msg[] = "Hello client!\n";

    fd = open("tmp_file", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);

    printf("fd num: %d\n", fd);

    if (fd < 0) {
        printf("Error! opening file\n");
        return -1;
    }

    while (1) {

        printf("Writing data...\n");
        ret = write(fd, msg, strlen(msg));
        printf("Bytes written: %d\n",ret);

        sleep (10);
    }

    close(fd);

    return 0;
}

//EOF

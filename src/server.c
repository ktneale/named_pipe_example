#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <error.h>
#include <signal.h>

int main()
{
    int fd = 0, buff_len = 0, count = 0, bytes_written = 0;

    struct stat fileStat;

    if(stat("./tmp_file",&fileStat) != 0) {
        // Create a named pipe.
        system("mkfifo ./tmp_file");
    }

    char msg[] = "Hello client!\n";

    char * buff = NULL;

    // Create a message buffer
    buff_len = strlen(msg) + 256;  // Buffer size should be sufficient for test/demo purposes.


    //Set up the writing side of the pipe.
    fd = open("tmp_file", O_WRONLY);

    printf("fd num: %d\n", fd);

    if (fd < 0) {
        printf("Error! opening file\n");
        return -1;
    }

    // Ignore signals raised on error. Instead handle them directly.
    signal(SIGPIPE, SIG_IGN);

    while (1) {

        buff = malloc(sizeof(char) * buff_len);

        if (!buff)
            return -1;

        memset(buff, 0, buff_len);
        snprintf(buff, buff_len, "%s:%d", msg, count);

        printf("Writing data...\n");

        while (bytes_written != strlen(buff)) {

            bytes_written = write(fd, buff, strlen(buff));

                if (bytes_written < 0) {
                    perror("write()");

                    // You could exit here or close and reopen as required.
                    printf("EPIPE! Read side of pipe closed?\n");
                    sleep(5);  //Just to slow down the debug in this case.
                } else {
                    printf("Num of bytes written: %d\n",bytes_written);
                }

            sleep(10);
        }

        bytes_written = 0;
        free(buff);

        sleep (10);
        count++;
    }

    close(fd);

    return 0;
}

//EOF

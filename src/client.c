#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

int main()
{
    int fd = 0, len = 0, ret = 0;
    char c = 0;

    fd_set fdset;
    struct timeval timeout;

    fd = open("tmp_file", O_RDONLY);

    printf("fd num: %d\n", fd);

    if (fd < 0) {
        printf("Error! opening file\n");
        return -1;
    }

    while (1) {

        c = 0;

        FD_ZERO(&fdset);
        FD_SET(fd, &fdset);

        // Setup a 1 s timeout, it's not that important.
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        ret = select(fd+1, &fdset, NULL, NULL, &timeout);

        //printf("select() returned: %d\n", ret);

        if (!ret || !FD_ISSET(fd, &fdset)) {
            continue;
        }

        ret = read(fd,&c,1);

        if (ret) {
            printf("byte: %c, %x\n",c,c);
        } else if (ret == 0){
            printf("EOF! Write side of pipe closed?\n");
            sleep(3);  // Just to slow down the debug
        } else {
            perror("read");
        }

    }

    close(fd);

    return 0;
}

// EOF

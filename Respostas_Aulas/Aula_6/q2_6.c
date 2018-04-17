#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char **argv){
    int i;

    for(i=1;i<=argc;i++){

    system(argv[i]);

    }

    return 0;
}

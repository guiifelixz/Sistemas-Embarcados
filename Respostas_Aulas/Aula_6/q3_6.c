#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char **argv){
    int i;
    pid_t argumento;

    argumento = fork();

    if (argumento==0) {
      printf("PID filho %d\n", (int) getpid() );
                      }
    else{
    for(i=1;i<=argc;i++){

    execvp(argc, argv[i]);
        }
                      }
    return 0;
}

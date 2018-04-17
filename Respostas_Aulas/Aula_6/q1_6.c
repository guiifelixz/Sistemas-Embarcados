#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main (int argc, char **argv){

  pid_t pid_1;
  pid_t pid_2;
  pid_t pid_3;

  pid_1 = fork();

  if (pid_1==0) {
    printf("O PID do processo filho é: %d\n", (int) getpid() );
  }

  else {
        pid_2 = fork();
        if (pid_2 == 0) {
          printf("O PID do processo filho 2 é : %d\n", (int) getpid());
    }
        else{
          pid_3 = fork();
            if (pid_3 == 0) {
              printf("O PID do processo filho 3 é : %d\n", (int) getpid() );
            }
            else {
              printf("O pid do proceso pai é : %d\n",(int) getpid() );
            }
            }
    }
    return 0;
  }

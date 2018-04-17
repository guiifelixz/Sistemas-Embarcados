#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int v_global = 0;
void Incrementa_Variavel_Global(pid_t id_atual)
{
	v_global++;
	printf("ID do processo que executou esta funcao = %d\n", id_atual);
	printf("v_global = %d\n", v_global);
}

int main(int argc, char **argv){
  pid_t pid_1;
  pid_t pid_2;
  pid_t pid_3;

    pid_1 = fork();
      if (pid_1 == 0) {
        Incrementa_Variavel_Global(getpid());
      }
      else{
        pid_2 = fork();
        if (pid_2 == 0) {
          Incrementa_Variavel_Global(getpid());
        }
        else{
          pid_3 = fork();
          if (pid_3 == 0) {
            Incrementa_Variavel_Global(getpid());
          }
          else{
          printf("PPID %d\n", (int) getpid());
        }
      }
      }

    return 0;
}

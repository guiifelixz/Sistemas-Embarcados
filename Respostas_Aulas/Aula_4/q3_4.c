#include<stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
  FILE *fp;
  char *nome, *idade, *x;

  nome = argv[1];
  idade = argv[2];

  sprintf(x, "%s.txt", nome);

    fp = fopen (x, "w");
    if (!fp) {
       printf ("ERRO.\n");
       return 0;
    }
    fprintf( fp, "Nome: %s\n",nome );
    fprintf( fp, "Idade: %s\n",idade );

fclose(fp);
return 0;
}

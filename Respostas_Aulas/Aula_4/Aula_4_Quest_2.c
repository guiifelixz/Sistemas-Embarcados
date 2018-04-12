#include<stdio.h>

int main(){

FILE *fp;
int idade;
char n1[30];
char nome[30];

printf("Digite seu nome:");
scanf("%s", nome);
printf("Digite sua idade:");
scanf("%d", &idade);

 sprintf(n1, "%s.txt", nome);

    fp = fopen (n1, "w");
    if (fp == NULL) {
       printf ("ERRO.\n");
       return 0;
    }

fprintf(fp,"Nome: %s \nIdade: %d anos\n", nome, idade);

fclose(fp);
return 0;
}
	

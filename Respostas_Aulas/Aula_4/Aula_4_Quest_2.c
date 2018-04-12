#include<stdio.h>

int main(){

FILE *fp;
int idade;
char nomea[15];
char nome[15];

printf("Digite seu nome:");
scanf("%s", nome);
printf("Digite sua idade:");
scanf("%d", &idade);

 sprintf(nomea, "%s.txt", nome);

    fp = fopen (nomea, "w");
    if (fp == NULL) {
       printf ("ERRO.\n");
       return 0;
    }

fprintf(fp,"Nome: %s \nIdade: %d anos\n", nome, idade);

fclose(fp);
return 0;
}
	

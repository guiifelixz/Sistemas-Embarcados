#include <stdio.h>
#include <stdlib.h>

	int main(int argc, char *argv){
		
		FILE *fp;
		int idade;
		char nome[100];
		fp = fopen("Olá_usuário1.txt","w");
		
		if(!fp){
			printf("Erro ao abrir o arquivo\n");
			exit(0);
				}
				
			scanf("Digite o seu nome : %s", &nome);	
			scanf("Digite sua idade : %d", &idade);	
			fputs("Nome : %s, Idade : %d", nome, idade, fp);
			//ou fputs(fp,"Nome : %s, Idade : %d", nome, idade);
			
			
			fprintf(fp,"Nome: %s\n",nome);
			fprintf(fp,"Idade: %d\n",idade);

			fclose(fp);
		return 0;
		
		
	}
	
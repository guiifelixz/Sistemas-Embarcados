#include <stdio.h>
#include <stdlib.h>

	int main(int argc, char *argv){
		
		FILE *fp;
		int x;
		fp = fopen("Olá_mundo.txt","w");
		
		if(!fp){
			printf("Erro ao abrir o arquivo\n");
			exit(0);
				}
				
				
			fputs("Ola Mundo!\n", fp);		
			fclose(fp);
		return 0;
		
		
	}
	
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
	wchar_t nome[100];
	printf("Digite seu Nome \n");
	scanf("%ls", nome);
	printf("   Olá %ls \n",nome);
	return 0;
}


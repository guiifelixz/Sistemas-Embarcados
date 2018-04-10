#include <stdio.h>
#include<stdlib.h>

int main(int argc , char **argv){
	int i =1;

        printf("Numero de argumentos : %d \n", argc);
     

        while(i!=argc){ 
                printf("%s\n", argv[i]);
                i++;
			}
	printf("\n");
return 0;
}





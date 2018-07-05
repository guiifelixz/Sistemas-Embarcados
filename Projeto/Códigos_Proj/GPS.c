#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>
//#include <wiringPi.h>
#include <gps.h>
#include <math.h>
#include <pthread.h>
#include <sys/poll.h>


// Compilar: gcc -o GPS GPS.c -lgps -lm
// Executar: ./GPS

#define N 1000
#define Nlim (N/2)
FILE *fp;
struct pollfd pfd;
int inicioArquivo = 0;

void poll_btn(struct pollfd *pfd)
{
	char buffer, vals[N] = {0};
	int pos = 0, test=1, i, s;
	lseek(pfd->fd, 0, SEEK_SET);
	read(pfd->fd, &buffer, 1);
	for(i=0;i<N;i++) vals[i] = buffer-'0';
	poll(pfd, 1, -1);
	while(test)
	{
		lseek(pfd->fd, 0, SEEK_SET);
		read(pfd->fd, vals+pos, 1);
		vals[pos] -= '0';
		pos = (pos+1)%N;
		for(s=i=0; i<N; i++)
			s += vals[i];
		if(buffer=='0')
			test = s<Nlim;
		else
			test = s>Nlim;
	}
}


void fecharPrograma( ){
	
	printf("Fechando programa...\n");
	fclose(fp);
	system("echo 24 > /sys/class/gpio/unexport");
	close(pfd.fd);
	sleep(1);
	exit(0);
}

void* gps(void *arg){

	gps_init( );
	loc_t data;
	

	while(1){

		//fp = fopen("/home/pi/Desktop/data.csv", "a+");
		fp = fopen("/var/www/html/data.csv", "a+");

		if(inicioArquivo ==0){
		fprintf( fp,"\"lat\",\"lon\",\"alt\",\"vel\"\n");
		inicioArquivo=1;
		puts("Iniciando arquivo");
		}

		gps_location(&data);
		fprintf(fp, "%lf,%lf,%f,%f\n", data.latitude, data.longitude, data.altitude, data.speed);
		fclose(fp);
		usleep(1000000);		

	}	
	return NULL;
}



void* rst(void *arg){

	int btn_press;
	system("echo 24     > /sys/class/gpio/export");
	system("echo falling > /sys/class/gpio/gpio24/edge");
	system("echo in    > /sys/class/gpio/gpio24/direction");
	pfd.fd = open("/sys/class/gpio/gpio24/value", O_RDONLY);
	if(pfd.fd < 0)
	{
		puts("Erro abrindo /sys/class/gpio/gpio24/value");
		puts("Execute este programa como root.");
		return 0;
	}
	pfd.events = POLLPRI | POLLERR;
	pfd.revents = 0;

	while(1){
	poll_btn(&pfd);
	remove("data.csv");
	puts("Apagando arquivo");
	inicioArquivo = 0;
	}

	return NULL;
	
}

int main(int argc, char** argv){
	
	pthread_t t0;
	pthread_t t1;
	
	signal(SIGINT, fecharPrograma);

	puts("Iniciando gps");
	pthread_create(&t0,NULL,&gps,NULL);
	puts("Botão de reset pronto");
	pthread_create(&t1,NULL,&rst,NULL);
	while(1){}

return 0;
}

#include <wiringPiI2C.h>
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

 
//executar : gcc -o mpu6050a mpu6050a.c -lwiringPi -lm -pthread

int fd;
int acclX, acclY, acclZ;
int gyroX, gyroY, gyroZ;
double acclX_scaled, acclY_scaled, acclZ_scaled;
double gyroX_scaled, gyroY_scaled, gyroZ_scaled;
struct pollfd pfd;
FILE *fp;
#define N 1000
#define Nlim (N*3)/4
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



int read_word_2c(int addr)
{
int val;
val = wiringPiI2CReadReg8(fd, addr);
val = val << 8;
val += wiringPiI2CReadReg8(fd, addr+1);
if (val >= 0x8000)
val = -(65536 - val);
 
return val;
}
 
double dist(double a, double b)
{
return sqrt((a*a) + (b*b));
}
 
double get_y_rotation(double x, double y, double z)
{
double radians;
radians = atan2(x, dist(y, z));
return -(radians * (180.0 / M_PI));
}
 
double get_x_rotation(double x, double y, double z)
{
double radians;
radians = atan2(y, dist(x, z));
return (radians * (180.0 / M_PI));
}


void* mpu(void *arg){
	

	fd = wiringPiI2CSetup (0x68);
	wiringPiI2CWriteReg8 (fd,0x6B,0x00);//disable sleep mode
	printf("set 0x6B=%X\n",wiringPiI2CReadReg8 (fd,0x6B));
 
	while(1) {

	fp = fopen("/var/www/html/mpu.csv", "a+");
	
	if(inicioArquivo == 0){
	fprintf( fp,"\"Giroscópio\",\"Acelerômetro angulo\"\n");
	inicioArquivo = 1;
	puts("Iniciando arquivo");
	}
   
	acclX = read_word_2c(0x3B);
	acclY = read_word_2c(0x3D);
	acclZ = read_word_2c(0x3F);
 
	acclX_scaled = acclX / 16384.0;
	acclY_scaled = acclY / 16384.0;
	acclZ_scaled = acclZ / 16384.0;


	fprintf(fp, "X=%f,X=%f\n", acclX_scaled,get_x_rotation(acclX_scaled, acclY_scaled, acclZ_scaled));
	fprintf(fp, "Y=%f,Y=%f\n", acclY_scaled,get_y_rotation(acclX_scaled, acclY_scaled, acclZ_scaled));
	fprintf(fp, "Z=%f, " "\n", acclZ_scaled);
	usleep(1000000);	
	fclose(fp);
	}

	return NULL;
}

void* rst(void *arg){

	int btn_press;
	system("echo 23     > /sys/class/gpio/export");
	system("echo falling > /sys/class/gpio/gpio23/edge");
	system("echo in    > /sys/class/gpio/gpio23/direction");
	pfd.fd = open("/sys/class/gpio/gpio23/value", O_RDONLY);
	if(pfd.fd < 0)
	{
		puts("Erro abrindo /sys/class/gpio/gpio23/value");
		puts("Execute este programa como root.");
		return 0;
	}
	pfd.events = POLLPRI | POLLERR;
	pfd.revents = 0;

	while(1){
	poll_btn(&pfd);
	remove("mpu.csv");
	puts("Apagando arquivo");
	inicioArquivo = 0;
	}

	return NULL;
	
}


void fecharPrograma( ){
	
	printf("Fechando programa...\n");
	fclose(fp);
	system("echo 23 > /sys/class/gpio/unexport");
	close(pfd.fd);
	sleep(1);
	exit(0);
}
 
int main(int argc, char** argv)
{

	pthread_t t2;
	pthread_t t3;
	
	signal(SIGINT, fecharPrograma);

	puts("Iniciando mpu");
	pthread_create(&t2,NULL,&mpu,NULL);
	puts("Botão de reset pronto");
	pthread_create(&t3,NULL,&rst,NULL);
	while(1){}

return 0;
}

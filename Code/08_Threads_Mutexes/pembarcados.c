#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


double max(double max_val){
	int i;

	max_val = v[0];
	for(i=0;i<N;i++){
		if(v[i] > max_val){
			max_val = v[i];
		}
	}
	return max_val;
}

double media(int *a, int N, double media);{
	int x ;
	
	for(x=0; x<N; i++){
		soma += a[N];
	}
		media = soma/N;
	
	return media;
}
	
	
int main ()
{
	pthread_t thread_id1;
	pthread_t thread_id2;
	pthread_t thread_id3;
	pthread_t thread_id4;
	
	pthread_create(&thread_id1,NULL,&media,media);
	pthread_create(&thread_id2,NULL,&max,max_val);
	
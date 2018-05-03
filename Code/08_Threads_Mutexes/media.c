int n,i;
int *a;
int soma1 = 0;
int soma2 = 0;
int soma3 = 0;
int soma4 = 0;

void *s1 (){

	for(i=0; i<n/4; i++){
		soma1 += a[i];
	}
}
void *s2 (){

	for(i=n/4; i<n/2; i++){
		soma2 += a[i];
	}
}
void *s3 (){

	for(i=n/2; i<3n/4; i++){
		soma3 += a[i];
	}
}
void *s4 (){

	for(i=3n/4; i<n; i++){
		soma4 += a[i];
	}
}

int main(){
int v_max = 0 ;
double media = 0;
	
	for(i=0; i<n; i++){
		if(a[i]>v_max){
			v_max=a[i];
		}
	}
	
	pthread_t x1;
	pthread_t x2;
	pthread_t x3;
	pthread_t x4;
	
	pthread_create(&x1,NULL,&s1,NULL);
	pthread_create(&x2,NULL,&s2,NULL);
	pthread_create(&x3,NULL,&s3,NULL);
	pthread_create(&x4,NULL,&s4,NULL);
	pthread_join (x1,NULL);	
	pthread_join 	(x2,NULL);
	pthread_join (x3,NULL);
	pthread_join (x4,NULL);
	
	media = (soma1+soma2+soma3+soma4-v_max)/n-1;	
	
	printf("A média é %lf",media);
		return 0 ;
	
}

#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int *prime_table(int prime_num){
	int i=2,j,p=0,primeflag;
	//int primes[prime_num];
	int *primes=(int*)malloc(prime_num*sizeof(int));
	while(p<prime_num)
	{
		primeflag=1;
		for(j=2;j<i;j++){
			if((i%j)==0){
				primeflag=0;
				break;
			}
		}
		if(primeflag){
			primes[p]=i;
			p+=1;
		}
		i+=1;
	}
	return primes;
}

double *sine_table(int sine_num){
	int i,j;
	double a,pi=3.14159;
	//double sines[sine_num];
	double *sines=(double*)malloc(sine_num * sizeof(double));
	for(i=0;i<sine_num;i++){
		sines[i]=0.0;
		for(j=0;j<=i;j++){
			a=(double)(j) * pi/(double)(sine_num-1);
			sines[i]=sines[i]+ sin(a);
		}
	}
	return sines;
}

int main(){
	int size;
	scanf("%d",&size);
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			int *a=(int*)malloc(size*sizeof(int));
			a=prime_table(size);
			for(int y=0;y<size;y++){
				printf("%d\n",a[y]);
			}
		}
		#pragma omp section
		{
			double *b=(double*)malloc(size*sizeof(double));
			b=sine_table(size);
			for(int z=0;z<size;z++){
				printf("%lf\n",b[z]);
			}
		}
	}
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
void mergesort(int a[],int i,int j);
void merge(int a[],int i1,int j1,int i2,int j2);

int main()
{
    omp_set_nested(1); //Enables nested parallelism.
    int num, i;
    scanf("%d",&num);
    int a[num];
    //a = (int *)malloc(sizeof(int) * num);
    for(i=0;i<num;i++)
        //scanf("%d",&a[i]);
        a[i]=rand()%100;

    printf("\nUnsorted array :\n");
    for(i=0;i<num;i++)
        printf("%d ",a[i]);
    printf("\n");
    
    double t1 = omp_get_wtime(); //Returns a value in seconds of the time elapsed from some point.
    mergesort(a, 0, num-1);
    double t2 = omp_get_wtime();
    printf("Time taken = %lf",t2-t1);
    
    printf("\nSorted array :\n");
    for(i=0;i<num;i++)
        printf("%d ",a[i]);
        
    return 0;
}
 
void mergesort(int a[],int i,int j)
{
    int mid;
        
    if(i<j)
    {
        mid=(i+j)/2;
        
        #pragma omp parallel sections 
        {

            #pragma omp section
            {
                printf("thread id = %d\n",omp_get_thread_num());
                mergesort(a,i,mid);        //left recursion
            }

            #pragma omp section
            {
                printf("thread id = %d\n",omp_get_thread_num());
                mergesort(a,mid+1,j);    //right recursion
            }
        }

        merge(a,i,mid,mid+1,j);    //merging of two sorted sub-arrays
    }
}
 
void merge(int a[],int i1,int j1,int i2,int j2)
{
    int temp[1000];    //array used for merging
    int i,j,k;
    i=i1;    //beginning of the first list
    j=i2;    //beginning of the second list
    k=0;
    
    while(i<=j1 && j<=j2)    //while elements in both lists
    {
        if(a[i]<a[j])
            temp[k++]=a[i++];
        else
            temp[k++]=a[j++];
    }
    
    while(i<=j1)    //copy remaining elements of the first list
        temp[k++]=a[i++];
        
    while(j<=j2)    //copy remaining elements of the second list
        temp[k++]=a[j++];
        
    //Transfer elements from temp[] back to a[]
    for(i=i1,j=0;i<=j2;i++,j++)
        a[i]=temp[j];
}

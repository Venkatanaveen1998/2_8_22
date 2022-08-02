#include <stdio.h>
#include<pthread.h>
#include<unistd.h>
pthread_mutex_t lock;
int j=97;
void *cap_alph()
{
    int i;
   pthread_mutex_lock(&lock);
    for(i=0;i<5;i++)
    {
        sleep(1);
    printf("thread 1 : %c\n",j-32+i);
    }
   pthread_mutex_unlock(&lock);
}
void *low_alph()
{
    int i;
   pthread_mutex_lock(&lock);
    for(i=0;i<5;i++)
    {
      //sleep(1);
    printf("thread 2 : %c\n",j+i);
    }
    pthread_mutex_unlock(&lock);
}
int main()
{
    pthread_t tid[2];
    pthread_mutex_init(&lock,NULL);
    pthread_create(&tid[0],NULL,&cap_alph,NULL);
    pthread_create(&tid[1],NULL,&low_alph,NULL);
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    pthread_mutex_destroy(&lock);
}


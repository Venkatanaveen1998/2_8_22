#include <stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
void *fun1();
void *fun2();
int shared=1;
sem_t s;
int main()
{
  sem_init(&s,0,1); // 1. address of semaphore variable 2. int pshared 0->threads ,non-zero ->process . 3.initial 
  //values 1->is free and 0-> is used.
  //int sem_init(sen_t *sem , int pshared , usage initial value)
  pthread_t t1,t2;
  pthread_create(&t1,NULL,fun1,NULL);
  pthread_create(&t2,NULL,fun2,NULL);
  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  printf("in main shared value : %d \n ",shared);
}
void *fun1()
{
    int x;
    sem_wait(&s);
    x=shared; 
    printf("thread1 reads the value as %d\n",x);
    x++; 
    printf("local updation by thread1 : %d\n",x);
    sleep(1);
    shared=x;
    printf("value of shared variable updated by thread1 is : %d\n",shared);
    sem_post(&s);
}
void *fun2()
{
    int y;
    sem_wait(&s);
    y=shared; 
    printf("thread2 reads the value as %d\n",y);
    y++;
    printf("local updation by thread2 : %d\n",y);
    sleep(1);
    shared=y;
    printf("value of shared variable updated by thread2 is : %d\n",shared);
    sem_post(&s);
}

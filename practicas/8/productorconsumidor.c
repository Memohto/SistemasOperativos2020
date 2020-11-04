#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUF_SIZE 10

sem_t mutexBuffer;
unsigned int buffer[BUF_SIZE];

sem_t semEspacios; // Indicar espacios dispoinbles
sem_t semDatos; // Indicar que hay algo que consumir

void * producer(void *args) {
  int i = 0;
  while(1) {
    sleep(1);
    sem_wait(&semEspacios);
    sem_wait(&mutexBuffer);
    buffer[i] = rand();
    sem_post(&mutexBuffer);
    sem_post(&semDatos);
    i = (i+1)%BUF_SIZE;
  }
  pthread_exit(NULL);
}

void * consumer(void *args) {
  int i = 0;
  while(1) {
    sem_wait(&semDatos);
    sem_wait(&mutexBuffer);
    int dato = buffer[i];
    sem_post(&mutexBuffer);
    sem_post(&semEspacios);
    printf("El valor leído es %d\n", dato);
    sleep(2);
    i = (i+1)%BUF_SIZE;
  }
  pthread_exit(NULL);
}

int main() {
  sem_init(&mutexBuffer, 0, 1);
  sem_init(&semEspacios, 0, BUF_SIZE);
  sem_init(&semDatos, 0, 0);
  pthread_t tproducer;
  pthread_t tconsumer;
  pthread_create(&tproducer, NULL, producer, NULL);
  pthread_create(&tconsumer, NULL, consumer, NULL);

  pthread_exit(NULL);
}
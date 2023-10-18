
#include <stdio.h>    // Standard I/O
#include <stdlib.h>   // Standard library
#include <unistd.h>   // Unix Standard
#include <pthread.h>  // POSIX thread library
#include <string.h>

#include "util_queue.h"

#define NUM_THREADS 50

/*
 * DEFINIR las variables globales necesarias (cola de trabajos, semáforos, etc) 
 */

pthread_mutex_t mutex;
printer_buffer_t buf;

/*
 * IMPLEMENTAR el código de la función de los threads 'Sender' 
 */
void* pthread_sender_job(int id) {
pthread_mutex_lock(&mutex);

printing_job_t job;
job.job_id=id;
strcpy(job.file_path, "C:/file");
printer_buffer_queue(&buf, &job);

pthread_mutex_unlock(&mutex);
}


/*
 * Main
 */
int main(int argc,char** argv) {
/* DEFINIR las variables locales del main necesarias y el CÓDIGO de la inicialización de la cola de trabajos 
   * y de los semáforos utilizados en el programa  
   */
printer_buffer_init(&buf);
pthread_mutex_init(&mutex,NULL);
pthread_t thread[NUM_THREADS];

  /*CÓDIGO para la creación de los threads 'Sender'*/
long int i;
  for (i=0;i<NUM_THREADS;++i) {
    pthread_create(thread+i,NULL,(void* (*)(void*))pthread_sender_job,(void*)(i));
  }
  
/*CÓDIGO de la espera de la finalización de los threads 'Sender'*/
  for (i=0;i<NUM_THREADS;++i) {
    pthread_join(thread[i],NULL);
  }
 /*CÓDIGO para imprimir todos los trabajos de la cola de impresión*/ 
printer_buffer_queue_termination_job(&buf);
printing_job_t job;
printer_buffer_dequeue(&buf, &job);
while(job.job_id!=-1)
{
printf("ID: %d, File Path: %s\n",job.job_id, job.file_path);
printer_buffer_dequeue(&buf, &job);
}
  return 0;
}


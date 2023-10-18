/*
 *  Copyright (c) 2019 by Santiago Marco-Sola  <santiagomsola@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * PROJECT: Operating Systems. Practical examples
 * AUTHOR(S): Santiago Marco-Sola <santiago.marco@uab.cat>
 * DESCRIPTION:
 *   This example shows how to create a mutux exclusion region using
 *   pthread mutexes. This program creates 50 threads, each one prints
 *   and increments a counter (in mutual exclusion), and exits.
 *   Meanwhile, the master thread waits to join all the worker/slave
 *   threads, and finally print the value of the counter.
 */

#include <stdio.h>    // Standard I/O
#include <stdlib.h>   // Standard library
#include <unistd.h>   // Unix Standard
#include <pthread.h>  // POSIX thread library

#define NUM_THREADS 50

pthread_mutex_t mutex;
int number = 0;

void* pthread_function(int id) {
  // Mutual exclusion region
  pthread_mutex_lock(&mutex);
  int number_read = number; // Read number
  printf("[Slave thread %d] Read Number = %d\n",id,number_read); // Print message
  number = number_read + 1; // Increment
  pthread_mutex_unlock(&mutex);
  // Exit
  pthread_exit(NULL);
}
int main(int argc,char** argv) {
  // Init mutex
  pthread_mutex_init(&mutex,NULL);
  // Create slave/worker threads
  long int i;
  pthread_t thread[NUM_THREADS];
  for (i=0;i<NUM_THREADS;++i) {
    pthread_create(thread+i,NULL,(void* (*)(void*))pthread_function,(void*)(i));
  }
  // Wait for the threads
  for (i=0;i<NUM_THREADS;++i) {
    pthread_join(thread[i],NULL);
  }
  // Print value of number
  printf("[Master thread] Number = %d\n",number);
  // Free mutex
  pthread_mutex_destroy(&mutex);
  // Terminate process OK
  return 0;
}



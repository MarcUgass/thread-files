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
 *   This example shows how to create, join, and exit threads
 *   using POSIX threads library.
 */

#include <stdio.h>    // Standard I/O
#include <stdlib.h>   // Standard library
#include <unistd.h>   // Unix Standard
#include <pthread.h>  // POSIX thread library
#include <sys/time.h> // Time
#include <time.h>     // Time
#include <string.h>   // String library

char* timestamp() {
  // Allocate buffer
  char* timestamp_buffer = malloc(100);
  // Get current time
  struct timeval tv;
  gettimeofday(&tv, NULL);
  // Convert elapsed time since the epoch in microseconds to human readable date
  strftime(timestamp_buffer,100, "%Y:%m:%d %H:%M:%S",localtime(&tv.tv_sec));
  sprintf(timestamp_buffer+strlen(timestamp_buffer),":%ld",tv.tv_usec);
  // Return timestamp
  return timestamp_buffer;
}
void* pthread_function(int id) {
  printf("[%s] Slave thread %d (PID=%d,TID=%ld)\n",timestamp(),id,getpid(),pthread_self());
  pthread_exit(NULL);
}
int main(int argc,char** argv) {
  // Create slave thread
  long int i = 1;
  pthread_t thread;
  pthread_create(&thread,NULL,(void* (*)(void*))pthread_function,(void*)(i));
  // Print message
  printf("[%s] Master thread (PID=%d,TID=%ld)\n",timestamp(),getpid(),pthread_self());
  // Wait for threads
  pthread_join(thread,NULL);
  // Terminate process OK
  return 0;
}



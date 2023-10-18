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
 *   This example shows worker 50 threads queuing printing jobs to a printer
 *   circular buffer meanwhile another worker dequeues jobs and prints its path.
 *   The master threads creates all threads and waits for all of them to finish.
 *   Race conditions are handled using mutex to regulate critical regions
 */
#ifndef UTIL_QUEUE_H
#define UTIL_QUEUE_H



#define BUFFER_SIZE 100
/*
 * Data types
 */
typedef struct {
  int job_id;
  char file_path[100];
} printing_job_t;

typedef struct {
  int next_job_queue;   // Next position in the buffer to write
  int next_job_dequeue; // Next position in the buffer to print
  int total_jobs;       // Total number of jobs in the queue
  printing_job_t jobs[BUFFER_SIZE]; // Circular buffer of jobs
} printer_buffer_t;


/*
 * Printer circular buffer
 */
// Creates and configures a printing job
printing_job_t* printing_job_create(char* file_path); 
// Initializes the printer jobs buffer
void printer_buffer_init(printer_buffer_t* printer_buffer); 
// Returns 1 if the buffer is full, 0 otherwise
int printer_buffer_full(printer_buffer_t* printer_buffer); 
// Returns 1 if the buffer is empty, 0 otherwise
int printer_buffer_empty(printer_buffer_t* printer_buffer); 
// Queues printing job in the buffer
void printer_buffer_queue(printer_buffer_t* buffer, printing_job_t* job); 
// Queues special job in the buffer to signal termination of printer
void printer_buffer_queue_termination_job(printer_buffer_t* buffer); 
// Dequeues next printing job from the buffer
void printer_buffer_dequeue(printer_buffer_t* buffer, printing_job_t* job); 

#endif

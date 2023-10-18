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

//#include <stdio.h>    // Standard I/O
#include <stdlib.h>   // Standard library
#include <string.h>  // String library
#include "util_queue.h"


/*
 * Printer circular buffer
 */
// Creates and configures a printing job
printing_job_t* printing_job_create(char* file_path) {
  printing_job_t* job = malloc(sizeof(printing_job_t));
  strcpy(job->file_path,file_path);
  return job;
}
// Initializes the printer jobs buffer
void printer_buffer_init(printer_buffer_t* printer_buffer) {
  printer_buffer->next_job_queue = 0;
  printer_buffer->next_job_dequeue = 0;
  printer_buffer->total_jobs = 0;
}
// Returns 1 if the buffer is full, 0 otherwise
int printer_buffer_full(printer_buffer_t* printer_buffer) {
  return (printer_buffer->total_jobs == BUFFER_SIZE);
}
// Returns 1 if the buffer is empty, 0 otherwise
int printer_buffer_empty(printer_buffer_t* printer_buffer) {
  return (printer_buffer->total_jobs == 0);
}
// Queues printing job in the buffer
void printer_buffer_queue(
    printer_buffer_t* buffer,
    printing_job_t* job) {
    // Assign unique job id
    static int job_id = 0;
    buffer->jobs[buffer->next_job_queue].job_id = job_id++;
    // Copy file path to print
    strcpy(buffer->jobs[buffer->next_job_queue].file_path,job->file_path);
  // Increase queue write position
    buffer->next_job_queue = (buffer->next_job_queue+1) % BUFFER_SIZE;
    ++buffer->total_jobs;
}
// Queues special job in the buffer to signal termination of printer
void printer_buffer_queue_termination_job(
    printer_buffer_t* buffer) {
    // Set job to terminate printer
    buffer->jobs[buffer->next_job_queue].job_id = -1;
    // Increase queue write position
    buffer->next_job_queue = (buffer->next_job_queue+1) % BUFFER_SIZE;
    ++buffer->total_jobs;
}
// Dequeues next printing job from the buffer
void printer_buffer_dequeue(
    printer_buffer_t* buffer,
    printing_job_t* job) {
    // Copy job from queue
    *job = buffer->jobs[buffer->next_job_dequeue];
    // Increase queue read position
    buffer->next_job_dequeue = (buffer->next_job_dequeue+1) % BUFFER_SIZE;
    --buffer->total_jobs;
}


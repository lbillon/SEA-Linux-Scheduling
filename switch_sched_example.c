/* Includes */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static void *task_a (void *p_data)
{
   puts ("Hello world A");

   (void) p_data;
   return NULL;
}

static void *task_b (void *p_data)
{
   puts ("Hello world B");

   (void) p_data;
   return NULL;
}

int main() {
    // Define threads
    pthread_t high_prio;
    pthread_t low_prio;
    
    // Threads Attributes
    pthread_attr_t high_prio_thread;
    pthread_attr_t low_prio_thread;

    pthread_create (&ta, NULL, task_a, NULL);
    pthread_create (&tb, NULL, task_b, NULL);

}

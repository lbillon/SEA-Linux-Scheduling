/* Includes */
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>  
#include <stdio.h>
#include <sys/wait.h> 
#include <stdlib.h>
#include <sched.h>

int main() {
    pid_t childpid;   
    int status; 
    
    childpid = fork();

    if (childpid >= 0) {
        if (childpid == 0) {
            printf("CHILD: I am the child process!\n");
            struct sched_param sp;
            printf("CHILD: Here's my PID: %d\n", getpid());
            printf("CHILD: My parent's PID is: %d\n", getppid());
            printf("CHILD: The value of my copy of childpid is: %d\n", childpid);
            
            printf("CHILD : Scheduler before change: %d\n", sched_getscheduler(0));
            sp.sched_priority = sched_get_priority_max(SCHED_FIFO);
            sched_setscheduler(0, SCHED_FIFO, &sp);
            printf("CHILD : Scheduler after change: %d\n", sched_getscheduler(0));
            
            int i;
            for (i = 0; i <= 20; i++) {
                printf("CHILD: Sleeping for 1 second...\n");
                sleep(1);
            }
           
            printf("CHILD: Goodbye!\n");
            
            exit(0); 
        } else {
            printf("PARENT: I am the parent process!\n");
            printf("PARENT: Here's my PID: %d\n", getpid());
            printf("PARENT: The value of my copy of childpid is %d\n", childpid);
            printf("PARENT: I will now wait for my child to exit.\n");
                    wait(&status);
                    printf("PARENT: Child's exit code is: %d\n", WEXITSTATUS(status));
                    printf("PARENT: Goodbye!\n");
                    exit(0); 
        }
    } else {
        perror("fork"); 
                exit(0);
    }
}

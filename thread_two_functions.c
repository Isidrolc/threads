#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


void *function1(void *ptr);
void *function2(void *ptr);
int counter1, counter2;

int main()
{
        pthread_t thread1, thread2;
        char *message1 = "Function 1";
        char *message2 = "Function 2";
        int  iret1, iret2;
	counter1 = 100;
	counter2 = 100;

        /* Create independent threads each of which will execute function */

        iret1 = pthread_create(&thread1, NULL, function1, (void*) message1);
        iret2 = pthread_create(&thread2, NULL, function2, (void*) message2);

        /* Wait till threads are complete before main continues. Unless we */
        /* wait we run the risk of execution an exit which will terminate  */
        /* the process and all threads before the threads have completed   */

        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
        printf("Thread 1 returns: %d\n", iret1);
        printf("Thread 2 returns: %d\n", iret2);
        exit(0);;
}

void *function1(void *ptr)
{
        char *message;
        message = (char*)ptr;
        printf("%s \n", message);
	while(counter1 != 0){
		printf("Counter1 = %d", counter1);
		counter1 = counter1 - 1;
		sleep(1);
	}
}


void *function2(void *ptr)
{
        char *message;
        message = (char*)ptr;
        printf("%s \n", message);
	while(counter2 != 0){
		printf("                        Counter2 =                                    %d\n", counter2);
		counter2 = counter2 - 1;
		sleep(1);
	}
}


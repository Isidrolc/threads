#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <ncurses.h>


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
        WINDOW *my_win;
       	char *message;
	int startx, starty, width, height;
	initscr();
        message = (char*)ptr;
	startx = 1;
	starty = 1;
	height = (LINES / 2) - 2;
        width  = (COLS / 2) - 2;
	my_win = newwin(height, width, starty, startx);
	box(my_win, 0, 0);	
        mvwprintw(my_win, 3,3, "%s", message);
	wrefresh(my_win);
	cbreak();
	curs_set(0);  // hide the cursor
	while(counter1 != 0){
		mvwprintw(my_win,7,7, "Counter1 = %d", counter1);
		wrefresh(my_win);
		counter1 = counter1 - 1;
		sleep(1);
                mvwprintw(my_win, 7,7, "Counter1 = %s", "     ");
                wrefresh(my_win);

	}
	endwin();
}


void *function2(void *ptr)
{
        WINDOW *my_win2;
       	char *message;
	int startx, starty, width, height;
	initscr();
        message = (char*)ptr;
        startx = (COLS / 2) + 2;
        starty = 1; 
	height = (LINES / 2) - 2;
        width  = (COLS / 2) - 2;
        my_win2 = newwin(height, width, starty, startx);
        box(my_win2, 0, 0);
        mvwprintw(my_win2, 3, 3, "%s", message);
        wrefresh(my_win2);
        cbreak();
        curs_set(0);  // hide the cursor
	while(counter2 != 0){
                mvwprintw(my_win2,7,7, "Counter2 = %d", counter2);
                wrefresh(my_win2);
                counter2 = counter2 - 1;
                sleep(1);
                mvwprintw(my_win2, 7,7, "Counter2 = %s", "     ");
                wrefresh(my_win2);
	}
	endwin();
}




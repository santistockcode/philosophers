2. First threads: independent workers (pthread_create + join)
Goal: Understand basic thread creation and termination.

Create a program threads_basics.c where you:
Define a worker(void *arg) function that:
Casts arg to int * (an ID).
Prints: "[timestamp] worker X: start".
Sleeps 500 ms using precise_usleep.
Prints: "[timestamp] worker X: end".
In main, create N = 5 threads with pthread_create, passing each its ID.
pthread_join each thread before exiting main.
Ensure you compile with -pthread.
Relates to philosophers: each philosopher will be a thread with an ID and a loop of actions.
Est.: 30–40 min.
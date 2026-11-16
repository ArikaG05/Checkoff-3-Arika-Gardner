/*
 * 1_priority_basic.c
 *
 * The simplest priority scheduler: NON-PREEMPTIVE, and every process
 * arrives at time 0.
 *
 * Idea: sort the processes by priority, then run them in that order.
 * Lower number = more important (same as Linux and most textbooks).
 *
 * Compile:  gcc -Wall -o basic 1_priority_basic.c
 * Run:      ./basic
 */

#include <stdio.h>
#include <stdlib.h>

/* One "process control block" (PCB): everything the scheduler needs to know */
struct process {
    char name[4];   /* "P1", "P2", ...                 */
    int  burst;     /* how long it needs the CPU       */
    int  priority;  /* lower number = more important   */
    int  start;     /* filled in by the scheduler      */
    int  finish;    /* filled in by the scheduler      */
};

/*
 * Comparison function for qsort.
 * This is the "policy": it decides what counts as more important.
 * Return a negative number if a should come before b.
 */
int compare_priority(const void *a, const void *b) {
    const struct process *pa = a;
    const struct process *pb = b;
    return pa->priority - pb->priority;
}

int main(void) {
    struct process procs[] = {
        /* name  burst  priority */
        { "P1",  10,    3 },
        { "P2",   1,    1 },
        { "P3",   2,    4 },
        { "P4",   5,    2 },
    };
    int n = sizeof(procs) / sizeof(procs[0]);

    /* Step 1: sort so the most important process is first */
    qsort(procs, n, sizeof(struct process), compare_priority);

    /* Step 2: run them one after another (non-preemptive = no interrupting) */
    int clock = 0;
    for (int i = 0; i < n; i++) {
        procs[i].start  = clock;
        clock          += procs[i].burst;   /* it runs until it's done */
        procs[i].finish = clock;
    }

    /* Step 3: print a simple Gantt chart */
    printf("Gantt chart:\n|");
    for (int i = 0; i < n; i++) {
        printf(" %s (%d-%d) |", procs[i].name, procs[i].start, procs[i].finish);
    }
    printf("\n\n");

    /* Step 4: waiting time = time spent sitting in line before starting */
    printf("Process  Priority  Burst  Waiting\n");
    int total_wait = 0;
    for (int i = 0; i < n; i++) {
        int wait = procs[i].start;   /* everyone arrived at 0 */
        total_wait += wait;
        printf("%-7s  %-8d  %-5d  %d\n",
               procs[i].name, procs[i].priority, procs[i].burst, wait);
    }
    printf("\nAverage waiting time = %.2f\n", (double)total_wait / n);

    return 0;
}

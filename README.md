# Checkoff-3-Arika-Gardner
Created by: Arika Gardner
PID: 730646316

# What's in this Repository
I have added a developer container (Linux) to run the sample code, but you can refigure any other container.

There is a basic sample code example that generally shows how priority scheduling works.

There is a sample code of a scenario I made up using generally programs we would use on our computers. This code example will be used in my presentation. (Both code examples were consulted through AI with some editing an my part in the second example)

There is a pdf and powerpoint version of my slides also attached inside of the "Slides" folder.


# What is Priority Scheduling
Priority scheduling is a type Operating System Scheduling that determines which program gets processing time from the CPU. Think of an emergency room, there are some patients in the hospital with non-life threatenng injuries, then there are some who must be attended to immediately. In this scenario, the "priority" are injuries based ranked by severity and the patients are the "programs" wnating processing time with the hospital staff which are the "CPU". Compared to other scheduling types, priority does have the most flexibility and creativity as priority is defined by the programmer.

Priority scheduling can be both preemptive and non-preemptive. Non-preemptive programs full process a program all at once while pre-emptive programs process programs in small increments so it can efficiently spread out the CPU so not program is starved. Generally priority scheduling is preemptive but if the CPU is empty, it will just pick the next top priorty task and process it.

# Drawbracks of using Priority Scheduling
Priority scheduling prioritizes the most import program when delagating time for CPU processing. That program would take precendence over a lower priority program, which in turn will starve that lower priority program processing time. This is a called starvation, and starvation can lead to lag time or glitches in the program that is being starved. A way to eliminate this is to implement an againg technique that will gradually move lower priority program up in the queue.

Another draw back is priority inversion. For example, you are downloading a new application while also browsing on google chrome, the application is lower priorty but requires way more processing time during its turn. Once it is the applications turn, the application places a temporary lock on the CPU that last the durtaion of its turn, but the higher priority program needs the CPU more often. Generally that high priority program will have to wait until thta lock is lifted which nullifies its priority ranking.

# General example
The OS keeps a struct for each process, called a PCB (process control block). Picking the next process is basically a “find the minimum” loop:

```
struct pcb {
    int pid;            // process ID
    int priority;       // lower number = more important
    int remaining_time; // how much CPU time it still needs
};
// Returns the index of the process that should run next
int pick_next(struct pcb ready[], int n) {
    int best = 0;
    for (int i = 1; i < n; i++) {
        if (ready[i].priority < ready[best].priority) {
            best = i;
        }
    }
    return best;
}
```

Real operating systems use faster data structures than a loop (like a heap or one queue per priority level), but the idea is generally the same: find the most important ready process.




Attestation: Claude AI was used for learning and coding examples, but presntation slide and the readme excluding the genral example were written by me.

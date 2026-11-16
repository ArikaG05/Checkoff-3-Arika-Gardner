// PID: 730646316

// This is a VERY basic showing of how music players such as spotify, apple music
// or even Youtube uses priotity scheduling to allow you music to play in the
// background while downloading other apps

#include <stdio.h>
#include <stdlib.h>

struct process {
    char name[20];      // lets say you want to listen to olivia dean while dowlading bambu studio and 
                    // scrolling through pintrest. hence we would need Spotify, Bambu_studio and 
                    // Pintrest as our processes as they each need time with the CPU

    int  priority;  
    int  work;      // the amount of time the CPU needs to process the appplication
};

void run(int use_priority) {
    struct process apps[3] = {
    {"Spotify", 1, 0}, // needs 2 ms of work every 10 ms
    {"Bambu Studio", 3, 1000}, // big file: always busy
    {"Pintrest", 2, 0} // needs 2 ms of work every 5 ms
    };

    struct process *spotify   = &apps[0];
    struct process *pinterest = &apps[1];
    struct process *bambu     = &apps[2];
    int skips = 0, lags = 0;

 printf("%-13s", use_priority ? "Priority:" : "No priority:");
    for (int t = 0; t < 30; t++) {               // 1 loop = 1 ms
        if (t % 10 == 0) {                       // every 10 ms...
            if (spotify->work > 0) skips++;      // if spotify is still waiting for cpu time, song SKIPS
            spotify->work = 2;
        }
        if (t % 5 == 0) {                        // every 5 ms...
            if (pinterest->work > 0) lags++;     // if browers is still waiting for cpu time, it LAGS
            pinterest->work = 2;
        }

        struct process *current = bambu;         // the download got the CPU first
        if (use_priority) {
            // pick the most important app that still needs the CPU
            for (int i = 0; i < 3; i++)
                if (apps[i].work > 0 && apps[i].priority < current->priority)
                    current = &apps[i];
        }

        current->work--;                         // run it for 1 ms
        printf("%c", current->name[0]);          // S, P, or B
    }
    if (spotify->work > 0) skips++;
    if (pinterest->work > 0) lags++;
    printf("  -> %d skips, %d lags\n", skips, lags);
}

int main(void) {
    run(0);   // without priority scheduling
    run(1);   // with priority scheduling
    return 0;
}
// This is a VERY basic showing of how music players such as spotify, apple music
// or even Youtube uses priotity scheduling to allow you music to play in the
// background while downloading other apps

#include <stdio.h>

struct process {
    char name;      // lets say you want to listen to olivia dean while dowlading bambu studio and 
                    // scrolling through pintrest. hence we would need Spotify, Bambu_studio and 
                    // Pintrest as our processes as they each need time with the CPU

    int  priority;  
    int  work;      // the amount of time the CPU needs to process the appplication
};

void run(int use_priority) {
    struct process music    = {'Spotify', 1, 0}; 
    struct process download = {'Bambu Studio', 3, 1000};
    struct process browser = {'Pintrest', 2, 800};  // big file: always busy
     
    int skips = 0;

    printf("%-13s", use_priority ? "Priority:" : "No priority:");
    for (int t = 0; t < 30; t++) {             // 1 loop = 1 ms
        if (t % 10 == 0) {                     // every 10 ms...
            if (music.work > 0) skips++;       // music still waiting? SKIP!
            music.work = 2;                    // music needs 2 ms of CPU
        }

        struct process *current = &download;   // download has the CPU
        if (use_priority && music.work > 0 &&
            music.priority < download.priority &&
            music.priority < browser.priority)
            current = &music;                  // music preempts download

        current->work--;                       // run it for 1 ms
        printf("%c", current->name);
    }
    if (music.work > 0) skips++;
    printf("  -> %d skips\n", skips);
}

int main(void) {
    run(0);   // without priority scheduling
    run(1);   // with priority scheduling
    return 0;
}

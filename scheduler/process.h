#ifndef PROCESS_H
#define PROCESS_H

#include <string>

struct Process {
    std::string pid;
    int arrival_time;
    int burst_time;
    int priority;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

#endif

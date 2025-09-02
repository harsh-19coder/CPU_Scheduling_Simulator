#include "priority.h"
#include <algorithm>

std::vector<Process> priority_scheduling(std::vector<Process> processes, bool preemptive) {
    std::vector<Process> completed;
    int n = processes.size();
    std::vector<bool> is_done(n, false);
    int time = 0, done = 0;

    while (done < n) {
        int idx = -1;
        int highest_priority = 1e9;

        for (int i = 0; i < n; i++) {
            if (!is_done[i] && processes[i].arrival_time <= time) {
                if (processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        processes[idx].start_time = time;
        processes[idx].completion_time = time + processes[idx].burst_time;
        processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
        processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
        time = processes[idx].completion_time;

        is_done[idx] = true;
        completed.push_back(processes[idx]);
        done++;
    }

    return completed;
}

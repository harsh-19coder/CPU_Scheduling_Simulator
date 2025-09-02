#include "fcfs.h"
#include <algorithm>

std::vector<Process> fcfs(std::vector<Process> processes) {
    std::sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.arrival_time < b.arrival_time;
    });

    int current_time = 0;

    for (auto &p : processes) {
        p.start_time = std::max(current_time, p.arrival_time);
        p.completion_time = p.start_time + p.burst_time;
        p.turnaround_time = p.completion_time - p.arrival_time;
        p.waiting_time = p.turnaround_time - p.burst_time;

        current_time = p.completion_time;
    }

    return processes;
}

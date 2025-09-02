#include "sjf.h"
#include <algorithm>

std::vector<Process> sjf(std::vector<Process> processes) {
    std::vector<Process> completed;
    int time = 0;

    while (!processes.empty()) {
        auto it = std::min_element(processes.begin(), processes.end(), [time](const Process &a, const Process &b) {
            if (a.arrival_time <= time && b.arrival_time <= time)
                return a.burst_time < b.burst_time;
            return a.arrival_time < b.arrival_time;
        });

        if (it->arrival_time > time)
            time = it->arrival_time;

        Process p = *it;
        p.start_time = time;
        p.completion_time = p.start_time + p.burst_time;
        p.turnaround_time = p.completion_time - p.arrival_time;
        p.waiting_time = p.turnaround_time - p.burst_time;

        time = p.completion_time;
        completed.push_back(p);
        processes.erase(it);
    }

    return completed;
}

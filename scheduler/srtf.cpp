#include "srtf.h"
#include <algorithm>

std::vector<Process> srtf(std::vector<Process> processes) {
    std::vector<Process> completed;
    int n = processes.size();
    std::vector<int> remaining(n);
    for (int i = 0; i < n; i++)
        remaining[i] = processes[i].burst_time;

    int done = 0, time = 0;
    std::vector<bool> is_completed(n, false);

    while (done < n) {
        int idx = -1;
        int min_bt = 1e9;

        for (int i = 0; i < n; i++) {
            if (!is_completed[i] && processes[i].arrival_time <= time && remaining[i] < min_bt && remaining[i] > 0) {
                min_bt = remaining[i];
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        if (remaining[idx] == processes[idx].burst_time)
            processes[idx].start_time = time;

        remaining[idx]--;
        time++;

        if (remaining[idx] == 0) {
            processes[idx].completion_time = time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
            is_completed[idx] = true;
            completed.push_back(processes[idx]);
            done++;
        }
    }

    std::sort(completed.begin(), completed.end(), [](const Process &a, const Process &b) {
        return a.start_time < b.start_time;
    });

    return completed;
}

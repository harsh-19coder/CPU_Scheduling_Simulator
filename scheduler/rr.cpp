#include "rr.h"
#include <queue>
#include <algorithm>

std::vector<Process> round_robin(std::vector<Process> processes, int quantum) {
    int n = processes.size();
    std::vector<int> remaining(n);
    for (int i = 0; i < n; i++) remaining[i] = processes[i].burst_time;

    std::queue<int> q;
    std::vector<bool> in_queue(n, false);
    std::vector<Process> result;
    int done = 0, time = 0;

    auto sorted = processes;
    std::sort(sorted.begin(), sorted.end(), [](const Process &a, const Process &b) {
        return a.arrival_time < b.arrival_time;
    });

    int i = 0;
    while (done < n) {
        while (i < n && sorted[i].arrival_time <= time) {
            int idx = std::find_if(processes.begin(), processes.end(), [&](const Process &p) {
                return p.pid == sorted[i].pid;
            }) - processes.begin();
            if (!in_queue[idx]) {
                q.push(idx);
                in_queue[idx] = true;
            }
            i++;
        }

        if (q.empty()) {
            time++;
            continue;
        }

        int idx = q.front(); q.pop();

        if (remaining[idx] == processes[idx].burst_time)
            processes[idx].start_time = std::max(time, processes[idx].arrival_time);

        int exec = std::min(quantum, remaining[idx]);
        time = std::max(time, processes[idx].arrival_time) + exec;
        remaining[idx] -= exec;

        while (i < n && sorted[i].arrival_time <= time) {
            int next_idx = std::find_if(processes.begin(), processes.end(), [&](const Process &p) {
                return p.pid == sorted[i].pid;
            }) - processes.begin();
            if (!in_queue[next_idx]) {
                q.push(next_idx);
                in_queue[next_idx] = true;
            }
            i++;
        }

        if (remaining[idx] > 0) {
            q.push(idx);
        } else {
            processes[idx].completion_time = time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
            result.push_back(processes[idx]);
            done++;
        }
    }

    std::sort(result.begin(), result.end(), [](const Process &a, const Process &b) {
        return a.start_time < b.start_time;
    });

    return result;
}

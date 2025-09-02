#include "process.h"
#include <iostream>
#include <vector>
#include <iomanip> // for formatting

void print_result(const std::vector<Process>& result, std::ostream& out) {
    int total_wt = 0, total_tat = 0;
    out << "PID\tAT\tBT\tCT\tWT\tTAT\n";

    for (const auto& p : result) {
        total_wt += p.waiting_time;
        total_tat += p.turnaround_time;
        out << p.pid << "\t"
            << p.arrival_time << "\t"
            << p.burst_time << "\t"
            << p.completion_time << "\t"
            << p.waiting_time << "\t"
            << p.turnaround_time << "\n";
    }

    float avg_wt = static_cast<float>(total_wt) / result.size();
    float avg_tat = static_cast<float>(total_tat) / result.size();

    out << "\nAverage Waiting Time: " << std::fixed << std::setprecision(2) << avg_wt << "\n";
    out << "Average Turnaround Time: " << std::fixed << std::setprecision(2) << avg_tat << "\n";
}

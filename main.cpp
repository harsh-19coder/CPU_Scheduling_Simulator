#include <fstream>
#include <sstream>
#include "scheduler/fcfs.h"
#include "scheduler/sjf.h"
#include "scheduler/srtf.h"
#include "scheduler/rr.h"
#include "scheduler/priority.h"
#include "scheduler/utils.h"

int main() {
    std::ifstream infile("input.txt");
    std::ofstream outfile("output.txt");

    if (!infile) {
        outfile << "Error: input.txt not found.\n";
        return 1;
    }

    std::string line;
    std::string algorithm;
    std::vector<Process> processes;

    // Read algorithm line
    std::getline(infile, line);
    if (line.find("ALGO:") != std::string::npos) {
        algorithm = line.substr(6);  // After "ALGO: "
    } else {
        outfile << "Invalid input format.\n";
        return 1;
    }

    // Read processes
    while (std::getline(infile, line)) {
        if (line.empty()) continue;
        std::istringstream ss(line);
        std::string pid;
        int at, bt, prio = 0;

        ss >> pid >> at >> bt;
        if (algorithm == "Priority")
            ss >> prio;

        processes.push_back({pid, at, bt, prio});
    }

    if (algorithm == "FCFS") {
        auto result = fcfs(processes);
        print_result(result, outfile);
    } else if (algorithm == "SJF") {
        auto result = sjf(processes);
        print_result(result, outfile);
    } else if (algorithm == "SRTF") {
        auto result = srtf(processes);
        print_result(result, outfile);
    } else if (algorithm == "Round Robin") {
        auto result = round_robin(processes, 2); // Use default time quantum = 2
        print_result(result, outfile);
    } else if (algorithm == "Priority") {
        auto result = priority_scheduling(processes);
        print_result(result, outfile);
    } else {
        outfile << "Unsupported algorithm: " << algorithm << "\n";
        return 1;
    }

    return 0;
}


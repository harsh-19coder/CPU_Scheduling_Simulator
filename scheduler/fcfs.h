#ifndef FCFS_H
#define FCFS_H

#include <vector>
#include "process.h"

std::vector<Process> fcfs(std::vector<Process> processes);
void print_result(const std::vector<Process>& result);

#endif

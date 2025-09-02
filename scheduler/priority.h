#ifndef PRIORITY_H
#define PRIORITY_H

#include <vector>
#include "process.h"

std::vector<Process> priority_scheduling(std::vector<Process> processes, bool preemptive = false);

#endif

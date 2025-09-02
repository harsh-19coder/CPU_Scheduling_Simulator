#ifndef RR_H
#define RR_H

#include <vector>
#include "process.h"

std::vector<Process> round_robin(std::vector<Process> processes, int quantum);

#endif

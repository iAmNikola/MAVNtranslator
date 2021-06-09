#pragma once

#include "SimplificationStack.h"


void doResourceAllocation(InterferenceGraph* ig, stack<Variable*>* simplifactionStack);

int freeReg(vector<int> occupied_regs);
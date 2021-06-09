#pragma once

#include "IR.h"
#include <stack>
#include "InterferenceGraph.h"

using namespace std;

typedef stack<Variable*> SimplificationStack;

SimplificationStack* doSimplification(InterferenceGraph* intGr, int degree);



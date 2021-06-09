#pragma once 
#ifndef __LIVENESS_ANALYSIS__
#define __LIVENESS_ANALYSIS__

#include "IR.h"

void livenessAnalysis(Instructions& instructions);

bool varIn(Variables& vars, Variable* v);

#endif

#pragma once

#include "IR.h"

/**
 * Builds the interference graph based on instruction list of the analyzed program.
 * @param - instructions
 *	List of instructions
 * @return
 *	Reference to the interference graph
 */

bool isInterfering(int pos, std::vector<int>& interferences);

/**
 * Prints the interference graph
 */
void printInterferenceMatrix();

/**
 * This type represents matrix of integers.
 */
typedef std::vector<std::vector<int>> InterferenceMatrix;


/**
 * This type represents stack of pointers to variables.
 */
typedef std::stack<Variable*> SimplificationStack;

/**
 * This type represents interference graph.
 */
typedef struct InterferenceGraphStruct
{
	Variables* variables;		// all variables from instructions
	InterferenceMatrix matrix;	// interference matrix

	/**
	 * Default construction.
	 */
	InterferenceGraphStruct()
	{
	}

	~InterferenceGraphStruct() {
		delete variables;
	}
} InterferenceGraph;

InterferenceGraph* makeInterferenceGraph(Instructions& insts);

#pragma once

#include "IR.h"
#include "LexicalAnalysis.h"
#include <map>


class InstructionSelection
{
public:
	Variables makeVariablesList(TokenList& t);

	Instructions makeInstructionsList(TokenList& t, Variables& vars);

	void printInstructions(Instructions& insts);

private:

	void putVars(Variables& out, Variables& in, TokenList::iterator it, int& r_count);

	Variable* varExistsAssignToV(Variables& in, std::string name);

	//bool isType(int type, Variables& vars, std::string name, Variable* var);

	void putInUse(Variables& use, Variables& src);

	void setPredAndSucc(Instruction* inst, Instructions& instructions);	
};

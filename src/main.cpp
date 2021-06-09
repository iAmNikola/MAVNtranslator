#include <iostream>
#include <exception>

#include "LexicalAnalysis.h"
#include "SyntaxAnalysis.h"
#include "InstructionSelection.h"
#include "LivenessAnalysis.h"
#include "InterferenceGraph.h"
#include "SimplificationStack.h"
#include "ResourceAllocation.h"
#include "Writer.h"


using namespace std;


int main()
{
	try
	{
		string file = "multiply";
		//string fileName = ".\\..\\examples\\" + file + ".mavn";
		string fileName = ".\\..\\examples\\" + file + ".mavn";
		bool retVal = false;

		LexicalAnalysis lex;

		if (!lex.readInputFile(fileName))
			throw runtime_error("\nException! Failed to open input file!\n");

		lex.initialize();

		if (lex.Do())
		{
			lex.printTokens();
			cout << "Lexical analysis finished successfully!" << endl << endl;
		}
		else
		{
			lex.printLexError();
			throw runtime_error("\nException! Lexical analysis failed!\n");
		}

		SyntaxAnalysis syntax(lex);

		syntax.Do();
		cout << "Syntax analysis finished successfully!" << endl << endl;

		InstructionSelection inSel;
		Variables vars = inSel.makeVariablesList(lex.getTokenList());
		Instructions insts = inSel.makeInstructionsList(lex.getTokenList(), vars);
		inSel.printInstructions(insts);
		cout << "Instruction selection finished successfully!" << endl << endl;

		livenessAnalysis(insts);
		inSel.printInstructions(insts);
		cout << "Liveness analysis finished successfully!" << endl << endl;

		InterferenceGraph* intGr = makeInterferenceGraph(insts);
		printInterferenceMatrix();
		cout << "Interference graph finished successfully!" << endl << endl;

		SimplificationStack* ss = doSimplification(intGr, __REG_NUMBER__);
		cout << "Simplified stack generation finished successfully!" << endl << endl;

		doResourceAllocation(intGr, ss);
		cout << "Resource allocation finished successfully!" << endl << endl;

		write(insts, vars, file);
		cout << endl << "Output file located in:" << ".\\..\\examples\\" + file + "Out.S" << endl << endl;
	}
	catch (runtime_error e)
	{
		cout << e.what() << endl;
		return 1;
	}

	return 0;
}


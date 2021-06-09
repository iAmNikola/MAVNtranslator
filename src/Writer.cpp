#include "Writer.h"

using namespace std;

void write(Instructions& insts, Variables& vars, string filename) {

	char* typeStr[] =
	{
		"no_type",
		"add",
		"addi",
		"sub",
		"la",
		"li",
		"lw",
		"sw",
		"bltz",
		"b",
		"nop",
		"abs",
		"neg",
		"seq"
	};
	char* regStr[] =
	{
		"no_assign",
		"t0",
		"t1",
		"t2",
		"t3",
		"t4",
		"t5",
		"t6",
		"t7"
	};

	filename = ".\\..\\examples\\" + filename + "Out.S";
	ofstream of(filename);

	if (of)
	{
		cout << ".globl main" << endl << endl;
		cout << ".data" << endl;
		of   << ".globl main" << endl << endl;
		of   << ".data" << endl;
		for each (Variable* var in vars)
		{
			if (var->getType() == Variable::MEM_VAR)
			{
				cout << var->getName() << ":\t\t.word " << var->getValue() << endl << endl;
				of   << var->getName() << ":\t\t.word " << var->getValue() << endl << endl;
			}
		}
		cout << ".text" << endl;
		of   << ".text" << endl;

		int counter = 0;
		for each (Instruction * inst in insts)
		{
			for (map<string, int>::iterator it = inst->getLabels().begin(); it != inst->getLabels().end(); it++) {
				if (it->second == counter)
				{
					cout << it->first << ":" << endl;
					of << it->first << ":" << endl;
				}
			}
			counter++;
			cout << "\t\t" << typeStr[inst->getType()] << "\t";
			of   << "\t\t" << typeStr[inst->getType()] << "\t";
			
			switch (inst->getType())
			{
			case I_ADD:
			case I_SUB:
			case I_SEQ:
				cout << "$" << regStr[inst->getDst().front()->getAssignment()] << ", " << "$" << regStr[inst->getSrc().front()->getAssignment()] << ", " << "$" << regStr[inst->getSrc().back()->getAssignment()];
				of   << "$" << regStr[inst->getDst().front()->getAssignment()] << ", " << "$" << regStr[inst->getSrc().front()->getAssignment()] << ", " << "$" << regStr[inst->getSrc().back()->getAssignment()];
				break;
			case I_ADDI:
				cout << "$" << regStr[inst->getDst().front()->getAssignment()] << ", " << "$" << regStr[inst->getSrc().front()->getAssignment()] << ", " << inst->getNum();
				of << "$" << regStr[inst->getDst().front()->getAssignment()] << ", " << "$" << regStr[inst->getSrc().front()->getAssignment()] << ", " << inst->getNum();
				break;
			case I_LA:
				cout << "$" << regStr[inst->getDst().front()->getAssignment()] << ", " << inst->getSrc().front()->getName();
				of   << "$" << regStr[inst->getDst().front()->getAssignment()] << ", " << inst->getSrc().front()->getName();
				break;
			case I_ABS:
			case I_NEG:
				cout << "$" << regStr[inst->getDst().front()->getAssignment()] << ", " << "$" << regStr[inst->getSrc().front()->getAssignment()];
				of   << "$" << regStr[inst->getDst().front()->getAssignment()] << ", " << "$" << regStr[inst->getSrc().front()->getAssignment()];
				break;
			case I_LW:
				cout << "$" << regStr[inst->getDst().front()->getAssignment()] << ", " << inst->getNum() << "(" << "$" << regStr[inst->getSrc().front()->getAssignment()] << ")";
				of   << "$" << regStr[inst->getDst().front()->getAssignment()] << ", " << inst->getNum() << "(" << "$" << regStr[inst->getSrc().front()->getAssignment()] << ")";
				break;
			case I_LI:
				cout << "$" << regStr[inst->getDst().front()->getAssignment()] << ", " << inst->getNum();
				of   << "$" << regStr[inst->getDst().front()->getAssignment()] << ", " << inst->getNum();
				break;
			case I_SW:
				cout << "$" << regStr[inst->getSrc().front()->getAssignment()] << ", " << inst->getNum() << "(" << "$" << regStr[inst->getDst().front()->getAssignment()] << ")";
				of   << "$" << regStr[inst->getSrc().front()->getAssignment()] << ", " << inst->getNum() << "(" << "$" << regStr[inst->getDst().front()->getAssignment()] << ")";
				break;
			case I_B:
				cout << inst->getLabel();
				of   << inst->getLabel();
				break;
			case I_BLTZ:
				cout << "$" << regStr[inst->getSrc().front()->getAssignment()] << ", " << inst->getLabel();
				of   << "$" << regStr[inst->getSrc().front()->getAssignment()] << ", " << inst->getLabel();
				break;
			default:
				break;
			}
			cout << endl;
			of   << endl;
		}
	}
	else
	{
		throw runtime_error("Cannot output to this file.");
	}
	of.close();
}


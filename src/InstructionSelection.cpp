#include "InstructionSelection.h"


using namespace std;

//pamtiti koje se koriste varijable, 


Variables InstructionSelection::makeVariablesList(TokenList& t)
{
	Variables vars;
	for (TokenList::iterator it = t.begin(); it != t.end(); it++) {
		if ((*it).getType() == T_MEM) {
			it++;
			string name = (*it).getValue();
			Variable* v = new Variable(Variable::MEM_VAR, name, (*++it).getValue());
			vars.push_back(v);
		}
		else if ((*it).getType() == T_REG) {
			Variable* v = new Variable(Variable::REG_VAR, (*++it).getValue());
			vars.push_back(v);
		}
	}

	return vars;
}

Instructions InstructionSelection::makeInstructionsList(TokenList& t, Variables& vars)
{
	Instructions insts;
	int r_count = 0;
	int inst_count = 0;
	map<string, int> labels;

	for (TokenList::iterator it = t.begin(); it != t.end(); it++) {
		Variables dst, src, use, def;

		if ((*it).getType() == T_ADD) {
			it++;
			putVars(dst, vars, it, r_count);
			it++; it++;
			putVars(src, vars, it, r_count);
			it++; it++;
			putVars(src, vars, it, r_count);
			putInUse(use, src);
			def = dst;
			Instruction* inst = new Instruction(inst_count, I_ADD, dst, src, use, def);
			if (inst_count > 0)
			{
				setPredAndSucc(inst, insts);
			}
			insts.push_back(inst);
			inst_count++;
		}
		else if ((*it).getType() == T_ADDI) {
			it++;
			putVars(dst, vars, it, r_count);
			it++; it++;
			putVars(src, vars, it, r_count);
			it++; it++;
			string number = (*it).getValue();
			putInUse(use, src);
			def = dst;
			Instruction* inst = new Instruction(inst_count, I_ADDI, number, dst, src, use, def);
			if (inst_count > 0)
			{
				setPredAndSucc(inst, insts);
			}
			insts.push_back(inst);
			inst_count++;
		}
		else if ((*it).getType() == T_SUB) {
			it++;
			putVars(dst, vars, it, r_count);
			it++; it++;
			putVars(src, vars, it, r_count);
			it++; it++;
			putVars(src, vars, it, r_count);
			putInUse(use, src);
			def = dst;
			Instruction* inst = new Instruction(inst_count, I_SUB, dst, src, use, def);
			if (inst_count > 0)
			{
				setPredAndSucc(inst, insts);
			}
			insts.push_back(inst);
			inst_count++;
		}
		else if ((*it).getType() == T_LA) {
			it++;
			putVars(dst, vars, it, r_count);
			it++; it++;
			putVars(src, vars, it, r_count);
			putInUse(use, src);
			def = dst;
			Instruction* inst = new Instruction(inst_count, I_LA, dst, src, use, def);
			if (inst_count > 0)
			{
				setPredAndSucc(inst, insts);
			}
			insts.push_back(inst);
			inst_count++;
		}
		else if ((*it).getType() == T_LW) {
			it++;
			putVars(dst, vars, it, r_count);
			it++; it++;
			string number = (*it).getValue();
			it++; it++;
			putVars(src, vars, it, r_count);
			it++;
			putInUse(use, src);
			def = dst;
			Instruction* inst = new Instruction(inst_count, I_LW, number, dst, src, use, def);
			if (inst_count > 0)
			{
				setPredAndSucc(inst, insts);
			}
			insts.push_back(inst);
			inst_count++;
		}
		else if ((*it).getType() == T_LI) {
			it++;
			putVars(dst, vars, it, r_count);
			it++; it++;
			string number = (*it).getValue();
			def = dst;
			Instruction* inst = new Instruction(inst_count, I_LI, number, dst, src, use, def);
			if (inst_count > 0)
			{
				setPredAndSucc(inst, insts);
			}
			insts.push_back(inst);
			inst_count++;
		}
		else if ((*it).getType() == T_SW) {
			it++;
			putVars(src, vars, it, r_count);
			it++; it++;
			string number = (*it).getValue();
			it++; it++;
			putVars(dst, vars, it, r_count);
			it++;
			putInUse(use, src);
			def = dst;
			Instruction* inst = new Instruction(inst_count, I_SW, number, dst, src, use, def);
			if (inst_count > 0)
			{
				setPredAndSucc(inst, insts);
			}
			insts.push_back(inst);
			inst_count++;
		}
		else if ((*it).getType() == T_B) {
			it++;
			string label = (*it).getValue();
			Instruction* inst = new Instruction(inst_count, I_B, dst, src, use, def, label);
			if (inst_count > 0)
			{
				setPredAndSucc(inst, insts);
			}
			insts.push_back(inst);
			inst_count++;
		}
		else if ((*it).getType() == T_BLTZ) {
			it++;
			putVars(src, vars, it, r_count);
			putInUse(use, src);
			it++; it++;
			string label = (*it).getValue();
			Instruction* inst = new Instruction(inst_count, I_BLTZ, dst, src, use, def, label);
			if (inst_count > 0)
			{
				setPredAndSucc(inst, insts);
			}
			insts.push_back(inst);
			inst_count++;
		}
		else if ((*it).getType() == T_NOP) {
			Instruction* inst = new Instruction(inst_count, I_NOP, dst, src, use, def);
			if (inst_count > 0)
			{
				setPredAndSucc(inst, insts);
			}
			insts.push_back(inst);
			inst_count++;
		}
		else if ((*it).getType() == T_ABS) {
			it++;
			putVars(dst, vars, it, r_count);
			it++; it++;
			putVars(src, vars, it, r_count);
			putInUse(use, src);
			def = dst;
			Instruction* inst = new Instruction(inst_count, I_ABS, dst, src, use, def);
			if (inst_count > 0)
			{
				setPredAndSucc(inst, insts);
			}
			insts.push_back(inst);
			inst_count++;
		}
		else if ((*it).getType() == T_NEG) {
			it++;
			putVars(dst, vars, it, r_count);
			it++; it++;
			putVars(src, vars, it, r_count);
			putInUse(use, src);
			def = dst;
			Instruction* inst = new Instruction(inst_count, I_NEG, dst, src, use, def);
			if (inst_count > 0)
			{
				setPredAndSucc(inst, insts);
			}
			insts.push_back(inst);
			inst_count++;
		}
		else if ((*it).getType() == T_SEQ) {
			it++;
			putVars(dst, vars, it, r_count);
			it++; it++;
			putVars(src, vars, it, r_count);
			it++; it++;
			putVars(src, vars, it, r_count);
			putInUse(use, src);
			def = dst;
			Instruction* inst = new Instruction(inst_count, I_SEQ, dst, src, use, def);
			if (inst_count > 0)
			{
				setPredAndSucc(inst, insts);
			}
			insts.push_back(inst);
			inst_count++;
		}
		else if ((*it).getType() == T_ID)
		{
			string label = (*it).getValue();
			if (labels.count(label) == 1)
			{
				throw runtime_error("Two labels cannot have the same name.");
			}
			labels[label] = inst_count;
		}
	}
	for (Instructions::iterator it = insts.begin(); it != insts.end(); it++) {
		inst_count = 0;
		bool labelExists = false;
		if ((*it)->getType() == I_B)
		{
			(*it)->clearSucc();
			for (Instructions::iterator it2 = insts.begin(); it2 != insts.end(); it2++) {
				if (labels[(*it)->getLabel()] == inst_count)
				{
					(*it)->setSucc(*it2);
					(*it2)->setPred(*it);
					labelExists = true;
					break;
				}
				inst_count++;
			}
			if (!labelExists)
			{
				throw runtime_error("Label:" + (*it)->getLabel() + "doesn't exist!");
			}
		}
		else if ((*it)->getType() == I_BLTZ)
		{
			for (Instructions::iterator it2 = insts.begin(); it2 != insts.end(); it2++) {
				if (labels[(*it)->getLabel()] == inst_count)
				{
					(*it)->setSucc(*it2);
					(*it2)->setPred(*it);
					labelExists = true;
					break;
				}
				inst_count++;
			}
			if (!labelExists)
			{
				throw runtime_error("Label: " + (*it)->getLabel() + " doesn't exist!");
			}
		}
		(*it)->setLabels(labels);
	}
	return insts;
}



void InstructionSelection::putVars(Variables& out, Variables& in, TokenList::iterator it, int& r_count) {
	
	Variable* v = varExistsAssignToV(in, (*it).getValue());
	
	if (v != nullptr)
	{
		if (v->getType() == Variable::REG_VAR) {
			if (v->getPosition() == -1)
			{
				v->setPosition(r_count++);
			}
		}
		out.push_back(v);
	}
	else {
		throw runtime_error("Variable not declared!");
	}
}

Variable* InstructionSelection::varExistsAssignToV(Variables& vars, string name) {
	for each (Variable* var in vars)
	{
		if (var->getName() == name)
		{
			return var;
		}
	}
	return nullptr;
}

void InstructionSelection::putInUse(Variables& use, Variables& src) {
	for each (Variable * var in src)
	{
		if (var->getType() != Variable::MEM_VAR)
		{
			use.push_back(var);
		}
	}
}

void InstructionSelection::setPredAndSucc(Instruction* inst, Instructions& insts) {
	Instructions::reverse_iterator it = insts.rbegin();
	inst->setPred((*it));
	(*it)->setSucc(inst);
}


void InstructionSelection::printInstructions(Instructions& insts) {

	char* InstructionTypeString[] =
	{
		"I_NO_TYPE",
		"I_ADD",
		"I_ADDI",
		"I_SUB",
		"I_LA",
		"I_LI",
		"I_LW",
		"I_SW",
		"I_BLTZ",
		"I_B",
		"I_NOP",
		"I_ABS",
		"I_NEG",
		"I_SEQ"
	};

	for (Instructions::iterator it = insts.begin(); it != insts.end(); it++) {

		int counter = 1;
		cout << "Type: " << InstructionTypeString[(*it)->getType()] << "	Pos: " << (*it)->getPosition() << endl;
		cout << "------------------------------------------" << endl;
		for (Variables::iterator i = (*it)->getDst(1).begin(); i != (*it)->getDst(1).end(); i++)
		{
			cout << "Dest" << "    "<< (*i)->getName() << ",  Pos: " << (*i)->getPosition() << ",  Assignment: " << (*i)->getAssignment() << endl;
		}
		counter = 1;
		for (Variables::iterator i = (*it)->getSrc(1).begin(); i != (*it)->getSrc(1).end(); i++)
		{
			cout << "Src" << counter++ << "    " << (*i)->getName() << ",  Pos: " << (*i)->getPosition() << ",  Assignment: " << (*i)->getAssignment() << endl;
		}
		cout << "------------------------------------------" << endl;
		cout << "Pred:	";

		for (Instruction* itt : (*it)->getPred()) {
			cout << itt->getPosition() << " ";
		}
		cout << endl;
		cout << "Succ:	";

		for (Instruction* itt : (*it)->getSucc()) {
			cout << itt->getPosition() << " ";
		}
		cout << endl;
		cout << "Use:	";
		for (Variables::iterator i = (*it)->getUse(1).begin(); i != (*it)->getUse(1).end(); i++)
		{
			if ((*i)->getType() != Variable::VariableType::MEM_VAR)
				cout << (*i)->getName() << '\t';
		}
		cout << endl;
		cout << "Def:	";
		for (Variables::iterator i = (*it)->getDef(1).begin(); i != (*it)->getDef(1).end(); i++)
		{
			if ((*i)->getType() != Variable::VariableType::MEM_VAR)
				cout << (*i)->getName() << '\t';
		}
		cout << endl;
		cout << "In:	";
		for (Variables::iterator i = (*it)->getIn(1).begin(); i != (*it)->getIn(1).end(); i++)
		{
			if ((*i)->getType() != Variable::VariableType::MEM_VAR)
				cout << (*i)->getName() << '\t';
		}
		cout << endl;
		cout << "Out:	";
		for (Variables::iterator i = (*it)->getOut(1).begin(); i != (*it)->getOut(1).end(); i++)
		{
			if ((*i)->getType() != Variable::VariableType::MEM_VAR)
				cout << (*i)->getName() << '\t';
		}
		cout << endl << "==========================================" << endl;

	}
}
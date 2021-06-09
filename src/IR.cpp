#include "IR.h"

using namespace std;

// Variable class functions

string Variable::getName() {
	return m_name;
}

Variable::VariableType Variable::getType() {
	return m_type;
}

string Variable::getValue() {
	return m_mem_value;
}

int Variable::getPosition() {
	return m_position;
}

void Variable::setPosition(int p) {
	m_position = p;
}

Regs Variable::getAssignment() {
	return m_assignment;
}

void Variable::setAssignment(int r) {
	m_assignment = (Regs)r;
}


// Instruction class functions
int Instruction::getPosition() {
	return m_position;
}

InstructionType Instruction::getType() {
	return m_type;
}

Variables Instruction::getDst() {
	return m_dst;
}

Variables Instruction::getSrc() {
	return m_src;
}

Variables Instruction::getUse() {
	return m_use;
}

Variables Instruction::getDef() {
	return m_def;
}

list<Instruction*> Instruction::getPred() {
	return m_pred;
}

void Instruction::setPred(Instruction* inst) {
	m_pred.push_back(inst);
}

list<Instruction*> Instruction::getSucc() {
	return m_succ;
}

void Instruction::setSucc(Instruction* inst) {
	m_succ.push_back(inst);
}

void Instruction::clearSucc() {
	m_succ.clear();
}

Variables Instruction::getIn() {
	return m_in;
}

void Instruction::setIn(Variables vars) {
	m_in = vars;
}

void Instruction::pushIn(Variable* v) {
	m_in.push_back(v);
}

Variables Instruction::getOut() {
	return m_out;
}

void Instruction::setOut(Variables vars) {
	m_out = vars;
}

void Instruction::pushOut(Variable* v) {
	m_out.push_back(v);
}

string Instruction::getNum() {
	return m_number;
}

string Instruction::getLabel() {
	return m_label;
}

map<string, int>& Instruction::getLabels() {
	return labels;
}

void Instruction::setLabels(map<string, int> l) {
	labels = l;
}

Variables& Instruction::getDst(int i) {
	return m_dst;
}

Variables& Instruction::getSrc(int i) {
	return m_src;
}

Variables& Instruction::getUse(int i) {
	return m_use;
}

Variables& Instruction::getDef(int i) {
	return m_def;
}

Variables& Instruction::getIn(int i) {
	return m_in;
}

Variables& Instruction::getOut(int i) {
	return m_out;
}

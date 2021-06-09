#ifndef __IR__
#define __IR__

#include "Types.h"
#include <map>

/**
 * This class represents one variable from program code.
 */
class Variable
{
public:
	enum VariableType
	{
		NO_TYPE,
		MEM_VAR,
		REG_VAR
	};
	Variable() : m_type(NO_TYPE), m_name(""), m_position(-1), m_assignment(no_assign) {}
	Variable(VariableType type, std::string name) : m_type(REG_VAR), m_name(name), m_position(-1), m_assignment(no_assign) {}
	Variable(VariableType type, std::string name, std::string mem_value) : m_type(MEM_VAR), m_name(name), m_mem_value(mem_value), m_position(-1), m_assignment(no_assign) {}

	std::string getName();
	VariableType getType();
	std::string getValue();
	int getPosition();
	void setPosition(int p);
	Regs getAssignment();
	void setAssignment(int r);

private:
	VariableType m_type;
	std::string m_name;
	int m_position;
	Regs m_assignment;
	std::string m_mem_value;
};


/**
 * This type represents list of variables from program code.
 */
typedef std::list<Variable*> Variables;


/**
 * This class represents one instruction in program code.
 */
class Instruction
{
public:
	Instruction () : m_position(0), m_type(I_NO_TYPE) {}
	Instruction (int pos, InstructionType type, Variables dst, Variables src) :
		m_position(pos), m_type(type), m_dst(dst), m_src(src), m_label("") {}
	Instruction(int pos, InstructionType type, Variables dst, Variables src, Variables use, Variables def) :
		m_position(pos), m_type(type), m_dst(dst), m_src(src), m_use(use), m_def(def), m_label("") {}
	Instruction(int pos, InstructionType type, std::string num, Variables dst, Variables src, Variables use, Variables def) :
		m_position(pos), m_type(type), m_number(num), m_dst(dst), m_src(src), m_use(use), m_def(def), m_label("") {}
	Instruction(int pos, InstructionType type, Variables dst, Variables src, Variables use, Variables def, std::string label) :
		m_position(pos), m_type(type), m_label(label), m_dst(dst), m_src(src), m_use(use), m_def(def) {}


	int getPosition();

	InstructionType getType();
	
	Variables getDst();

	Variables getSrc();

	Variables getUse();

	Variables getDef();

	Variables getIn();
	void setIn(Variables vars);
	void pushIn(Variable* v);

	Variables getOut();
	void setOut(Variables vars);
	void pushOut(Variable* v);

	std::list<Instruction*> getPred();
	void setPred(Instruction* inst);

	std::list<Instruction*> getSucc();
	void setSucc(Instruction* inst);
	void clearSucc();

	std::string getNum();

	std::string getLabel();

	std::map<std::string, int>& getLabels();
	void setLabels(std::map<std::string, int> l);
	
	Variables& getDst(int i);
	Variables& getSrc(int i);
	Variables& getUse(int i);
	Variables& getDef(int i);
	Variables& getIn(int i);
	Variables& getOut(int i);

private:
	int m_position;
	InstructionType m_type;
	
	Variables m_dst;
	Variables m_src;

	Variables m_use;
	Variables m_def;
	Variables m_in;
	Variables m_out;
	std::list<Instruction*> m_succ;
	std::list<Instruction*> m_pred;
	std::string m_number;
	std::string m_label;
	std::map<std::string, int> labels;
};

/**
 * This type represents list of instructions from program code.
 */
typedef std::list<Instruction*> Instructions;

char* VariableTypeString[];
char* InstructionTypeString[];


#endif

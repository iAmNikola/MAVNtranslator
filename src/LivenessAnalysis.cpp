#include "LivenessAnalysis.h"

using namespace std;


void livenessAnalysis(Instructions& insts)
{
	bool loop = true;
	while (loop) {

		loop = false;

		for (Instructions::reverse_iterator rit = insts.rbegin(); rit != insts.rend(); rit++) {
			Variables& outPrim = (*rit)->getOut();
			Variables& inPrim = (*rit)->getIn();
			Variables out;

			Instructions& succ = (*rit)->getSucc();
			for (Instructions::iterator it = succ.begin(); it != succ.end(); it++) {
				Variables& succIn = (*it)->getIn();
				out.insert(out.end(), succIn.begin(), succIn.end());
			}
			out.sort();
			out.unique();

			Variables& def = (*rit)->getDef();
			Variables outMinusDef;
			Variables::iterator varIt = out.begin();
			for (; varIt != out.end(); varIt++) {
				if (!varIn(def, *varIt)) {
					outMinusDef.push_back(*varIt);
				}
			}

			Variables in;
			in = (*rit)->getUse();
			in.insert(in.end(), outMinusDef.begin(), outMinusDef.end());
			in.sort();
			in.unique();

			if (in != inPrim || out != outPrim) {
				loop = true;
			}

			(*rit)->setIn(in);
			(*rit)->setOut(out);
		}
	}
}

bool varIn(Variables& vars, Variable* v) {
	for each (Variable * var in vars)
	{
		if (var->getName() == v->getName())
		{
			return true;
		}
	}
	return false;
}

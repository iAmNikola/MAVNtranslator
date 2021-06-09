#include "ResourceAllocation.h"


using namespace std;


void doResourceAllocation(InterferenceGraph* ig, stack<Variable*>* ss)
{
    vector<int> occ_regs;

    while (true)
    {
        if (ss->empty()) 
        {
            break;
        }
        Variable* var1 = ss->top();
        ss->pop();

        for (Variable* var2 : *(ig->variables))
        {
            if (ig->matrix[var1->getPosition()][var2->getPosition()] == __INTERFERENCE__ && var2->getAssignment() != Regs::no_assign)
            {
                occ_regs.push_back(var2->getAssignment());
            }
        }
        var1->setAssignment(freeReg(occ_regs));
    }
};


int freeReg(vector<int> occ_regs)
{
    vector<int> regs(__REG_NUMBER__, 0);
    for (int i = 1; i <= __REG_NUMBER__; i++)
    {
        regs[i-1] = i;
    }

    for each (int reg in regs)
    {
        bool occupied = false;
        for each (int occ in occ_regs)
        {
            if (occ == reg)
            {
                occupied = true;
            }
        }
        if (!occupied) return reg;
    }
}

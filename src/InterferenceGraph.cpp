#include "InterferenceGraph.h"

#include <map>
#include <iostream>
#include <vector>

using namespace std;


static InterferenceGraph ig;

InterferenceGraph* makeInterferenceGraph(Instructions& insts) {

	ig.variables = new Variables;
	map<int, vector<int>> matrix;

	for each (Instruction * inst in insts)
	{
		for each (Variable * v_def in inst->getDef())
		{	
			vector<int> inter1;
			ig.variables->push_back(v_def);
			
			if (matrix.find(v_def->getPosition()) != matrix.end())
			{
				inter1 = matrix[v_def->getPosition()];
			}
			for each (Variable* v_out in inst->getOut())
			{
				if (v_def->getName() != v_out->getName())
				{
					if (!isInterfering(v_out->getPosition(), inter1))
					{
						inter1.push_back(v_out->getPosition());
					}
					vector<int> inter2;
					if (matrix.find(v_out->getPosition()) != matrix.end())
					{
						inter2 = matrix[v_out->getPosition()];
					}
					if (!isInterfering(v_def->getPosition(), inter2))
					{
						inter2.push_back(v_def->getPosition());
					}
					matrix[v_out->getPosition()] = inter2;
				}
			}
			matrix[v_def->getPosition()] = inter1;
		}
	}
	ig.variables->sort([](Variable* first, Variable* second) {return (first->getPosition() < second->getPosition());});
	ig.variables->unique();

	map<int, vector<int>>::iterator it;
	for (it = matrix.begin(); it != matrix.end(); it++) 
	{
		vector<int> inter;
		for (int i = 0; i < ig.variables->size(); i++)
		{
			if (isInterfering(i, it->second))
			{
				inter.push_back(__INTERFERENCE__);
			}
			else
			{
				inter.push_back(__EMPTY__);
			}
		}
		ig.matrix.push_back(inter);
	}
	return &ig;
}

bool isInterfering(int pos, vector<int>& inter) {
	for each (int i in inter)
	{
		if (pos == i)
		{
			return true;
		}
	}
	return false;
}

void printInterferenceMatrix()
{
	if (ig.matrix.size() == 0)
	{
		cout << "There is nothing to print!" << endl;
		return;
	}
	
	cout << "==========================================" << endl;
	cout << "Interference matrix:" << endl;
	cout << "==========================================" << endl;

	// print existing variables in order to mark rows and columns
	for (auto varIt = ig.variables->begin(); varIt != ig.variables->end(); varIt++)
	{
		cout << "\t" << (*varIt)->getName();
	}
	cout << endl;

	auto varIt = ig.variables->begin();
	for (auto it1 = ig.matrix.begin(); it1 != ig.matrix.end(); it1++)
	{
		cout << (*varIt++)->getName();
		for (auto it2 = (*it1).begin(); it2 != (*it1).end(); it2++)
		{
			cout << "\t" << *it2;
		}
		cout << endl;
	}
	cout << "==========================================" << endl;
}

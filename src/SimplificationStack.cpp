// nadjem registar sa najvise smetnji, ne sme biti veci od broja reg_num, i ne gleda se njegov red i kolona

#include "SimplificationStack.h"


using namespace std;

SimplificationStack* doSimplification(InterferenceGraph* intGr, int degree) {

	SimplificationStack* ss = new SimplificationStack;
	int maxPos, neighbours, counter;
	int size = intGr->variables->size();
	vector<bool> ignore(size, false);

	for (int s = 0; s < size; s++)
	{
		neighbours = -1;
		maxPos = -1;
		for (int i = 0; i < size; i++)
		{
			if (ignore[i])
			{
				continue;
			}
			counter = 0;
			for (int j = 0; j < size; j++)
			{
				if (intGr->matrix[i][j] == __INTERFERENCE__ && !ignore[j])
				{
					counter++;
				}
			}
			if (counter > neighbours && counter < degree)
			{
				neighbours = counter;
				maxPos = i;
			}
		}
		if (!(neighbours < 0))
		{
			ignore[maxPos] = true;
			counter = 0;
			for (auto it = intGr->variables->begin(); it != intGr->variables->end(); it++)
			{
				if ((*it)->getPosition() == maxPos)
				{
					ss->push(*it);
				}
			}
		}
	}
	if (ss->size() < intGr->matrix.size())
		throw std::runtime_error("Spilling! Simplification stack failed.");
	return ss;
}
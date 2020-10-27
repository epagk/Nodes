#include <iostream>
#include <bits/stdc++.h> 
#include "agent.h" // header in local directory

using namespace std;

Agent* getAgent(vector<Agent>* agents, int ID)
{	
	Agent* it;

	for (unsigned n = 0; n < agents->size(); n++)
	{	
		it = &(agents->at(n));
		if (it->getID() == ID){
			return it;
		}
	}

	Agent ag(-1, true, -1, "ghost", -1);		// if given ID does not exist
	Agent *ag_r = &ag;
	
	return ag_r;
}
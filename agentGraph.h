#include <iostream>
#include <bits/stdc++.h> 
#include "agent.h" // header in local directory

using namespace std;

Agent getAgent(vector<Agent> agents, int ID)
{
	for (auto it = agents.begin(); it!=agents.end(); it++)
	{
		if ((*it).getID() == ID)
			return (*it);
	}

	Agent ag(-1, true, -1, "ghost", -1);		// if given ID does not exist
	return ag;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "agent.h"
#include "agentGraph.h"

using namespace std;

vector<Agent> agents;
// vector<pair<int, int>>	edges;

int main(int argc, char *argv[])
{
	// argv[1]: # of agents

	// Read Data - Construct Graph of agents
	// in header file agentGraph.h we construct
	// the vector of participant-agents with
	// all the information needed
	read_data(atoi(argv[1]));	// in agentGraph.h

	for (auto it = agents.begin(); it != agents.end(); ++it)
	{
		(*it).displayAgent();
	}
	cout << agents.size() << endl;

	cout << connected_nodes(288,316) << endl;

	// Agent* g0 = getAgent(&agents, 285);
	// vector<Agent*> v = g0->getNeighbors();

	// if (v.empty()) { cout << "empty list!\n"; }
	// else { cout << "Not empty list\n"; }
	// Agent* vi;
	// for (auto it = v.begin(); it != v.end(); ++it)
	// {	
	// 	vi = *it;
	// 	cout << vi->getID() << " ";
	// }

	// cout << endl;

	return 0;
}
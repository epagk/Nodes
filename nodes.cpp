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

	// int rand1 = rand() % agents.size();
 	// 	Agent g0 = agents.at(rand1);
 	// 	cout << "Randomly picked: " << g0.getID() << endl;

	// vector<Agent*> v = g0.getNeighbors();

	// for (auto it = v.begin(); it != v.end(); ++it)
	// {	
	// 	cout << (*it)->getID() << " ";
	// }

	cout << endl;

	return 0;
}
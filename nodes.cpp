#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "agent.h"
#include "agentGraph.h"

using namespace std;

vector<Agent> agents;
vector<pair<int, int>>	edges;

int main(int argc, char** argv)
{
	cout << "Num of agents: " << argv[1] << endl;
	
	read_data();	// Read Data
	set_edges();	// Construct the Graph


	for (auto it = agents.begin(); it != agents.end(); ++it)
	{
		(*it).displayAgent();
	}

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
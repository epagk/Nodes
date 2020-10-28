#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "agent.h"
#include "agentGraph.h"

using namespace std;

vector<Agent> agents;
vector<pair<int, int>>	edges;
vector<Agent> agentsFinal;

int main()
{
	
	read_data();	// Read Data
	// set_edges();	// Construct the Graph


	for (auto it = agentsFinal.begin(); it != agentsFinal.end(); ++it)
	{
		(*it).displayAgent();
	}
	cout << agentsFinal.size() << endl;

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
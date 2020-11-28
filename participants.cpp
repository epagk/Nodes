#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "agent.h"
#include "agentGraph.h"

using namespace std;

vector<Agent> agents;
float drivePercentage;
int agentsNum;

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		cout << "Some arguments are missing!" << endl;
		return 0;
	}

	// argv[1]: # of agents - participants
	// argv[2]: percentage of drivers
	agentsNum = atoi(argv[1]);
	drivePercentage = atoi(argv[2]);

	// Read Data - Construct Graph of agents
	// in header file agentGraph.h we construct
	// the vector of participant-agents with
	// all the information needed
	read_data();

	for (auto it = agents.begin(); it != agents.end(); ++it)
		(*it).displayAgent();

	cout << endl;

	cout << "Agents # : " << agents.size() << endl;

	return 0;
}
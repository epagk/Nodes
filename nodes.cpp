#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "agent.h"
#include "agentGraph.h"

using namespace std;

vector<Agent>	agents;
vector<pair<int, int>>	edges;

void Agent::displayAgent()
{
    string gndr = (gender == true) ? "Male" : "Female";
    cout << "Agent: " << id << "\n\tGender: " << gndr << "\n\tAge: " << age << "\n\tEmployment: " << employment << "\n\tExtroversion rate: " << extroversion << endl;
    if (neighbors.empty()) { cout << "No neighbors found!\n"; }
    else { 
    	cout << "He has " << this->neighbors.size() << " neighbors\n";
	    // for(int i =0;i<this->neighbors.size();i++){
	    // 	cout << this->neighbors.at(i)->getID() << "\n";
	    // } 
	}
}

int binarySearch(vector<int> agents, int l, int r, int x) 
{ 
    if (r >= l) 
    { 
        int mid = l + (r - l) / 2; 
  
        if (agents[mid] == x) // We don't want to insert 
            return -1;		  // an element that already exists
  
        if (agents[mid] > x) 
            return binarySearch(agents, l, mid - 1, x); 
  
        return binarySearch(agents, mid + 1, r, x); 
    } 

    //if element not present
    // return where it should be placed
    return l; 
} 

// Set the features for each agent
void set_data(vector<int> sorted)
{
	srand ( time(NULL) );

	for (int i = 0; i < sorted.size(); ++i)
	{
		Agent ag;
		ag.setID(sorted.at(i));
		ag.setGender((rand() % 2 == 1) ? true : false);
		ag.setAge(18 + ( rand() % ( 40 - 18 + 1 ) ));

		int emp = ( rand() % ( 2  + 1 ) );
		string employment;

		switch (emp){
			case 0:
				ag.setEmployment("Student");
    			break;
    		case 1:
    			ag.setEmployment("Employee");
    			break;
    		case 2:
    			ag.setEmployment("Unemployed");
    			break;
		}

		ag.setExtroversion(rand() % 10 + 1);

		agents.push_back(ag);
	}
}

// Record all nodes by ID. Sort them increasingly
void read_data()
{
	vector<int> sorted;

	ifstream infile("0.edges");

	int a, b;
	while (infile >> a >> b)
	{
		int idx;

		idx = binarySearch(sorted, 0, sorted.size()-1, a);
		if (idx != -1)	// element Does not exists
		{
			auto it = sorted.insert(sorted.begin() + idx, a);
		}

		idx = binarySearch(sorted, 0, sorted.size()-1, b);
		if (idx != -1)	// element Does not exists
		{
			auto it = sorted.insert(sorted.begin() + idx, b);
		}

		edges.push_back(make_pair(a,b));
	}

	for (int i = 0; i < sorted.size(); i++) 
	{
		cout << sorted.at(i) << ' ';
	}

	
	cout << "\nNumber of nodes: " << sorted.size() << endl;
	set_data(sorted);
}

// void set_edges()
// {
// 	for (auto it = edges.begin(); it != edges.end(); ++it)
// 	{
// 		Agent a = getAgent(agents, (*it).first);
// 		Agent b = getAgent(agents, (*it).second);
// 		a.addNeighbor(b);
// 		b.addNeighbor(a);
// 		// Agent *A = &a;
// 		// Agent *B = &b;
// 		// A->addNeighbor(b);
// 		// B->addNeighbor(a);
// 	}


// }

int main()
{
	read_data();
	for (int i=0; i<edges.size();i++){
		cout << edges.at(i).first << "\t" << edges.at(i).second << "\n";
	}
	// set_edges();
	for (auto it = edges.begin(); it != edges.end(); ++it)
	{
		cout << it->first <<"\t" << it->second << "\n";
		Agent* a = getAgent(&agents, it->first);
		// assert(a->getID()!=-1);
		Agent* b = getAgent(&agents, it->second);
		// assert(b->getID()!=-1);
		a->addNeighbor(b);
		// cout <<a->neighbors.size() << "\n";
		b->addNeighbor(a);
		// cout <<b->neighbors.size() << "\n";
		// Agent *A = &a;
		// Agent *B = &b;
		// A->addNeighbor(b);
		// B->addNeighbor(a);
	}

	// for (auto it = agents.begin(); it != agents.end(); ++it)
	// {
	// 	(*it).displayAgent();
	// }

	Agent* g0 = getAgent(&agents, 345);
	

	vector<Agent*> v = g0->getNeighbors();

	if (v.empty()) { cout << "empty list!\n"; }
	else { cout << "Not empty list\n"; }
	Agent* vi;
	for (auto it = v.begin(); it != v.end(); ++it)
	{	
		vi = *it;
		cout << vi->getID() << " ";
	}

	cout << endl;

	return 0;
}
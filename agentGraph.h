#include <iostream>
#include <bits/stdc++.h> 
#include "agent.h" // header in local directory
#include <list>
#include <algorithm>

using namespace std;

extern vector<Agent> agents;
extern vector<pair<int, int>>	edges;
extern vector<Agent> agentsFinal;

Agent* getAgent(vector<Agent> &agents, int ID)
{	
	Agent* it;

	for (unsigned n = 0; n < agents.size(); n++)
	{	
		it = &(agents.at(n));
		if (it->getID() == ID){
			return it;
		}
	}

	Agent ag(-1, true, -1, "ghost", -1);		// if given ID does not exist
	Agent *ag_r = &ag;
	
	return ag_r;
}

void Agent::displayAgent()
{
    string gndr = (gender == true) ? "Male" : "Female";
    cout << "Agent: " << id << "\n\tGender: " << gndr << "\n\tAge: " << age << "\n\tEmployment: " << employment << "\n\tExtroversion rate: " << extroversion << endl;
    
    if (neighbors.empty()) { cout << "No neighbors found!\n"; }
    else {  cout << "\tNum of neighbors: " << this->neighbors.size() << endl; }
	
	// cout << "Neighbors: ";
	// Agent* n;
	// for (unsigned i = 0; i < neighbors.size(); ++i)
	// {
	// 	n = neighbors.at(i);
	// 	cout << n->getID() << " ";
	// }
	// cout << endl;
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

// Connect the Agents
void set_edges()
{
	for (auto it = edges.begin(); it != edges.end(); ++it)
	{
		Agent* a = getAgent(agents, it->first);
		Agent* b = getAgent(agents, it->second);
		a->addNeighbor(b);
	}
}

void BFS(int max) 
{ 
    srand ( time(NULL) );
    int count = 1;

	// Mark all the vertices as not visited 
    list<int> visited; 
  
    // Create a queue for BFS 
    list<Agent> queue; 
  
  	// Pick randomly an agent
    // Mark the current node as visited and enqueue it 
    int randomIndex = rand() % agents.size();
    Agent s = agents.at(randomIndex);
    cout << "randomly picked: " << s.getID() << endl;

    visited.push_back(s.getID());
    queue.push_back(s); 
    agentsFinal.push_back(s);
  
    while(!queue.empty()) 
    { 
        // Dequeue a vertex from queue and print it 
        s = queue.front(); 
        // cout << s.getID() << " ";
        queue.pop_front(); 
  
        // Get all adjacent vertices of the dequeued 
        // vertex s. If a adjacent has not been visited,  
        // then mark it visited and enqueue it 
        Agent* n;
		for (unsigned i = 0; i < s.getNeighbors().size(); ++i)
		{
			n = s.getNeighbors().at(i);
			if (find(visited.begin(), visited.end(), n->getID()) != visited.end() == 0 )
			{
				visited.push_back(n->getID());
				queue.push_back(*n);
				agentsFinal.push_back(*n);
				count++;
			}
			if ( count == max ) break;
		} 
		if ( count == max ) break;
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

	// for (int i = 0; i < sorted.size(); i++) 
	// {
	// 	cout << sorted.at(i) << ' ';
	// }

	
	cout << "Number of nodes: " << sorted.size() << endl;
	// set_data(sorted);

	Agent ag;
	for (int i = 0; i < sorted.size(); ++i)
	{
		ag.setID(sorted.at(i));
		agents.push_back(ag);
	}

	set_edges();
	BFS(100);
}

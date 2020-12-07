#include <iostream>
#include <bits/stdc++.h> 
#include "agent.h" // header in local directory
#include <list>
#include <algorithm>

using namespace std;

vector<Agent> nodes;
vector<pair<int, int>>	edges;
extern vector<Agent> agents;
extern float drivePercentage;
extern int agentsNum;

Agent* getAgent(vector<Agent> &v, int ID)
{	
	Agent* it;

	for (unsigned n = 0; n < v.size(); n++)
	{	
		it = &(v.at(n));
		if (it->getID() == ID){
			return it;
		}
	}

	Agent ag(-1, false, true, -1, "ghost", -1);		// if given ID does not exist
	Agent *ag_r = &ag;
	
	return ag_r;
}

// True if nodes with IDs a and b are connectes
// False otherwise
bool connected_nodes(int a, int b)
{
	for (int i = 0; i < edges.size(); ++i)
	{
		pair<int, int> edge = edges.at(i);
		if ( edge.first == a && edge.second == b ) { return true; }
		if ( edge.first == b && edge.second == a ) { return true; }
	}

	return false;
}

void Agent::displayAgent()
{
    string gndr = (gender == true) ? "Male" : "Female";
    string role = (driver == true) ? "Driver" : "Passenger";
    cout << "Agent: " << id << " " << role << "\n\tGender: " << gndr << "\n\tAge: " << age << "\n\tEmployment: " << 
    employment << "\n\tExtroversion rate: " << extroversion << endl;
    
    if (neighbors.empty()) { cout << "No neighbors found!\n"; }
    else {  cout << "\tNum of neighbors: " << this->neighbors.size() << endl; }

	cout << endl;
	
	// cout << "\tNeighbors: " << endl;
	// Agent* n;
	// float w;
	// for (unsigned i = 0; i < neighbors.size(); ++i)
	// {
	// 	n = neighbors.at(i).first;
	// 	w = neighbors.at(i).second;
	// 	cout << "\t(" << n->getID() << "," << setprecision(2) << w << ")";
	// }
	// cout << endl;
}


// Returns a file with enough number of nodes to satisfy 
// user's requirement
string randomFile()
{
	srand ( time(NULL) );

	vector<pair<string, int>> files; 	// first -> files name, second -> # of nodes in that file
	vector<int> indexes;

	files.push_back(make_pair("0.edges", 333));		// name of file - # of nodes
	files.push_back(make_pair("107.edges", 1034));
	files.push_back(make_pair("348.edges", 224));
	files.push_back(make_pair("414.edges", 150));
	files.push_back(make_pair("686.edges", 168));
	files.push_back(make_pair("698.edges", 61));
	files.push_back(make_pair("1684.edges", 786));
	files.push_back(make_pair("1912.edges", 747));
	files.push_back(make_pair("3437.edges", 534));
	files.push_back(make_pair("3980.edges", 52));

	for (int i = 0; i < files.size(); ++i)
	{
		pair<string, int> p = files.at(i);
		if (p.second >= agentsNum)
			indexes.push_back(i);
	}

	int r = rand() % indexes.size();
	return files.at(indexes.at(r)).first;	// name of file
}

int binarySearch(vector<int> v, int l, int r, int x) 
{ 
    if (r >= l) 
    { 
        int mid = l + (r - l) / 2; 
  
        if (v[mid] == x) // We don't want to insert 
            return -1;		  // an element that already exists
  
        if (v[mid] > x) 
            return binarySearch(v, l, mid - 1, x); 
  
        return binarySearch(v, mid + 1, r, x); 
    } 

    //if element not present
    // return where it should be placed
    return l; 
} 

// Set the features for each agent
void set_data()
{
	srand ( time(NULL) );

	drivePercentage /= 100;
	int driversNum = ceil(drivePercentage*agentsNum);	// Number of Drivers

	vector<int> drivers;	// IDs of drivers
	vector<int> indexes;

	for (int i = 0; i < agents.size(); ++i)
		indexes.push_back(i);

	random_shuffle(indexes.begin(), indexes.end()); // randomly shuffle indexes

	// Pick first (driverNum) random indexes
	// The IDs in vector drivers are sorted!
	for (int i = 0; i < driversNum; ++i)
	{
		int val = agents.at(indexes.at(i)).getID();
		int idx = binarySearch(drivers, 0, drivers.size()-1, val);
		drivers.insert(drivers.begin() + idx, val);
	}

	for (auto it = agents.begin(); it != agents.end(); ++it)
	{
		if ( count(drivers.begin(), drivers.end(), (*it).getID()) )		// Agent belons in Driver's set
			(*it).setDriver(true);
		else
			(*it).setDriver(false);

		(*it).setGender((rand() % 2 == 1) ? true : false);	// Participant's Gender

		int age = 18 + ( rand() % ( 40 - 18 + 1 ) );	// Participant's Age
		(*it).setAge(age);

		float p = ((double) rand() / (RAND_MAX));	// Πrobability

		if (age >= 18 && age <= 25)	// Aged 18-25
		{
			if (p <= 0.8)
				(*it).setEmployment("Student");		// Probability 0.8

			if (p > 0.8 && p <= 0.9)
				(*it).setEmployment("Employee");	// Probability 0.1
			
			if (p > 0.9)
				(*it).setEmployment("Unemployed");	// Probability 0.1
		}

		if (age >= 26 && age <=30)	// Aged 26-30
		{
			if (p <= 0.25)
				(*it).setEmployment("Student");		// Probability 0.25

			if (p > 0.25 && p <= 0.5)
				(*it).setEmployment("Employee");	// Probability 0.25
			
			if (p > 0.5)
				(*it).setEmployment("Unemployed");	// Probability 0.5
		}

		if (age >= 31)	// Aged 31-40
		{
			if (p <= 0.1)
				(*it).setEmployment("Student");		// Probability 0.1

			if (p > 0.1 && p <= 0.3)
				(*it).setEmployment("Unemployed");	// Probability 0.2
			
			if (p > 0.3)
				(*it).setEmployment("Employee");	// Probability 0.7
		}

		(*it).setExtroversion(rand() % 10 + 1);
	}

}

// Connect the nodes. Set new neighbor for each node
void set_edges()
{
	for (auto it = edges.begin(); it != edges.end(); ++it)
	{
		Agent* a = getAgent(nodes, it->first);
		Agent* b = getAgent(nodes, it->second);

		// Pair (a,b) 
		a->addNeighbor(b, ((double) rand() / (RAND_MAX)));	// random weight! Just for now!

		// Pair (b,a) is a different edge for now. This is why we don't match symmetrically b->a 
	}
}

// Use BFS in order to pick a random subgraph with the number of nodes asked by user
void BFS() 
{ 
    srand ( time(NULL) );
    int count = 1;

	// Mark all the vertices as not visited 
    list<int> visited; 
  
    // Create a queue for BFS 
    list<Agent> queue; 
  
  	// Pick randomly an agent
    // Mark the current node as visited and enqueue it 
    int randomIndex = rand() % nodes.size();
    Agent s = nodes.at(randomIndex);

    visited.push_back(s.getID());
    queue.push_back(s); 
    agents.push_back(s);
  
    while(!queue.empty()) 
    { 
        // Dequeue a vertex from queue and print it 
        s = queue.front(); 
        queue.pop_front(); 
  
        // Get all adjacent vertices of the dequeued 
        // vertex s. If a adjacent has not been visited,  
        // then mark it visited and enqueue it 
        Agent* n;
		for (unsigned i = 0; i < s.getNeighbors().size(); ++i)
		{
			n = s.getNeighbors().at(i).first;
			if (find(visited.begin(), visited.end(), n->getID()) != visited.end() == 0 )
			{
				visited.push_back(n->getID());
				queue.push_back(*n);
				agents.push_back(*n);
				count++;
			}
			if ( count == agentsNum ) break;
		} 
		if ( count == agentsNum ) break;
    } 
} 

// Record all nodes by ID. Sort them increasingly
void read_data()
{
	vector<int> sorted;
	
	// do while is used in case that user's request for number of agents it's not satisfied
	// due to BFS failure. 
	do{
		sorted.clear();
		nodes.clear();
		agents.clear();
		edges.clear();

		string filename = "Facebook Graph/facebook/" + randomFile();	// Pick a graph of a random file
		ifstream infile(filename);

		int a, b;
		while (infile >> a >> b)	// a,b are connected nodes (neighbors)
		{
			int idx;

			idx = binarySearch(sorted, 0, sorted.size()-1, a);	// Search for a

			if (idx != -1)	// element Does not exists
				auto it = sorted.insert(sorted.begin() + idx, a);	// insert new node in vector

			idx = binarySearch(sorted, 0, sorted.size()-1, b);	// Search for b

			if (idx != -1)	// element Does not exists
				auto it = sorted.insert(sorted.begin() + idx, b);	// insert new node in vector

			edges.push_back(make_pair(a,b));
		}

		Agent ag;
		for (int i = 0; i < sorted.size(); ++i)
		{
			ag.setID(sorted.at(i));
			nodes.push_back(ag);
		}

		set_edges();	// set connections between nodes
		BFS();			// reduce agents to number asked
	}while(agents.size() != agentsNum);

	set_data();		// give features to agents
}

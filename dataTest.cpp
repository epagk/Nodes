#include<iostream>
#include <vector>
#include <fstream>

using namespace std;

vector< pair<int,int> > edges;

void read_data()
{
	ifstream infile("0.edges");

	int a, b;
	while (infile >> a >> b)
	{
		edges.push_back(make_pair(a,b));
	}
}


int main()
{
	read_data();
	vector<int> indexes;

	for (int i = 0; i < edges.size(); ++i)
	{
		bool flag = false;	// pair not found

		pair<int, int> edge = edges.at(i);
		int a = edge.first;
		int b = edge.second;

		for (int j = 0; j < edges.size(); ++j)
		 {
		 	pair<int, int> conn = edges.at(j);
		 	int v = conn.first;
			int w = conn.second;

			if ( (a == w) && (b == v) ) { flag = true; }
		 } 

		 if (!flag) { indexes.push_back(i); }	// if no pair found
	}

	if (indexes.empty()) { cout << "All good\n"; }
	else { cout << "Problems detected\n"; }
	cout << "# of directed edges: " << indexes.size() << endl;
	for (int i = 0; i < indexes.size(); ++i)
	{
		cout << "Index: " << indexes.at(i) << endl;
	}

	return 0;
}
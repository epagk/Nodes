#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

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

int main()
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
	}

	for (int i = 0; i < sorted.size(); i++) 
	{
		cout << sorted.at(i) << ' ';
	}
	
	cout << "\nNumber of nodes: " << sorted.size() << endl;

	return 0;
}
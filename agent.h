#ifndef AGENT_H
#define AGENT_H

#include <iostream>
#include <string>

using namespace std;

class Agent
{
	private:
		int id;			           // Identifier of agent
		bool gender;	         // Male = True or Female = False
		int age;	             // age of agent
    string employment;     // employment of agent
		float extroversion;		 // extroversion of agent
    vector<Agent> neighbors;
	
	public:
		Agent(int ID, bool g, int a, string e, float ext) { // Constructor with parameters
		  id = ID;
	    gender = g;
      age = a;
	    employment = e;
      extroversion = ext;
	  }

	  Agent(){ }

    public:
    	// Setter
    	void setID(int ID) {
      		id = ID;
    	}

    	// Getter
    	int getID() {
      		return id;
    	}

    	// Setter
    	void setGender(bool g) {
      		gender = g;
    	}

    	// Getter
    	bool getGender() {
      		return gender;
    	}

    	// Setter
    	void setAge(int a) {
      		age = a;
    	}

    	// Getter
    	int getAge() {
      		return age;
    	}

    	// Setter
    	void setEmployment(string e) {
      		employment = e;
    	}

    	// Getter
    	string getEmployment() {
      		return employment;
    	}

    	// Setter
    	void setExtroversion(float ext) {
      		extroversion = ext;
    	}

    	// Getter
    	float getExtroversion() {
      		return extroversion;
    	}

      void addNeighbor(Agent a)
      {
        cout << "in addNeighbor! Connect: " << id << " with: " << a.getID() << endl;
        neighbors.push_back(a);
      }

      vector<Agent> getNeighbors()
      {
        return neighbors;
      }

      void displayAgent();
};

#endif
#ifndef AGENT_H
#define AGENT_H

#include <iostream>
#include <string>

using namespace std;

class Agent
{
	private:
		int id;			           // Identifier of agent
    bool driver;           // True if driver or Flase otherwise
		bool gender;	         // Male = True or Female = False
		int age;	             // age of agent
    string employment;     // employment of agent
		float extroversion;		 // extroversion of agent
    vector<pair<Agent*, float>> neighbors;  // neighbor + weight
	
	public:
		Agent(int ID, bool d, bool g, int a, string e, float ext) // Constructor with parameters
    {
		  id = ID;
      driver = d;
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

      //Setter
      void setDriver(bool d){
          driver = d;
      }

      // Getter
      bool getDriver(){
          return driver;
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

      void addNeighbor(Agent* a, float weight)
      {
        pair<Agent*, float> n = make_pair(a, weight);
        neighbors.push_back(n);
      }

      vector<pair<Agent*, float>> getNeighbors()
      {
        return neighbors;
      }

      void displayAgent();
};

#endif
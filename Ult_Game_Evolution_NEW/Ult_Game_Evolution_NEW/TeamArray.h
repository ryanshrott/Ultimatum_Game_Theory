#include <iostream>
#include <string>
#include "Team.h"
#include <math.h>


#ifndef TeamArray_h
#define TeamArray_h

class TeamArray
{
private:
	Team* m_data; // a dynamic TeamArray of Team objects which I initialize on the heap 
	int m_size;
public:
	TeamArray(); //Default Constructor 
	TeamArray(int size); // overloaded constructor with a user inputed size argument 
	TeamArray(const TeamArray &data); // copy constructor 
	~TeamArray(); // Destructor 

	bool operator == (const TeamArray& p) const; // Equality compare operator.
	TeamArray& operator = (const TeamArray& arr); // Assignment operator.

	int size() const;

	void SetElement(const int element, const Team& pnt); //sets a user specified element in the TeamTeamArray to a user specified value 

	Team GetElement(const int element) const;

	Team& operator [] (int index); // a more robust implementation of setter and getter functions 
	Team& operator [] (int index) const; // must be used when declaring a constant TeamArray since a constant object cannot invoke a nonconstant method

										 // Returns the richest team amongst the teams 
	Team richest() const;  // the function only observes member variables and DOES NOT change them 
						   // returns the richest

						   // Returns the poorest team amongst the teams 
	Team poorest() const; // the function only observes member variables and DOES NOT change them 
						  // returns the poorest

	int tot_sum(int numTeams) const; 
	
	float average(int numTeams) const; // returns the average sum amongst the teams 

	float standardD(int numTeams) const; // returns the standard deviation of the money distribution 

	// Honesty Analysis 

	double avgHonesty() const; // returns the average number of gold stickers 

	//friend void interact(Team& teamA, Team& teamB, const TeamArray& data, int& exchanges);

};

#endif
#ifndef Team_h
#define Team_h

#include <iostream>
#include <string>

using namespace std;

// Remark: A well defined strategy is a line in R^2. Let the x-axis represent the amount the team gives, and let the y-axis 
// represent the amount the team accepts. We could also represent a strategy as a 2-D point by considering the point:
// (amount team gives, min amount team accepts). The class implementation below generalizes this notion. Instances of this class
// are used in the Main() function. 

class Team // TEAM strategy 
{
private:
	int m_give; // the amount a team will give :: CONST VAR
	int m_min_accept; // the minimum amount a team will accept :: CONST VAR
	bool m_decline; // stores TRUE if previous round was REJECTION, and FALSE otherwise :: DYNAMIC VARIABLE 
	long m_sum; // stores the total amount of money the team has :: DYNAMIC VARIABLE 

public:
	//Default Constructor: Sets member variables to their null space
	Team();

	// Overloaded Input Constructor 
	Team(int g, int a, bool d, long s);

	// Copy Constructor: can perform a deep copy of instances of a class to another instance of the same class
	Team(const Team &team);

	// Destructor 
	~Team();

	// Accessor Functions

	int A() const; // returns m_give
	int G() const; // returns m_min_accept
	int D() const; // returns m_min_decline
	long S() const; // returns m_sum

	// Setter Function

	void A(const int a); // assigns m_give to a 
	void G(const int g); // assigns m_min_accept to g
	void G(const bool d); // assigns m_decline to d
	void S(const long s); // assigns m_sum to s

	// Printing a strategy to the console

	friend ostream& operator << (ostream& os, const Team& team);

	// Dynamic Interaction Function 

	friend void interact(Team& teamA, Team& teamB); 
	// Remark: The Function is NOT constant since the decline value and sum may change 
	// Remark: We assume that team A is the giver and team B is the acceptor 

	// Operator Overloading 

	bool operator == (const Team& p) const; // Equality compare operator.
	bool operator != (const Team& p) const; // NOT equal compare operator.
	Team& operator = (const Team& source); // Assignment operator.

};

#endif 

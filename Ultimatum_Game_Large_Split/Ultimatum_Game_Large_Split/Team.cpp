// Implementation of Member Functions in the Team Class

#include "Team.h"

//Default Constructor: Sets member variables to their null space
Team::Team() : m_give(0), m_min_accept(0), m_decline(false), m_sum(0) // sets the member variables to the origin in R^2
{}

// Overloaded Input Constructor 
Team::Team(int g, int a, bool d, long s) : m_give(g), m_min_accept(a), m_decline(d), m_sum(s)
{}

// Copy Constructor: can perform a deep copy of instances of a class to another instance of the same class
Team::Team(const Team &team)
{
	m_give = team.m_give; // perform a deep copy 
	m_min_accept = team.m_min_accept; // perform a deep copy
	m_decline = team.m_decline; // perform a deep copy
	m_sum = team.m_sum;
}

// Destructor 
Team::~Team()
{}

// Accessor Functions

int Team::A() const // returns m_give
{
	return m_give;
}
int Team::G() const // returns m_min_accept
{
	return m_min_accept;
}
int Team::D() const // returns m_decline
{
	return m_decline;
}
long Team::S() const // returns m_sum
{
	return m_sum;
}

// Setter Function

void Team::A(const int a) // assigns m_give to a 
{
	m_give = a;
}
void Team::G(const int g) // assigns m_min_accept to g
{
	m_min_accept = g;
}

void Team::G(const bool d) // assigns m_decline to d
{
	m_decline = d;
}
void Team::S(const long s) // assigns m_sum to s
{
	m_sum = s;
}
// Printing a strategy to the console 

ostream& operator<< (ostream& os, const Team& team)
{
	cout << "(" << team.m_give << ", " << team.m_min_accept << ", " << team.m_decline << ", " << team.m_sum << ")" << endl;

	return os; // returns the output stream 
}

 //Interactions 

void interact(Team& teamA, Team& teamB)
{
	if ((teamA.m_give >= teamB.m_min_accept) && (teamB.m_decline == false))
	{
		teamA.m_sum += 100 - teamA.m_give;
		teamB.m_sum += teamA.m_give;
	}
	else if (teamB.m_decline == true)
	{
		teamA.m_sum += 50;
		teamB.m_sum += 50;
		teamB.m_decline = false;
	}
	else
	{
		teamB.m_decline = true;
	}
}

//void interact(Team& teamA, Team& teamB)
//{
//	if (teamA.m_give >= teamB.m_min_accept)
//		teamA.m_sum += 100 - teamA.m_give;
//		teamB.m_sum += teamA.m_give;
//}

// Operator Overloading 

bool Team::operator == (const Team& team) const // Equality compare operator.
{
	return((m_give == team.m_give) && (m_min_accept == team.m_min_accept) && (m_decline == team.m_decline) && (m_sum == team.m_sum)); // return true if both teams give and accept the same amount 
}

bool Team::operator != (const Team& team) const // NOT equal compare operator.
{
	return(!((*this) == team));
}

Team& Team::operator = (const Team& source) // Assignment operator.
{
	if (this != &source) // precludes self assigment 
	{
		m_give = source.G(); // copy the data over into the current instance
		m_min_accept = source.A(); // copy the data over into the current instance
		m_decline = source.D();
		m_sum = source.S();
	}
	return *this; // return the current object to enable cascading effect 
}


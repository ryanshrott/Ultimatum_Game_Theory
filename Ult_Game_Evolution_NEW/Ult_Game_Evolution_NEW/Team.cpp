// Implementation of Member Functions in the Team Class

#include "Team.h"

//Default Constructor: Sets member variables to their null space
Team::Team() : m_give(0), m_min_accept(0), m_decline(false), m_sum(0), m_sticker(0), m_Dev(0), m_games(0), m_risk(0.0) // sets the member variables to the origin in R^2
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	vector<double> weights;
	for (int i = 0; i < m_Dev; i++)
	{
		weights[i] = 1; // uniform distribution 
	}
	discrete_distribution<int> m_distribution(weights.begin(), weights.end());
}

// Overloaded Input Constructor 
Team::Team(int g, int a, bool d, long s, long gold, int dev, float r) : m_give(g), m_min_accept(a), m_decline(d), m_sum(s), m_sticker(gold), 
																	  m_Dev(dev), m_games(0), m_risk(r)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	vector<int> weights;
	for (int i = 0; i < m_Dev; i++)
	{
		weights[i] = (1/m_Dev) * exp(i/m_Dev); // probability of a lie as a function of the deviation from the truth 
	}
	discrete_distribution<int> m_distribution(weights.begin(), weights.end());
}

// Copy Constructor: can perform a deep copy of instances of a class to another instance of the same class
Team::Team(const Team &team)
{
	//cout << "copy invoked" << endl;
	m_give = team.m_give; // perform a deep copy 
	m_min_accept = team.m_min_accept; // perform a deep copy
	m_decline = team.m_decline; // perform a deep copy
	m_sum = team.m_sum;
	m_sticker = team.m_sticker;
	m_Dev = team.m_Dev;
	m_games = team.m_games;
	m_distribution = team.m_distribution;
	m_risk = team.m_risk;
}

// Destructor 
Team::~Team()
{}

// Accessor Functions

int Team::G() const // returns m_give
{
	return m_give;
}
int Team::A() const // returns m_min_accept
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

long Team::Gold() const // return m_sticker
{
	return m_sticker;
}

int Team::Dev() const
{
	return m_Dev;
}

float Team::R() const
{
	return m_risk;
}


// Setter Function

void Team::G(const int g) // assigns m_give to a 
{
	m_give = g;
}
void Team::A(const int a) // assigns m_min_accept to g
{
	m_min_accept = a;
}

void Team::D(const bool d) // assigns m_decline to d
{
	m_decline = d;
}
void Team::S(const long s) // assigns m_sum to s
{
	m_sum = s;
}
void Team::Gold(const long gold) // asigns m_sticker to gold
{
	m_sticker = gold;
}
void Team::Dev(const int dev)
{
	 m_Dev= dev; 
}
void Team::R(const float r)
{
	m_risk = r;
}
// Printing a strategy to the console 

ostream& operator<< (ostream& os, const Team& team)
{
	cout << "(" << team.m_give << ", " << team.m_min_accept << ", " << team.m_decline << ", " << team.m_sum << ", " 
		<< team.m_sticker << ", " << team.m_Dev<< ", " << team.m_risk << ")" << endl;

	return os; // returns the output stream 
}
//Interactions

// No declining: basic 

void interact(Team& teamA, Team& teamB, int &exchanges)
{
	if (teamA.m_give >= teamB.m_min_accept)
	{
	teamA.m_sum += 100 - teamA.m_give;
	teamB.m_sum += teamA.m_give;
	exchanges++;
	}	
}


// Decline effect 
//void interact(Team& teamA, Team& teamB, int &exchanges) // with declining effect 
//{
//	if ((teamA.m_give >= teamB.m_min_accept) && (teamB.m_decline == false))
//	{
//		teamA.m_sum += 100 - teamA.m_give;
//		teamB.m_sum += teamA.m_give;
//		exchanges++;
//	}
//	else if (teamB.m_decline == true)
//	{
//		teamA.m_sum += 50;
//		teamB.m_sum += 50;
//		teamB.m_decline = false;
//		exchanges++;
//	}
//	else
//	{
//		teamB.m_decline = true;
//	}
//}

//Risk vs. Reward Model: Deviation for each team is public knowledge 
//void interact(Team& teamA, Team& teamB, int &exchanges) // no declining 
//{ 
//	bool told_truth = false; // becomes true if teamB tells the truth 
//
//	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
//	default_random_engine generator(seed);
//
//	int REAL_B_min_accept = teamB.m_min_accept - (teamB.m_Dev - teamB.m_distribution(generator)); // this is the actual amount teamB will accept 
//	
//	int D_tilde; // an estimate of the deviation of teamB is D_tilda =  min_accept - Prob(telling truth) * D_max; teamA makes this estimation based on an inference 
//	int D_max = 16; 
//
//	if (teamB.m_games < 4)
//	{
//		D_tilde = 8; // not enough sample data to say anything useful, so assume average honesty 
//	}
//	else
//	{
//		D_tilde = (int)((D_max)*(1 - (teamB.m_sticker) / (teamB.m_games + 1))); // teamA will make an estimate of teamB's deviation  
//	}
//
//	vector<double> weights(teamB.m_Dev);
//	double sum = 0;
//	for (int i = 0; i < teamB.m_Dev; i++)
//	{
//		weights[i] = (1 / teamB.m_Dev) * exp(i / (teamB.m_Dev + 0.1)); // probability of a lie as a function of the deviation from the truth 
//		sum += weights[i];
//	}
//	// Normalize to find probabilities
//	vector<double> probabilities(teamB.m_Dev);
//	for (int i = 0; i < teamB.m_Dev; i++)
//	{
//		probabilities[i] = weights[i] / sum; // normalizing 
//	}
//	vector<double> outcomes(teamB.m_Dev);
//	for (int i = 0; i < teamB.m_Dev; i++)
//	{
//		outcomes[i] = i; // outcome space 
//	}
//	double expectedAccept = inner_product(weights.begin(), weights.end(), outcomes.begin(), 0);
//
//	teamA.m_give = expectedAccept + teamA.m_risk; // depends on teamA's risk tolerance 
//
//	if (teamA.m_give >= REAL_B_min_accept) // if the amount team A gives is greater than or equal to the REAL amount team B will accept, do stuff 
//	{
//		teamA.m_sum += 100 - teamA.m_give;
//		teamB.m_sum += teamA.m_give;
//		exchanges++;
//		teamB.m_games++;
//		told_truth = true;
//	}
//	// Stickers
//	if (told_truth = true)
//	{
//		teamB.m_sticker++;
//	}
//}

// Operator Overloading 

bool Team::operator == (const Team& team) const // Equality compare operator.
{
	return((m_give == team.m_give) && (m_min_accept == team.m_min_accept) && (m_decline == team.m_decline) && (m_sum == team.m_sum) && (m_sticker == team.m_sticker) && (m_Dev == team.m_Dev) && (m_risk == team.m_risk)); // return true if both teams give and accept the same amount 
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
		m_sticker = source.Gold();
		m_Dev = source.Dev();
		m_risk = source.R();
	}
	return *this; // return the current object to enable cascading effect 
}



float percentDiff(Team& teamA, Team& teamB)
{
	return (float)(100.0 *(teamA.m_sum - teamB.m_sum) / (teamB.m_sum));
}

int range(Team& teamA, Team& teamB)
{
	return (teamA.S() - teamB.S());
}
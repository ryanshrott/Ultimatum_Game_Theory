// Defintions for TeamArray.h

#include "TeamArray.h"

TeamArray::TeamArray() // Default Constructor 
{
	m_size = 10;
	m_data = new Team[m_size]; // the default constructor allocates 10 elements 
							   //cout << "Default called" << endl;
}

TeamArray::TeamArray(int size)
{
	m_size = size;
	m_data = new Team[m_size]; // allocates the number of elements specified by the size input argument 
							   //cout << "Overloaded constructor called" << endl;
}

TeamArray::TeamArray(const TeamArray &data)
{
	m_size = data.m_size; // set m_size to the size of the data which should be copied
	m_data = new Team[m_size]; // allocate memory on the heap for m_data to be copied from the new data TeamArray 
	for (int i = 0; i < m_size; ++i)
	{
		m_data[i] = data.m_data[i]; // copy each element one at a time 
	}
	//cout << "Copy called" << endl;
}

TeamArray:: ~TeamArray()
{
	delete[] m_data;
	//cout << "Destructor called!" << endl;
}

bool TeamArray::operator == (const TeamArray& arr) const
{ // two TeamArrays are equal iff each element is equal 
	bool true_false = false; // true if and only if each element is identical;
	if (arr.m_size == m_size) // a necessary condition for equality 
	{
		true_false = true; // becomes false if there exists a non equal element 

		for (int i = 0; i < m_size; ++i)
		{
			if (m_data[i] != arr.m_data[i]) // check each data member, if one is not equal-> set FALSE 
			{
				true_false = false; // at least one element is not the same 
				break; // since at least one element is not the same, the TeamArrays are not equal 
			}
		}
	}
	return (true_false);
}

TeamArray& TeamArray::operator = (const TeamArray& arr) // Assignment operator
{
	if (*this == arr) // if the current instance is equal (as defined above) to the RHS, return the current object 
	{
		return *this;
	}
	else if (m_size == arr.m_size)
	{
		delete[] m_data; // clear the old TeamArray from the heap 
		m_data = new Team[m_size];// reassign a fresh address on the heap that can be filled using the assignment operator 
		for (int i = 0; i < m_size; ++i)
		{
			m_data[i] = arr.m_data[i]; // assign each element on the RHS to the current instance of the Team class 
		}
	}
	return *this;
}

int TeamArray::size() const
{
	return(m_size); // returns the size of the specified TeamArray 
}

void TeamArray::SetElement(const int element, const Team& pnt) // sets an element in the current instance to a user specified Team
{
	if (element > -1 && element < m_size)
		m_data[element] = pnt; // set the specified element of the current instance to a specified 2-D pnt in \mathbb{R}^2
}

Team TeamArray::GetElement(const int element) const
{
	return(m_data[element]);
}

Team& TeamArray::operator [] (int index)
{
	if (index > -1 && index < m_size)
	{
		return(m_data[index]);
	}
	else
	{
		return(m_data[0]);
	}

}

Team& TeamArray::operator [] (int index) const //must be used when declaring a constant TeamArray since a constant object cannot invoke a nonconstant method
{
	if (index > -1 && index < m_size)
	{
		return(m_data[index]);
	}
	else
	{
		return(m_data[0]);
	}
}

// Returns the richest team amongst the teams 
Team TeamArray::richest() const  // the function only observes member variables and DOES NOT change them 
{
	long max_sum = 0;
	Team TeamRichest;
	for (int i = 0; i < 51 * 51; ++i)
	{
		if ((m_data[i]).S() > max_sum)
		{
			max_sum = (m_data[i]).S();
			TeamRichest = m_data[i];
		}
	}
	return(TeamRichest);
}


// Returns the poorest team amongst the teams 
Team TeamArray::poorest() const // the function only observes member variables and DOES NOT change them 
{
	long min_sum = 9999999999; // some massive number
	Team TeamPoorest;
	for (int i = 0; i < 51 * 51; ++i)
	{
		if ((m_data[i]).S() < min_sum)
		{
			min_sum = (m_data[i]).S();
			TeamPoorest = m_data[i];
		}
	}
	return(TeamPoorest);
}

int TeamArray::tot_sum(int numTeams) const
{
	int sum = 0;
	for (int i = 0; i < numTeams; ++i)
	{
		sum += m_data[i].S();
	}
	return sum;
}
// Returns the average sum amongst the teams
float TeamArray::average(int numTeams) const
{
	long sum = 0; 

	for (int i = 0; i < numTeams; i++)
	{
		sum += m_data[i].S(); 
	}

	return (float)(sum / numTeams);
}

float TeamArray::standardD(int numTeams) const
{
	long sum = 0;
	float average;
	for (int i = 0; i < numTeams; i++)
	{
		sum += m_data[i].S();
	}

	average =  (float)(sum / numTeams);
	
	float sum1 = 0;
	for (int i = 0; i < numTeams; i++)
	{
		sum1 += (float)(m_data[i].S() - average)* (float)(m_data[i].S() - average);
	}


	return (float)(sqrt((float)(sum1/numTeams)));
}

double TeamArray::avgHonesty() const // returns the average number of gold stickers amongst the population 
{
	long sum = 0;
	for (int i = 0; i < 51 * 51; i++)
	{
		sum += m_data[i].Gold();
	}

	double average = (double)((double)(sum) / (double)(51 * 51));

	return average; 
}

// Interaction function with honesty (no decline effects)
//void interact(Team& teamA, Team& teamB, const TeamArray& data, int& exchanges) // no declining effects 
//{
//
//	if (((teamA.D() == 0) && (39 < teamA.G() < 51)) || ((teamA.D() == 0) && (14 < teamA.G() < 40))
//		|| ((teamA.D() == 0) && (-1 < teamA.G() < 15))) // occurs if and only if teamA is honest 
//	{
//		teamA.Gold(teamA.Gold() + 1); // increase the number of honesty stickers teamA owns 
//	}
//	else // if team A is dishonest decrease the sticker count 
//	{
//		teamA.Gold(teamA.Gold() - 1); 
//	}
//	if (teamA.Gold() >= data.avgHonesty())  // if team A is more honest than the average honesty level, 
//											// then team B will trust team A and the interaction may occur
//	{
//		if (teamA.G() >= teamB.A()) // necessary conditions for interaction
//		{
//			teamA.S(teamA.S() + 100 - teamA.G());
//			teamB.S(teamB.S() + teamA.G());
//			exchanges++;
//		}
//	}
//}

// Premise of implementation: Each team has a deviation measure 

// Question: Is honest signalling a necessary condition for victory? Under which conditions does honest signalling work? 
// Does it ever pay off to be dishonest? Does there exist a threshold honesty level? What is it? 
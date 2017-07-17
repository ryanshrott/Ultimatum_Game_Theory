// This program will extend the idea of team strategies to a broader scope in the ultimatum game 

#include "TeamArray.h"
#include <ctime> // for random number generator 
#include <random>
#include <iterator>
#include <vector>
#include <algorithm>
#include <type_traits>


#define rounds 10000000 // macro for number of games played 

void basic(TeamArray& teamData);
void evolution(void);

int main()
{

	int give[11];
	int min_accept[11]; 

	// Remark: There will be 11*11 possible strategies and therefore 121 teams 

	TeamArray teamData(11 * 11);

	for (int a = 0; a < 11; a++)
	{
		give[a] = 5 * a;
	}

	for (int g = 0; g < 11; g++)
	{
		min_accept[g] = 5 * g;
	}

	int i = 0;
	for (int a = 0; a < 11; a++)
	{
		for (int g = 0; g < 11; g++)
		{
			
			Team team(give[a], min_accept[g], false, 0); // assigns 121 teams into the teamData array 
			Team temp = team;
			teamData[i] = temp;
			i++;
		}
	}

	// Implementation 1: BASIC MODEL: Choose a random team, then choose another random team, then call the interact function. Repeat. 

	//basic(teamData);

	// Implementation 2: Evolutionary Model: Same as basic model except probability of being choosen becomes a function of current sum 

	evolution();

	return 0;
} // END MAIN()

void basic(TeamArray& teamData) //Choose a random team, then choose another random team, then call the interact function.Repeat.
{
	default_random_engine randomGenerator((unsigned int)time(NULL));
	uniform_int_distribution<int> rand120(0, 120);

	int* RandA;
	int* RandB;

	RandA = new int[rounds];
	RandB = new int[rounds];

	for (int i = 0; i < rounds; ++i)
	{
		RandA[i] = rand120(randomGenerator); // generates random numbers from 0 to 120 (121 elements)
	}

	for (int i = 0; i < rounds; ++i)
	{
		RandB[i] = rand120(randomGenerator); // generates random numbers from 0 to 120 (121 elements)
	}

	for (int i = 0; i < rounds; i++)
	{
		interact(teamData[RandA[i]], teamData[RandB[i]]);
	}

	delete[] RandA;
	delete[] RandB;

	cout << "The richest team in the BASIC MODEL is: " << teamData.richest() << endl;
	cout << "The poorest team in the BASIC MODEL is: " << teamData.poorest() << endl;
}

template< class InputIt >

void evolution(void)
{
	cout << "test" << endl;
}
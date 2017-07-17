// This program will extend the idea of team strategies to a broader scope in the ultimatum game 

// Ideas to explore: Who makes the most deals for both models? Total number of deals for both models? Does the richest provide the most? 
// Does the poorest provide the least? How do the fair and how do the greedy do? How can I force the richest to be the fairest? 

// Honest signalling? Each team has a constant statement stored. The statement measures the honesty of the team. If a team tells the truth, then 
// they get a gold sticker. If they lie, they lose a gold sticker. Teams with positive number of gold stickers gain benifits. Teams with negative number
// of gold stickers have adverse effects. 


#include "TeamArray.h"
#include <ctime> // for random number generator 
#include <random>
#include <iterator>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <iostream>
#include <chrono>
#include <random>
#include <functional>
#include <array>
#include <fstream>

using namespace std;

#define rounds 100000 // macro for number of games played 

void basic(TeamArray& teamData);
void evolution(TeamArray& teamData);

using namespace std;

int main()
{

	int give[51];
	int min_accept[51];
	int deviation[51];

	// Remark: There will be 51*51 possible strategies and therefore 51*51 teams 

	TeamArray teamData(51 * 51);

	for (int j = 0; j < 51; j++)
	{
		give[j] = j;
		min_accept[j] = j;
	}


	int i = 0;
	for (int g = 0; g < 51; g++)
	{
		for (int a = 0; a < 51; a++)
		{
			Team team(give[g], min_accept[a], false, 0, 0, 0, 0); // assigns 51*51 teams into the teamData array 
			Team temp = team;
			teamData[i] = temp;
			i++;
		}
	}

	//cout << teamData[0] << endl;
	// Setting deviation for each team 
	// Assume the deviation of a team  increases as the min_accept value increases

	for (int i = 0; i < 51 * 51; i++)
	{
		teamData[i].Dev(teamData[i].A()/3.0); // set the deviation to 1/3 the minimum amount you will accept; lie more as the minimum amount you accept increases 
	}
	//cout << teamData[0] << endl;

	// Setting risk tolerance for each team
	for (int i = 0; i < 51 * 51; i++)
	{
		if (teamData[i].G() <= 10) // very risky
		{
			teamData[i].R(-0.1*teamData[i].Dev());
			continue;
		}
		if (10 < teamData[i].G() && teamData[i].G() <= 20) // medium-high risk 
		{
			teamData[i].R(-0.05*teamData[i].Dev());
			continue;
		}
		if (20 < teamData[i].G() && teamData[i].G() <= 20) // medium risk 
		{
			teamData[i].R(0);
			continue;
		}
		if (30 < teamData[i].G() && teamData[i].G() <= 20) // low-medium risk 
		{
			teamData[i].R(0.05*teamData[i].Dev());
			continue;
		}
		if (40 < teamData[i].G() && teamData[i].G() <= 50) // not risky, just wants the money 
		{
			teamData[i].R(0.1*teamData[i].Dev());
			continue;
		}
	}
	//cout << teamData[0] << endl;


	TeamArray temp = teamData;
	// Implementation 1: BASIC MODEL: Choose a random team, then choose another random team, then call the interact function. Repeat. 

	basic(teamData);

	teamData = temp; // reassign data back to temp for evolution model

	// Implementation 2: Evolutionary Model: Same as basic model except probability of being choosen becomes a function of current sum 

	evolution(teamData);

	return 0;
}


void basic(TeamArray& teamData) //Choose a random team, then choose another random team, then call the interact function.Repeat.
{
	default_random_engine randomGenerator((unsigned int)time(NULL));
	uniform_int_distribution<int> rand2600(0, 2600);

	int* RandA;
	int* RandB;

	RandA = new int[rounds];
	RandB = new int[rounds];

	for (int i = 0; i < rounds; ++i)
	{
		RandA[i] = rand2600(randomGenerator); // generates random numbers from 0 to 2600 (51*51 elements)
	}

	for (int i = 0; i < rounds; ++i)
	{
		RandB[i] = rand2600(randomGenerator); // generates random numbers from 0 to 2600 (51*51 elements)
	}

	int exchanges = 0; // counts the number of exchanges of money 
	for (int i = 0; i < rounds; i++)
	{
		interact(teamData[RandA[i]], teamData[RandB[i]], exchanges);
	}

	delete[] RandA;
	delete[] RandB;

	// writing final results 
	ofstream myfile;
	myfile.open("FinalBasic.txt");
	for (int i = 1; i < 51 * 51; i++)
	{
		myfile << teamData.GetElement(i).G() << "\t" << teamData.GetElement(i).A() << "\t" << 100.000 * (double)(teamData.GetElement(i).S()) / (double)(teamData.tot_sum(51 * 51)) << endl;
	}
	myfile.close();
	// end writing 

	cout << "BASIC:" << endl;
	cout << "The richest team in the BASIC MODEL is: " << teamData.richest() << endl;
	cout << "The poorest team in the BASIC MODEL is: " << teamData.poorest() << endl;
	cout << "Number of deals made is " << exchanges << endl;
	cout << "The total sum is " << teamData.tot_sum(51 * 51) << endl;
	cout << "\nThe richest team has " << percentDiff(teamData.richest(), teamData.poorest()) << "% more than the poorest team." << endl;
	cout << "\nThe average sum is: " << teamData.average(51 * 51) << endl;
	cout << "The standard deviation is: " << teamData.standardD(51 * 51) << endl;
	cout << "The range is " << range(teamData.richest(), teamData.poorest());
}


void evolution(TeamArray& teamData) //Same as basic model except probability of being choosen becomes a function of current sum 
{
	int num_eras = 100;
	int count_num_rounds = rounds / num_eras;
	// construct a trivial random generator engine from a time-based seed:

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);

	uniform_int_distribution<int> uniform(0, 2600);

	int* RandA;
	int* RandB;

	RandA = new  int[rounds];
	RandB = new  int[rounds];

	// Time Period 1: Assume at time = 0, the distribution is uniform 

	for (int i = 0; i < rounds / num_eras; ++i)
	{
		RandA[i] = uniform(generator); // generates random numbers from 0 to 2600 (2601 elements)
	}

	for (int i = 0; i < rounds / num_eras; ++i)
	{
		RandB[i] = uniform(generator); // generates random numbers from 0 to 2600 (2601 elements)
	}

	int exchanges = 0;
	for (int i = 0; i < rounds / num_eras; i++)
	{
		interact(teamData[RandA[i]], teamData[RandB[i]], exchanges);
	}

	delete[] RandA;
	delete[] RandB;

	// Later time periods (ERA 2 through 10)
	// 
	for (int t = 1; t < num_eras; ++t) // looping through the next 9 ERA's
	{

		RandA = new  int[rounds];
		RandB = new  int[rounds];

		array<int, 51 * 51> weights;

		for (int i = 0; i < 51 * 51; i++)
		{
			weights[i] = (teamData[i]).S();
		}

		discrete_distribution<int> custom(weights.begin(), weights.end());

		for (int i = t *(rounds / num_eras); i < (t + 1) * (rounds / num_eras); ++i)
		{
			RandA[i] = custom(generator);
		}

		for (int i = t * (rounds / num_eras); i < (t + 1) * (rounds / num_eras); ++i)
		{
			RandB[i] = custom(generator);
		}

		for (int i = t * (rounds / num_eras); i < (t + 1) * (rounds / num_eras); ++i)
		{
			interact(teamData[RandA[i]], teamData[RandB[i]], exchanges);
			count_num_rounds++;
		}

		delete[] RandA;
		delete[] RandB;
	}

	// writing final results 
	ofstream myfile;
	myfile.open("FinalEvolution.txt");
	for (int i = 1; i < 51 * 51; i++)
	{
		myfile << teamData.GetElement(i).G() << "\t" << teamData.GetElement(i).A() << "\t" << 100.000 * (double)(teamData.GetElement(i).S()) / (double)(teamData.tot_sum(51 * 51)) << endl;
	}
	myfile.close();

	cout << "\n\nEVOLUTION: " << endl;
	cout << "The richest team in the EVOLUTION MODEL is: " << teamData.richest() << endl;
	cout << "The poorest team in the EVOLUTION MODEL is: " << teamData.poorest() << endl;
	cout << "Number of deals made is " << exchanges << endl;
	cout << "The total sum is " << teamData.tot_sum(51 * 51) << endl;
	cout << "\nThe richest team has " << percentDiff(teamData.richest(), teamData.poorest()) << "% more than the poorest team." << endl;
	cout << "\nThe average sum is: " << teamData.average(51 * 51) << endl;
	cout << "The standard deviation is: " << teamData.standardD(51 * 51) << endl;
	cout << "The range is " << range(teamData.richest(), teamData.poorest()) << "\n";
}


// Ultimatum Game with Gaussian Acceptances. There are also three different risk levels: risk lover, risk adverse, risk neutral. 

#include <boost/math/distributions/normal.hpp> // Gaussian distribution 
#include <boost/math/distributions.hpp> // For non-member functions of distributions
#include "boost/tuple/tuple.hpp"
#include "boost/tuple/tuple_io.hpp"
#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions.hpp> // For non-member functions of distributions
#include <cmath>
#include <vector>
#include <math.h>
#include <iostream>
#include <boost/random.hpp> // Convenience header file
#include <ctime>			// std::time
#include <boost/Random/detail/const_mod.hpp> // LCG class

using boost::tuple;
using namespace boost::math;
using namespace std;
using boost::math::normal;

boost::tuple<int, int, int, int> makeTeam(int risk_type, int expected_minAccept, int standard_deviation, int sum) // Team Creation
{
	return boost::make_tuple(risk_type, expected_minAccept, standard_deviation, sum); // Derives an anonymous object which uniquely defines a strategy 
}

typedef boost::tuple<int, int, int, int> Team;
typedef vector<Team> vectorTuple;

void interact(Team& giver, Team& acceptor);
normal gaussian(const Team& acceptor); // creates gaussian distribution
double EV(const double &x, const Team& acceptor); // finds expected payoff function for risk neutral teams 
double EV2(const double &x, const Team& acceptor); // finds expected payoff function for risk loving teams 
double EVsqrt(const double &x, const Team& acceptor); // finds expected payoff function for risk adverse teams 
double maxx(double(*EV)(const double &, const Team &acceptor), double &a, double &b, Team &acceptor, const double tol = 1e-5);

bool mycompare(const Team &lhs, const Team &rhs) {
	return get<3>(lhs) < get<3>(rhs);
}

int main()
{
	int numStrategies = 3 * 3 * 101; 
	vectorTuple teamData; // a vector filled with all the Team Data 
	teamData.reserve(numStrategies); 
	for (int k = 0; k < 3; ++k) // possible risk types: 0, 1, 2
	{
		for (int i = 1; i < 4; ++i) // possible standard deviations 1, 2, 3
		{
			for (int j = 0; j < 101; ++j) // possible expected_minAccept 
			{
				teamData.push_back(makeTeam(k, j, i, 0));  // creating 3 * 3 * 101 = 909 different teams 
			}
		}
	}
	cout << teamData.size() << endl;

	int numRounds = 100000; // the number of games played 

	boost::uniform_int<> uniform(0, numStrategies - 1); // there are numStrategies possible strategy sets 
	boost::lagged_fibonacci607 rng; // fibonacci pseudo random number generation 
	rng.seed(static_cast<unsigned int> (std::time(0))); // set a seed 
	boost::variate_generator<boost::lagged_fibonacci607&, boost::uniform_int<>> Rng(rng, uniform);

	for (int n = 0; n < numRounds; ++n)
	{
		interact(teamData[Rng()], teamData[Rng()]); // standard ultimatum game conditions 
	}

	cout << "After " << numRounds << " rounds of the game: " << endl;

	sort(teamData.begin(), teamData.end(), mycompare);
	cout << "Risk" << "\t" << "Avg min_Accept" << "\t" << "SD" << "\t" << "Money" << endl;

	vectorTuple::iterator it1 = teamData.begin() + 850;
	vectorTuple::iterator it2 = teamData.end();

	for (vector<Team>::iterator iter = it1; iter != it2; iter++)
	{
		cout << get<0>(*iter) << "\t" << get<1>(*iter) << "\t\t" << get<2>(*iter) << "\t" << get<3>(*iter) << endl;
	}

	return 0;
}

void interact(Team& giver, Team& acceptor)
{
	boost::normal_distribution<> norm(acceptor.get<1>(), acceptor.get<2>());
	boost::lagged_fibonacci607 rng;
	rng.seed(static_cast<unsigned int> (std::time(0)));
	boost::variate_generator<boost::lagged_fibonacci607&, boost::normal_distribution<> >
		Rng(rng, norm);

	// generate a realAccept value 
	double realAccept; 
	do{ // generate a min_accept value using the gaussian distribution 
		realAccept = Rng(); 
	}while (realAccept < 0 || realAccept > 100); // prevents impossible realAccept value from occuring 

	// generate give value 
	
	double a = 0.0; // lower bound in Golden section search alg
	double b = 100.0; // upper bound in Golden section search alg
	double give = 0; // initialize to zero 

	if (giver.get<0>() == 0) // risk adverse!
	{
		give = maxx(EVsqrt, a, b, acceptor); // invoke optimization algorithm: Golden section search
	}
	else if (giver.get<0>() == 1) // risk neutral!
	{
		give = maxx(EV, a, b, acceptor); // invoke optimization algorithm: Golden section search
	}
	else // risk lover!
	{
		give = maxx(EV2, a, b, acceptor); // invoke optimization algorithm: Golden section search
	}

	if (give >= realAccept)
	{
		get<3>(giver) += 100 - give;
		get<3>(acceptor) += give;	
	}	
}

// Optimization implementation for giving amount 
using boost::math::normal;
normal gaussian(const Team& acceptor)
{
	normal ndist(acceptor.get<1>(), acceptor.get<2>());
	return ndist; 
}

double EV(const double &x, const Team& acceptor) // multiplying the payoff function by the pdf for every x 
{
	return cdf(gaussian(acceptor), x) * (100.0 - x);
}

double EV2(const double &x, const Team& acceptor) // multiplying the payoff function by the pdf for every x 
{
	return cdf(gaussian(acceptor), x) * (100.0 - x) * cdf(gaussian(acceptor), x) * (100.0 - x);
}

double EVsqrt(const double &x, const Team& acceptor) // multiplying the payoff function by the pdf for every x 
{
	return sqrt(cdf(gaussian(acceptor), x) * (100.0 - x));
}

double maxx(double(*f)(const double &, const Team&), double &a, double &b, Team &acceptor, const double tol)
{
	static double goldenratio = 0.618034;
	double c = b - goldenratio * (b - a);
	double d = a + goldenratio * (b - a);
	while (abs(c - d) > tol)
	{
		double fc = (*f)(c, acceptor); double fd = (*f)(d, acceptor);
		if (fc > fd)
		{
			b = d;
			d = c;
			c = b - goldenratio * (b - a);
		}
		else
		{
			a = c;
			c = d;
			d = a + goldenratio * (b - a);
		}
	}
	return 0.5 * (b + a);
}

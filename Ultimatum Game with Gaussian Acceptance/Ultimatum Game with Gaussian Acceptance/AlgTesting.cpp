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
#define _USE_MATH_DEFINES
# define M_PI           3.14159265358979323846

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

double maxx(double(*f)(const double &), double &a, double &b, const double tol = 1e-5);
double f(const double &x, const int &y); // finds expected payoff function 

int main()
{
	double a = 0.0;
	double b = 100.0;
	maxx(f, a, b);

	return 0;
}

using boost::math::normal;

normal ndist(50.0, 1.0);

double f(const double &x)
{
	return pdf(ndist, x) * (100.0 - x);
}

double maxx(double(*f)(const double &), double &a, double &b, const double tol)
{
	static double goldenratio = 0.618034;
	double c = b - goldenratio * (b - a);
	double d = a + goldenratio * (b - a);
	while (abs(c - d) > tol)
	{
		double fc = (*f)(c); double fd = (*f)(d);
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
//// discrete_distribution constructor
//#include <iostream>
//#include <chrono>
//#include <random>
//#include <functional>
//#include <array>
//
//int main()
//{
//	// construct a trivial random generator engine from a time-based seed:
//	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
//	std::default_random_engine generator(seed);
//
//	//std::array<int, 4> init = { 1,2,3,4 };
//
//	std::array<int, 120> init;
//
//	for (int i = 0; i < 120; i++)
//		init[i] = i;
//
//	std::discrete_distribution<int> second(init.begin(), init.end());
//	
//
//	// display probabilities:
//	std::cout << "displaying probabilities:";
//	std::cout << std::endl << "first : ";
//
//	for (double x : second.probabilities()) std::cout << x << " ";
//	std::cout << std::endl << "third : ";
//	
//
//	return 0;
//}
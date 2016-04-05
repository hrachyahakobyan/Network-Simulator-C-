#include "stdafx.h"
#include "RandomManager.h"
#include <time.h>

RandomManager* RandomManager::sharedRandomManager = NULL;

RandomManager::RandomManager()
{
	srand(time(NULL));
}


RandomManager::~RandomManager()
{
}

int RandomManager::random(int a, int b)
{
	assert(a > -1 && "ERROR: random_n: negative a");
	assert(b > -1 && "ERROR: random_n: negative b");
	if (a > b)
	{
		a += b;
		b = a - b;
		a -= b;
	}
	return rand() % (b - a + 1) + a;
}
std::vector<int> RandomManager::random(int a, int b, int n)
{
	std::vector<int> vec;
	for (int i = 0; i < n; i++)
		vec.push_back(random(a, b));
	return vec;
}


std::vector<int> RandomManager::pruefer(int n)
{
	assert(n > 1 && "ERROR: RandomManager::pruefer: n must be greater than 1");
	return random(1, n, n - 2);
}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			

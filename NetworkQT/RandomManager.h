#pragma once
class RandomManager
{
public:
	static RandomManager* sharedManager()
	{
		if (sharedRandomManager == 0)
			sharedRandomManager = new RandomManager;
		return sharedRandomManager;
	}

	static void release()
	{
		if (sharedRandomManager != 0)
		{
			delete sharedRandomManager;
			sharedRandomManager = 0;
		}
	}

	/*A realization of a random event with probability p*/
	bool event(double p);
	/*A randomly chosen index based on the probabilities p*/
	int random_index(std::vector<double> p);
	/*A random number between a and b, inclusive*/
	int random(int a, int b);
	/*A vector of size n of random numbers between a and b, inclusive*/
	std::vector<int> random(int a, int b, int n);
	/*Pruefer sequence of length n*/
	std::vector<int> pruefer(int n);


private:
	static RandomManager* sharedRandomManager;
	RandomManager();
	~RandomManager(); 

	bool leq(double a, double b);
	bool eq(double a, double b);
	bool beq(double a, double b);
};


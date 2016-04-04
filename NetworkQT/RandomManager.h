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

	int random(int a, int b);
	std::vector<int> random(int a, int b, int n);
	std::vector<int> pruefer(int n);


private:
	static RandomManager* sharedRandomManager;
	RandomManager();
	~RandomManager();
};


#pragma once
class DiseaseFactory
{
public:
	enum DiseaseModelType{SIR, SIS, SIRS};
public:
	static DiseaseFactory* sharedFactory()
	{
		if (_sharedFactory == 0)
			_sharedFactory = new DiseaseFactory;
		return _sharedFactory;
	}

	static void release()
	{
		if (_sharedFactory != 0)
		{
			delete _sharedFactory;
			_sharedFactory = 0;
		}
	}

private:
	static DiseaseFactory* _sharedFactory;
	DiseaseFactory();
	~DiseaseFactory();
};


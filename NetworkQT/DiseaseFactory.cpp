#include "stdafx.h"
#include "DiseaseFactory.h"

DiseaseFactory *DiseaseFactory::sharedDiseaseFactory = 0;

DiseaseFactory::DiseaseFactory()
{
	Register<DiseaseSimulationSIR>(DiseaseSimulation::ModelType::SIR);
	Register<DiseaseSimulationSIS>(DiseaseSimulation::ModelType::SIS);
	Register<DiseaseSimulationSIRS>(DiseaseSimulation::ModelType::SIRS);
}


DiseaseFactory::~DiseaseFactory()
{
}

#include "stdafx.h"
#include "Simulation.h"


Simulation::Simulation()
{
}


Simulation::~Simulation()
{
}

const HNAGraph& Simulation::state() const
{
	return (*graph_p_);
}

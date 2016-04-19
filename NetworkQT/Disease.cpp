#include "stdafx.h"
#include "Disease.h"


Disease::Disease()
{
}


Disease::~Disease()
{
}


void Disease::set_inf_period(int p)
{
	assert(p > 0 && "ERROR:Disease: illegal inf_period");
	inf_period_ = p;
}

void Disease::set_loss_im_period(int p)
{
	assert(p > 0 && "ERROR:Disease: illegal loss_of_imm rate");
	loss_of_imm_period_ = p;
}

void Disease::set_inf_rate(double p)
{
	assert(p >= 0 && p <= 1 && "ERROR:Disease: illegal inf_rate");
	inf_rate_ = p;
}

int Disease::get_inf_preiod()
{
	return inf_period_;
}

int Disease::get_loss_im_period()
{
	return loss_of_imm_period_;
}

double Disease::get_inf_rate()
{
	return inf_rate_;
}
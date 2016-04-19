#pragma once
class Disease
{
public:
	Disease();
	~Disease();
	void set_inf_period(int p);
	void set_loss_im_period(int p);
	void set_inf_rate(double p);

	int get_inf_preiod();
	int get_loss_im_period();
	double get_inf_rate();
private:
    int inf_period_;
	int loss_of_imm_period_;
	double inf_rate_;
};


#pragma once
#include "Simulation.h"
class DiseaseSimulation : public Simulation
{
public:
	enum ModelType{ SIR, SIS, SIRS };
	struct DiseaseOptions
	{
		enum class ImmunityType{Fixed, Probabilistic};
		enum class InfectionType{Fixed, Probabilistic};

		ModelType type;
		/*The probability that an infected unit will infect a susceptible unit within one unit of time*/
		double inf_rate_;

		ImmunityType imType_;
		/*Only one of two required*/
		/*The probability that within one time unit an immune unit will become susceptible*/
		double imm_loss_rate_;
		/*The length of period of the immune state*/
		int imm_period_;

		InfectionType infType_;
		/*Only one of two required*/
		/*The probability that within one time unit an infected unit will become recovered/susceptible*/
		double rec_rate_;
		/*The length of period of the infected state*/
		int inf_period_;
	};
public:
	DiseaseSimulation();
	DiseaseSimulation(const GraphBuilder::GraphOptions& g_options, const DiseaseSimulation::DiseaseOptions& options);
	virtual ~DiseaseSimulation();
	virtual bool tick(int count = 1) = 0;
	virtual bool finished() const = 0;
protected:
	typedef DiseaseSimulation::DiseaseOptions Options;
	Options options_;
protected:
	virtual void updateData() = 0;
	virtual void send(const HNAGraph::Vertex& sender, std::map<HNAGraph::Vertex, HNAGraph::HNANodeBundle>& messages) = 0;
	virtual void receive(const HNAGraph::Vertex& node, const std::map<HNAGraph::Vertex, HNAGraph::HNANodeBundle>& messages) = 0;
	virtual void iterate() = 0;
};


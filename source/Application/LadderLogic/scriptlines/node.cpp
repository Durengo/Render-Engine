#include "node.h"

#include "../utils/DataManager.h"

node::node(ladderLogic::gateType type) : logicGate(type), Unique_ID(0)	{}

node::~node()	{
		std::cout << "GATE DELETED; GATE TYPE: " << m_GateType << "\n";
}

int node::getUniqueId() const	{
		return Unique_ID;
}

void node::setUniqueId(int uniqueId)	{
		Unique_ID = uniqueId;
}

ladderLogic::gateType node::getm_GateType() const	{
		return m_GateType;
}

void node::setm_GateType(ladderLogic::gateType type)	{
		m_GateType = type;
}

std::string node::getm_GateTypeByString() const {
		switch (m_GateType) {
				case ladderLogic::gateType::NO:
						return "NORMALLY OPEN GATE";
				case ladderLogic::gateType::NC:
						return "NORMALLY CLOSED GATE";
				case ladderLogic::gateType::AND:
						return "AND GATE";
				case ladderLogic::gateType::OR:
						return "OR GATE";
				default:
						std::cout << "\nEXCEPTION IN m_GateTypeByString!\n";
						break;
		}
}
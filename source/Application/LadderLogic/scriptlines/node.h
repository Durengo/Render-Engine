#pragma once

#include <iostream>
#include <utility>

#include "../utils/DataManager.h"
#include "../gates/ladderLogicHeader.h"

class node
				: public ladderLogic::andGate,
						public ladderLogic::orGate,
						public ladderLogic::normallyOpenGate,
						public ladderLogic::normallyClosedGate	{
public:
				node *next = nullptr;

				std::string UserFlag;

				node(ladderLogic::gateType type);

				~node();

				int getUniqueId() const;

				void setUniqueId(int uniqueId);

				ladderLogic::gateType getm_GateType() const;

				std::string getm_GateTypeByString() const;

				void setm_GateType(ladderLogic::gateType type);

private:
				int Unique_ID;

				ladderLogic::gateType m_GateType;
};
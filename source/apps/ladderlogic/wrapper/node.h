#pragma once

#include <iostream>
#include <utility>
#include <memory>

#include "../gatesMemory/gatesHeaderLoader.h"

namespace ladderLogic {

				enum gateType {
								NONE = 0,
								NO = 1,
								NC = 2,
								AND = 3,
								OR = 4
				};

				class node
				{
				public:
								node *next = nullptr;

								lgates::AND *ANDgate;

								lgates::OR *ORgate;

								lgates::NO *NOgate;

								lgates::NC *NCgate;

								explicit node(ladderLogic::gateType type);

								~node();

								int getUniqueId() const;

								void setUniqueId(int uniqueId);

								ladderLogic::gateType getm_GateType() const;

								std::string getm_GateTypeByString() const;

								void setm_GateType(ladderLogic::gateType type);

								//NO
								void NOsetnextpin(int* pin);

								void NOsetoutput(int* OB);

								int* NOgetoutput();

								//NC
								void NCsetnextpin(int* pin);

								void NCsetoutput(int* OB);

								int* NCgetoutput();

								//AND
								void ANDsetnextpin(int* pin);

								void ANDsetoutput(int* OB);

								int* ANDgetoutput();

								//OR
								void ORsetnextpin(int* pin);

								void ORsetoutput(int* OB);

								int* ORgetoutput();

				private:
								int Unique_ID;

								ladderLogic::gateType m_GateType;


				};

}
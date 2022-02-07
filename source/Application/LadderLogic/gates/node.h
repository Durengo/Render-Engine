#pragma once

#include <iostream>
#include <utility>
#include <memory>

#include "ladderLogicHeader.h"

namespace ladderLogic {

				class node
//								: public ladderLogic::andGate,
//										public ladderLogic::orGate,
//										public ladderLogic::normallyOpenGate,
//										public ladderLogic::normallyClosedGate
				{
				public:
								node *next = nullptr;

//								[[maybe_unused]] std::unique_ptr<andGate> ANDgate;
//								[[maybe_unused]] std::unique_ptr<orGate> ORgate;
//								[[maybe_unused]] std::unique_ptr<normallyOpenGate> NOgate;
//								[[maybe_unused]] std::unique_ptr<normallyClosedGate> NCgate;

								andGate *ANDgate;

								orGate *ORgate;

								normallyOpenGate *NOgate;

								normallyClosedGate *NCgate;

								std::string UserFlag;

								//node(ladderLogic::gateType type);
								node(ladderLogic::gateType type, int *firstpin, int *secondpin, int *output);

								node(ladderLogic::gateType type, int *firstpin, int *output);
								//node(ladderLogic::gateType type);
								//node(ladderLogic::gateType type);
								//node(ladderLogic::gateType type);

								~node();

								int getUniqueId() const;

								void setUniqueId(int uniqueId);

								void executeANDlogic();

								void executeORlogic();

								void executeNOlogic();

								void executeNClogic();

								int* NOgetfirstpin();

								int* NCgetfirstpin();

								int* ANDgetfirstpin();

								int* ANDgetsecondpin();

								int* ORgetfirstpin();

								int* ORgetsecondpin();

								void NOsetfirstpin(int *input1);

								void NCsetfirstpin(int *input1);

								void ANDsetfirstpin(int *input1);

								void ANDsetsecondpin(int *input2);

								void ORsetfirstpin(int *input1);

								void ORsetsecondpin(int *input2);

								void NOnewheapoutput();

								void NOnewheapfirstpin();

								void NCnewheapoutput();

								void NCnewheapfirstpin();

								void ANDnewheapoutput();

								void ANDnewfirstpin();

								void ANDnewsecondpin();

								void ORnewheapoutput();

								void ORnewheapfirstpin();

								void ORnewheapsecondpin();

								int* NOgetoutput();

								int* NCgetoutput();

								int* ANDgetoutput();

								int* ORgetoutput();

								int* NOsetoutput(int* gateinput);

								int* NCsetoutput(int* gateinput);

								int* ANDsettoutput(int* gateinput);

								int* ORgsetoutput(int* gateinput);

								ladderLogic::gateType getm_GateType() const;

								std::string getm_GateTypeByString() const;

								void setm_GateType(ladderLogic::gateType type);

								bool isAssigned;

				private:
								int Unique_ID;

								ladderLogic::gateType m_GateType;
				};

}
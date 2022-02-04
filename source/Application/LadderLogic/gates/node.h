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

								[[maybe_unused]] andGate* ANDgate;
								[[maybe_unused]] orGate* ORgate;
								[[maybe_unused]] normallyOpenGate* NOgate;
								[[maybe_unused]] normallyClosedGate* NCgate;

								std::string UserFlag;

								//node(ladderLogic::gateType type);
								node(ladderLogic::gateType type, int& firstpin, int& secondpin);

								node(ladderLogic::gateType type, int& firstpin);
								//node(ladderLogic::gateType type);
								//node(ladderLogic::gateType type);
								//node(ladderLogic::gateType type);

								~node();

								int getUniqueId() const;

								void setUniqueId(int uniqueId);

								bool executeANDlogic() const;
								bool executeORlogic() const;
								bool executeNOlogic() const;
								bool executeNClogic() const;

								ladderLogic::gateType getm_GateType() const;

								std::string getm_GateTypeByString() const;

								void setm_GateType(ladderLogic::gateType type);

								bool isAssigned;

				private:
								int Unique_ID;

								ladderLogic::gateType m_GateType;
				};

}
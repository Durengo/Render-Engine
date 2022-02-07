#include "node.h"

namespace ladderLogic {

//				node::node(ladderLogic::gateType type) :
////logicGate(type),
//								Unique_ID(0), isAssigned(false) {
//
//				}

				node::node(ladderLogic::gateType type, int *firstpin, int *secondpin, int *output) {
/*						if (output == nullptr) {
								output = new int;
						}*/
						switch (type) {
								case ladderLogic::gateType::NO:
										std::cout << "\nEXCEPTION: CANNOT ASSIGN TWO INPUTS TO NORMALLY OPEN GATE\n";
										return;
								case ladderLogic::gateType::NC:
										std::cout << "\nEXCEPTION: CANNOT ASSIGN TWO INPUTS TO NORMALLY CLOSED GATE\n";
										return;
								case ladderLogic::gateType::AND:
										//std::make_unique<andGate>(firstpin, secondpin);
										ANDgate = new andGate(firstpin, secondpin, output);
										m_GateType = gateType::AND;
										return;
								case ladderLogic::gateType::OR:
										//std::make_unique<orGate>(firstpin, secondpin);
										ORgate = new orGate(firstpin, secondpin, output);
										m_GateType = gateType::OR;
										return;
								default:
										std::cout << "\nEXCEPTION IN NODE CONSTRUCTOR!\n";
										break;
						}
				}

				node::node(ladderLogic::gateType type, int *firstpin, int *output) {
/*						if (output == nullptr) {
								output = new int;
						}*/
						switch (type) {
								case ladderLogic::gateType::NO:
										NOgate = new normallyOpenGate(firstpin, output);
										m_GateType = gateType::NO;
										return;
								case ladderLogic::gateType::NC:
										NCgate = new normallyClosedGate(firstpin, output);
										m_GateType = gateType::NC;
										return;
								case ladderLogic::gateType::AND:
										std::cout << "\nEXCEPTION: CANNOT ASSIGN ONE INPUT TO AND GATE\n";
										return;
								case ladderLogic::gateType::OR:
										std::cout << "\nEXCEPTION: CANNOT ASSIGN ONE INPUT TO OR GATE\n";
										return;
								default:
										std::cout << "\nEXCEPTION IN NODE CONSTRUCTOR!\n";
										break;
						}
				}

				node::~node() {
						std::cout << "GATE DELETED; GATE TYPE: " << m_GateType << "\n";
						switch (m_GateType) {
								case ladderLogic::gateType::NO:
										delete NOgate;
										return;
								case ladderLogic::gateType::NC:
										delete NCgate;
										return;
								case ladderLogic::gateType::AND:
										delete ANDgate;
										return;
								case ladderLogic::gateType::OR:
										delete ORgate;
										return;
								default:
										std::cout << "\nEXCEPTION IN NODE CONSTRUCTOR!\n";
										break;
						}
				}


				void node::executeANDlogic() {
						ANDgate->executeGateLogic();
				}

				void node::executeORlogic() {
						ORgate->executeGateLogic();
				}

				void node::executeNOlogic() {
						NOgate->executeGateLogic();
				}

				void node::executeNClogic() {
						NCgate->executeGateLogic();
				}


				int *node::NOgetfirstpin() {
						return NOgate->getfirstpin();
				}

				int *node::NCgetfirstpin() {
						return NCgate->getfirstpin();
				}

				int *node::ANDgetfirstpin() {
						return ANDgate->getfirstpin();
				}

				int *node::ANDgetsecondpin() {
						return ANDgate->getsecondpin();
				}

				int *node::ORgetfirstpin() {
						return ORgate->getfirstpin();
				}

				int *node::ORgetsecondpin() {
						return ORgate->getsecondpin();
				}

				int node::getUniqueId() const {
						return Unique_ID;
				}


				void node::NOsetfirstpin(int *input1) {
						NOgate->setfirstPin(input1);
				}

				void node::NCsetfirstpin(int *input1) {
						NCgate->setfirstPin(input1);
				}

				void node::ANDsetfirstpin(int *input1) {
						ANDgate->setfirstPin(input1);
				}

				void node::ANDsetsecondpin(int *input2) {
						ANDgate->setfirstPin(input2);
				}

				void node::ORsetfirstpin(int *input1) {
						ORgate->setfirstPin(input1);
				}

				void node::ORsetsecondpin(int *input2) {
						ORgate->setfirstPin(input2);
				}


				void node::NOnewheapoutput() {
/*							int* current =;
							current = new int;
							*current = 0;*/
				}

				void node::NOnewheapfirstpin() {
						int *current = NOgetfirstpin();
						current = new int;
						NOsetfirstpin(current);
				}

				void node::NCnewheapoutput() {

				}

				void node::NCnewheapfirstpin() {

				}

				void node::ANDnewheapoutput() {

				}

				void node::ANDnewfirstpin() {

				}

				void node::ANDnewsecondpin() {

				}

				void node::ORnewheapoutput() {

				}

				void node::ORnewheapfirstpin() {

				}

				void node::ORnewheapsecondpin() {

				}




				int* node::NOgetoutput() {
						return NOgate->getoutput();
				}

				int* node::NCgetoutput() {
						return NCgate->getoutput();
				}

				int* node::ANDgetoutput() {
						return ANDgate->getoutput();
				}

				int* node::ORgetoutput() {
						return ORgate->getoutput();
				}


				int *node::NOsetoutput(int* gateinput) {
						int* current = NOgate->getoutput();
						current = gateinput;
				}

				int *node::NCsetoutput(int* gateinput) {
						int* current = NCgate->getoutput();
						current = gateinput;
				}

				int *node::ANDsettoutput(int* gateinput) {
						return nullptr;
				}

				int *node::ORgsetoutput(int* gateinput) {
						return nullptr;
				}








				void node::setUniqueId(int uniqueId) {
						Unique_ID = uniqueId;
				}

				ladderLogic::gateType node::getm_GateType() const {
						return m_GateType;
				}

				void node::setm_GateType(ladderLogic::gateType type) {
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
}
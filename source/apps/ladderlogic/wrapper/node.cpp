#include "node.h"

namespace ladderLogic {

//				node::node(ladderLogic::gateType type) :
////logicGate(type),
//								Unique_ID(0), isAssigned(false) {
//
//				}

				node::node(ladderLogic::gateType type)
				: ANDgate(nullptr), ORgate(nullptr), NOgate(nullptr), NCgate(nullptr)
				{
						switch (type) {
								case ladderLogic::gateType::NO:
										NOgate = new lgates::NO("NO");
										m_GateType = gateType::NO;
										delete ANDgate;
										delete ORgate;
										delete NCgate;
										return;
								case ladderLogic::gateType::NC:
										NCgate = new lgates::NC("NC");
										m_GateType = gateType::NC;
										delete ANDgate;
										delete ORgate;
										delete NOgate;
										return;
								case ladderLogic::gateType::AND:
										ANDgate = new lgates::AND("AND");
										m_GateType = gateType::AND;
										delete ORgate;
										delete NOgate;
										delete NCgate;
										return;
								case ladderLogic::gateType::OR:
										ORgate = new lgates::OR("OR");
										m_GateType = gateType::OR;
										delete ANDgate;
										delete NOgate;
										delete NCgate;
										return;
								default:
										std::cout << "\nEXCEPTION IN NODE CONSTRUCTOR!\n";
										break;
						}
				}

				node::~node() {
						std::cout << "GATE DELETED; GATE TYPE: " << getm_GateType() << "\n";
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
										//NORMALLY OPEN GATE
										return "NO";
								case ladderLogic::gateType::NC:
										//NORMALLY CLOSED GATE
										return "NC";
								case ladderLogic::gateType::AND:
										//AND GATE
										return "AND";
								case ladderLogic::gateType::OR:
										//OR GATE
										return "OR";
								default:
										std::cout << "\nEXCEPTION IN m_GateTypeByString!\n";
										break;
						}
				}

				int node::getUniqueId() const {
						return Unique_ID;
				}

				//Node-to-gate
				//NO GATE
				void node::NOsetnextpin(int *pin) {
						if(pin == nullptr){
								std::cout << "NO NEXT PIN IS NULLPTR. ABORTING\n";
								return;
						}
						NOgate->setNextPin(pin);
				}

				void node::NOsetoutput(int *OB) {
						if(OB == nullptr){
								std::cout << "CANNOT SET OUTPUT BUFFER FOR NO GATE. OB IS NULLPTR. ABORTING\n";
								return;
						}
						NOgate->setOutput(OB);
				}

				int *node::NOgetoutput() {
						if(NOgate->getOutput() == nullptr){
								std::cout << "NO OUTPUT IS NULLPTR. ABORTING\n";
								return nullptr;
						}
						return NOgate->getOutput();
				}
				//NC GATE
				void node::NCsetnextpin(int *pin) {
						if(pin == nullptr){
								std::cout << "NC NEXT PIN IS NULLPTR. ABORTING\n";
								return;
						}
						NCgate->setNextPin(pin);
				}

				void node::NCsetoutput(int *OB) {
						if(OB == nullptr){
								std::cout << "CANNOT SET OUTPUT BUFFER FOR NC GATE. OB IS NULLPTR. ABORTING\n";
								return;
						}
						NCgate->setOutput(OB);
				}

				int *node::NCgetoutput() {
						if(NCgate->getOutput() == nullptr){
								std::cout << "NC OUTPUT IS NULLPTR. ABORTING\n";
								return nullptr;
						}
						return NCgate->getOutput();
				}

				//AND GATE
				void node::ANDsetnextpin(int *pin) {
						if(pin == nullptr){
								std::cout << "AND NEXT PIN IS NULLPTR. ABORTING\n";
								return;
						}
						ANDgate->setNextPin(pin);
				}

				void node::ANDsetoutput(int *OB) {
						if(OB == nullptr){
								std::cout << "CANNOT SET OUTPUT BUFFER FOR AND GATE. OB IS NULLPTR. ABORTING\n";
								return;
						}
						ANDgate->setOutput(OB);
				}

				int *node::ANDgetoutput() {
						if(NOgate->getOutput() == nullptr){
								std::cout << "AND OUTPUT IS NULLPTR. ABORTING\n";
								return nullptr;
						}
						return ANDgate->getOutput();
				}

				//OR GATE
				void node::ORsetnextpin(int *pin) {
						if(pin == nullptr){
								std::cout << "OR NEXT PIN IS NULLPTR. ABORTING\n";
								return;
						}
						ORgate->setNextPin(pin);
				}

				void node::ORsetoutput(int *OB) {
						if(OB == nullptr){
								std::cout << "CANNOT SET OUTPUT BUFFER FOR OR GATE. OB IS NULLPTR. ABORTING\n";
								return;
						}
						ORgate->setOutput(OB);
				}

				int *node::ORgetoutput() {
						if(NOgate->getOutput() == nullptr){
								std::cout << "OR OUTPUT IS NULLPTR. ABORTING\n";
								return nullptr;
						}
						return ORgate->getOutput();
				}
}
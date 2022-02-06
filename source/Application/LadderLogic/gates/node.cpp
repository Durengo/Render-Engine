#include "node.h"

namespace ladderLogic {

	//				node::node(ladderLogic::gateType type) :
	////logicGate(type),
	//								Unique_ID(0), isAssigned(false) {
	//
	//				}

	node::node(ladderLogic::gateType type, int& firstpin, int& secondpin) {
		switch (type) {
		case ladderLogic::gateType::NO:
			std::cout << "\nEXCEPTION: CANNOT ASSIGN TWO INPUTS TO NORMALLY OPEN GATE\n";
			return;
		case ladderLogic::gateType::NC:
			std::cout << "\nEXCEPTION: CANNOT ASSIGN TWO INPUTS TO NORMALLY CLOSED GATE\n";
			return;
		case ladderLogic::gateType::AND:
			//std::make_unique<andGate>(firstpin, secondpin);
			ANDgate = new andGate(firstpin, secondpin);
			return;
		case ladderLogic::gateType::OR:
			//std::make_unique<orGate>(firstpin, secondpin);
			ORgate = new orGate(firstpin, secondpin);
			return;
		default:
			std::cout << "\nEXCEPTION IN NODE CONSTRUCTOR!\n";
			break;
		}
	}

	node::node(ladderLogic::gateType type, int& firstpin) {
		switch (type) {
		case ladderLogic::gateType::NO:
			NOgate = new normallyOpenGate(firstpin);
			return;
		case ladderLogic::gateType::NC:
			NCgate = new normallyClosedGate(firstpin);
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

	bool node::executeANDlogic() const {
		return ANDgate->executeGateLogic();
	}

	bool node::executeORlogic() const {
		return ORgate->executeGateLogic();
	}

	bool node::executeNOlogic() const {
		return NOgate->executeGateLogic();
	}

	bool node::executeNClogic() const {
		return NCgate->executeGateLogic();
	}

	int node::getUniqueId() const {
		return Unique_ID;
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
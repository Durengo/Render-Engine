#include "normallyClosedGate.h"

namespace ladderLogic {

				normallyClosedGate::normallyClosedGate()
								: type(ladderLogic::gateType::NC), logicGate(type), output(false), firstPin(false), firstPinTaken(false),
										secondPin(false), secondPinTaken(false) {}

				normallyClosedGate::normallyClosedGate(int firstpin)
								: type(ladderLogic::gateType::NC), logicGate(type), output(false), firstPin(firstpin), firstPinTaken(false),
										secondPin(false), secondPinTaken(false) {

				}

				bool normallyClosedGate::executeGateLogic() {
						if (firstPin == 0) {
								return false;
						} else if (firstPin == 1) {
								return true;
						}
				}

				bool normallyClosedGate::getfirstPin() {
						if (!firstPinTaken) {
								std::cout << "Enter first input pin for " << getgateType() << " : ";
								std::cin >> firstPin;
								firstPinTaken = true;
						}
						return firstPin;
				}

				bool normallyClosedGate::executeNormallyCloseGateLogic() {
						bool a = getfirstPin();
						if (a == 0) {
								output = false;
								return output;
						} else if (a == 1) {
								output = true;
								return output;
						}
				}

}
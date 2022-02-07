#include "normallyOpenGate.h"

namespace ladderLogic {

/*				normallyOpenGate::normallyOpenGate()
								: type(ladderLogic::gateType::NO), logicGate(type), output(true), firstPin(false), firstPinTaken(false),
										secondPin(false), secondPinTaken(false) {}

				normallyOpenGate::normallyOpenGate(int *firstpin)
								: type(ladderLogic::gateType::NO), logicGate(type), output(true), firstPin(*firstpin), firstPinTaken(false),
										secondPin(false), secondPinTaken(false) {

				}*/

				normallyOpenGate::normallyOpenGate(int *firstpin, int *output)
								: type(ladderLogic::gateType::NO), logicGate(type), firstPin(firstpin), output(output)  {
						//*output = 1;
				}

				void normallyOpenGate::executeGateLogic() {
						if (*firstPin == 0) {
								*output = 1;
								return;
						} else if (*firstPin == 1) {
								*output = 0;
								return;
						}
				}

				int *normallyOpenGate::getfirstpin() {
						return firstPin;
				}

				int *normallyOpenGate::getoutput() {
						return output;
				}

				void normallyOpenGate::setfirstPin(int *input1) {
						*firstPin = *input1;
				}

/*				bool normallyOpenGate::getfirstPin() {
						if (!firstPinTaken) {
								std::cout << "Enter first input pin for " << getgateType() << " : ";
								std::cin >> firstPin;
								firstPinTaken = true;
						}
						return firstPin;
				}

				bool normallyOpenGate::executeNormallyOpenGateLogic() {
						bool a = getfirstPin();
						if (a == 0) {
								output = true;
								return output;
						} else if (a == 1) {
								output = false;
								return output;
						}
				}*/
}
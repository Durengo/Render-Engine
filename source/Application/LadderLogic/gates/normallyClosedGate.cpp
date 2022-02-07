#include "normallyClosedGate.h"

namespace ladderLogic {

/*				normallyClosedGate::normallyClosedGate()
								: type(ladderLogic::gateType::NC), logicGate(type), output(false), firstPin(false), firstPinTaken(false),
										secondPin(false), secondPinTaken(false) {}

				normallyClosedGate::normallyClosedGate(int *firstpin)
								: type(ladderLogic::gateType::NC), logicGate(type), output(false), firstPin(firstpin), firstPinTaken(false),
										secondPin(false), secondPinTaken(false) {

				}*/

				normallyClosedGate::normallyClosedGate(int *firstpin, int *output)
								: type(ladderLogic::gateType::NC), logicGate(type), firstPin(firstpin), output(output)
								{
/*										if(firstPin == nullptr){
												firstPin = new int;
										}
										if(output == nullptr){
												output = new int;
										}*/
										//*output = 0;
								}

				void normallyClosedGate::executeGateLogic() {
						if (*firstPin == 0) {
								*output = 0;
								return;
						} else if (*firstPin == 1) {
								*output = 1;
								return;
						}
				}

				int *normallyClosedGate::getfirstpin() {
						return firstPin;
				}

				int *normallyClosedGate::getoutput() {
						return output;
				}

				void normallyClosedGate::setfirstPin(int *input1) {
						*firstPin = *input1;
				}

/*				bool normallyClosedGate::getfirstPin() {
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
				}*/

}
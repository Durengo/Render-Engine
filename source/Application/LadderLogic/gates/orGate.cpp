#include "orGate.h"

namespace ladderLogic {

/*				orGate::orGate()
								: type(ladderLogic::gateType::OR), logicGate(type), output(false), firstPin(false), firstPinTaken(false),
										secondPin(false), secondPinTaken(false) {}

				orGate::orGate(int *firstPin, int *secondPin)
								: type(ladderLogic::gateType::OR), logicGate(type), output(false), firstPin(firstPin), firstPinTaken(false),
										secondPin(secondPin), secondPinTaken(false) {

				}*/

				orGate::orGate(int *firstPin, int *secondPin, int *output)
								: type(ladderLogic::gateType::OR), logicGate(type), firstPin(firstPin), secondPin(secondPin), output(output){
/*						if(firstPin == nullptr){
								firstPin = new int;
						}
						if(secondPin == nullptr){
								secondPin = new int;
						}
						if(output == nullptr){
								output = new int;
						}*/
						//*output = 0;
				}

				void orGate::executeGateLogic() {
						if (*firstPin == 1 || *secondPin == 1) {
								*output = 1;
								return;
						} else {
								*output = 0;
								return;
						}
				}

				int *orGate::getfirstpin() {
						return firstPin;
				}

				int *orGate::getsecondpin() {
						return secondPin;
				}

				int *orGate::getoutput() {
						return output;
				}

				void orGate::setfirstPin(int *input1) {
						*firstPin = *input1;
				}

				void orGate::setsecondPin(int *input2) {
						*secondPin = *input2;
				}

/*				bool orGate::getfirstPin() {
						if (!firstPinTaken) {
								std::cout << "Enter first input pin for " << getgateType() << " : ";
								std::cin >> firstPin;
								firstPinTaken = true;
						}
						return firstPin;
				}

				bool orGate::getsecondPin() {
						if (!secondPinTaken) {
								std::cout << "Enter first input pin for " << getgateType() << " : ";
								std::cin >> secondPin;
								secondPinTaken = true;
						}
						return secondPin;
				}

				bool orGate::executeOrGateLogic() {
						bool a = getfirstPin();
						bool b = getsecondPin();
						if (a == 1 || b == 1) {
								output = true;
								return output;
						} else {
								output = false;
								return output;
						}
				}*/

}
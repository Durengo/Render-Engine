#include "andGate.h"

namespace ladderLogic {

/*				andGate::andGate()
								: type(ladderLogic::gateType::AND), logicGate(type), output(false), firstPin(false), firstPinTaken(false),
										secondPin(false), secondPinTaken(false) {}*/

/*				andGate::andGate(int *firstPin, int *secondPin)
								: type(ladderLogic::gateType::AND), logicGate(type), output(false), firstPin(firstPin), firstPinTaken(false),
										secondPin(secondPin), secondPinTaken(false) {}*/

				andGate::andGate(int *firstPin, int *secondPin, int *output)
								: type(ladderLogic::gateType::AND), logicGate(type),firstPin(firstPin), secondPin(secondPin), output(output){
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

				void andGate::executeGateLogic() {
						if (*firstPin == 1 && *secondPin == 1) {
								*output = 1;
								return;
						} else {
								*output = 0;
								return;
						}
				}

				int *andGate::getfirstpin() {
						return firstPin;
				}

				int *andGate::getsecondpin() {
						return secondPin;
				}

				int *andGate::getoutput() {
						return output;
				}

				void andGate::setfirstPin(int *input1) {
						*firstPin = *input1;
				}

				void andGate::setsecondPin(int *input2) {
						*secondPin = *input2;
				}

/*				bool andGate::getfirstPin() {
						if (!firstPinTaken) {
								std::cout << "Enter first input pin for " << getgateType() << " : ";
								std::cin >> firstPin;
								firstPinTaken = true;
						}
						return firstPin;
				}

				bool andGate::getsecondPin() {
						if (!secondPinTaken) {
								std::cout << "Enter first input pin for " << getgateType() << " : ";
								std::cin >> secondPin;
								secondPinTaken = true;
						}
						return secondPin;
				}*/


/*
				bool andGate::executeAndGateLogic() {
						bool a = getfirstPin();
						bool b = getsecondPin();
						if (a == 1 && b == 1) {
								output = true;
								return output;
						} else {
								output = false;
								return output;
						}
				}*/
}
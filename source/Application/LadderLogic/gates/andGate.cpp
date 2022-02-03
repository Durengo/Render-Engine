#include "andGate.h"

namespace ladderLogic {

				andGate::andGate()
								: type(ladderLogic::gateType::AND), logicGate(type), output(false), firstPin(false), firstPinTaken(false),
										secondPin(false), secondPinTaken(false)	{}


				bool andGate::getfirstPin() {
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
				}

				bool andGate::executeAndGateLogic() {
						bool a = getfirstPin();
						bool b = getsecondPin();
						if (a == 1 && b == 1)	{
								output = true;
								return output;
						}	else {
								output = false;
								return output;
						}
				}
}
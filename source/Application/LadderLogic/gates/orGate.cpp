#include "orGate.h"

namespace ladderLogic {

				orGate::orGate()
								: type(ladderLogic::gateType::OR), logicGate(type), output(false), firstPin(false), firstPinTaken(false),
										secondPin(false), secondPinTaken(false)	{}

				bool orGate::getfirstPin() {
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
						if (a == 1 || b == 1)	{
								output = true;
								return output;
						}	else {
								output = false;
								return output;
						}
				}
}
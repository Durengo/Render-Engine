#include "andGate.h"

namespace ladderLogic {

				andGate::andGate(std::string gateLable)
								: logicGate(gateLable), firstPinTaken(false), secondPinTaken(false)	{
				}

				bool andGate::getfirstPin() {
						if (!firstPinTaken)	{
								std::cout << "Enter first input pin for " << getLabel() << " : ";
								std::cin >> firstPin;
								firstPinTaken = true;
						}
						return firstPin;
				}

				bool andGate::getsecondPin() {
						if (!secondPinTaken)	{
								std::cout << "Enter first input pin for " << getLabel() << " : ";
								std::cin >> secondPin;
								secondPinTaken = true;
						}
						return secondPin;
				}

				bool andGate::executeGateLogic() {
						bool a = getfirstPin();
						bool b = getsecondPin();
						if (a == 1 && b == 1) { return true; } else { return false; }
				}
}
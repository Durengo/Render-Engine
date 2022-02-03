#include "normallyOpenGate.h"

namespace ladderLogic {

				normallyOpenGate::normallyOpenGate()
								: type(ladderLogic::gateType::NO), logicGate(type), output(true), firstPin(false), firstPinTaken(false),
										secondPin(false), secondPinTaken(false)	{}

				bool normallyOpenGate::getfirstPin() {
						if (!firstPinTaken) {
								std::cout << "Enter first input pin for " << getgateType() << " : ";
								std::cin >> firstPin;
								firstPinTaken = true;
						}
						return firstPin;
				}

				bool normallyOpenGate::executeNormallyOpenGateLogic() {
						bool a = getfirstPin();
						if (a == 0)	{
								output = true;
								return output;
						}	else if (a == 1)	{
								output = false;
								return output;
						}
				}
}
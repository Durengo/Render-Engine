#pragma once

#include "logicGate.h"

namespace ladderLogic {
				class normallyOpenGate : virtual public logicGate {
				public:
								normallyOpenGate();

								normallyOpenGate(int *firstpin, int *output);

								void executeGateLogic();

								int* getfirstpin();

								int* getoutput();

								void setfirstPin(int* input1);
								/*

								bool getfirstPin();

								bool executeNormallyOpenGateLogic();*/

				protected:

								gateType type;

								int* firstPin;
								int* output;

/*								bool output;

								int firstPin, firstPinTaken;

								int secondPin, secondPinTaken;*/
				};
}
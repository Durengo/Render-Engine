#pragma once

#include "logicGate.h"

namespace ladderLogic {
				class normallyClosedGate : virtual public logicGate {
				public:
								normallyClosedGate();

								normallyClosedGate(int *firstpin, int *output);

								void executeGateLogic();

								int* getfirstpin();

								int* getoutput();

								void setfirstPin(int* input1);
								/*

								bool getfirstPin();

								bool executeNormallyCloseGateLogic();*/

				protected:

								gateType type;

								int* firstPin;
								int* output;

/*								bool output;

								bool firstPin, firstPinTaken;

								bool secondPin, secondPinTaken;*/
				};
}
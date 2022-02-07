#pragma once

#include "logicGate.h"

namespace ladderLogic {
				class andGate : virtual public logicGate {
				public:
								andGate();

								andGate(int *firstPin, int *secondPin, int *output);

								void executeGateLogic();

								int* getfirstpin();

								int* getsecondpin();

								int* getoutput();

								void setfirstPin(int* input1);

								void setsecondPin(int* input2);

/*								bool getfirstPin();

								bool getsecondPin();

								bool executeAndGateLogic();*/

				protected:

								gateType type;

								int* firstPin;
								int* secondPin;
								int* output;

/*								bool output;

								bool firstPin, firstPinTaken;

								bool secondPin, secondPinTaken;*/
				};
}
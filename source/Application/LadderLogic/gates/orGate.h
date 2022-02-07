#pragma once

#include "logicGate.h"

namespace ladderLogic {
				class orGate : virtual public logicGate {
				public:
								orGate();

								orGate(int *firstPin, int *secondPin, int *output);

								void executeGateLogic();

								int* getfirstpin();

								int* getsecondpin();

								int* getoutput();

								void setfirstPin(int* input1);

								void setsecondPin(int* input2);

/*								bool getpin();

								bool getfirstPin();

								bool getsecondPin();

								bool executeOrGateLogic();*/

				protected:
								gateType type;

								int* firstPin;
								int* secondPin;
								int* output;
/*
								bool output;

								bool firstPin, firstPinTaken;

								bool secondPin, secondPinTaken;*/
				};
}
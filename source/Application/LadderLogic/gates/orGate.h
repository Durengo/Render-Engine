#pragma once

#include "logicGate.h"

namespace ladderLogic {
				class orGate : virtual public logicGate {
				public:
								orGate();

								bool getpin();

								bool getfirstPin();

								bool getsecondPin();

								bool executeOrGateLogic();

				private:
								gateType type;

								bool output;

								bool firstPin, firstPinTaken;

								bool secondPin, secondPinTaken;
				};
}
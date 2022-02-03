#pragma once

#include "logicGate.h"

namespace ladderLogic {
				class andGate : virtual public logicGate {
				public:
								andGate();

								bool getfirstPin();

								bool getsecondPin();

								bool executeAndGateLogic();

				protected:

								gateType type;

								bool output;

								bool firstPin, firstPinTaken;

								bool secondPin, secondPinTaken;
				};
}
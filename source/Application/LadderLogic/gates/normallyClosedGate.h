#pragma once

#include "logicGate.h"

namespace ladderLogic {
				class normallyClosedGate : virtual public logicGate {
				public:
								normallyClosedGate();

								bool getfirstPin();

								bool executeNormallyCloseGateLogic();

				protected:

								gateType type;

								bool output;

								bool firstPin, firstPinTaken;

								bool secondPin, secondPinTaken;
				};
}
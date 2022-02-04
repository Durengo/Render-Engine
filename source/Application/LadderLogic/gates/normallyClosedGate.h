#pragma once

#include "logicGate.h"

namespace ladderLogic {
				class normallyClosedGate : virtual public logicGate {
				public:
								normallyClosedGate();

								normallyClosedGate(int firstpin);

								bool getfirstPin();

								bool executeGateLogic();

								bool executeNormallyCloseGateLogic();

				protected:

								gateType type;

								bool output;

								bool firstPin, firstPinTaken;

								bool secondPin, secondPinTaken;
				};
}
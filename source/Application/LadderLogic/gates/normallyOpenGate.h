#pragma once

#include "logicGate.h"

namespace ladderLogic {
				class normallyOpenGate : virtual public logicGate {
				public:
								normallyOpenGate();

								bool getfirstPin();

								bool executeNormallyOpenGateLogic();

				protected:

								gateType type;

								bool output;

								bool firstPin, firstPinTaken;

								bool secondPin, secondPinTaken;
				};
}
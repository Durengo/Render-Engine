#pragma once

#include "logicGate.h"

namespace ladderLogic {
				class normallyOpenGate : virtual public logicGate {
				public:
								normallyOpenGate();

								normallyOpenGate(int firstpin);

								bool getfirstPin();

								bool executeGateLogic();

								bool executeNormallyOpenGateLogic();

				protected:

								gateType type;

								bool output;

								bool firstPin, firstPinTaken;

								bool secondPin, secondPinTaken;
				};
}
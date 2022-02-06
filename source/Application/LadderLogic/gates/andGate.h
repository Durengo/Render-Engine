#pragma once

#include "logicGate.h"

namespace ladderLogic {
	class andGate : virtual public logicGate {
	public:
		andGate();

		andGate(bool firstPin, bool secondPin);

		bool getfirstPin();

		bool getsecondPin();

		bool executeGateLogic();

		bool executeAndGateLogic();

	protected:

		gateType type;

		bool output;

		bool firstPin, firstPinTaken;

		bool secondPin, secondPinTaken;
	};
}
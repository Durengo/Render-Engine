#pragma once

#include "logicGate.h"

namespace ladderLogic {
	class orGate : virtual public logicGate {
	public:
		orGate();

		orGate(bool firstPin, bool secondPin);

		bool getpin();

		bool getfirstPin();

		bool getsecondPin();

		bool executeGateLogic();

		bool executeOrGateLogic();

	protected:
		gateType type;

		bool output;

		bool firstPin, firstPinTaken;

		bool secondPin, secondPinTaken;
	};
}
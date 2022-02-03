#pragma once

#include "logicGate.h"

namespace ladderLogic {
				class andGate : public logicGate {
				public:
								andGate(std::string gateLable);

								bool getfirstPin();

								bool getsecondPin();

								virtual bool executeGateLogic() override;

				protected:
bool firstPin, firstPinTaken;
bool secondPin, secondPinTaken;
				};
}
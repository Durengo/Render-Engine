#pragma once

#include "logicGate.h"

namespace ladderLogic {
				class orGate : public logicGate{
				public:
								orGate(std::string gateLable);

								bool getpin();
				private:
								bool pin, pinTaken;
				};
}
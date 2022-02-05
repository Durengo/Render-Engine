#pragma once

#include <iostream>

namespace ladderLogic {

				enum gateType {
								NONE = 0,
								NO = 1,
								NC = 2,
								AND = 3,
								OR = 4
				};

				class logicGate {
				public:
								logicGate(gateType type);

								gateType getgateType() const;

				protected:
								gateType type;
				};

}
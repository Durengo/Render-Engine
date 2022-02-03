#pragma once

#include <iostream>

namespace ladderLogic {

				class logicGate {
				public:
								logicGate(std::string gateLable);

								std::string getLabel();

								bool getOutput();

								virtual bool executeGateLogic();

				protected:
								std::string gateLabel;

								bool output;
				};

}
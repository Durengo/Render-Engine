#pragma once

#include <iostream>

namespace lgates {
				class logicgate {
				public:
								logicgate(std::string lbl) {
										label = lbl;
								}

								std::string getLabel() {
										return label;
								}

								bool getOutput() {
										output = performGateLogic();
										return output;
								}

								virtual bool performGateLogic() {
										std::cout << "ERROR! performGateLogic BASE" << std::endl;
										return false;
								}

								virtual void setNextPin(bool source) {
										std::cout << "ERROR! setNextPin BASE" << std::endl;
								}

				private:
								std::string label;

								bool output;
				};
}
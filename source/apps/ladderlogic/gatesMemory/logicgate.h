#pragma once

#include <iostream>

namespace lgates {
				class logicgate {
				public:
								logicgate(std::string lbl) {
										label = lbl;
										output = new int;
								}

								std::string getLabel() {
										return label;
								}

								int* getOutput() {
/*										if(output == nullptr){
												output = new int;
										}*/
										*output = performGateLogic();
										return output;
								}

								void setOutput(int* OB) {
										output = OB;
								}

								virtual int performGateLogic() {
										std::cout << "ERROR! performGateLogic BASE" << std::endl;
										return 0;
								}

								virtual void setNextPin(int* source) {
										std::cout << "ERROR! setNextPin BASE" << std::endl;
								}

				private:
								std::string label;

								int* output;
				};
}
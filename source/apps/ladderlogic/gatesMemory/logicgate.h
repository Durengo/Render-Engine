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

								virtual int* returnpin1(){
										std::cout << "ERROR! returnpin1 BASE. RETURNING NULLPTR" << std::endl;
										return nullptr;
								}

								virtual int* returnpin2(){
										std::cout << "ERROR! returnpin1 BASE. RETURNING NULLPTR" << std::endl;
										return nullptr;
								}

				private:
								std::string label;

								int* output;
				};
}
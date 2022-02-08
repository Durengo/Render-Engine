#pragma once

#include "logicgate.h"

namespace lgates {
				class unary : public logicgate {
				public:
								unary(std::string lbl) : logicgate(lbl) {
										pin = new int;
										pinTaken = new int;
										*pinTaken = 0;
								}

								int* getPin() {
										if (*pinTaken == 0) {
												std::cout << "Enter Pin input for gate " << getLabel() << ": ";
												std::cin >> *pin;
												*pinTaken = 1;
										}
										return pin;
								}

								virtual void setNextPin(int* source) {
										if (*pinTaken == 0) {
												pin = source;
												*pinTaken = 1;
										}	else {
												return;
										}
								}

				private:
								int* pin, *pinTaken;
				};
}
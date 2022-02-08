#pragma once

#include "logicgate.h"

namespace lgates {
				class unary : public logicgate {
				public:
								unary(std::string lbl) : logicgate(lbl) {
										pinTaken = false;
								}

								bool getPin() {
										if (pinTaken == false) {
												std::cout << "Enter Pin input for gate " << getLabel() << ": ";
												std::cin >> pin;
												pinTaken = true;
										}
										return pin;
								}

								virtual void setNextPin(bool source) {
										if (pinTaken == false) {
												pin = source;
												pinTaken = true;
										}	else {
												return;
										}
								}

				private:
								bool pin, pinTaken;
				};
}
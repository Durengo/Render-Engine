#pragma once

#include "logicgate.h"

namespace lgates {
				class binary : public logicgate {
				public:
								binary(std::string lbl) : logicgate(lbl) {
										pinATaken = false;
										pinBTaken = false;
								}

								bool getPinA() {
										if (pinATaken == false) {
												std::cout << "Enter Pin A input for gate " << getLabel() << ": ";
												std::cin >> pinA;
												pinATaken = true;
										}
										return pinA;
								}

								bool getPinB() {
										if (pinBTaken == false) {
												std::cout << "Enter Pin B input for gate " << getLabel() << ": ";
												std::cin >> pinB;
												pinBTaken = true;
										}
										return pinB;
								}

								virtual void setNextPin(bool source) {
										if (pinATaken == false) {
												pinA = source;
												this->pinATaken = true;
										}	else if (pinBTaken == false) {
												pinB = source;
												this->pinBTaken = true;
										}
								}

				private:
								bool pinA, pinATaken, pinB, pinBTaken;
				};
}
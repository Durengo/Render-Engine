#pragma once

#include "logicgate.h"

namespace lgates {
				class binary : public logicgate {
				public:
								binary(std::string lbl) : logicgate(lbl) {
										pinA = new int;
										pinB = new int;
										pinATaken = new int;
										pinBTaken = new int;
										*pinATaken = 0;
										*pinBTaken = 0;
								}

								int* getPinA() {
										if (*pinATaken == 0) {
												std::cout << "Enter Pin A input for gate " << getLabel() << ": ";
												std::cin >> *pinA;
												*pinATaken = 1;
										}
										return pinA;
								}

								int* getPinB() {
										if (*pinBTaken == 0) {
												std::cout << "Enter Pin B input for gate " << getLabel() << ": ";
												std::cin >> *pinB;
												*pinBTaken = 1;
										}
										return pinB;
								}

								virtual void setNextPin(int* source) {
										if (*pinATaken == 0) {
												pinA = source;
												*this->pinATaken = 1;
										}	else if (*pinBTaken == 0) {
												pinB = source;
												*this->pinBTaken = 1;
										}
								}

								virtual int* returnpin1(){
										return pinA;
								}

								virtual int* returnpin2(){
										return pinB;
								}

				private:
								int* pinA, *pinATaken, *pinB, *pinBTaken;
				};
}
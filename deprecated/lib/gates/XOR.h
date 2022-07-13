#pragma once

#include "binary.h"

namespace lgates {
				class XOR : public binary	{
				public:
								XOR(std::string lbl) : binary(lbl) {};

								virtual bool performGateLogic() {
										bool a = getPinA();
										bool b = getPinB();
										if (a == 1 && b == 1) {
												return false;
										}	else if (a == 1 || b == 1) {
												return true;
										}	else {
												return false;
										}
								}
				};
}
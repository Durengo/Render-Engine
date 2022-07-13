#pragma once

#include "binary.h"

namespace lgates {
				class NOR : public binary	{
				public:
								NOR(std::string lbl) : binary(lbl) {};

								virtual bool performGateLogic() {
										bool a = getPinA();
										bool b = getPinB();
										if (a == 0 && b == 0) {
												return true;
										}	else {
												return false;
										}
								}
				};
}
#pragma once

#include "binary.h"

namespace lgates {
				class AND : public binary {
				public:
								AND(std::string lbl) : binary(lbl) {};

								virtual bool performGateLogic() {
										bool a = getPinA();
										bool b = getPinB();
										if (a == 1 && b == 1) {
												return true;
										} else {
												return false;
										}
								}
				};
}
#pragma once

#include "binary.h"

namespace lgates {
				class OR : public binary {
				public:
								OR(std::string lbl) : binary(lbl) {};

								virtual int performGateLogic() {
										int* a = getPinA();
										int* b = getPinB();
										if (*a == 1 || *b == 1) {
												return 1;
										} else {
												return 0;
										}
								}
				};
}
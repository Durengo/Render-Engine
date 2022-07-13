#pragma once

#include "unary.h"

namespace lgates {
				class NO : public unary {
				public:
								NO(std::string lbl) : unary(lbl) {};

								virtual int performGateLogic() {
										if (!*getPin()) {
												return 1;
										} else {
												return 0;
										}
								}
				};
}
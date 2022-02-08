#pragma once

#include "unary.h"

namespace lgates {
				class NC : public unary {
				public:
								NC(std::string lbl) : unary(lbl) {};

								virtual int performGateLogic() {
										if (!*getPin()) {
												return 0;
										} else {
												return 1;
										}
								}
				};
}
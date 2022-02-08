#pragma once

#include "unary.h"

namespace lgates {
				class NOT : public unary {
				public:
								NOT(std::string lbl) : unary(lbl) {};

								virtual bool performGateLogic() {
										if (getPin()) {
												return false;
										} else {
												return true;
										}
								}
				};
}
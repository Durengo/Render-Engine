#pragma once

#include "binary.h"

namespace lgates {
				class NAND : public binary	{
				public:
								NAND(std::string lbl) : binary(lbl) {};

								virtual bool performGateLogic() {
										bool a = getPinA();
										bool b = getPinB();
										if (a == 0 && b == 0) {
												return true;
										}	else if (a == 1 || b == 1) {
												return true;
										}	else {
												return false;
										}
								}
				};
}
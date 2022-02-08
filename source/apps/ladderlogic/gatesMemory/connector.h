#pragma once

#include "logicgate.h"

namespace lgates {

				class connector {
				public:
								connector(logicgate *fgate, logicgate *tgate) {
										fromgate = fgate;
										togate = tgate;
										togate->setNextPin(fromgate->getOutput());
								}

								logicgate *getFrom() {
										return fromgate;
								}

								logicgate *getTo() {
										return togate;
								}

				private:
								logicgate *fromgate, *togate;
				};
}
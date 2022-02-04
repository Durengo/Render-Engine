#include "logicGate.h"

namespace ladderLogic {

				logicGate::logicGate(gateType type)
								: type(type) {
						type = type;
				}

				gateType logicGate::getgateType() const {
						return type;
				}
}
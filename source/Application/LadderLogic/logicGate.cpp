#include "logicGate.h"

namespace ladderLogic {

				logicGate::logicGate(std::string gateLable)
								: gateLabel(gateLable), output(false)	{

				}

				std::string logicGate::getLabel() {
						return gateLabel;
				}

				bool logicGate::getOutput() {
						output = executeGateLogic();
						return output;
				}

				bool logicGate::executeGateLogic() {

				}
}
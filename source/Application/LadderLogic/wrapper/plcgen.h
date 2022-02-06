#pragma once

#include "plc.h"
#include "IOBuffer.h"
#include "../gates/gateList.h"

namespace PLC {
				class plcgen {
				public:
								plcgen(DataManager* managerInstance, PLC::plc *PLCSource, PLC::IOBuffer *IOBuffersource);

				private:
								PLC::plc *plcsource;

								PLC::IOBuffer *iobuffersource;

								DataManager* Manager;

								std::vector<ladderLogic::gateList*> Ladders;
				};
}
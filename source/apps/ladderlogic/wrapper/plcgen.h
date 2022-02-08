#pragma once

#include "plc.h"
#include "IOBuffer.h"
#include "ladderlist.h"
#include "../gatesMemory/connector.h"

namespace PLC {
				class plcgen {
				public:
								ladderLogic::ladderlist* Ladder;

								plcgen(DataManager* managerInstance, PLC::plc *PLCSource, PLC::IOBuffer *IOBuffersource);

								~plcgen();

								void onRender();

								void onImGuiRender();

								void construct();

								void execute();

				private:
								PLC::plc *plcsource;

								PLC::IOBuffer *iobuffersource;

								DataManager* Manager;

								std::vector<lgates::connector*> Connector;

								int* output;

								//std::vector<int*> IBptrs;

								int IBptrs;

								int OBptrs;

								void setinputlabels();

								void setoutputlables();

								void bindSourceBuffersWithOutput();

				};
}
#pragma once

#include "../gates/gateList.h"
#include "IOBuffer.h"

namespace ladderLogic {

				class scriptline : public ladderLogic::gateList {
				public:
								scriptline(DataManager &managerInstance, PLC::IOBuffer *buffer);

								~scriptline();

								void execute();

								void toggleisComplete();

								void onRender(PLC::IOBuffer &buffer);

								void onImGuiRender();

								std::pair<std::pair<std::vector<int>, std::vector<std::string>>, std::vector<std::string>>
								createInstructionSet();

//								const std::unique_ptr<ladderLogic::gateList> &getLineInstance() const;
//
//								void setLineInstance(const std::unique_ptr<ladderLogic::gateList> &lineInstance);

								scriptline *next = nullptr;

								void setUniqueID(int uniqueid);

								int getUniqueID() const;

				protected:
								//ladderLogic::gateList glist;
								DataManager *managerInstance;

								PLC::IOBuffer *ioBuffer;

								//bool isActive, isComplete;
								bool isComplete;

								int uniqueID;
				};

}
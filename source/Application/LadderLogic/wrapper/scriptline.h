#pragma once

#include "../gates/gateList.h"
#include "IOBuffer.h"

namespace ladderLogic {

				class scriptline : public ladderLogic::gateList{
				public:
								scriptline(DataManager &managerInstance);

								~scriptline();

								void dosomething();

								void onRender(ladderLogic::IOBuffer &buffer);

								void onImGuiRender();

								const std::string &getInputLabel() const;

								void setInputLabel(const std::string &inputLabel);

								const std::string &getOutputLabel() const;

								void setOutputLabel(const std::string &outputLabel);

								bool isInput() const;

								void setInput(bool input);

								bool isOutput() const;

								void setOutput(bool output);

								bool isActive1() const;

								void setIsActive(bool isActive);

								bool isComplete1() const;

								void setIsComplete(bool isComplete);

//								const std::unique_ptr<ladderLogic::gateList> &getLineInstance() const;
//
//								void setLineInstance(const std::unique_ptr<ladderLogic::gateList> &lineInstance);

				private:
								DataManager* managerInstance;
								std::string inputLabel, outputLabel;
								bool input, output;
								bool isActive, isComplete;
								//ladderLogic::gateList gate;
								//std::unique_ptr<ladderLogic::gateList> lineInstance;
				};

}
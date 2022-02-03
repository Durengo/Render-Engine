#pragma once

#include <string>
#include <vector>
#include <memory>

namespace ladderLogic {

				class IOBuffer {
				public:
								IOBuffer();

								void initInputBuffer();

								void initOutputBuffer();

								std::string* getInputLabel();

								std::string* getOutputLabel();

								void displayInputLabel();

								void displayOutputLabel();

				private:

								//std::unique_ptr<std::string> inputLable;

								std::string inputLabel[10][2];

								std::string outputLabel[10][2];
				};

}
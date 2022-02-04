#pragma once

#include <string>
#include <vector>
#include <memory>

namespace ladderLogic {

				struct inputPair{
								std::pair<std::string, bool> boundInputBuffer[10];
				};

				struct outputPair{
								std::pair<std::string, bool> boundOutputBuffer[10];
				};

				class IOBuffer {
				public:
								IOBuffer();

								void newIOBuffer();

								void initInputBuffer();

								void initOutputBuffer();

								void initInputBools();

								void initOutputBools();

								void bindBuffers();

								void changeSingleBufferElement(int position, bool buffertype, std::string newbuffername, bool newbufferstate);

								void changeInput(int position);

								void changeOutput(int position);

								void displayBuffers();

								void displayInputBuffers();

								void displayOutputBuffers();

								std::pair<std::string, bool>* getInputBufferPointer();

								std::pair<std::string, bool>* getOutputBufferPointer();

				private:

								inputPair boundInputPair;

								outputPair boundOutputPair;

								bool inputBools[10];

								bool outputBools[10];

								std::string inputLabel[10];

								std::string outputLabel[10];

				};

}
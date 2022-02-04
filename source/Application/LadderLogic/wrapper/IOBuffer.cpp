#include "IOBuffer.h"

#include <iostream>

namespace ladderLogic {
				IOBuffer::IOBuffer() {
						std::cout << "\nconstructor\n";
						newIOBuffer();
				}

				void IOBuffer::newIOBuffer() {
						initInputBuffer();
						initOutputBuffer();
						initInputBools();
						initOutputBools();
						bindBuffers();
				}

				void IOBuffer::bindBuffers() {
						for (int i = 0; i < 10; i++) {
								{
										boundInputPair.boundInputBuffer[i].first = inputLabel[i];
										boundInputPair.boundInputBuffer[i].second = inputBools[i];
								}
								{
										boundOutputPair.boundOutputBuffer[i].first = outputLabel[i];
										boundOutputPair.boundOutputBuffer[i].second = outputBools[i];
								}
//								std::cout << "Input buffer: " << boundInputPair.boundInputBuffer[i].first << " : "
//																		<< boundInputPair.boundInputBuffer[i].second << ";\n";
//								std::cout << "Output buffer: " << boundOutputPair.boundOutputBuffer[i].first << " : "
//																		<< boundOutputPair.boundOutputBuffer[i].second << ";\n";
						}
				}

				void IOBuffer::initInputBuffer() {
						std::string inputX = "X";
						int count = 1;
						for (int i = 0; i < 10; i++) {
								std::string combo = inputX + std::to_string(count);
								inputLabel[i] = combo;
								count++;
								combo = inputX + std::to_string(count);
								//std::cout << inputLabel[i] << std::endl;
						}
				}

				void IOBuffer::initOutputBuffer() {
						std::string inputX = "Q";
						int count = 1;
						for (int i = 0; i < 10; i++) {
								std::string combo = inputX + std::to_string(count);
								outputLabel[i] = combo;
								count++;
								combo = inputX + std::to_string(count);
								//std::cout << outputLabel[i] << std::endl;
						}
				}

				void IOBuffer::initInputBools() {
						for (int i = 0; i < 10; i++) {
								inputBools[i] = false;
								//std::cout << inputBools[i] << std::endl;
						}
				}

				void IOBuffer::initOutputBools() {
						for (int i = 0; i < 10; i++) {
								outputBools[i] = false;
								//std::cout << outputBools[i] << std::endl;
						}
				}

				void
				IOBuffer::changeSingleBufferElement(int position, bool buffertype, std::string newbuffername, bool newbufferstate) {
						if (position <= 0 || position > 10) {
								std::cout << "\nEXCEPTION: OUT OF BOUNDS\n";
						}
						position = position - 1;
						if (buffertype == 0) //if input
						{
								inputLabel[position] = newbuffername;
								inputBools[position] = newbufferstate;
								boundInputPair.boundInputBuffer[position].first = inputLabel[position];
								boundInputPair.boundInputBuffer[position].second = inputBools[position];
						}
						if (buffertype == 1) //if output
						{
								outputLabel[position] = newbuffername;
								outputBools[position] = newbufferstate;
								boundOutputPair.boundOutputBuffer[position].first = outputLabel[position];
								boundOutputPair.boundOutputBuffer[position].second = outputBools[position];
						}

				}

				void IOBuffer::changeInput(int position) {
						if (position <= 0 || position > 10) {
								std::cout << "\nEXCEPTION: OUT OF BOUNDS\n";
						}
						position = position - 1;
						if (!boundInputPair.boundInputBuffer[position].second) {
								inputBools[position] = true;
								boundInputPair.boundInputBuffer[position].second = true;
						} else if (boundInputPair.boundInputBuffer[position].second) {
								inputBools[position] = false;
								boundInputPair.boundInputBuffer[position].second = false;
						}
				}

				void IOBuffer::changeOutput(int position) {
						if (position <= 0 || position > 10) {
								std::cout << "\nEXCEPTION: OUT OF BOUNDS\n";
						}
						position = position - 1;
						if (!boundOutputPair.boundOutputBuffer[position].second) {
								outputBools[position] = true;
								boundOutputPair.boundOutputBuffer[position].second = true;
						} else if (boundOutputPair.boundOutputBuffer[position].second) {
								outputBools[position] = false;
								boundOutputPair.boundOutputBuffer[position].second = false;
						}
				}

				void IOBuffer::displayBuffers() {
						std::cout << "Input buffer: \n";
						for (int i = 0; i < 10; i++) {
								std::cout << boundInputPair.boundInputBuffer[i].first << " : "
																		<< boundInputPair.boundInputBuffer[i].second << ";\n";
						}
						std::cout << "Output buffer: \n";
						for (int i = 0; i < 10; i++) {
								std::cout << boundOutputPair.boundOutputBuffer[i].first << " : "
																		<< boundOutputPair.boundOutputBuffer[i].second << ";\n";
						}
				}

				void IOBuffer::displayInputBuffers() {
						std::cout << "Input buffer: \n";
						for (int i = 0; i < 10; i++) {
								std::cout << boundInputPair.boundInputBuffer[i].first << " : "
																		<< boundInputPair.boundInputBuffer[i].second << ";\n";
						}
				}

				void IOBuffer::displayOutputBuffers() {
						std::cout << "Output buffer: \n";
						for (int i = 0; i < 10; i++) {
								std::cout << boundOutputPair.boundOutputBuffer[i].first << " : "
																		<< boundOutputPair.boundOutputBuffer[i].second << ";\n";
						}
				}

				std::pair<std::string, bool> *IOBuffer::getInputBufferPointer() {
						return boundInputPair.boundInputBuffer;
				}

				std::pair<std::string, bool> *IOBuffer::getOutputBufferPointer() {
						return boundOutputPair.boundOutputBuffer;
				}


}

/*				void IOBuffer::displayInputLabel() {
						for (int i = 0; i < 10; i++) {
								for (int j = 0; j < 2; j++) {
										std::cout << outputLabel[i][j] << std::endl;
								}
						}
						std::cout << std::endl;
				}

				void IOBuffer::displayOutputLabel() {
						for (int i = 0; i < 10; i++) {
								for (int j = 0; j < 2; j++) {
										std::cout << outputLabel[i][j] << std::endl;
								}
						}
						std::cout << std::endl;
				}*/

/*				void IOBuffer::initInputBuffer() {
						std::string inputX = "X";
						int count = 1;
						for (int i = 0; i < 10; i++) {
								std::string combo = inputX + std::to_string(count);
								for (int j = 0; j < 2; j++) {
										inputLabel[i][j] = combo;
										count++;
										combo = inputX + std::to_string(count);
										//std::cout << inputLabel[i][j] << std::endl;
								}
						}
				}

				void IOBuffer::initOutputBuffer() {
						std::string inputX = "Q";
						int count = 1;
						for (int i = 0; i < 10; i++) {
								std::string combo = inputX + std::to_string(count);
								for (int j = 0; j < 2; j++) {
										outputLabel[i][j] = combo;
										count++;
										combo = inputX + std::to_string(count);
										//std::cout << outputLabel[i][j] << std::endl;
								}
						}
				}*/

//				std::string *IOBuffer::getInputLabel() {
//						return *inputLabel;
//				}
//
//				std::string *IOBuffer::getOutputLabel() {
//						return *outputLabel;
//				}
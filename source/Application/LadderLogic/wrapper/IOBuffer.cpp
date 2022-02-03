#include "IOBuffer.h"

#include <iostream>

namespace ladderLogic {
				IOBuffer::IOBuffer() {
						std::cout << "\nconstructor\n";
						initInputBuffer();
						initOutputBuffer();
				}

				void IOBuffer::initInputBuffer() {
						std::string inputX = "X";
						int count = 1;
						for (int i = 0; i < 10; i++) {
								std::string combo = inputX + std::to_string(count);
								for (int j = 0; j < 2; j++) {
										inputLabel[i][j] = combo;
										count++;
										combo = inputX + std::to_string(count);
										std::cout << inputLabel[i][j] << std::endl;
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
										std::cout << outputLabel[i][j] << std::endl;
								}
						}
				}

				std::string *IOBuffer::getInputLabel() {
						return *inputLabel;
				}

				std::string *IOBuffer::getOutputLabel() {
						return *outputLabel;
				}

				void IOBuffer::displayInputLabel() {
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
				}

}
#include "IOBuffer.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace PLC{
								IOBuffer::IOBuffer(DataManager *managerInstance, const std::string &Filepath)
												: Manager(managerInstance), filepath(Filepath), totalinputlabels(0), totaloutputlabels(0) {
										{
												std::fstream quickCHK(Filepath);
												if (quickCHK.is_open()) {
														C->PTC("HOOKED FILEPATH: ", filepath, "\n");
												} else {
														C->PTC("FILEPATH UNREACHABLE!\n");
												}
										}
										BUFFERSOURCE IBOSource = parseIOBUFFERS(Filepath);
										setIOBUFFERS(IBOSource);

								}

								IOBuffer::~IOBuffer() {}

								BUFFERSOURCE IOBuffer::parseIOBUFFERS(const std::string &Filepath) {
										std::ifstream stream(Filepath);

										enum class BUFFERType {
														NONE = 0,
														INPUTBUFFER = 1,
														OUTPUTBUFFER = 2
										};

										std::string line;
										std::stringstream ss[3];
										BUFFERType type = BUFFERType::NONE;

										while (getline(stream, line)) {
												if (line.find('#') != std::string::npos) {
														if (line.find("INPUT") != std::string::npos) {
																type = BUFFERType::INPUTBUFFER;
														} else if (line.find("OUTPUT") != std::string::npos) {
																type = BUFFERType::OUTPUTBUFFER;
														}
												} else {
														ss[(int) type] << line << '\n';
												}
										}
										//std::cout << ss[4].str();
										return {ss[1].str(), ss[2].str()};
								}

								void IOBuffer::setIOBUFFERS(BUFFERSOURCE &IBOSource) {
										setinputbuffers(IBOSource);
										setoutputbuffers(IBOSource);
								}

				void IOBuffer::setinputbuffers(BUFFERSOURCE &IBOSource) {
						std::stringstream stream(IBOSource.INPUTBUFFER);
						std::string line;
						int count = 1;
						while (getline(stream, line)) {
								if (line.find(count)) {
										totalinputlabels = totalinputlabels + 1;
										//if (line.find("NO") != std::string::npos) {
										std::string inputlabel = line;
										std::string inputstate = line;
										if(totalinputlabels >= 10){
												inputlabel = inputlabel.substr(3, 3);
												inputstate = inputstate.substr(7, 11);
										}
										else{
												inputlabel = inputlabel.substr(2, 3);
												inputstate = inputstate.substr(6, 10);
										}
														int state = 0;
														if(inputstate == "FALSE")
														{
																state = 0;
														}
														else if(inputstate == "TRUE"){
																state = 1;
														}
														int * stateptr = new int;
														*stateptr = state;
												IBUFFER.first.first.push_back(count);
												IBUFFER.first.second.emplace_back(inputlabel);
												IBUFFER.second.emplace_back(stateptr);
									//	}
								}
								count++;
						}
				}

				void IOBuffer::setoutputbuffers(BUFFERSOURCE &IBOSource) {
						std::stringstream stream(IBOSource.OUTPUTBUFFER);
						std::string line;
						int count = 1;
						while (getline(stream, line)) {
								if (line.find(count)) {
										totaloutputlabels = totaloutputlabels + 1;
										//if (line.find("NO") != std::string::npos) {
										std::string outputlabel = line;
										std::string outputstate = line;
										if(totaloutputlabels >= 10){
												outputlabel = outputlabel.substr(3, 3);
												outputstate = outputstate.substr(7, 11);
										}
										else{
												outputlabel = outputlabel.substr(2, 3);
												outputstate = outputstate.substr(6, 10);
										}
										int state = 0;
										if(outputstate == "FALSE")
										{
												state = 0;
										}
										else if(outputstate == "TRUE"){
												state = 1;
										}
										int * stateptr = new int;
										*stateptr = state;
										OBUFFER.first.first.push_back(count);
										OBUFFER.first.second.emplace_back(outputlabel);
										OBUFFER.second.emplace_back(stateptr);
										//	}
								}
								count++;
						}
				}
								void IOBuffer::printAllInfo() {
										std::cout << "Total labels: " << totalinputlabels + totaloutputlabels << std::endl;
										std::cout << "Total input labels: " << totalinputlabels << std::endl;
										std::cout << "Total output labels: " << totaloutputlabels << std::endl;
										std::cout << "Input labels:\n";
										for(int i = 0; i < totalinputlabels; i++){
												std::cout << IBUFFER.first.first[i] << ". LABEL: " << IBUFFER.first.second[i] << "; STATE: " << *IBUFFER.second[i] << std::endl;
										}
										std::cout << "Output labels:\n";
										for(int i = 0; i < totaloutputlabels; i++){
												std::cout << OBUFFER.first.first[i] << ". LABEL: " << OBUFFER.first.second[i] << "; STATE: " << *OBUFFER.second[i] << std::endl;
										}
								}

				void IOBuffer::switchIBUFFERELEMENT(const std::string &ilabel) {
						for(int i = 0; i < totalinputlabels; i++){
								if(IBUFFER.first.second[i] == ilabel){
										if(*IBUFFER.second[i] == 1){
												*IBUFFER.second[i] = 0;
												return;
										}
										else if(*IBUFFER.second[i] == 0){
												*IBUFFER.second[i] = 1;
												return;
										}
								}
						}
				}

				void IOBuffer::switchOBUFFERELEMENT(const std::string &olabel) {
						for(int i = 0; i < totaloutputlabels; i++){
								if(OBUFFER.first.second[i] == olabel){
										if(*OBUFFER.second[i] == 1){
												*OBUFFER.second[i] = 0;
												return;
										}
										else if(*OBUFFER.second[i] == 0){
												*OBUFFER.second[i] = 1;
												return;
										}
								}
						}
				}

				int IOBuffer::getTotalinputlabels() const {
						return totalinputlabels;
				}

				int IOBuffer::getTotaloutputlabels() const {
						return totaloutputlabels;
				}

/*				std::string *IOBuffer::getIbufferLabel(int which)  {
						return &IBUFFER.first.second[which];
				}

				int *IOBuffer::getIbufferState(int which) {
						return &IBUFFER.second[which];
				}

				std::string *IOBuffer::getObufferLabel(int which) {
						return &OBUFFER.first.second[which];
				}

				int *IOBuffer::getObufferState(int which) {
						return &OBUFFER.second[which];
				}*/
}

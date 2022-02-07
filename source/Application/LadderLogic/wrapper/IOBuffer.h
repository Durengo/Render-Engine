#pragma once

#include <string>
#include <vector>

#include "../utils/DataManager.h"

namespace PLC {
				struct BUFFERSOURCE {
								std::string INPUTBUFFER;
								std::string OUTPUTBUFFER;
				};

				class IOBuffer {
				public:
								IOBuffer(DataManager *managerInstance, const std::string &Filepath);

								~IOBuffer();

								void printAllInfo();

								void switchIBUFFERELEMENT(const std::string& ilabel);

								void switchOBUFFERELEMENT(const std::string& olabel);

/*								std::string *getIbufferLabel(int which);

								int *getIbufferState(int which);

								std::string *getObufferLabel(int which);

								int *getObufferState(int which);*/

								int getTotalinputlabels() const;

								int getTotaloutputlabels() const;

								std::pair<std::pair<std::vector<int>, std::vector<std::string>>, std::vector<int>> IBUFFER;

								int totalinputlabels;

								std::pair<std::pair<std::vector<int>, std::vector<std::string>>, std::vector<int>> OBUFFER;

								int totaloutputlabels;

				protected:
								DataManager *Manager;

								std::string filepath;

								BUFFERSOURCE parseIOBUFFERS(const std::string &Filepath);

								void setIOBUFFERS(BUFFERSOURCE &IBOSource);

								void setinputbuffers(BUFFERSOURCE &IBOSource);

								void setoutputbuffers(BUFFERSOURCE &IBOSource);
				};

}
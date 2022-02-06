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

								void setinputbuffers(BUFFERSOURCE &IBOSource);

								void setoutputbuffers(BUFFERSOURCE &IBOSource);

				protected:
								DataManager *Manager;

								std::string filepath;

								BUFFERSOURCE parseIOBUFFERS(const std::string &Filepath);

				public:
								const std::pair<std::pair<std::vector<int>, std::vector<std::string>>, std::vector<bool>> &getIbuffer() const;

								void
								setIbuffer(const std::pair<std::pair<std::vector<int>, std::vector<std::string>>, std::vector<bool>> &ibuffer);

								int getTotalinputlabels() const;

								void setTotalinputlabels(int totalinputlabels);

								const std::pair<std::pair<std::vector<int>, std::vector<std::string>>, std::vector<bool>> &getObuffer() const;

								void
								setObuffer(const std::pair<std::pair<std::vector<int>, std::vector<std::string>>, std::vector<bool>> &obuffer);

								int getTotaloutputlabels() const;

								void setTotaloutputlabels(int totaloutputlabels);

				protected:
								void setIOBUFFERS(BUFFERSOURCE &IBOSource);

								std::pair<std::pair<std::vector<int>, std::vector<std::string>>, std::vector<bool>> IBUFFER;

								int totalinputlabels;

								std::pair<std::pair<std::vector<int>, std::vector<std::string>>, std::vector<bool>> OBUFFER;

								int totaloutputlabels;
				};

}
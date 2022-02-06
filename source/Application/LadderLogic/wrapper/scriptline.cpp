#include "scriptline.h"

namespace ladderLogic {

	scriptline::scriptline(DataManager& managerInstance, ladderLogic::IOBuffer* buffer)
		: gateList(&managerInstance, buffer), managerInstance(&managerInstance), ioBuffer(buffer),
		isComplete(false), inputLabel("X0"), outputLabel("Q0"), input(false), output(false)
		//										isActive(true),
	{
	}


	scriptline::~scriptline() {
		std::cout << "\ndecon\n";
	}

	void scriptline::execute() {
		if (isComplete) {
			return;
		}

		toggleisComplete();
	}

	void scriptline::toggleisComplete() {
		if (isComplete) {
			isComplete = false;
		}
		else if (!isComplete) {
			isComplete = true;
		}
	}

	void scriptline::setUniqueID(int uniqueid) {
		uniqueID = uniqueid;
	}

	int scriptline::getUniqueID() const {
		return uniqueID;
	}

	void scriptline::onRender(IOBuffer& buffer) {

	}

	void scriptline::onImGuiRender() {

	}


}
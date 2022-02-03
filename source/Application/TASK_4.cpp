#include "LadderLogic/ladderLogicHeader.h"
#include "LadderLogic/utils/LocalHeaderPreLoader.h"

int main()
{
		DataManager manager;

		nodelist scriptlines(&manager, UserList::Admin);
		scriptlines.CreateUser("script","script");
		scriptlines.DisplayList();

//		ladderLogic::andGate gate2("and gate");
//		std::cout << gate2.getOutput();
//
//		ladderLogic::signalNode signalinput;
//		signalinput.print();

		return 0;
}
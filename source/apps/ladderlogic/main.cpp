#include <iostream>

#include "utils/LocalHeaderPreLoader.h"
#include "gatesMemory/gatesHeaderLoader.h"
#include "wrapper/IOBuffer.h"
#include "wrapper/plc.h"
#include "wrapper/plcgen.h"

#include "basictest.h"

int main() {
		/*basictest test;
test.runtest();*/

		DataManager Manager;

		//PLC::plc plc(&Manager, "../source/res/template.plc");
		PLC::plc plc(&Manager, "../source/apps/ladderlogic/res/1LXG.plc");
		plc.printAllInfo();

		PLC::IOBuffer iob(&Manager, "../source/apps/ladderlogic/res/simpleiob.iob");
		iob.printAllInfo();

		PLC::plcgen plcgen1(&Manager, &plc, &iob);

		//std::cout << plcgen1.Ladder->getnodebypos(1);
		//PLC::plcgen gen1(&Manager, &plc, &iob);
		//ladderLogic::gateList buga(&Manager, &plc, &iob);

		plcgen1.execute();


		std::cin.get();
		return 0;
}

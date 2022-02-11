#include <iostream>

#include "wrapper/wrapperHeader.h"

#include "basictest.h"

int main() {
		basictest test;
		test.runtest(0);


		DataManager Manager;

		PLC::IOBuffer iob(&Manager, "../source/apps/ladderlogic/res/ll/iob/uandbgates.iob");
		iob.printAllInfo();

		PLC::plc plc(&Manager, "../source/apps/ladderlogic/res/ll/plc/UaB.plc");
		plc.printAllInfo();

		PLC::plcgen plcgen1(&Manager, &plc, &iob);
		plcgen1.execute();
		plcgen1.switchinput(2, 3);
		//plcgen1.switchinput(4);
		plcgen1.execute();

		std::cin.get();
		return 0;
}

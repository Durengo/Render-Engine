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
/*		{
				DataManager Manager;

				//PLC::plc plc(&Manager, "../source/res/template.plc");
				PLC::plc plc(&Manager, "../source/apps/ladderlogic/res/NC.plc");
				plc.printAllInfo();

				PLC::IOBuffer iob(&Manager, "../source/apps/ladderlogic/res/simpleiob.iob");
				iob.printAllInfo();

				PLC::plcgen plcgen1(&Manager, &plc, &iob);
				while(true){
						plcgen1.switchinput();
						plcgen1.execute();
				}
		}*/
		int loopon = 1;
		while(loopon){
				DataManager Manager;
				PLC::IOBuffer iob(&Manager, "../source/apps/ladderlogic/res/simpleiob.iob");
				iob.printAllInfo();
				std::cout << "\n0. to exit\n";
				std::cout << "1. NO.iob TEST\n";
				std::cout << "2. NC.iob TEST\n";
				std::cout << "3. a.iob TEST\n";
				std::cout << "4. b.iob TEST\n";
				std::cout << "5. 1LXG.iob TEST\n\n";
				int getint = Manager.ConsoleHook->Get_Input_By_INT(0, 5);
				if (getint == 0) {
						loopon = 0;
						break;
				}
				else if(getint == 1){
						PLC::plc plc(&Manager, "../source/apps/ladderlogic/res/NO.plc");
						plc.printAllInfo();
						PLC::plcgen plcgen2(&Manager, &plc, &iob);
						plcgen2.execute();
				}
				else if(getint == 2){
						PLC::plc plc(&Manager, "../source/apps/ladderlogic/res/NC.plc");
						plc.printAllInfo();
						PLC::plcgen plcgen2(&Manager, &plc, &iob);
						plcgen2.execute();
				}
				else if(getint == 3){
						PLC::plc plc(&Manager, "../source/apps/ladderlogic/res/a.plc");
						plc.printAllInfo();
						PLC::plcgen plcgen2(&Manager, &plc, &iob);
						plcgen2.execute();
				}
				else if(getint == 4){
						PLC::plc plc(&Manager, "../source/apps/ladderlogic/res/b.plc");
						plc.printAllInfo();
						PLC::plcgen plcgen2(&Manager, &plc, &iob);
						plcgen2.execute();
				}
				else if(getint == 5){
						PLC::plc plc(&Manager, "../source/apps/ladderlogic/res/1LXG.plc");
						plc.printAllInfo();
						PLC::plcgen plcgen2(&Manager, &plc, &iob);
						plcgen2.execute();
				}
		}

		//std::cout << plcgen1.Ladder->getnodebypos(1);
		//PLC::plcgen gen1(&Manager, &plc, &iob);
		//ladderLogic::gateList buga(&Manager, &plc, &iob);


		std::cin.get();
		return 0;
}

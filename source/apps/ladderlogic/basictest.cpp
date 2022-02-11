#include "basictest.h"

#include "wrapper/wrapperHeader.h"

void basictest::runtest(int test){
		if (test == 0) {
				std::cout << "NO TEST STATEMENT\n";
				return;
		}
		else if(test == 1){
				int loopon = 1;
				while(loopon){
						DataManager Manager;
						PLC::IOBuffer iob(&Manager, "../source/apps/ladderlogic/res/ll/iob/unarygates.iob");
						iob.printAllInfo();
						std::cout << "\nUNARY GATE TEST\n";
						std::cout << "\n0. to exit\n";
						std::cout << "1. NO.plc TEST\n";
						std::cout << "2. NC.plc TEST\n";
						std::cout << "3. a.plc TEST\n";
						std::cout << "4. b.plc TEST\n";
						std::cout << "5. 1LXG.plc TEST\n\n";
						int getint = Manager.ConsoleHook->Get_Input_By_INT(0, 5);
						if (getint == 0) {
								loopon = 0;
								break;
						}
						else if(getint == 1){
								PLC::plc plc(&Manager, "../source/apps/ladderlogic/res/ll/plc/NO.plc");
								plc.printAllInfo();
								PLC::plcgen plcgen1(&Manager, &plc, &iob);
								plcgen1.execute();
								plcgen1.switchinput(1);
								plcgen1.execute();
						}
						else if(getint == 2){
								PLC::plc plc(&Manager, "../source/apps/ladderlogic/res/ll/plc/NC.plc");
								plc.printAllInfo();
								PLC::plcgen plcgen1(&Manager, &plc, &iob);
								plcgen1.execute();
								plcgen1.switchinput(1);
								plcgen1.execute();
						}
						else if(getint == 3){
								PLC::plc plc(&Manager, "../source/apps/ladderlogic/res/ll/plc/a.plc");
								plc.printAllInfo();
								PLC::plcgen plcgen1(&Manager, &plc, &iob);
								plcgen1.execute();
								plcgen1.switchinput(1);
								plcgen1.execute();
						}
						else if(getint == 4){
								PLC::plc plc(&Manager, "../source/apps/ladderlogic/res/ll/plc/b.plc");
								plc.printAllInfo();
								PLC::plcgen plcgen1(&Manager, &plc, &iob);
								plcgen1.execute();
								plcgen1.switchinput(1);
								plcgen1.execute();
						}
						else if(getint == 5){
								PLC::plc plc(&Manager, "../source/apps/ladderlogic/res/ll/plc/1LXG.plc");
								plc.printAllInfo();
								PLC::plcgen plcgen1(&Manager, &plc, &iob);
								plcgen1.execute();
								plcgen1.switchinput(1);
								plcgen1.execute();
						}
				}
				return;
		}
		else if(test == 2){
				int loopon = 1;
				while(loopon) {
						DataManager Manager;
						PLC::IOBuffer iob(&Manager, "../source/apps/ladderlogic/res/ll/iob/binarygates.iob");
						iob.printAllInfo();
						std::cout << "\nBINARY GATE TEST\n";
						std::cout << "\n0. to exit\n";
						std::cout << "1. AND.plc TEST\n";
						std::cout << "2. OR.plc TEST\n\n";
						int getint = Manager.ConsoleHook->Get_Input_By_INT(0, 2);
						if (getint == 0) {
								loopon = 0;
								break;
						}
						else if (getint == 1) {
								PLC::plc plc(&Manager, "../source/apps/ladderlogic/res/ll/plc/AND.plc");
								plc.printAllInfo();
								PLC::plcgen plcgen2(&Manager, &plc, &iob);
								plcgen2.execute();
								plcgen2.switchinput(1);
								plcgen2.execute();
								plcgen2.switchinput(2);
								plcgen2.execute();
								plcgen2.switchinput(2);
								plcgen2.execute();
								plcgen2.switchinput(1);
								plcgen2.execute();
						}
						else if (getint == 2) {
								PLC::plc plc(&Manager, "../source/apps/ladderlogic/res/ll/plc/OR.plc");
								plc.printAllInfo();
								PLC::plcgen plcgen2(&Manager, &plc, &iob);
								plcgen2.execute();
								plcgen2.switchinput(1);
								plcgen2.execute();
								plcgen2.switchinput(2);
								plcgen2.execute();
								plcgen2.switchinput(2);
								plcgen2.execute();
								plcgen2.switchinput(1);
								plcgen2.execute();
						}
				}
		}
		else if(test == 3){
				int loopon = 1;
				while(loopon) {
						DataManager Manager;
						PLC::IOBuffer iob(&Manager, "../source/apps/ladderlogic/res/ll/iob/uandbgates.iob");
						iob.printAllInfo();
						std::cout << "\nUNARY GATES TEST\n";
						std::cout << "\n0. to exit\n";
						std::cout << "1. UaB.plc TEST\n\n";
						int getint = Manager.ConsoleHook->Get_Input_By_INT(0, 1);
						if (getint == 0) {
								loopon = 0;
								break;
						}
						else if (getint == 1) {
								PLC::plc plc(&Manager, "../source/apps/ladderlogic/res/ll/plc/UaB.plc");
								plc.printAllInfo();
								PLC::plcgen plcgen3(&Manager, &plc, &iob);
								plcgen3.execute();
								plcgen3.switchinput(1);
								plcgen3.execute();
								plcgen3.switchinput(2);
								plcgen3.execute();
								plcgen3.switchinput(3);
								plcgen3.execute();
								plcgen3.switchinput(4);
								plcgen3.execute();
								plcgen3.switchinput(1, 2);
								plcgen3.execute();
								plcgen3.switchinput(1, 2);
								plcgen3.execute();
								plcgen3.switchinput(3, 4);
								plcgen3.execute();
								plcgen3.switchinput(3, 4);
								plcgen3.execute();
								plcgen3.switchinput(2, 3);
								plcgen3.execute();
								plcgen3.switchinput(1);
								plcgen3.execute();
								plcgen3.switchinput(1);
								plcgen3.execute();
								plcgen3.switchinput(4);
								plcgen3.execute();
								plcgen3.switchinput(4);
								plcgen3.execute();
								plcgen3.switchinput(1, 4);
								plcgen3.execute();
						}
				}


		}
		else{
				std::cout << "TEST STATEMENT OUT OF BOUNDS.\n";
				return;
		}
}
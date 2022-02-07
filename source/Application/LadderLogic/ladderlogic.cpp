//#include "gates/ladderLogicHeader.h"
//#include "utils/LocalHeaderPreLoader.h"

//#include "tests/testUnit.h"

//#include "wrapper/scriptlinelist.h"
//#include "wrapper/instructionSet.h"
//#include "wrapper/plc.h"
//#include "wrapper/IOBuffer.h"
#include "wrapper/plcgen.h"
#include "gates/gateList.h"

int main() {
//		DataManager Manager;
//		testUnit test;
//		test.setGlobalTick(2);


		DataManager Manager;
/*		ladderLogic::IOBuffer* ioBuffer = new ladderLogic::IOBuffer;
		ladderLogic::scriptlinelist line1(Manager, ioBuffer);
		line1.createLine();
		line1.head->createGate(ladderLogic::AND, 1, 1);
		line1.head->deleteByPos(1);
		line1.head->displayList();*/

		//ladderLogic::instructionSet instset(Manager);
//instset.createInstructionSet();

//PLC::plc plc(Manager, "res/oneladder.plc");
		PLC::plc plc(&Manager, "../source/Application/LadderLogic/res/oneladder.plc");
		//PLC::plc plc(Manager, "../source/Application/LadderLogic/res/oneladder.plc");
		plc.printAllInfo();

		PLC::IOBuffer iob(&Manager, "../source/Application/LadderLogic/res/template.iob");
		iob.printAllInfo();

		PLC::plcgen gen1(&Manager, &plc, &iob);

		ladderLogic::gateList buga(&Manager, &plc, &iob);
		//buga.linkPLCandBuffers();

		//std::cout << "\n" << 5 / 2 << std::endl;

		std::cin.get();

//ladderLogic::IOBuffer iobuf;
//
//iobuf.displayInputLabel();
//iobuf.displayOutputLabel();

//		ladderLogic::scriptline line2(&Manager);
//		line2.createGate(ladderLogic::gateType::OR);

//iobuf.provideInputBuffer(1,2);

//		ladderLogic::andGate gate2("and gate");
//		std::cout << gate2.getOutput();
//
//		ladderLogic::signalNode signalinput;
//		signalinput.print();

		return 0;
}
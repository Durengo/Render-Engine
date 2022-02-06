#include "testUnit.h"

void testUnit::setGlobalTick(int T) {
	Global_Tick = T;
	switch (Global_Tick) {
	case 0:
		return;
	case 1:
		testBasicAppLogic();
		return;
	case 2:
		testWrapper();
		return;
	default:
		return;
	}
}

void testUnit::testBasicAppLogic() {
	/*DataManager manager;

	ladderLogic::gateList scriptlist(&manager);
	scriptlist.createGate(ladderLogic::gateType::AND);
	std::cout << scriptlist.head->getm_GateTypeByString();
	scriptlist.createGate(ladderLogic::gateType::OR);
	std::cout << scriptlist.head->next->getm_GateTypeByString();
	scriptlist.createGate(ladderLogic::gateType::NO);
	std::cout << scriptlist.head->next->next->getm_GateTypeByString();
	scriptlist.createGate(ladderLogic::gateType::NC);
	std::cout << scriptlist.head->next->next->next->getm_GateTypeByString();
	scriptlist.displayList();
	scriptlist.executeSpecificGateLogic(0);
	scriptlist.executeSpecificGateLogic(1);
	scriptlist.executeSpecificGateLogic(2);
	scriptlist.executeSpecificGateLogic(3);

	scriptlist.deleteByPos(5);
	scriptlist.deleteByPos(3);
	scriptlist.displayList();
	scriptlist.createGate(ladderLogic::gateType::AND);
	std::cout << scriptlist.head->getm_GateTypeByString();
	scriptlist.displayList();
	scriptlist.createGate(ladderLogic::gateType::AND);
	std::cout << scriptlist.head->getm_GateTypeByString();
	scriptlist.displayList();
	scriptlist.createGate(ladderLogic::gateType::AND);
	std::cout << scriptlist.head->getm_GateTypeByString();
	scriptlist.deleteByPos(3);
	scriptlist.deleteByPos(3);
	scriptlist.deleteByPos(1);
	scriptlist.displayList();
	scriptlist.createGate(ladderLogic::gateType::NC);
	std::cout << scriptlist.head->next->next->next->getm_GateTypeByString();
	scriptlist.createGate(ladderLogic::gateType::NC);
	std::cout << scriptlist.head->next->next->next->getm_GateTypeByString();
	scriptlist.createGate(ladderLogic::gateType::NC);
	std::cout << scriptlist.head->next->next->next->getm_GateTypeByString();
	scriptlist.createGate(ladderLogic::gateType::NC);
	std::cout << scriptlist.head->next->next->next->getm_GateTypeByString();
	scriptlist.createGate(ladderLogic::gateType::NC);
	std::cout << scriptlist.head->next->next->next->getm_GateTypeByString();
	scriptlist.createGate(ladderLogic::gateType::NC);
	std::cout << scriptlist.head->next->next->next->getm_GateTypeByString();
	scriptlist.displayList();
	ladderLogic::gateList scriptlist2(&manager);
	scriptlist2.createGate(ladderLogic::gateType::AND);
	std::cout << scriptlist2.head->getm_GateTypeByString();
	scriptlist2.createGate(ladderLogic::gateType::OR);
	std::cout << scriptlist2.head->next->getm_GateTypeByString();
	scriptlist2.createGate(ladderLogic::gateType::NO);
	std::cout << scriptlist2.head->next->next->getm_GateTypeByString();
	scriptlist2.createGate(ladderLogic::gateType::NC);
	std::cout << scriptlist2.head->next->next->next->getm_GateTypeByString();
	scriptlist2.displayList();
	scriptlist.executeSpecificGateLogic(0);
	scriptlist.executeSpecificGateLogic(1);
	scriptlist.executeSpecificGateLogic(2);
	scriptlist.executeSpecificGateLogic(3);

	scriptlist2.deleteByPos(5);
	scriptlist2.deleteByPos(3);
	scriptlist2.displayList();
	scriptlist2.createGate(ladderLogic::gateType::AND);
	std::cout << scriptlist2.head->getm_GateTypeByString();
	scriptlist2.displayList();
	scriptlist2.createGate(ladderLogic::gateType::AND);
	std::cout << scriptlist2.head->getm_GateTypeByString();
	scriptlist2.displayList();
	scriptlist2.createGate(ladderLogic::gateType::AND);
	std::cout << scriptlist2.head->getm_GateTypeByString();
	scriptlist2.deleteByPos(3);
	scriptlist2.deleteByPos(3);
	scriptlist2.deleteByPos(1);
	scriptlist2.displayList();
	scriptlist2.createGate(ladderLogic::gateType::NC);
	std::cout << scriptlist2.head->next->next->next->getm_GateTypeByString();
	scriptlist2.createGate(ladderLogic::gateType::NC);
	std::cout << scriptlist2.head->next->next->next->getm_GateTypeByString();
	scriptlist2.createGate(ladderLogic::gateType::NC);
	std::cout << scriptlist2.head->next->next->next->getm_GateTypeByString();
	scriptlist2.createGate(ladderLogic::gateType::NC);
	std::cout << scriptlist2.head->next->next->next->getm_GateTypeByString();
	scriptlist2.createGate(ladderLogic::gateType::NC);
	std::cout << scriptlist2.head->next->next->next->getm_GateTypeByString();
	scriptlist2.createGate(ladderLogic::gateType::NC);
	std::cout << scriptlist2.head->next->next->next->getm_GateTypeByString();
	scriptlist2.displayList();*/
}

void testUnit::testWrapper() {
	//		DataManager Manager;
	//		ladderLogic::IOBuffer* ioBuffer = new ladderLogic::IOBuffer;
	//		ladderLogic::scriptline line1(*&Manager, ioBuffer);
	//		line1.createGate(ladderLogic::gateType::AND);
	//		line1.createGate(ladderLogic::gateType::AND);
	//		line1.displayList();
	//		line1.deleteByPos(2);
	//		line1.displayList();
	//		line1.createGate(ladderLogic::gateType::AND);
	//		line1.displayList();
	//		ladderLogic::scriptline line2(*&Manager, ioBuffer);
	//		line2.createGate(ladderLogic::gateType::OR);
	//		line2.createGate(ladderLogic::gateType::OR);
	//		line2.createGate(ladderLogic::gateType::OR);
	//		line2.createGate(ladderLogic::gateType::OR);
	//		line2.displayList();
	//		ladderLogic::scriptline line3(*&Manager, ioBuffer);
	//		line3.createGate(ladderLogic::gateType::OR);
	//		line3.createGate(ladderLogic::gateType::OR);
	//		line3.createGate(ladderLogic::gateType::OR);
	//		line3.displayList();
}
//void testUnit::testAccountModule()
//{
//  DataManager localInstance;
//  AdministratorList adminl(&localInstance, gateList::Admin);
//  adminl.CreateUser("admin", "admin");
//  adminl.CreateUser("admin", "admin");
//  adminl.CreateUser("admin1", "admin");
//  adminl.CreateUser("admin2", "admin");
//  adminl.CreateUser("admin3", "admin");
//  adminl.DisplayList();
//  TeacherList teacherl(&localInstance, gateList::Lecturer);
//  teacherl.CreateUser("teach", "teach");
//  teacherl.CreateUser("teach", "teach");
//  teacherl.CreateUser("teach1", "teach");
//  teacherl.DisplayList();
//  adminl.DisplayList();
//  StudentList studl(&localInstance, gateList::Learner);
//  studl.CreateUser("stud", "teach");
//  studl.CreateUser("stud", "teach");
//  studl.CreateUser("stud1", "teach");
//  studl.CreateUser("stud2", "teach");
//  studl.DisplayList();
//  teacherl.DisplayList();
//  adminl.DisplayList();
//  adminl.deleteByPos(1);
//  adminl.deleteByPos(3);
//  studl.deleteByPos(2);
//  adminl.DisplayList();
//}
//
//void testUnit::testAccountAndClassroomModule(){
//  DataManager localInstance;
//
//#define Print localInstance.ConsoleHook
//
//  AdministratorList adminl(&localInstance, gateList::Admin);
//  TeacherList teacherl(&localInstance, gateList::Lecturer);
//  StudentList studl(&localInstance, gateList::Learner);
//
//  adminl.CreateUser("admin", "admin");
//  adminl.CreateUser("admin1", "admin");
//  adminl.CreateUser("admin2", "admin");
//  adminl.CreateUser("admin3", "admin");
//
//  teacherl.CreateUser("teach", "teach");
//  teacherl.CreateUser("teach1", "teach");
//
//  studl.CreateUser("stud", "teach");
//  studl.CreateUser("stud1", "teach");
//  studl.CreateUser("stud2", "teach");
//
//
//  adminl.DisplayList();
//  teacherl.DisplayList();
//  studl.DisplayList();
//
//  Print->PTC("\n\n\nclassroom tests:\n\n\n");
//  Print->PTC("objects: ", localInstance.getTotalClassrooms());
//  ClassroomList math(&localInstance);
//
//
//  math.add("\nmathematics\n");
//  Print->PTC("objects: ", localInstance.getTotalClassrooms());
//
//  Print->PTC("\n", math.length(), "\n");
//  math.displayAll();
//  math.removeFront();
//  Print->PTC("objects: ", localInstance.getTotalClassrooms());
//  math.displayAll();
//
//  math.removeFront();
//  Print->PTC("objects: ", localInstance.getTotalClassrooms());
//
//  Print->PTC("\n\n\n\n\n:END\n");
//
//}
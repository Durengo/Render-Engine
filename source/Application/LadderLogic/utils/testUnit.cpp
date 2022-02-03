//#include "testUnit.h"
//
//void testUnit::setGlobalTick(int T)
//{
//  Global_Tick = T;
//  switch (Global_Tick) {
//    case 0:
//      return;
//    case 1:
//      testAccountModule();
//      return;
//    case 2:
//      testAccountAndClassroomModule();
//      return;
//    default:
//      return;
//  }
//}
//
//void testUnit::testAccountModule()
//{
//  DataManager localInstance;
//  AdministratorList adminl(&localInstance, UserList::Admin);
//  adminl.CreateUser("admin", "admin");
//  adminl.CreateUser("admin", "admin");
//  adminl.CreateUser("admin1", "admin");
//  adminl.CreateUser("admin2", "admin");
//  adminl.CreateUser("admin3", "admin");
//  adminl.DisplayList();
//  TeacherList teacherl(&localInstance, UserList::Lecturer);
//  teacherl.CreateUser("teach", "teach");
//  teacherl.CreateUser("teach", "teach");
//  teacherl.CreateUser("teach1", "teach");
//  teacherl.DisplayList();
//  adminl.DisplayList();
//  StudentList studl(&localInstance, UserList::Learner);
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
//  AdministratorList adminl(&localInstance, UserList::Admin);
//  TeacherList teacherl(&localInstance, UserList::Lecturer);
//  StudentList studl(&localInstance, UserList::Learner);
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
#pragma once

#include "LocalHeaderPreLoader.h"

class testUnit {
private:
  int Global_Tick = 0;
//Global variable for running tests.
//Global_Tick = 0 - Run nothing;
//Global_Tick = 1 - Account Module test;
//Global_Tick = 2 - Account and classroom list manipulation test;

public:
  void setGlobalTick(int T);

  void testAccountModule();

  void testAccountAndClassroomModule();

};
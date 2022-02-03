#pragma once

#include "../utils/LocalHeaderPreLoader.h"

class testUnit {
private:
				int Global_Tick = 0;
//Global variable for running tests.
//Global_Tick = 0 - Run nothing;
//Global_Tick = 1 - Gate Logic Test;

public:
				void setGlobalTick(int T);

				void testBasicAppLogic();

};
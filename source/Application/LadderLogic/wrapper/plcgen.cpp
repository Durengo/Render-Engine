#include "plcgen.h"

namespace PLC{

				plcgen::plcgen(DataManager* managerInstance, PLC::plc *PLCSource, PLC::IOBuffer *IOBuffersource)
				: Manager(managerInstance), plcsource(PLCSource), iobuffersource(IOBuffersource)
				{
						//iobuffersource.
				}
}
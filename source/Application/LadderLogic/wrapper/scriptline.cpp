#include "scriptline.h"

namespace ladderLogic{

				scriptline::scriptline(DataManager &managerInstance)
								: managerInstance(&managerInstance), ladderLogic::gateList(&managerInstance), inputLabel("X0"), outputLabel("Q0"), input(false), output(false),
										isActive(true), isComplete(false)
										//lineInstance(std::make_unique<ladderLogic::gateList>(&managerInstance))
										{
											//lineInstance->displayList();
										}


				scriptline::~scriptline() {
std::cout << "\ndecon\n";
				}
}
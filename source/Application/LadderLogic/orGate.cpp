#include "orGate.h"

namespace ladderLogic{

				orGate::orGate(std::string gateLable) : logicGate(gateLable), pinTaken(false) {

				}

				bool orGate::getpin() {
						if(!pinTaken){
								std::cout << "Enter first input pin for " << getLabel() << " : ";
								std::cin >> pin;
								pinTaken = true;
						}
						return pin;
						}
}
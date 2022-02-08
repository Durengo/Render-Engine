#include <iostream>

#include "gates/gatesHeaderLoader.h"

int main() {

		using namespace lgates;

		//setting lables
		AND AND1("AND1");
		AND AND2("AND2");
		OR OR3("OR");
		NOT NC4("NOT");
		//changing input
		AND1.setNextPin(1);
		AND1.setNextPin(0);
		AND2.setNextPin(0);
		AND2.setNextPin(0);
		//making comnnections
		connector c1(&AND1, &OR3);
		connector c2(&AND2, &OR3);
		connector c3(&OR3, &NC4);
		std::cout << NC4.getOutput() << std::endl;

		NOR NOR1("NOR1");


		NOR1.setNextPin(0);
		NOR1.setNextPin(0);

		std::cout << "1: " << NOR1.getOutput() << "\n";

		std::cin.get();
		return 0;
}

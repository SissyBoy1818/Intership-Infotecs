#include <iostream>
#include "Journal.h"
#include "Menu.h"

int main(int argc, char* argv[])
{
	if (argc < 3) {
		std::cerr << "Usage: " << argv[0] << " <journal_file> <default_importance>" << std::endl;
		return 1;
	}

	Importance imp;
	try {
		imp = stringToImportance(argv[2]);
	} catch(const std::invalid_argument& e) {
		std::cerr << e.what() << '\n';
		return 1;
	}

	Journal j(argv[1], imp);
	Menu menu(j);

	do{
		menu.printMenu();
	} while (menu.handleControllers());

	return 0;
}
////////////////////////////////////
// RPN CALC & PROGRAMMING LANG
// syusui_s
////////////////////////////////////

// initialization of this program
#include "init.h"

int main(void){
	std::string input;
	
	////////////////////////////////////
	std::cout << PROGNAME << ", version " << PROGVER << std::endl;
	while(1){
		std::cout << INPUTSTR;
		std::getline(std::cin, input);
		std::cout << "{" << delsp(input) << "}" << std::endl;
	}

	return 0;
}


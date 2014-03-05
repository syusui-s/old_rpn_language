////////////////////////////////////
// interpret.h
// these functions 
////////////////////////////////////
void help(){
	std::cout
		<< " -- Special commands -- \n"	
		<< "\t:h, :help \t show this message\n" 
		<< "\t:q, :quit \t exit " << PROGNAME << "\n"
	<< std::endl;
}

void interpret(std::string input){
	if(input[0]==':'){
		if(input==":h" || input==":help" || input==":?") help();
		else if(input==":q" || input==":quit") exit(0);
		else std::cerr << "error: No such a command." << std::endl;
		std::cout << std::endl;
	}else if(delsp(input)==""){
		// do nothing
	}else{
		std::cout << calclate(input) << std::endl;
	}
}

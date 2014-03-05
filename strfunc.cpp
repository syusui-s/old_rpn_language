////////////////////////////////////
// strfunc.cpp
// •¶š—ñ•ÏŒ`—pŠÖ”
////////////////////////////////////

#include <iostream>
#include <string>
#include <list>
//#include "strfunc.h"

// delsp
// delete needless spaces
std::string delsp(std::string input){
	//str+=(std::string)" ";
	input.insert(input.length()," ");
	while(1){
		if(input.find("  ",0)==std::string::npos) break;
		input.erase(input.find("  ",0),1);
	}
	if(input[0]==' ') input.erase(0,1);
	#ifdef DEBUG
	std::cout << input << std::endl;
	#endif

	return input;
}

// split
// devide a string by space and make it into list
std::list<std::string> split(std::string input){
	int i,pos,n=(int)input.length();
	std::list<std::string> output;
	
	pos = 0;
	for(i=0;i<n;i++){
		if(input[i]==' '){
			output.push_back(input.substr(i-pos,pos));
			#if MYDEBUG
			std::cout << input.substr(i-pos,pos) << std::endl;
			#endif
			pos = 0;
			continue;
		}
		pos++;
	}
	return output;
}





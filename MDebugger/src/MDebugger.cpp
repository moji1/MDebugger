//============================================================================
// Name        : MDebugger.cpp
// Author      : mojtaba bagherzadeh (mojtaba@cs.queensu.ca)
// Version     :
//============================================================================

#include <iostream>
#include <thread>
#include "UMLRTDebugger.h"
//#include <typeinfo>




std::string processArgs(int argc, char ** argv){
	if (argc<=1)
			return "";
	else {
		std::stringstream tempStr;
		for (int i=1;i<argc;i++)
			tempStr<<argv[i]<< " ";
		tempStr<<"\n";
		return tempStr.str();
	}
}
int main(int argc, char ** argv) {
	mdebugger::UMLRTDebugger debugger;
	std::cout << "MDebugger is started" << std::endl;
	//std::string c="0fklfk";
	//std::cout<<typeid(debugger).name()<<"\n";
	//std::cout<<"Parsed args are:"<< processArgs(argc,argv)<<"\n";
	debugger.intialize();
	std::string intailCmd=processArgs(argc,argv);
	if (intailCmd!="")
		debugger.setIntialInput(intailCmd);
	std::thread eventRead(&mdebugger::UMLRTDebugger::readEvents,&debugger);
	std::thread cmdInterface(&mdebugger::UMLRTDebugger::cmdMainLoop,&debugger);
	eventRead.join();
	cmdInterface.join();
	return 0;
}

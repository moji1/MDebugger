/*
 * CmdLineInterface.h
 *
 *  Created on: Nov 24, 2016
 *      Author: mojtababagherzadeh
 */

#ifndef CMDINTERFACE_H_
#define CMDINTERFACE_H_
#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>

namespace mdebugger {
typedef struct {
	std::string commandName;
	std::string commandL;
	std::vector<std::vector<std::string>>  commandOptions; // option, mandatory or optional, value name
	std::string commandHelp;
} CMDDesc;
typedef enum {BREAKPOINT,CONTINUEEXEC,HELP,LIST,MODIFY,NEXT,SAVE,VIEW,RUNEXEC,CONNECT,EXIT,RESTART,UNKOWNCOMMAND} mdebuggerCommand;
typedef struct {
	mdebugger::mdebuggerCommand cmdID;
	std::map<std::string,std::string>  commandOptions; // option, mandatory or optional, value name
} ParsedCMD;


class CmdInterface {

public:
	CmdInterface();
	virtual ~CmdInterface();
	void showHelp();
	void getCommand();
	bool parseCommand();
	const std::string& getCommandStr() const;
	void setCommandStr(const std::string& commandStr);
	mdebugger::mdebuggerCommand stringToUserCommad(std::string);
	void showPrompt();
	bool isCommandValid();
	void tokenizeCommand();
	const ParsedCMD& getParsedCmd() const;
	void setParsedCmd(const ParsedCMD& parsedCmd);

private:
	const static std::vector<mdebugger::CMDDesc> cmdDescList;
	std::string commandStr;
	std::vector<std::string> cmdTokens;
	ParsedCMD parsedCMD;

};

} /* namespace mdebugger */

#endif /* CMDINTERFACE_H_ */

/*
 * DebugCommand.h
 *
 *  Created on: Nov 22, 2016
 *      Author: mojtababagherzadeh
 */

#ifndef DEBUGCOMMAND_H_
#define DEBUGCOMMAND_H_
#include "umlrttimespec.hh"
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include "ParsingUtil.h"
#include "SROManager.h"

namespace mdebugger {
enum dbgCmd{EXEC,SETEXECMODE,VARCHANGE,VARVIEW,SETBREAKPOINT,VIEWBREAKPOINTS,REMBREAKPOINT,REMALLBREAKPOINTS,UNKOWN};
typedef std::map<std::string,std::string> CmdParams;

class DebugCommand {
public:
	DebugCommand();
	virtual ~DebugCommand();
	int  getCapsuleIndex() const;
	void setCapsuleIndex(int capsuleIndex);
	const std::string& getCapsuleInstance() const;
	void setCapsuleInstance(const std::string& capsuleInstance);
	const std::string& getCapsuleName() const;
	void setCapsuleName(const std::string& capsuleName);
	dbgCmd getCmdId() const;
	void setCmdId(dbgCmd cmdId);
	const CmdParams& getCmdParams() const;
	void setCmdParams(const CmdParams& cmdParams);
	const std::string& getTraceNo() const;
	void setTraceNo(const std::string& traceNo);
	void setCmdParams(const std::string& paramName,const std::string& paramValue);
	void generateTraceNo();
	std::string serialize();
	std::string serializeParams();
	void deserialize(std::string buffer);
	void deSerializeParams(std::string buffer);
	void clearParams();
	int  paramCount();
	std::string getQualifiedName();
	void setQualifiedName(std::string qualifiedName);
	std::string getCapsuleId();
	std::string getCmdParam(std::string key) ; //return the command param based on provideded key


private:
	std::string capsuleInstance;     // show capsule instance name that generate event
	std::string capsuleName;         // refer to the class name
	int capsuleIndex;
	std::string traceNo;
	dbgCmd cmdId;
	CmdParams cmdParams;
};


inline std::string mdebugger::DebugCommand::getCmdParam(std::string key)  //return the command param based on provideded key
{
	if (this->getCmdParams().count(key))
		return this->getCmdParams().at(key);
	else
		return "";
}

inline int mdebugger::DebugCommand::getCapsuleIndex() const {
	return capsuleIndex;
}

inline void mdebugger::DebugCommand::setCapsuleIndex(int capsuleIndex) {
	this->capsuleIndex = capsuleIndex;
}

inline const std::string& mdebugger::DebugCommand::getCapsuleInstance() const {
	return capsuleInstance;
}

inline void mdebugger::DebugCommand::setCapsuleInstance(const std::string& capsuleInstance) {
	this->capsuleInstance = capsuleInstance;
}

inline const std::string& mdebugger::DebugCommand::getCapsuleName() const {
	return capsuleName;
}

inline void mdebugger::DebugCommand::setCapsuleName(const std::string& capsuleName) {
	this->capsuleName = capsuleName;
}

inline mdebugger::dbgCmd mdebugger::DebugCommand::getCmdId() const {
	return cmdId;
}

inline void mdebugger::DebugCommand::setCmdId(dbgCmd cmdId) {
	this->cmdId = cmdId;
}

inline const mdebugger::CmdParams& mdebugger::DebugCommand::getCmdParams() const {
	return cmdParams;
}

inline void mdebugger::DebugCommand::setCmdParams(const CmdParams& cmdParams) {
	this->cmdParams = cmdParams;
}

inline const std::string& mdebugger::DebugCommand::getTraceNo() const {
	return traceNo;
}

inline void mdebugger::DebugCommand::setTraceNo(const std::string& traceNo) {
	this->traceNo = traceNo;
}



inline void mdebugger::DebugCommand::generateTraceNo() {
	UMLRTTimespec ts;
	ts.getclock(ts);
	std::stringstream ss;
	int r=random();
	ss<<ts.tv_sec<<ts.tv_nsec<<r;
	this->traceNo=ss.str();
}
inline std::string mdebugger::DebugCommand::getQualifiedName(){
	std::stringstream s1;
	s1 << getCapsuleName()<<":"<<getCapsuleInstance()<<":"<<getCapsuleIndex();
	return s1.str();
}
inline std::string mdebugger::DebugCommand::serialize() {
	std::stringstream ss1;
	ss1 << this->getTraceNo() <<";";
	ss1 << this->getCmdId() <<";";
	ss1 << this->getCapsuleName() <<";";
	ss1 << this->getCapsuleInstance() <<";";
	ss1 << this->getCapsuleIndex() <<";";
	if ((this->getCmdParams()).size()>0){
		ss1<<';';
		ss1 << this->serializeParams();
	}
	return ss1.str();
}

inline std::string mdebugger::DebugCommand::serializeParams() {
	std::string ss;
	bool secondRec=false;
	for(std::map<std::string,std::string>::const_iterator it = this->cmdParams.begin(); it != this->cmdParams.end(); ++it)
	{
		if (secondRec)
			ss.append(",");
		else
			secondRec=true;
		ss.append( it->first+":");
		ss.append(it->second);

	}
	return ss;
}

inline void mdebugger::DebugCommand::deserialize(std::string buffer) {
	std::string tempS="";
	std::vector<std::string> tempVector;
	bool newVar=false;
	for (int i=0;i< buffer.length();i++){
		if ((buffer[i]==';'|| buffer[i]=='\n') && newVar){
			newVar=false;
			tempVector.push_back(tempS);
			tempS="";
		}
		else if (buffer[i]!=';'){
			tempS=tempS+(buffer[i]);
			newVar=true;
		}
	}
	if (newVar)
		tempVector.push_back(tempS);
	if (tempVector.size()<5)
		std::cerr<<"Error in parsing event stream, only "<<tempVector.size()<<" are parsed \n";
	else  {
		this->traceNo=tempVector[0];
		this->setCmdId((dbgCmd)(atoi(tempVector[1].c_str())));
		this->setCapsuleName(tempVector[2]);
		this->setCapsuleInstance(tempVector[3]);
		this->setCapsuleIndex(atoi(tempVector[4].c_str()));
		if (tempVector.size()==6)
			this->deSerializeParams(tempVector[5]);
	}


}

inline void mdebugger::DebugCommand::setCmdParams(const std::string& paramName,const std::string& paramValue) {
	if (paramName.length()>=1)
			this->cmdParams[paramName]=paramValue;
}

inline void mdebugger::DebugCommand::deSerializeParams(std::string buffer) {
	std::string tempS="";
	std::vector<std::string> tempVector;
	bool newVar=false;
	for (int i=0;i< buffer.length();i++){
			if ((buffer[i]==',' || buffer[i]=='\n') && newVar){
				newVar=false;
				tempVector.push_back(tempS);
				tempS="";
			}
			else if (buffer[i]!=','){
				tempS=tempS+(buffer[i]);
				newVar=true;
			}
		}
	if (newVar)
		tempVector.push_back(tempS);
	if (tempVector.size()>0){
		this->cmdParams.clear();
		for (int i=0;i<tempVector.size();i++){
			//std::cout<<"Whole value is"<<tempVector[i];
			std::string::size_type sepIndex=tempVector[i].find(":",0);
			std::string key=tempVector[i].substr(0,sepIndex);
			//std::cout<<"key is:"<<key;
			std::string value=tempVector[i].substr(sepIndex+1,tempVector[i].length());
			//std::cout<<"value is:"<<value;
			this->setCmdParams(key, value);
		}
	}
}

inline void mdebugger::DebugCommand::clearParams() {
	this->cmdParams.clear();
}

inline int mdebugger::DebugCommand::paramCount() {
	return this->cmdParams.size();
}

inline void mdebugger::DebugCommand::setQualifiedName(std::string qualifiedName) {
	std::vector<std::string> tempsTokens=Util::split(qualifiedName, ':');
	//std::cout<<tempsTokens.size()<<"\n";
	//std::cout<<tempsTokens[0]<<"\n";
	//std::cout<<tempsTokens[1]<<"\n";
	//std::cout<<tempsTokens[2]<<"\n";
	if (tempsTokens.size()==3){
		this->setCapsuleIndex(atoi(tempsTokens[2].c_str()));
		this->setCapsuleName(tempsTokens[0]);
		this->setCapsuleInstance(tempsTokens[1]);
	}
}

inline mdebugger::DebugCommand::DebugCommand() {
	///
}

inline mdebugger::DebugCommand::~DebugCommand() {
	///
}

inline std::string mdebugger::DebugCommand::getCapsuleId() {
	std::stringstream ss;
	ss<<getCapsuleInstance();
	ss<<getCapsuleIndex();
	return ss.str();
}

} /* namespace mdebugger */
#endif /* DEBUGCOMMAND_H_ */

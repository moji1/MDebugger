/*
 * BreakPointManager.h
 *
 *  Created on: Feb 7, 2017
 *      Author: mojtababagherzadeh
 *      no permission allowed outside MDebugger project
 */

#ifndef SROMANAGER_H_
#define SROMANAGER_H_
enum BreakPointType{TransitionEffectBreakPoint,StateEntryBreakPoint,StateExitBreakPoint};
enum ExecMode{Stepping,Resume,Running};
struct Transition{
	std::string name;
	std::string targetState;
	std::string signalName;
	std::string protocol;
	//Transition(std::string signalName) : signalName(signalName) {};
	void setTransition(std::string name, std::string targetState,std::string signalName,std::string protocol){
		this->name=name;
		this->protocol=protocol;
		this->signalName=signalName;
		this->targetState=targetState;
	}
    /*bool operator () (const Transition& m ) const
    {
        return m.signalName == this->signalName;
    }*/

};
struct BreakPoint{
	std::string loc;
	BreakPointType type;  // 0 = means TransitionEffectBreakPoint  1= StateEntryBreakPoint 2=StateExitBreakPoint
	int place; // 0 means start , 1 means end
};

class SROManager {
public:

	SROManager();
	virtual ~SROManager();
	void addState(std::string name);
	void addTransitionsFromState(std::string name,Transition transition);
	void addBreakPoint(std::string loc,BreakPointType breakType,int place);
	void remBreakPoint(std::string loc,BreakPointType breakType,int place);
	void setExecMode(ExecMode execmode);
	void dumpBreakPointList();
	ExecMode getExecMode();
	bool checkDebug(std::string loc,std::string signalName,std::string protocol,int mode,BreakPointType breakType,int place);
	bool checkBreakPoint(std::string loc,BreakPointType breakType,int place);
	const std::vector<BreakPoint>& getBreakPoints() const;
	const std::map<std::string, std::vector<Transition> >& getTransitions() const;
	void dumpAllTranstion();
	void addTransitionsFromState(std::string stateName,std::string transName,std::string targetName,std::string signalName,std::string protocolName);
	const std::string serializeBreakPoint();
	void deSerializeBreakPoint(std::string breakPointsDump);
	int getStatus() const;
	void setStatus(int status);
	std::string getStatusStr() ;
private:
	std::map<std::string,std::vector<Transition> >  transitions;
	std::vector<BreakPoint> breakPoints;
	ExecMode execMode;
	int status; // 0 means running, 1 means stopped
	bool entryInFlag;
};

inline SROManager::SROManager() {
	// TODO Auto-generated constructor stub
	this->execMode=Running;
	entryInFlag=false;
	status=1;

}

inline SROManager::~SROManager() {
	// TODO Auto-generated destructor stub
}

inline void SROManager::addState(std::string name) {
	std::vector<Transition> t1;
	this->transitions[name]=t1;
}

inline void SROManager::remBreakPoint(std::string loc, BreakPointType breakType,int place) {
    std::cout<<"Try to remove the breakpoint with loc='"<<loc<<"' type='"<<breakType<<"' place='"<<place<<"' \n";
	for (std::vector<BreakPoint>::const_iterator it=this->breakPoints.begin();it!=this->breakPoints.end();it++){
		if (it->loc==loc and it->type==breakType and (it->place==place or place==3)){
			std::cout<<"find breakpoint to be removed"<<"\n";
			this->breakPoints.erase(it);
			break;
		}
	}
}

inline void SROManager::addTransitionsFromState(std::string stateName,std::string transName,std::string targetName,
		std::string signalName,std::string protocolName) {
	Transition t;
	t.setTransition(transName, targetName, signalName, protocolName);
	this->transitions[stateName].push_back(t);
}

inline void SROManager::addTransitionsFromState(std::string stateName,Transition transition) {
	this->transitions[stateName].push_back(transition);
}

inline void SROManager::addBreakPoint(std::string loc,BreakPointType breakType, int place) {
	BreakPoint b;
	b.loc=loc;
	b.type=breakType;
	b.place=place;
	breakPoints.push_back(b);
}

inline void SROManager::setExecMode(ExecMode execmode) {
	this->execMode=execmode;
}

inline ExecMode SROManager::getExecMode() {
	return this->execMode;
}

inline bool SROManager::checkDebug(std::string loc, std::string protocol,std::string signalName,
	int mode, BreakPointType breakType,int place) {
	//std::cout<<"Checking Breakpoint at location '" <<loc<< "' using signal '"<<signalName<<"' with protocol '"
	//			<<protocol<<"' type '"<<breakType<<"'\n";
	ExecMode execMode=this->getExecMode();
	std::vector<Transition> trans;
	this->dumpBreakPointList();
	bool result=false;
	if (mode==0 or mode==1){
		if (execMode==Running)
			result=false;
		else if (execMode==Stepping)
			result=true;
		else if (execMode==Resume){
			std::cout<<"Enter to checking for breakpoints loop\n";
			if (checkBreakPoint(loc, StateExitBreakPoint,3)){ // if the state exit has breakpoint before or after
				result=true;
			}
			trans=this->transitions[loc];
			for (std::vector<Transition>::const_iterator it=trans.begin();it!=trans.end();it++){
				std::cout<<"signal='"<<it->signalName<<"' protocol='"<<protocol<<"' transName='"<<it->name<<"' \n";
				if (it->signalName==signalName and it->protocol==protocol){
					std::cout<<"Signal and protocol name is matched\n";
					if ((checkBreakPoint(it->targetState, StateEntryBreakPoint,3)) or
							(checkBreakPoint(it->name,TransitionEffectBreakPoint,3))){
						//std::cout<<"result is set to true\n";
						result=true;
						break;
					}
				}
			}
		}
	} else if ((mode==2 or mode==3 or mode==4)){
		if (execMode==Running)
			result=false;
		else if (execMode==Stepping)
			result=true;
		else if (execMode==Resume)
			result=checkBreakPoint(loc,breakType,place);
	} else if (mode==5){
			status=0; // the system is not in debug state, so the status should be running
			if (entryInFlag ){ // fliping the entryInFlag make sure that during history, the entry of substate is executed
				entryInFlag=false;
				return true;
			}
	}

	if (result){
		this->entryInFlag=true;
		this->setStatus(1); // the system is stopped
	} else
		this->setStatus(0);  // the system is in running status

	std::cout<<"Checking Breakpoint at location '" <<loc<< "' using mode '"<<mode<<"' at place '"
			<<place<<"' in exec mode '"<<execMode<<"' was '" << result <<"'\n";
	return result;

}


/*inline bool SROManager::checkDebug(std::string loc, std::string protocol,std::string signalName,
	int mode, BreakPointType breakType,int place) {
	bool result=false;
	if (this->getExecMode()==Running){
		std::cout<<"Running Mode for capsule is Renning, go through normal path \n";
		result=false;
	}
	else if (this->getExecMode()==Stepping ){
		if (mode!=0){
			std::cout<<"Stepping  Mode for capsule , go through debug path \n";
			result=true;
		}
	}
	std::vector<Transition> trans;
	if (mode==0 or mode==1) {    // check at state before exit
		if (checkBreakPoint(loc, StateExitBreakPoint,3)) // if the state exit has breakpoint
			return true;
		trans=this->transitions[loc];
		for (std::vector<Transition>::const_iterator it=trans.begin();it!=trans.end();it++)
			if (it->signalName==signalName and it->protocol==protocol)
				if ((checkBreakPoint(it->targetState, StateEntryBreakPoint,3)) or
						(checkBreakPoint(it->name,TransitionEffectBreakPoint,3)) or (this->getExecMode()==Stepping))
						return true;
	}
	else if (mode==1){ // chek at path choice point for transition type P2P and P2C and P2S
		trans=this->transitions[loc];
		if ((checkBreakPoint(trans[0].name, TransitionEffectBreakPoint,3)) or
				(checkBreakPoint(trans[0].targetState, StateEntryBreakPoint,3)))
			result=true;
	}
	else if (mode>=2 and mode<=4 and this->getExecMode()==Resume){ // check at debugging state for state exit -- need to be fixed with other condition
		result=checkBreakPoint(loc,breakType,place);
	}
	else if (mode==5){
		if (entryInFlag ){ // fliping the entryInFlag make sure that during history, the entry of substate is executed
			entryInFlag=false;
			return true;
		}
		else
			return false;
	}
	//// state  entry executed in debug path, so this flag to make sure the next flag will not be executed
	if (result) this->entryInFlag=true;
	return result;
}*/

inline const std::vector<BreakPoint>& SROManager::getBreakPoints() const {
	return breakPoints;
}


inline const std::map<std::string, std::vector<Transition> >& SROManager::getTransitions() const {
	return transitions;
}

inline bool SROManager::checkBreakPoint(std::string loc,BreakPointType breakType,int place) {
	//std::cout<<"check breakpoint function for loc ='"<<loc<<"' type='"<<breakType<<"' place='"<<place<<"' \n";
	for (std::vector<BreakPoint>::const_iterator it=this->breakPoints.begin();it!=this->breakPoints.end();it++){
		//std::cout<<"loop detail loc ='"<<it->loc<<"' type='"<<it->type<<"' place='"<<it->place<<"' \n";
		if (it->loc==loc and it->type==breakType and (it->place==place or place==3)){
			//std::cout<<"BreakPoint is matched!!!!\n";
			return true;
		}
	}
	return false;
}

inline void SROManager::dumpBreakPointList() {
	std::cout<<"Dump Breakpoint list\n";
	for (std::vector<BreakPoint>::const_iterator it=this->breakPoints.begin();it!=this->breakPoints.end();it++){
		std::cout<<"loc='"<<it->loc<<"' type='"<<it->type<<"' place='"<<it->place<<"'\n";

	}
}

inline void SROManager::dumpAllTranstion() {
    for(std::map<std::string,std::vector<Transition> >::const_iterator it =this->transitions.begin(); it!=this->transitions.end(); ++it){
    	std::cout<<"Transition started from "<< it->first <<"\n";
    	for(std::vector<Transition>::const_iterator it1 =it->second.begin(); it1!=it->second.end(); ++it1)
    		std::cout<<it1->name<<","<<it1->protocol<<","<<it1->targetState<<","<<it1->signalName<<"\n";
    }
}

inline const std::string SROManager::serializeBreakPoint() {
	std::stringstream ss1;
	bool firstRec=true;
	for (std::vector<BreakPoint>::const_iterator it=this->breakPoints.begin();it!=this->breakPoints.end();it++){
		if (! firstRec)
			ss1<<";";
		ss1<<it->loc<<",";
		ss1<<it->type<<",";
		ss1<<it->place;
	}
	return ss1.str();
}

inline void SROManager::deSerializeBreakPoint(std::string breakPointsDump) {

}

inline int SROManager::getStatus() const {
	return status;
}

inline void SROManager::setStatus(int status) {
	this->status = status;
}

inline std::string SROManager::getStatusStr() {
	if (this->getStatus()==0)
		return "0";
	else if (getStatus()==1)
		return "1";
	else
		return "Unkown";
}

#endif /* SROMANAGER_H_ */

/*
 * DebuggerEvent.hh
 *
 *  Created on: Nov 11, 2016
 *      Author: mojtababagherzadeh
 */

#ifndef EVENT_H_OLD_
#define EVENT_H_OLD_

/*
 * Event.h
 *
 *  Created on: Sep 2, 2016
 *      Author: mojtababagherzadeh
 *      event class for saving real-time system events during observation
 *      part of the event kind and type  are defined based on paper
 *      Graf, Susanne, Ileana Ober, and Iulian Ober. "A real-time profile for UML."
 *      International Journal on Software Tools for Technology Transfer 8.2 (2006): 113-127.
 */


#include <iostream>
#include <map>
#include "umlrttimespec.hh"
#include <sstream>
#include  <time.h>
//#include "umlrtobjectclass.hh"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>


namespace debugEvents {
// main category for the event sources, refer to appendix of paper for detail
enum EVENTSOURCEKIND{SIGNALLING,METHOD,ACTIONECODE,TRANISTION,STATE,CAPSULE,ATTRIBUTE,TIMER,RESOURCE,CONNECTION,DEBUG,RESERVE1,RESERVE2,UNKOWNSOURCEKIND};
// types of signal events
enum EVENTTYPE{
	SENDSIGNAL,RECIEVESIGNAL,DEFERSIGNAL,RECALLSIGNAL,CANCELLSIGNAL, // signal event
	METHODCALL,METHODCALLRECIEVE,METHODSTARTEXECUTE,METHODRETURN,METHODFAILED,METHODRETURNRECIEVED, // method event
	ACTIONSTART,ACTIONEND, // action code events
	TRANISTIONSTART,TRANISTIONEND ,// TRANSITION
	STATEENTRYSTART,STATEENTRYEND,STATEEXITSTART,STATEEXITEND,STATEIDLESTART,STATEIDLEEND, // state events
	CAPSULEINSTNSIATE,CAPSULEFREE, // capsule event
	ATTRIBUTEINSTNSIATE,ATTRIBUTEFREE,ATTRIBUTECHANGE, // attribute event
	TIMERSTART,TIMERRESET,TIMERCANCELL,TIMERTIMEDOUT, // Timer events
	RESOURCEASSIGNED,RESOURCERELEASED,RESOURCEPREEMPTED,RESOURCERESUMED,   // resource event
	CONNECTIONESTABLISHED,CONNECTIONFAILED, // connection event
	REGISTER,VARIABLEDATA,BREAKPOINTDATA,RESERVE5,RESERVE6, //Debug Event
	UNKOWNTYPE
};

typedef std::map<std::string,std::string> EventPayload;
class Event {
public:
	Event(std::string capsuleInstance="",std::string sourceName="",EVENTSOURCEKIND eventSourceKind=UNKOWNSOURCEKIND, EVENTTYPE eventType=UNKOWNTYPE,long timepointsec=0,long timepointnano=0);

	virtual ~Event();

	const std::string& getCapsuleInstance() const;

	void setCapsuleInstance(const std::string& capsuleInstance);

	const EventPayload& getEventPayload() const;

	void setEventPayload(const EventPayload& eventPayload);

	EVENTSOURCEKIND getEventSourceKind() const;

	void setEventSourceKind(EVENTSOURCEKIND eventsource);

	const std::string& getSourceName() const;

	void setSourceName(const std::string& sourceName);
	/// set time of event to the current timestamp, the time stamp is the nanosecond counted from 1970 and saved as sec and nanosecond

	void setTimePointToNow();


	friend std::ostream & operator << (std::ostream & out, const Event  Event );

	long getTimePointNano() const;

	void setTimePointNano(long timePointNano);

	long getTimePointSecond() const;  // read the current timestamp and save them in related fields, it is better we use this field instead of setting time manually

	void setTimePointSecond(long timePointSecond);

	/// add filed to the message payload
	void setPayloadField(std::string key, std::string value);

	std::string getPayloadField(std::string key);

	std::string  getEventSourceKindLabel() const;


	EVENTTYPE getEventType() const;

	void setEventType(EVENTTYPE eventType);

	std::string getEventTypeLabel() const;

    //// generate unqiue if for each thread
	void generateEventID();

    //// cpu time fuction
	double getCpuTik() const;

	void setCpuTik();  ///  this save the cpu tick process until that moment, by using setCpuTik/CLOCKS_PER_SEC can be converted to second

	static double currentCpuTik();

	const std::string& getEventId() const; /// Unique event id

	std::string dumpToString(std::string format,  char seperator='@');

	std::string payloadToString(char seperator=',');

	std::string serialize();

	std::string serializePayload();

	void deserialize(std::string buffer);

	void deSerializePayload(std::string buffer);

	const std::string& getVariableData() const ;

	void setVariableData(const std::string& variableData) ;

	int getCapsuleIndex() const ;

	void setCapsuleIndex(int capsuleIndex) ;

	const std::string& getCapsuleName() const ;

	void setCapsuleName(const std::string& capsuleName) ;

	void clearEventPayload();

	std::string getOwnerName() const;

	std::string getSimpleSourceName();

private:
	EVENTSOURCEKIND eventSourceKind; // shows the evenetsource kind
	EVENTTYPE eventType;                   // shows event type
	std::string capsuleInstance;     // show capsule instance name that generate event
	std::string capsuleName;         // refer to the class name
	std::string sourceName;          // based on the event source kind, this fields shows the
	long timePointSecond;
	long timePointNano;
	EventPayload eventPayload;
	std::string eventID;
	double cpuTik;
	int capsuleIndex;
	std::string variableData;

};


inline Event::~Event() {
	// TODO Auto-generated destructor stub
}

inline std::ostream & operator << (std::ostream & out, const Event  event )
{
	 // print all fields seperated with ';', subfiled seperated with ',' and : for mapped value
	 out<<event.getEventId()<<'|';
	 out<<event.getSourceName()<<'|';
	 out<<event.getOwnerName()<<'|';
	 out<<event.getEventSourceKindLabel()<<'|';
	 out<<event.getEventTypeLabel()<<'|';
	 out<<event.getTimePointSecond()<<':';
	 out<<event.getTimePointNano()<<"\n";
	 out<<event.getVariableData();
	 /// message payload
	 bool secondRec=false;
	 for(std::map<std::string,std::string>::const_iterator it = event.eventPayload.begin(); it != event.eventPayload.end(); ++it){
		 if (secondRec)
			 out<<";";
		 else {
			 secondRec=true;
			 out<<"";
		 }
	    	out<< it->first <<':'<<it->second;
	 }
	 out<<"\n";
	 return out;
}


inline void Event::clearEventPayload(){
	this->eventPayload.clear();
}
inline const std::string& Event::getCapsuleInstance() const {
	return capsuleInstance;
}

inline void Event::setCapsuleInstance(const std::string& capsuleInstance) {
	this->capsuleInstance = capsuleInstance;
}

inline const EventPayload& Event::getEventPayload() const {
	return eventPayload;
}

inline void Event::setEventPayload(const EventPayload& eventPayload) {
	this->eventPayload = eventPayload;
}

inline EVENTSOURCEKIND Event::getEventSourceKind() const {
	return eventSourceKind;
}

inline void Event::setEventSourceKind(EVENTSOURCEKIND eventSourceKind) {
	this->eventSourceKind = eventSourceKind;
}

inline const std::string& Event::getVariableData() const {
		return variableData;
	}

inline void Event::setVariableData(const std::string& variableData) {
		this->variableData = variableData;
	}

inline int Event::getCapsuleIndex() const {
		return capsuleIndex;
	}

inline void Event::setCapsuleIndex(int capsuleIndex) {
		this->capsuleIndex = capsuleIndex;
	}

inline const std::string& Event::getCapsuleName() const {
		return capsuleName;
	}

inline void Event::setCapsuleName(const std::string& capsuleName) {
		this->capsuleName = capsuleName;
	}

inline const std::string& Event::getSourceName() const {
	return sourceName;
}

inline void Event::setSourceName(const std::string& sourceName) {
	this->sourceName = sourceName;
}


inline void Event::setTimePointToNow() {
	UMLRTTimespec ts;
	ts.getclock(ts);
    this->setTimePointNano(ts.tv_nsec);
    this->setTimePointSecond(ts.tv_sec);
}

inline long Event::getTimePointNano() const {
	return timePointNano;
}

inline void Event::setTimePointNano(long timePointNano) {
	this->timePointNano = timePointNano;
}

inline long Event::getTimePointSecond() const {
	return timePointSecond;
}


inline Event::Event(std::string capsuleInstance,std::string sourceName,EVENTSOURCEKIND eventSourceKind,
	EVENTTYPE eventType,long timepointsec,long timepointnano) {
	this->capsuleInstance=capsuleInstance;
	this->sourceName=sourceName;
	this->eventSourceKind=eventSourceKind;
	this->eventType=eventType;
	this->timePointSecond=timepointsec;
	this->timePointNano=timepointnano;
	generateEventID();
}


inline void Event::setTimePointSecond(long timePointSecond) {
	this->timePointSecond = timePointSecond;
}



inline EVENTTYPE Event::getEventType() const {
	return eventType;
}

inline std::string Event::getEventSourceKindLabel() const {
	 //// label for enumeration
	static const   std::string EVENTSOURCEKINDLABEL[]={"SIGNALLING","METHOD","ACTIONECODE","TRANISTION","STATE","CAPSULE","ATTRIBUTE",
			"TIMER","RESOURCE","CONNECTION","DEBUG","RESERVE1","RESERVE2","UNKOWNSOURCEKIND"};
	return EVENTSOURCEKINDLABEL[this->getEventSourceKind()];
}

inline void Event::setEventType(EVENTTYPE eventType) {
	this->eventType = eventType;
}



inline std::string Event::getEventTypeLabel() const {
	static const   std::string EVENTTYPELABEL[]={
		    		"SENDSIGNAL","RECIEVESIGNAL","DEFERSIGNAL","RECALLSIGNAL","CANCELLSIGNAL", // signal event
		    		"METHODCALL","METHODCALLRECIEVE","METHODSTARTEXECUTE","METHODRETURN","METHODFAILED","METHODRETURNRECIEVED", // method event
		    		"ACTIONSTART","ACTIONEND", // action code events
		    		"TRANISTIONSTART","TRANISTIONEND" ,// TRANSITION
		    		"STATEENTRYSTART","STATEENTRYEND","STATEEXITSTART","STATEEXITEND","STATEIDLESTART","STATEIDLEEND", // state events
		    		"CAPSULEINSTNSIATE","CAPSULEFREE", // capsule event
		    		"ATTRIBUTEINSTNSIATE","ATTRIBUTEFREE","ATTRIBUTECHANGE", // attribute event
		    		"TIMERSTART","TIMERRESET","TIMERCANCELL","TIMERTIMEDOUT", // Timer events
		    		"RESOURCEASSIGNED","RESOURCERELEASED","RESOURCEPREEMPTED","RESOURCERESUMED", // resource event
		    		"CONNECTIONESTABLISHED","CONNECTIONFAILED", //
					"REGISTER","RESERVE3","RESERVE4","RESERVE5","RESERVE6",
		    		"UNKOWNTYPE"};
	return EVENTTYPELABEL[this->getEventType()];
}



inline void Event::setPayloadField(std::string key, std::string value) {
	if (key.length()>=1)
		this->eventPayload[key]=value;
}

 inline std::string Event::getPayloadField(std::string key) {
	if (this->eventPayload.count(key))
			return this->eventPayload.at(key);
		else
			return "";
}

inline void Event::generateEventID() {
	UMLRTTimespec ts;
	ts.getclock(ts);
	std::stringstream ss;
	int r=random();
	ss<<ts.tv_sec<<ts.tv_nsec<<r;
	this->eventID=ss.str();
}



inline double Event::getCpuTik() const {
	return this->cpuTik;
}

inline const std::string& Event::getEventId() const {
	return eventID;
}

inline void Event::setCpuTik() {

    this->cpuTik = currentCpuTik();
}

inline double Event::currentCpuTik() {
    return double(clock());

}

inline std::string Event::getOwnerName() const{
	std::stringstream s1;
	s1 << getCapsuleName()<<":"<<getCapsuleInstance()<<":"<<getCapsuleIndex();
	return s1.str();
}

inline std::string Event::dumpToString(std::string format, char seperator) {
	//std::vector<std::string> fieldNames;
	// parse the format was requested
	std::stringstream ss(format);
	std::string tempS;
	std::vector<std::string > fieldNames;
	char ch1;
	if (format!=""){
		while (ss >> ch1){
			if ( ch1=='\f' || ch1=='\t' || ch1=='\v' )
				continue;
			else if (ch1=='@'){
				fieldNames.push_back(tempS);
				tempS="";
				continue;
			}
			else
				tempS=tempS+ch1;
	    }
		if (tempS!="")
			fieldNames.push_back(tempS);
	}
	std::stringstream ss1;
	std::vector<std::string>::iterator it;
	bool needSeperator=false;
	for(it=fieldNames.begin() ; it < fieldNames.end(); it++ ){
			std::string tempS1=(std::string(*it));
			std::transform(tempS1.begin(), tempS1.end(), tempS1.begin(), ::tolower);
			//std::cout<<tempS1<<"\n";
			if (tempS1=="eventsourcesind"){
				if (needSeperator)
					ss1<<seperator;
				else
					needSeperator=true;
				ss1<<this->getEventSourceKindLabel();
			}
			else if (tempS1=="eventtype"){
				if (needSeperator)
					ss1<<seperator;
				else
					needSeperator=true;
				ss1<<this->getEventTypeLabel();
			}
			else if (tempS1=="capsuleinstance")
			{
				if (needSeperator)
					ss1<<seperator;
				else
					needSeperator=true;
				ss1<<this->getCapsuleInstance();
			}
			else if (tempS1=="capsulename")
			{
				if (needSeperator)
					ss1<<seperator;
				else
					needSeperator=true;
				ss1<<this->getCapsuleName();
			}
			else if (tempS1=="sourcename")
			{
			if (needSeperator)
				ss1<<seperator;
			else
				needSeperator=true;
			ss1<<this->getSourceName();
			}
			else if (tempS1=="timepointsecond")
			{
			if (needSeperator)
				ss1<<seperator;
			else
				needSeperator=true;
			ss1<<this->getTimePointSecond();
			}
			else if (tempS1=="timepointnano")
			{
			if (needSeperator)
				ss1<<seperator;
			else
				needSeperator=true;
			ss1<<this->getTimePointNano();
			}
			else if (tempS1=="eventid")
			{
			if (needSeperator)
				ss1<<seperator;
			else
				needSeperator=true;
			ss1<<this->getEventId();
			}
			else if (tempS1=="cputik")
			{
			if (needSeperator)
				ss1<<seperator;
			else
				needSeperator=true;
			ss1<<this->getCpuTik();
			}
			else if (tempS1=="eventpayload")
			{
			if (needSeperator)
				ss1<<seperator;
			else
				needSeperator=true;
			ss1<<this->payloadToString(',');
			}
			else if (tempS1=="variableData")
			{
			if (needSeperator)
				ss1<<seperator;
			else
				needSeperator=true;
				ss1<<this->getVariableData();
			}
			else if (tempS1=="capsuleIndex")
			{
			if (needSeperator)
				ss1<<seperator;
			else
				needSeperator=true;
				ss1<<this->getCapsuleIndex();
			}
	    }
	return ss1.str();
}

inline std::string Event::payloadToString(char seperator) {
	std::stringstream ss;
	bool secondRec=false;
	for(std::map<std::string,std::string>::const_iterator it = this->eventPayload.begin(); it != this->eventPayload.end(); ++it)
	{
		if (secondRec)
			ss<<seperator;
		else
			secondRec=true;
		ss<< it->first <<':'<<it->second;
	}
	 return ss.str();
}

inline std::string Event::serializePayload() {
	std::string ss;
	bool secondRec=false;
	for(std::map<std::string,std::string>::const_iterator it = this->eventPayload.begin(); it != this->eventPayload.end(); ++it)
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

inline void Event::deSerializePayload(std::string buffer) {

	std::string tempS="";
	std::vector<std::string> tempVector;
	bool newVar=false;
	for (int i=0;i< buffer.length();i++){
			if (buffer[i]==','){
				newVar=false;
				tempVector.push_back(tempS);
				tempS="";
			}
			else{
				tempS=tempS+(buffer[i]);
				newVar=true;
			}
		}
	if (newVar)
		tempVector.push_back(tempS);
	if (tempVector.size()>0){
		this->eventPayload.clear();
		for (int i=0;i<tempVector.size();i++){
			//std::cout<<"Whole value is"<<tempVector[i];
			std::string::size_type sepIndex=tempVector[i].find(":",0);
			std::string key=tempVector[i].substr(0,sepIndex);
			//std::cout<<"key is:"<<key;
			std::string value=tempVector[i].substr(sepIndex+1,tempVector[i].length());
			//std::cout<<"value is:"<<value;
			this->setPayloadField(key, value);
		}
	}
}

inline std::string Event::serialize() {

	std::stringstream ss1;
	ss1 << this->getEventId() <<";";
	ss1 << this->getEventSourceKind() << ";";
	ss1 << this->getEventType() << ';';
	ss1 << this->getCapsuleName() << ";";
	ss1 << this->getCapsuleInstance() << ";";
	ss1 << this->getCapsuleIndex() << ";";
	ss1 << this->getSourceName() << ";";
	ss1 << this->getCpuTik() << ';';
	ss1 << this->getTimePointSecond() << ';';
	ss1 << this->getTimePointNano()<<";";
	ss1 << this->getVariableData();
	if ((this->getEventPayload()).size()>0){
		ss1<<';';
		ss1 << this->serializePayload();
	}
	return ss1.str();
}

inline void Event::deserialize(std::string buffer) {
	//std::cout<<"deseralize started\n";
	std::string tempS="";
	std::vector<std::string> tempVector;
	bool newVar=false;
	for (int i=0;i< buffer.length();i++){
		if (buffer[i]==';'){
			newVar=false;
			tempVector.push_back(tempS);
			tempS="";
		}
		else{
			tempS=tempS+(buffer[i]);
			newVar=true;
		}
	}
	if (newVar)
		tempVector.push_back(tempS);
	//std::cout<<"pasring is done\n";
	if (tempVector.size()<11)
		std::cerr<<"Error in parsing event stream, only "<<tempVector.size()<<" are parsed \n";
	else {
		this->eventID=tempVector[0];
		this->setEventSourceKind((debugEvents::EVENTSOURCEKIND)(atoi(tempVector[1].c_str())));
		this->setEventType((debugEvents::EVENTTYPE)(atoi(tempVector[2].c_str())));
		this->setCapsuleName(tempVector[3]);
		this->setCapsuleInstance(tempVector[4]);
		this->setCapsuleIndex(atoi(tempVector[5].c_str()));
		this->setSourceName(tempVector[6]);
		this->cpuTik=atof(tempVector[7].c_str());
		this->setTimePointSecond(atol(tempVector[8].c_str()));
		this->setTimePointNano(atol(tempVector[9].c_str()));
		this->setVariableData(tempVector[10]);
		if (tempVector.size()==12)
			this->deSerializePayload(tempVector[11]);
	}

	//std::cout<<"deseralize done\n";
}

inline std::string Event::getSimpleSourceName() {
	int i=this->sourceName.length()-1;
	for (;i>=1;i--)
		if (this->sourceName[i]==this->sourceName[i-1] && this->sourceName[i]==':')
			break;
	if (i>=1)
		return this->sourceName.substr(i+1,this->sourceName.length()-i+1);
	else
		return this->sourceName;
}

}

#endif /* EVENT_H_OLD_ */

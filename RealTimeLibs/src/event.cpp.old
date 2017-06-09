/*
 * Event.cpp
 *
 *  Created on: Sep 2, 2016
 *      Author: mojtababagherzadeh
 */

#include "event.hh"

namespace events {
const   std::string Event::EVENTSOURCEKINDLABEL[]={"SIGNALLING","METHOD","ACTIONECODE","TRANISTION","STATE","CAPSULE","ATTRIBUTE","TIMER","RESOURCE","CONNECTION","UNKOWNSOURCEKIND"};
const   std::string Event::EVENTTYPELABEL[]={
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
		"UNKOWNTYPE"
};

Event::Event() {

	this->capsuleInstance="";
	this->eventType=UNKOWNTYPE;
	this->eventSourceKind=UNKOWNSOURCEKIND;
	this->sourceName="";
	this->timePointSecond=0;
	this->timePointNano=0;
	this->eventID=generateEventID();
}

Event::~Event() {
	// TODO Auto-generated destructor stub
}

std::ostream & operator << (std::ostream & out, const Event  event )
{
	 // print all fields seperated with ';', subfiled seperated with ',' and : for mapped value
	 out<<event.getEventId()<<';';
	 out<<event.getCapsuleInstance()<<';';
	 out<<event.getEventSourceKindLabel()<<';';
	 out<<event.getEventTypeLabel()<<';';
	 out<<event.getSourceName()<<';';
	 out<<event.getCpuTik()<<';';
	 out<<event.getTimePointSecond()<<',';
	 out<<event.getTimePointNano()<<';';
	 /// message payload
	 for(std::map<std::string,std::string>::const_iterator it = event.eventPayload.begin(); it != event.eventPayload.end(); ++it)
	    	out<< it->first <<':'<<it->second<<",";
	 return out;
}
/*
std::istream & operator >> (std::istream & in, const Event  Event )
{
	return in;
}*/
const std::string& Event::getCapsuleInstance() const {
	return capsuleInstance;
}

void Event::setCapsuleInstance(const std::string& capsuleInstance) {
	this->capsuleInstance = capsuleInstance;
}

const EventPayload& Event::getEventPayload() const {
	return eventPayload;
}

void Event::setEventPayload(const EventPayload& eventPayload) {
	this->eventPayload = eventPayload;
}

EVENTSOURCEKIND Event::getEventSourceKind() const {
	return eventSourceKind;
}

void Event::setEventSourceKind(EVENTSOURCEKIND eventSourceKind) {
	this->eventSourceKind = eventSourceKind;
}


const std::string& Event::getSourceName() const {
	return sourceName;
}

void Event::setSourceName(const std::string& sourceName) {
	this->sourceName = sourceName;
}



Event::Event( std::string capsuleInstance,
		std::string sourceName) {
	this->capsuleInstance=capsuleInstance;
	this->sourceName=sourceName;
	this->eventType=UNKOWNTYPE;
	this->eventSourceKind=UNKOWNSOURCEKIND;
	this->timePointSecond=0;
	this->timePointNano=0;
	this->eventID=generateEventID();
}


void Event::setTimePointToNow() {
	UMLRTTimespec ts;
	ts.getclock(ts);
    this->setTimePointNano(ts.tv_nsec);
    this->setTimePointSecond(ts.tv_sec);
}

long Event::getTimePointNano() const {
	return timePointNano;
}

void Event::setTimePointNano(long timePointNano) {
	this->timePointNano = timePointNano;
}

long Event::getTimePointSecond() const {
	return timePointSecond;
}

Event::Event(std::string capsuleInstance,
		std::string sourceName, EVENTSOURCEKIND eventSourceKind, EVENTTYPE eventType) {
	this->capsuleInstance=capsuleInstance;
	this->sourceName=sourceName;
	this->eventSourceKind=eventSourceKind;
	this->eventType=eventType;
	this->timePointSecond=0;
	this->timePointNano=0;
	this->eventID=generateEventID();
}



Event::Event( std::string capsuleInstance,
		std::string sourceName, EVENTSOURCEKIND eventSourceKind, EVENTTYPE eventType,
		long timepointsec, long timepointnano) {
	this->capsuleInstance=capsuleInstance;
	this->sourceName=sourceName;
	this->eventSourceKind=eventSourceKind;
	this->eventType=eventType;
	this->timePointSecond=timepointsec;
	this->timePointNano=timepointnano;
	this->eventID=generateEventID();
}

Event::Event(std::string capsuleInstance,std::string sourceName,EVENTSOURCEKIND eventSourceKind,
	EVENTTYPE eventType,EventPayload eventPayload,long timepointsec,long timepointnano) {
	this->capsuleInstance=capsuleInstance;
	this->sourceName=sourceName;
	this->eventSourceKind=eventSourceKind;
	this->eventType=eventType;
	this->timePointSecond=timepointsec;
	this->timePointNano=timepointnano;
	this->eventPayload=eventPayload;
	this->eventID=generateEventID();
}

Event::Event(std::string capsuleInstance, std::string sourceName,
		EVENTSOURCEKIND eventSourceKind) {
	this->capsuleInstance=capsuleInstance;
	this->sourceName=sourceName;
	this->eventSourceKind=eventSourceKind;
	this->eventType=UNKOWNTYPE;
	this->timePointSecond=0;
	this->timePointNano=0;
	this->eventID=generateEventID();
}

void Event::setTimePointSecond(long timePointSecond) {
	this->timePointSecond = timePointSecond;
}



EVENTTYPE Event::getEventType() const {
	return eventType;
}

std::string Event::getEventSourceKindLabel(
		) const {
	return this->EVENTSOURCEKINDLABEL[this->getEventSourceKind()];
}

void Event::setEventType(EVENTTYPE eventType) {
	this->eventType = eventType;
}



std::string Event::getEventTypeLabel() const {
	return this->EVENTTYPELABEL[this->getEventType()];
}



void events::Event::setPayloadField(std::string key, std::string value) {
	if (key.length()>=1)
		this->eventPayload[key]=value;
}

 std::string events::Event::getPayloadField(std::string key) {
	if (this->eventPayload.count(key))
			return this->eventPayload.at(key);
		else
			return "";
}

std::string Event::generateEventID() {
	UMLRTTimespec ts;
	ts.getclock(ts);
	std::stringstream ss;
	ss<<ts.tv_sec<<ts.tv_nsec;
	return ss.str();
}



double events::Event::getCpuTik() const {
	return this->cpuTik;
}

const std::string& events::Event::getEventId() const {
	return eventID;
}

void events::Event::setCpuTik() {

    this->cpuTik = currentCpuTik();
}

double events::Event::currentCpuTik() {
    return double(clock());

}

std::string Event::dumpToString(std::string format, char seperator) {
	//std::vector<std::string> fieldNames;
	// parse the format was requested
	std::stringstream ss(format);
	std::string tempS;
	char ch1;
	if (format!="")
	{
		while (ss >> ch1)
	    {
			if ( ch1=='\f' || ch1=='\t' || ch1=='\v' )
				continue;
			else if (ch1=='@')
			{
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
	for(it=fieldNames.begin() ; it < fieldNames.end(); it++ )
		{
			std::string tempS1=(std::string(*it));
			std::transform(tempS1.begin(), tempS1.end(), tempS1.begin(), ::tolower);
			//std::cout<<tempS1<<"\n";
			if (tempS1=="eventsourcesind")
			{
				if (needSeperator)
					ss1<<seperator;
				else
					needSeperator=true;
				ss1<<this->getEventSourceKindLabel();
			}
			else if (tempS1=="eventtype")
			{
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
	    }
	return ss1.str();
}

std::string Event::payloadToString(char seperator) {
	std::stringstream ss;
	bool needSeperator;
	for(std::map<std::string,std::string>::const_iterator it = this->eventPayload.begin(); it != this->eventPayload.end(); ++it)
	{
		if (needSeperator)
			ss<<seperator;
		else
			needSeperator=true;
		ss<< it->first <<':'<<it->second;
	}
	 return ss.str();
}

} /* namespace events */

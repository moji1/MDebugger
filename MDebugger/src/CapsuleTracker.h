/*
 * CapsuleTracker.h
 *
 *  Created on: Nov 22, 2016
 *      Author: mojtababagherzadeh
 *      keep all information required to debug an instance of capsule
 */

#ifndef CAPSULETRACKER_H_
#define CAPSULETRACKER_H_
#include "Event.h"
//#include <boost/circular_buffer.hpp>
#include <iostream>
#include <string>
#include <deque>
#include "SROManager.h"

#define MAX_EVENT_BUFFER_SIZE 1024
namespace mdebugger {

//enum EXECMODE{STEPIN,STEPOVER,CONTINUE,RUN};

class CapsuleTracker {
public:
	CapsuleTracker();
	CapsuleTracker(debugEvents::Event);
	virtual ~CapsuleTracker();
	int getCapsuleIndex() const;
	void setCapsuleIndex(int capsuleIndex);
	const std::string& getCapsuleInstance() const;
	void setCapsuleInstance(const std::string& capsuleInstanceName);
	const std::string& getCapsuleName() const;
	void setCapsuleName(const std::string& capsuleName);
	void addEvent(std::string);
	void addEvent(debugEvents::Event);
	const debugEvents::Event lastEvent();
	const std::vector<debugEvents::Event> lastNEvents(int count);
	void clearEvents();
	int  eventsSize();
	const std::string& getCurrentState() const;
	void setCurrentState(const std::string& currentState);
	bool existBreakPoints(std::string location);
	void setBreakPoints(const std::string & breakPoint);
	void remBreakPoint(std::string location);
	void remAllBreakPoints(std::string location);
	std::string getQualifiedName();
	ExecMode getExecMode() const;
	void setExecMode(ExecMode execMode);
	const std::deque<std::string>& getBreakPoints() const;
	const std::deque<debugEvents::Event>& getCapsuleEvents() const;
	const std::deque<debugEvents::Event>& getCapsuleHistoryEvents() const;
	void setCapsuleHistoryEvents(
	const std::deque<debugEvents::Event>& capsuleHistoryEvents);
	const debugEvents::Event& getLastEvent() const;
	void setLastEvent(const debugEvents::Event& lastEvent);
	const std::string& getLastState() const;
	void setLastState(const std::string& lastState);
	//void processLiveEvent();
	std::string getExecModeStr();
private:
	std::string capsuleInstance,capsuleName;
	int capsuleIndex;
	std::string currentState;
	std::deque<debugEvents::Event>  capsuleLiveEvents;
	//std::deque<debugEvents::Event>  capsuleHistoryEvents;
	std::deque<std::string> breakPoints;
	std::string lastState;
	ExecMode execMode;

};

} /* namespace mdebugger */

#endif /* CAPSULETRACKER_H_ */

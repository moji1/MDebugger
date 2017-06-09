//============================================================================
// Name        : RealTimeLibs.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "SharedMem.h"
//#include "event.hh"
#include <string.h>

#include "Event.h"

/*int main() {
	debugEvents::Event e1;
	e1.generateEventID();
	e1.setCpuTik();
	e1.setTimePointToNow();
	e1.setEventSourceKind(debugEvents::STATE);
	e1.setEventType(debugEvents::STATEEXITEND);
	e1.setCapsuleInstance("test");
	e1.setVariableData(variableData)
	debugEvents::EventPayload payload;
	char * t="test";
	e1.setPayloadField("signalPorotocol",t);
	e1.setPayloadField("Test2key", "test2Value");
	e1.setPayloadField("Source",)
	e1.setEventPayload(payload);
	debugEvents::EVENTTYPE evetType;
	std::string s11;
	s11=e1.serialize();
	debugEvents::Event e2;
	e2.deserialize(s11);
	std::cout<<e1<<"\n";
	std::cout<<e2;

	return 0;
}*/

/*int main3() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	//define event class and assign the values
	events::Event e1;
	e1.setCapsuleInstance("testCapsule");
	e1.setTimePointToNow();
	e1.setEventSourceKind(events::SIGNALLING);
	e1.setEventType(events::SENDSIGNAL);
	e1.setSourceName("sampleSignal");
	e1.setPayloadField("signalPorotocol", "protocol1");
	e1.setPayloadField("param1", "paramData");
	e1.setCpuTik();
	std::cout<<e1.currentCpuTik()/CLOCKS_PER_SEC<<"\n";
	// define stream and seralize the event
	std::stringstream st;
	std::stringstream sb;
	std::stringstream sx;
	boost::archive::text_oarchive oa(st);
	boost::archive::text_oarchive bb(sb);
	boost::archive::xml_oarchive xx(sx);
	oa << e1;
    bb << e1;
    xx << BOOST_SERIALIZATION_NVP(e1);
	//// convert the seralized stream to string
	std::string ts=st.str();
	st.seekg(0, ios::end);
	int size = st.tellg();
	std::cout<<"text serialize format is:"<<st.str().length()<<"\n";
	std::cout<<" Length is"<<size<<"\n";
	std::cout<<"xml serialize format is:\n"<<sx.str()<<"\n";
	/// you can write the string to shared memory
    Comms::SharedMem shm1("test", "testq", 8900, true);
    shm1.setUp(server);
    shm1.safePushBackString(ts);
	/// read the data from shared memory as string, load the data to string stream and then deseralize,
	//you have an event object do whatever you need
    std::string ts1=shm1.safePopBackString();
	std::stringstream ss1;
	ss1<<ts1;
	boost::archive::text_iarchive ia(ss1);
    events::Event e2;
    events::Event e3;
    events::Event e4;
    std::cout<<e2<<"\n"<<e3<<"\n"<<e4<<"\n";
    ia>>e2;
    std::cout<<"new object loaded with deserialization\n" << e2<<"\n";
    std::cout<<e1.currentCpuTik()/CLOCKS_PER_SEC<<"\n";
    //e1.dumpToString("",'@');
    std::cout<<e1.dumpToString("eventid@capsuleinstance@eventsourcesind@eventpayload",';');
    //e1.dumpToString("",'@');
	return 0;
}*/
#include "SROManager.h"
int main(){
	SROManager testSRO;
	//testSRO.addState("testState");
	Transition t1;
	t1.setTransition("t1", "targetState", "testSignal", "testProtocol");
	testSRO.addTransitionsFromState("testState",t1);
	t1.setTransition("t2", "targetState1", "testSignal1", "testProtocol1");
	testSRO.addTransitionsFromState("testState",t1);
	//testSRO.addState("testState1");
	t1.setTransition("t3", "targetState2", "testSignal2", "testProtocol2");
	testSRO.addTransitionsFromState("testState1",t1);
	t1.setTransition("t4", "targetState3", "testSignal3", "testProtocol3");
	testSRO.addTransitionsFromState("testState1",t1);
	testSRO.dumpAllTranstion();
	testSRO.addBreakPoint("t1", TransitionEffectBreakPoint, 0);
	testSRO.addBreakPoint("targetState", StateEntryBreakPoint, 0);
	testSRO.addBreakPoint("testState", StateEntryBreakPoint, 0);
	testSRO.addBreakPoint("testState", StateEntryBreakPoint, 0);
	std::cout<<testSRO.checkDebug("testState", "", "",3,StateEntryBreakPoint,0);
	testSRO.setExecMode(Running);
	return 0;
}
int main2() {
	std::cout << "!!!Sample Application for read event and send command!!!\n" ; // prints !!!Hello World!!!
	//define event class and assign the values
	debugEvents::Event e1;

    Comms::SharedMem eventShm("EventArea", "EventQ", 999999999, true);
    eventShm.setUp(client);
    Comms::SharedMem commandShm("CommandArea", "CommandQ", 999999999, true);
    eventShm.setUp(client);
    commandShm.setUp(client);
    while (true)
    {
    		std::string tempStr=eventShm.safePopBackString();
    		if (tempStr!="")
    		{
    		    std::cout<<"new event is received and deserailized to event object with these fields:"<<tempStr<<"\n";
    		}
    		else
    		{
    			std::string tempsStr;
    			std::cout<<"enter the capsule instance to receive command, currently we send default command only\n";
    			std::cin>>tempStr;
    			//std::cout<<tempStr;
    			//std::cin>>tempStr;
    			commandShm.safePushBackString(tempStr);
    		}
    }

	return 0;
}


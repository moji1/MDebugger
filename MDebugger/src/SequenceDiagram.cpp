/*
 * SequenceDiagram.cpp
 *
 *  Created on: Jul 8, 2017
 *      Author: David Seekatz
 */

#include "../../MDebugger/src/SequenceDiagram.h"

namespace diagram {

SequenceDiagram::SequenceDiagram(std::vector<debugEvents::Event> transitions, bool isSorted) {
	this->transitions = transitions;
	this->plantumlDirectory = ".";
	if (!isSorted)
		sortTransitions();
}

SequenceDiagram::~SequenceDiagram() {
	// TODO Auto-generated destructor stub
}

std::vector<debugEvents::Event> SequenceDiagram::getTransitions() const {
	return transitions;
}

void SequenceDiagram::setPlantumlDirectory(std::string directory) {
	this->plantumlDirectory = directory;
}

//std::string& SequenceDiagram::getPlantumlDirectory() const {
//	return plantumlDirectory;
//}

void SequenceDiagram::printPlantUML(std::ostream& output, int numTransitions) {
	output<<"@startuml\n";
	if (transitions.size() < numTransitions)
		numTransitions = transitions.size() - 1;
	long baseTimeSecond = transitions[numTransitions].getTimePointSecond();
	long baseTimeNano = transitions[numTransitions].getTimePointNano();
	for (int i = numTransitions; i > 0; i--){
		std::string sender = transitions[i].getPayloadField("SenderCapsule");
		std::string owner = transitions[i].getOwnerName();
		std::string port = transitions[i].getPayloadField("Port");
		std::string signal = transitions[i].getPayloadField("Signal");
		output<<owner.substr(0,owner.find(":"))<<" <- ";
		if (signal == "timeout")
			output<<port;
		else
			output<<sender;
		output<<": "<<signal<<"\n";
		if (i == numTransitions){
			output<<"note right: 0.00s\n";
		} else {
			output<<"note right: "<<convertTime(baseTimeSecond, baseTimeNano, transitions[i].getTimePointSecond(), transitions[i].getTimePointNano());
		}
	} // end for
	output<<"@enduml\n";
}

// Hard-coded to open png with gnome image viewer
void SequenceDiagram::runPlantUML(int numTransitions) {
	std::ostringstream uml;
	printPlantUML(uml, numTransitions);
	std::ofstream outFile;
	outFile.open("seqDiagram.txt");
	outFile<<uml.str();
	outFile.close();
	std::string cmd = "cat seqDiagram.txt | java -jar " + this->plantumlDirectory + "/plantuml.jar -pipe > seqDiagram.png";
	system(cmd.c_str());
	char const * viewImg = "eog seqDiagram.png";
	system(viewImg);
}

void SequenceDiagram::sortTransitions() {
	sort(transitions.begin(),transitions.end(),eventComp);
}

bool SequenceDiagram::eventComp(const debugEvents::Event &e1, const debugEvents::Event &e2){
	if (e1.getTimePointSecond() == e2.getTimePointSecond())
		return e1.getTimePointNano() > e2.getTimePointNano();
	else
		return e1.getTimePointSecond() > e2.getTimePointSecond();
}

// Returns a formatted string of the event timestamp relative to the initial event.
// Truncates nanoseconds to three digits.
std::string SequenceDiagram::convertTime(long baseSec, long baseNano, long timeSecond, long timeNano) {
	bool negativeFlag = false;
	timeSecond = timeSecond - baseSec;
	timeNano = timeNano - baseNano;
	if (timeNano < 0) {
		timeSecond--;
		negativeFlag = true;
	}
	timeNano = 1000000000L + timeNano;
	std::string output = "+";
	std::string second = std::to_string(timeSecond);
	std::string nano = std::to_string(timeNano);
	if (negativeFlag)
		nano = nano.substr(0,1);
	else
		nano = nano.substr(1,2);
	output.append(second).append(".").append(nano).append("s").append("\n");
	return output;
}

} // namespace diagram


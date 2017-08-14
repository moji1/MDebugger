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
	for (int i = 0; i < numTransitions && i < transitions.size(); i++){
		std::string sender = transitions[i].getPayloadField("SenderCapsule");
		std::string owner = transitions[i].getOwnerName();
		std::string port = transitions[i].getPayloadField("Port");
		std::string signal = transitions[i].getPayloadField("Signal");
		output<<owner.substr(0,owner.find(":"))<<" <- ";
		if (signal == "timeout")
			// Which is better: unique timers for each capsule, or just one "timer" lifeline?
			output<<port;
			//output<<"timer";
		else
			output<<sender;
		output<<": "<<signal<<"\n";
		output<<"note right: "<<convertTime(transitions[i].getTimePointSecond(), transitions[i].getTimePointNano());
	} // end for
	output<<"@enduml\n";
}

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

std::string SequenceDiagram::convertTime(long timeSecond, long timeNano) {
	char t[23];
	strftime(t, 23, "%Y-%m-%d\\n(%H:%M:%S:",localtime(&timeSecond));
	std::string output(t);
	std::string nano = std::to_string(timeNano);
	output.append(nano).append(")\n");
	return output;
}

} // namespace diagram


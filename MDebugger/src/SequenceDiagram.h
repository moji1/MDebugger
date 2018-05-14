/*
 * SequenceDiagram.h
 *
 *  Created on: Jul 8, 2017
 *      Author: David Seekatz
 */

#ifndef SEQUENCEDIAGRAM_H_
#define SEQUENCEDIAGRAM_H_

#include <iostream>
#include <fstream>
#include <vector>
#include "Event.h"

namespace diagram {

class SequenceDiagram {
public:
	SequenceDiagram(std::vector<debugEvents::Event> transitions, bool isSorted = false);
	virtual ~SequenceDiagram();
	std::vector<debugEvents::Event> getTransitions() const;
	void setPlantumlDirectory(std::string directory);
	//std::string& getPlantumlDirectory() const;
	void printPlantUML(std::ostream& output, int numTransitions);
	void runPlantUML(int numTransitions);


private:
	std::vector<debugEvents::Event> transitions;
	std::string plantumlDirectory;
	void sortTransitions();
	static bool eventComp(const debugEvents::Event &e1, const debugEvents::Event &e2);
	std::string convertTime(long baseSec, long baseNano, long timeSecond, long timeNano);
};

} // namespace diagram

#endif /* SEQUENCEDIAGRAM_H_ */

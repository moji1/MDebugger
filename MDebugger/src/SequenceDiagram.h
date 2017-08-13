/*
 * SequenceDiagram.h
 *
 *  Created on: Jul 8, 2017
 *      Author: David Seekatz
 */

#ifndef SEQUENCEDIAGRAM_H_
#define SEQUENCEDIAGRAM_H_

#include <iostream>
#include <vector>
#include "Event.h"

namespace diagram {

class SequenceDiagram {
public:
	SequenceDiagram(std::string capsuleQualifiedName, int count);
	virtual ~SequenceDiagram();
	void printPlantUML();
	void runPlantUML();

private:
	std::vector<debugEvents::Event> transitions;
};

} // namespace diagram

#endif /* SEQUENCEDIAGRAM_H_ */

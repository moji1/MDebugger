
#ifndef TOPCONTROLLERS_HH
#define TOPCONTROLLERS_HH

class UMLRTController;
struct UMLRTCommsPort;
struct UMLRTSlot;

enum CapsuleInstanceId
{
    InstId_Top,
    InstId_Top_controlSoftware,
    InstId_Top_rover,
    InstId_Top_rover_detectionSensor,
    InstId_Top_rover_detectionSensor2,
    InstId_Top_rover_engineController,
    InstId_Top_rover_temperatureSensor
};
extern UMLRTController * DefaultController;
extern UMLRTCommsPort borderports_Top_controlSoftware[];
extern UMLRTCommsPort borderports_Top_rover[];
extern UMLRTCommsPort borderports_Top_rover_detectionSensor[];
extern UMLRTCommsPort borderports_Top_rover_detectionSensor2[];
extern UMLRTCommsPort borderports_Top_rover_engineController[];
extern UMLRTCommsPort borderports_Top_rover_temperatureSensor[];
extern UMLRTSlot Top_slots[];

#endif


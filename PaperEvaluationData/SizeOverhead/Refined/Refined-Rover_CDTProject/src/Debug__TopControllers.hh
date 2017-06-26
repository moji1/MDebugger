
#ifndef DEBUG__TOPCONTROLLERS_HH
#define DEBUG__TOPCONTROLLERS_HH

class UMLRTController;
struct UMLRTCommsPort;
struct UMLRTSlot;

enum CapsuleInstanceId
{
    InstId_Debug__Top,
    InstId_Debug__Top_Debug__Gateway,
    InstId_Debug__Top_Debug__Top,
    InstId_Debug__Top_Debug__Top_controlSoftware,
    InstId_Debug__Top_Debug__Top_rover,
    InstId_Debug__Top_Debug__Top_rover_detectionSensor,
    InstId_Debug__Top_Debug__Top_rover_detectionSensor2,
    InstId_Debug__Top_Debug__Top_rover_engineController,
    InstId_Debug__Top_Debug__Top_rover_temperatureSensor
};
extern UMLRTController * DefaultController;
extern UMLRTCommsPort borderports_Debug__Top_Debug__Gateway[];
extern UMLRTCommsPort borderports_Debug__Top_Debug__Top_controlSoftware[];
extern UMLRTCommsPort borderports_Debug__Top_Debug__Top_rover[];
extern UMLRTCommsPort borderports_Debug__Top_Debug__Top_rover_detectionSensor[];
extern UMLRTCommsPort borderports_Debug__Top_Debug__Top_rover_detectionSensor2[];
extern UMLRTCommsPort borderports_Debug__Top_Debug__Top_rover_engineController[];
extern UMLRTCommsPort borderports_Debug__Top_Debug__Top_rover_temperatureSensor[];
extern UMLRTSlot Debug__Top_slots[];

#endif



#ifndef SIMULATORCONTROLLERS_HH
#define SIMULATORCONTROLLERS_HH

class UMLRTController;
struct UMLRTCommsPort;
struct UMLRTSlot;

enum CapsuleInstanceId
{
    InstId_Simulator,
    InstId_Simulator_ENV,
    InstId_Simulator_client_0,
    InstId_Simulator_client_1,
    InstId_Simulator_client_2,
    InstId_Simulator_client_3,
    InstId_Simulator_client_4,
    InstId_Simulator_server1,
    InstId_Simulator_server2
};
extern UMLRTController * DefaultController;
extern UMLRTCommsPort borderports_Simulator_ENV[];
extern UMLRTCommsPort borderports_Simulator_client_0[];
extern UMLRTCommsPort borderports_Simulator_client_1[];
extern UMLRTCommsPort borderports_Simulator_client_2[];
extern UMLRTCommsPort borderports_Simulator_client_3[];
extern UMLRTCommsPort borderports_Simulator_client_4[];
extern UMLRTCommsPort borderports_Simulator_server1[];
extern UMLRTCommsPort borderports_Simulator_server2[];
extern UMLRTSlot Simulator_slots[];

#endif


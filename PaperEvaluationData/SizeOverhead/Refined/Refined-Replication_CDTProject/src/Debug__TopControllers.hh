
#ifndef DEBUG__TOPCONTROLLERS_HH
#define DEBUG__TOPCONTROLLERS_HH

class UMLRTController;
struct UMLRTCommsPort;
struct UMLRTSlot;

enum CapsuleInstanceId
{
    InstId_Debug__Top,
    InstId_Debug__Top_Debug__Gateway,
    InstId_Debug__Top_Debug__Simulator,
    InstId_Debug__Top_Debug__Simulator_ENV,
    InstId_Debug__Top_Debug__Simulator_client_0,
    InstId_Debug__Top_Debug__Simulator_client_1,
    InstId_Debug__Top_Debug__Simulator_client_2,
    InstId_Debug__Top_Debug__Simulator_client_3,
    InstId_Debug__Top_Debug__Simulator_client_4,
    InstId_Debug__Top_Debug__Simulator_server1,
    InstId_Debug__Top_Debug__Simulator_server2
};
extern UMLRTController * DefaultController;
extern UMLRTCommsPort borderports_Debug__Top_Debug__Gateway[];
extern UMLRTCommsPort borderports_Debug__Top_Debug__Simulator_ENV[];
extern UMLRTCommsPort borderports_Debug__Top_Debug__Simulator_client_0[];
extern UMLRTCommsPort borderports_Debug__Top_Debug__Simulator_client_1[];
extern UMLRTCommsPort borderports_Debug__Top_Debug__Simulator_client_2[];
extern UMLRTCommsPort borderports_Debug__Top_Debug__Simulator_client_3[];
extern UMLRTCommsPort borderports_Debug__Top_Debug__Simulator_client_4[];
extern UMLRTCommsPort borderports_Debug__Top_Debug__Simulator_server1[];
extern UMLRTCommsPort borderports_Debug__Top_Debug__Simulator_server2[];
extern UMLRTSlot Debug__Top_slots[];

#endif


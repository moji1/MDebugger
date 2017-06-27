
#ifndef DEBUG__TOPCONTROLLERS_HH
#define DEBUG__TOPCONTROLLERS_HH

class UMLRTController;
struct UMLRTCommsPort;
struct UMLRTSlot;

enum CapsuleInstanceId
{
    InstId_Debug__Top,
    InstId_Debug__Top_Debug__Car,
    InstId_Debug__Top_Debug__Car_centralLock,
    InstId_Debug__Top_Debug__Car_door1,
    InstId_Debug__Top_Debug__Car_door1_lock,
    InstId_Debug__Top_Debug__Car_door2,
    InstId_Debug__Top_Debug__Car_door2_lock,
    InstId_Debug__Top_Debug__Car_door3,
    InstId_Debug__Top_Debug__Car_door3_lock,
    InstId_Debug__Top_Debug__Car_door4,
    InstId_Debug__Top_Debug__Car_door4_lock,
    InstId_Debug__Top_Debug__Gateway
};
extern UMLRTController * DefaultController;
extern UMLRTCommsPort borderports_Debug__Top_Debug__Car_centralLock[];
extern UMLRTCommsPort borderports_Debug__Top_Debug__Car_door1[];
extern UMLRTCommsPort borderports_Debug__Top_Debug__Car_door1_lock[];
extern UMLRTCommsPort borderports_Debug__Top_Debug__Car_door2[];
extern UMLRTCommsPort borderports_Debug__Top_Debug__Car_door2_lock[];
extern UMLRTCommsPort borderports_Debug__Top_Debug__Car_door3[];
extern UMLRTCommsPort borderports_Debug__Top_Debug__Car_door3_lock[];
extern UMLRTCommsPort borderports_Debug__Top_Debug__Car_door4[];
extern UMLRTCommsPort borderports_Debug__Top_Debug__Car_door4_lock[];
extern UMLRTCommsPort borderports_Debug__Top_Debug__Gateway[];
extern UMLRTSlot Debug__Top_slots[];

#endif


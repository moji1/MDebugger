
#ifndef CARCONTROLLERS_HH
#define CARCONTROLLERS_HH

class UMLRTController;
struct UMLRTCommsPort;
struct UMLRTSlot;

enum CapsuleInstanceId
{
    InstId_Car,
    InstId_Car_centralLock,
    InstId_Car_door1,
    InstId_Car_door1_lock,
    InstId_Car_door2,
    InstId_Car_door2_lock,
    InstId_Car_door3,
    InstId_Car_door3_lock,
    InstId_Car_door4,
    InstId_Car_door4_lock
};
extern UMLRTController * DefaultController;
extern UMLRTCommsPort borderports_Car_centralLock[];
extern UMLRTCommsPort borderports_Car_door1[];
extern UMLRTCommsPort borderports_Car_door1_lock[];
extern UMLRTCommsPort borderports_Car_door2[];
extern UMLRTCommsPort borderports_Car_door2_lock[];
extern UMLRTCommsPort borderports_Car_door3[];
extern UMLRTCommsPort borderports_Car_door3_lock[];
extern UMLRTCommsPort borderports_Car_door4[];
extern UMLRTCommsPort borderports_Car_door4_lock[];
extern UMLRTSlot Car_slots[];

#endif


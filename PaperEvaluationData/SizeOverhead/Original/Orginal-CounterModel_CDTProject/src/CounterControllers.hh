
#ifndef COUNTERCONTROLLERS_HH
#define COUNTERCONTROLLERS_HH

class UMLRTController;
struct UMLRTCommsPort;
struct UMLRTSlot;

enum CapsuleInstanceId
{
    InstId_Counter
};
extern UMLRTController * DefaultController;
extern UMLRTCommsPort borderports_Counter[];
extern UMLRTSlot Counter_slots[];

#endif



#ifndef DEBUG__TOPCONTROLLERS_HH
#define DEBUG__TOPCONTROLLERS_HH

class UMLRTController;
struct UMLRTCommsPort;
struct UMLRTSlot;

enum CapsuleInstanceId
{
    InstId_Debug__Top,
    InstId_Debug__Top_Debug__Counter,
    InstId_Debug__Top_Debug__Gateway
};
extern UMLRTController * DefaultController;
extern UMLRTCommsPort borderports_Debug__Top_Debug__Counter[];
extern UMLRTCommsPort borderports_Debug__Top_Debug__Gateway[];
extern UMLRTSlot Debug__Top_slots[];

#endif


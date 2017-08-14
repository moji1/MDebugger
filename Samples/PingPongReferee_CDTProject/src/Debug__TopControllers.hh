
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
    InstId_Debug__Top_Debug__Top_pinger,
    InstId_Debug__Top_Debug__Top_ponger,
    InstId_Debug__Top_Debug__Top_referee
};
extern UMLRTController * DefaultController;
extern UMLRTCommsPort borderports_Debug__Top_Debug__Gateway[];
extern UMLRTCommsPort internalports_Debug__Top_Debug__Gateway[];
extern UMLRTCommsPort borderports_Debug__Top_Debug__Top_pinger[];
extern UMLRTCommsPort internalports_Debug__Top_Debug__Top_pinger[];
extern UMLRTCommsPort borderports_Debug__Top_Debug__Top_ponger[];
extern UMLRTCommsPort internalports_Debug__Top_Debug__Top_ponger[];
extern UMLRTCommsPort borderports_Debug__Top_Debug__Top_referee[];
extern UMLRTCommsPort internalports_Debug__Top_Debug__Top_referee[];
extern UMLRTSlot Debug__Top_slots[];

#endif


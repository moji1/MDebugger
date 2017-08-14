
#ifndef TOPCONTROLLERS_HH
#define TOPCONTROLLERS_HH

class UMLRTController;
struct UMLRTCommsPort;
struct UMLRTSlot;

enum CapsuleInstanceId
{
    InstId_Top,
    InstId_Top_pinger,
    InstId_Top_ponger,
    InstId_Top_referee
};
extern UMLRTController * DefaultController;
extern UMLRTCommsPort borderports_Top_pinger[];
extern UMLRTCommsPort internalports_Top_pinger[];
extern UMLRTCommsPort borderports_Top_ponger[];
extern UMLRTCommsPort internalports_Top_ponger[];
extern UMLRTCommsPort borderports_Top_referee[];
extern UMLRTCommsPort internalports_Top_referee[];
extern UMLRTSlot Top_slots[];

#endif


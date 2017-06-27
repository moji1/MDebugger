
#ifndef PARCER_ROUTERCONTROLLERS_HH
#define PARCER_ROUTERCONTROLLERS_HH

class UMLRTController;
struct UMLRTCommsPort;
struct UMLRTSlot;

enum CapsuleInstanceId
{
    InstId_Parcer_Router,
    InstId_Parcer_Router_bin0,
    InstId_Parcer_Router_bin1,
    InstId_Parcer_Router_bin2,
    InstId_Parcer_Router_bin3,
    InstId_Parcer_Router_gen,
    InstId_Parcer_Router_left,
    InstId_Parcer_Router_left_chute1,
    InstId_Parcer_Router_left_chute2,
    InstId_Parcer_Router_left_sensor,
    InstId_Parcer_Router_left_switcher,
    InstId_Parcer_Router_right,
    InstId_Parcer_Router_right_chute1,
    InstId_Parcer_Router_right_chute2,
    InstId_Parcer_Router_right_sensor,
    InstId_Parcer_Router_right_switcher,
    InstId_Parcer_Router_top,
    InstId_Parcer_Router_top_chute1,
    InstId_Parcer_Router_top_chute2,
    InstId_Parcer_Router_top_sensor,
    InstId_Parcer_Router_top_switcher
};
extern UMLRTController * DefaultController;
extern UMLRTCommsPort borderports_Parcer_Router_bin0[];
extern UMLRTCommsPort borderports_Parcer_Router_bin1[];
extern UMLRTCommsPort borderports_Parcer_Router_bin2[];
extern UMLRTCommsPort borderports_Parcer_Router_bin3[];
extern UMLRTCommsPort borderports_Parcer_Router_gen[];
extern UMLRTCommsPort borderports_Parcer_Router_left[];
extern UMLRTCommsPort borderports_Parcer_Router_left_chute1[];
extern UMLRTCommsPort borderports_Parcer_Router_left_chute2[];
extern UMLRTCommsPort borderports_Parcer_Router_left_sensor[];
extern UMLRTCommsPort borderports_Parcer_Router_left_switcher[];
extern UMLRTCommsPort borderports_Parcer_Router_right[];
extern UMLRTCommsPort borderports_Parcer_Router_right_chute1[];
extern UMLRTCommsPort borderports_Parcer_Router_right_chute2[];
extern UMLRTCommsPort borderports_Parcer_Router_right_sensor[];
extern UMLRTCommsPort borderports_Parcer_Router_right_switcher[];
extern UMLRTCommsPort borderports_Parcer_Router_top[];
extern UMLRTCommsPort borderports_Parcer_Router_top_chute1[];
extern UMLRTCommsPort borderports_Parcer_Router_top_chute2[];
extern UMLRTCommsPort borderports_Parcer_Router_top_sensor[];
extern UMLRTCommsPort borderports_Parcer_Router_top_switcher[];
extern UMLRTSlot Parcer_Router_slots[];

#endif


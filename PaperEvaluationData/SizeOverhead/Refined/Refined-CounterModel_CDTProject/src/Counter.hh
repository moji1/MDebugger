
#ifndef COUNTER_HH
#define COUNTER_HH

#include "ExtInterface.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtmessage.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

#include <iostream>
#include "Event.h"

#include "SROManager.h"

class Capsule_Counter : public UMLRTCapsule
{
public:
    Capsule_Counter( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
    enum PortId
    {
        port_extComm,
        port_timer1
    };
    virtual void inject( const UMLRTMessage & message );
    virtual void initialize( const UMLRTMessage & message );
    const char * getCurrentStateString() const;
private:
    enum State
    {
        Debug__C__intittrans,
        Debug__C__trans1,
        Debug__C__intittrans__Debug__A__Ac__intittrans,
        Debug__C__intittrans__Debug__A__En__intittrans,
        Debug__C__intittrans__Debug__B__Ac__intittrans,
        Debug__C__intittrans__boundary,
        Debug__C__trans1__Debug__A__Ac__trans1,
        Debug__C__trans1__Debug__A__En__State1,
        Debug__C__trans1__Debug__B__Ac__trans1,
        Debug__C__trans1__Debug__B__Ex__State1,
        Debug__C__trans1__boundary,
        Debug__InitState,
        State1,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[14];
    State currentState;
    State history[2];
    void save_history( State compositeState, State subState );
    bool check_history( State compositeState, State subState );
    void entryaction_____Debug__C__intittrans__Debug__A__Ac__intittrans( const UMLRTMessage * msg );
    void entryaction_____Debug__C__intittrans__Debug__A__En__intittrans( const UMLRTMessage * msg );
    void entryaction_____Debug__C__intittrans__Debug__B__Ac__intittrans( const UMLRTMessage * msg );
    void entryaction_____Debug__C__intittrans__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__trans1__Debug__A__Ac__trans1( const UMLRTMessage * msg );
    void entryaction_____Debug__C__trans1__Debug__A__En__State1( const UMLRTMessage * msg );
    void entryaction_____Debug__C__trans1__Debug__B__Ac__trans1( const UMLRTMessage * msg );
    void entryaction_____Debug__C__trans1__Debug__B__Ex__State1( const UMLRTMessage * msg );
    void entryaction_____Debug__C__trans1__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__InitState( const UMLRTMessage * msg );
    void entryaction_____State1( const UMLRTMessage * msg );
    void exitaction_____Debug__C__intittrans__Debug__A__Ac__intittrans( const UMLRTMessage * msg );
    void exitaction_____Debug__C__intittrans__Debug__A__En__intittrans( const UMLRTMessage * msg );
    void exitaction_____Debug__C__intittrans__Debug__B__Ac__intittrans( const UMLRTMessage * msg );
    void exitaction_____Debug__C__intittrans__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__trans1__Debug__A__Ac__trans1( const UMLRTMessage * msg );
    void exitaction_____Debug__C__trans1__Debug__A__En__State1( const UMLRTMessage * msg );
    void exitaction_____Debug__C__trans1__Debug__B__Ac__trans1( const UMLRTMessage * msg );
    void exitaction_____Debug__C__trans1__Debug__B__Ex__State1( const UMLRTMessage * msg );
    void exitaction_____Debug__C__trans1__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__InitState( const UMLRTMessage * msg );
    void exitaction_____State1( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__intittrans__Debug__Ac__intittrans( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__intittrans__Debug__En__State1( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__intittrans__Debug__end__trans__intittrans( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__intittrans__Debug__init__trans__intittrans( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__trans1__Debug__AC__trans1( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__trans1__Debug__En__State1( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__trans1__Debug__Ex__State1( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__trans1__Debug__end__trans__trans1( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__trans1__Debug__init__trans__trans1( const UMLRTMessage * msg );
    void transitionaction_____Debug__InitDebug( const UMLRTMessage * msg );
    void transitionaction_____Debug__intittrans( const UMLRTMessage * msg );
    void transitionaction_____Debug__intittrans__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__intittrans__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__intittrans__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__trans1( const UMLRTMessage * msg );
    void transitionaction_____Debug__trans1__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__trans1__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__trans1__dbg( const UMLRTMessage * msg );
    void transitionaction_____intittrans( const UMLRTMessage * msg );
    void transitionaction_____trans1( const UMLRTMessage * msg );
    bool action_____Debug__intittrans__S__Debug__Guardintittrans( const UMLRTMessage * msg );
    bool action_____Debug__trans1__S__Debug__Guardtrans1( const UMLRTMessage * msg );
    void actionchain_____Debug__C__intittrans__Debug__Ac__intittrans( const UMLRTMessage * msg );
    void actionchain_____Debug__C__intittrans__Debug__En__State1( const UMLRTMessage * msg );
    void actionchain_____Debug__C__intittrans__Debug__end__trans__intittrans( const UMLRTMessage * msg );
    void actionchain_____Debug__C__intittrans__Debug__init__trans__intittrans( const UMLRTMessage * msg );
    void actionchain_____Debug__C__intittrans__new_transition_1( const UMLRTMessage * msg );
    void actionchain_____Debug__C__intittrans__new_transition_2( const UMLRTMessage * msg );
    void actionchain_____Debug__C__intittrans__new_transition_3( const UMLRTMessage * msg );
    void actionchain_____Debug__C__intittrans__new_transition_4_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__intittrans__new_transition_5( const UMLRTMessage * msg );
    void actionchain_____Debug__C__intittrans__new_transition_6( const UMLRTMessage * msg );
    void actionchain_____Debug__C__intittrans__new_transition_7( const UMLRTMessage * msg );
    void actionchain_____Debug__C__intittrans__new_transition_8( const UMLRTMessage * msg );
    void actionchain_____Debug__C__trans1__Debug__AC__trans1( const UMLRTMessage * msg );
    void actionchain_____Debug__C__trans1__Debug__En__State1( const UMLRTMessage * msg );
    void actionchain_____Debug__C__trans1__Debug__Ex__State1( const UMLRTMessage * msg );
    void actionchain_____Debug__C__trans1__Debug__end__trans__trans1( const UMLRTMessage * msg );
    void actionchain_____Debug__C__trans1__Debug__init__trans__trans1( const UMLRTMessage * msg );
    void actionchain_____Debug__C__trans1__new_transition_10( const UMLRTMessage * msg );
    void actionchain_____Debug__C__trans1__new_transition_11( const UMLRTMessage * msg );
    void actionchain_____Debug__C__trans1__new_transition_12( const UMLRTMessage * msg );
    void actionchain_____Debug__C__trans1__new_transition_13_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__trans1__new_transition_14( const UMLRTMessage * msg );
    void actionchain_____Debug__C__trans1__new_transition_15( const UMLRTMessage * msg );
    void actionchain_____Debug__C__trans1__new_transition_16( const UMLRTMessage * msg );
    void actionchain_____Debug__C__trans1__new_transition_17( const UMLRTMessage * msg );
    void actionchain_____Debug__C__trans1__new_transition_18( const UMLRTMessage * msg );
    void actionchain_____Debug__C__trans1__new_transition_9( const UMLRTMessage * msg );
    void actionchain_____Debug__InitDebug( const UMLRTMessage * msg );
    void actionchain_____Debug__intittrans( const UMLRTMessage * msg );
    void actionchain_____Debug__intittrans__E( const UMLRTMessage * msg );
    void actionchain_____Debug__intittrans__S( const UMLRTMessage * msg );
    void actionchain_____Debug__intittrans__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__trans1( const UMLRTMessage * msg );
    void actionchain_____Debug__trans1__E( const UMLRTMessage * msg );
    void actionchain_____Debug__trans1__S( const UMLRTMessage * msg );
    void actionchain_____Debug__trans1__dbg( const UMLRTMessage * msg );
    void actionchain_____intittrans( const UMLRTMessage * msg );
    void actionchain_____trans1( const UMLRTMessage * msg );
    State junction_____Debug__C__intittrans__en( const UMLRTMessage * msg );
    State junction_____Debug__C__intittrans__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__intittrans__new_exitpoint_1( const UMLRTMessage * msg );
    State junction_____Debug__C__trans1__en( const UMLRTMessage * msg );
    State junction_____Debug__C__trans1__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__trans1__new_exitpoint_2( const UMLRTMessage * msg );
    State choice_____Debug__C__intittrans__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__trans1__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__Path__intittrans( const UMLRTMessage * msg );
    State choice_____Debug__Path__trans1( const UMLRTMessage * msg );
    State state_____Debug__C__intittrans__Debug__A__Ac__intittrans( const UMLRTMessage * msg );
    State state_____Debug__C__intittrans__Debug__A__En__intittrans( const UMLRTMessage * msg );
    State state_____Debug__C__intittrans__Debug__B__Ac__intittrans( const UMLRTMessage * msg );
    State state_____Debug__C__intittrans__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__trans1__Debug__A__Ac__trans1( const UMLRTMessage * msg );
    State state_____Debug__C__trans1__Debug__A__En__State1( const UMLRTMessage * msg );
    State state_____Debug__C__trans1__Debug__B__Ac__trans1( const UMLRTMessage * msg );
    State state_____Debug__C__trans1__Debug__B__Ex__State1( const UMLRTMessage * msg );
    State state_____Debug__C__trans1__boundary( const UMLRTMessage * msg );
    State state_____Debug__InitState( const UMLRTMessage * msg );
    State state_____State1( const UMLRTMessage * msg );
protected:
    ExtInterface::Conj extComm;
public:
    enum BorderPortId
    {
        borderport_extComm,
        borderport_timer1
    };
protected:
    UMLRTTimerProtocol_baserole timer1;
public:
    enum PartId
    {
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    int Attribute1;
    int counter;
    bool Debug__flag;
    char * Debug__variablesData;
    debugEvents::Event Debug__event;
    SROManager Debug__SRO;
    void Debug__variablesView();
    bool Debug__variablesChange( char * varName, char * varValue );
    void Debug__sendEvent( debugEvents::EVENTSOURCEKIND eventSourceKind, debugEvents::EVENTTYPE eventType, const char * instanceName, int capsuleIndex, const char * signalName, char * capsuleName, char * sourceName, char * reserve1, char * reserve2, char * reserve3 );
};
extern const UMLRTCapsuleClass Counter;

#endif


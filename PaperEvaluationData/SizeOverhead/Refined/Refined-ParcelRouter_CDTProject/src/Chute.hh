
#ifndef CHUTE_HH
#define CHUTE_HH

#include "ExtInterface.hh"
#include "Parcel.hh"
#include "detection.hh"
#include "transmission.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtlogprotocol.hh"
#include "umlrtmessage.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

#include "Event.h"

#include "SROManager.h"

class Capsule_Chute : public UMLRTCapsule
{
public:
    Capsule_Chute( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
    enum BorderPortId
    {
        borderport_enter,
        borderport_detection,
        borderport_exit,
        borderport_extComm,
        borderport_timer,
        borderport_log
    };
protected:
    detection::Base detection;
    transmission::Conj enter;
    transmission::Base exit;
    ExtInterface::Conj extComm;
    UMLRTLogProtocol_baserole log;
    UMLRTTimerProtocol_baserole timer;
public:
    enum PartId
    {
    };
    enum PortId
    {
        port_detection,
        port_enter,
        port_exit,
        port_extComm,
        port_log,
        port_timer
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    Parcel parcel;
    bool successorFree;
    int delay;
    bool Debug__flag;
    char * Debug__variablesData;
    debugEvents::Event Debug__event;
    SROManager Debug__SRO;
    void Debug__variablesView();
    bool Debug__variablesChange( char * varName, char * varValue );
    void Debug__sendEvent( debugEvents::EVENTSOURCEKIND eventSourceKind, debugEvents::EVENTTYPE eventType, const char * instanceName, int capsuleIndex, const char * signalName, char * capsuleName, char * sourceName, char * reserve1, char * reserve2, char * reserve3 );
    virtual void inject( const UMLRTMessage & message );
    virtual void initialize( const UMLRTMessage & message );
    const char * getCurrentStateString() const;
private:
    enum State
    {
        Debug__C__IDLE__IDLE__15,
        Debug__C__Initial,
        Debug__C__OCCUPIED__OCCUPIED__14,
        Debug__C__jam____IDLE__16,
        Debug__C__jam____OCCUPIED__13,
        Debug__C__reception,
        Debug__C__transmission,
        Debug__C__IDLE__IDLE__15__Debug__A__Ac__IDLE__IDLE__15,
        Debug__C__IDLE__IDLE__15__Debug__A__En__IDLE,
        Debug__C__IDLE__IDLE__15__Debug__B__Ac__IDLE__IDLE__15,
        Debug__C__IDLE__IDLE__15__Debug__B__Ex__IDLE,
        Debug__C__IDLE__IDLE__15__boundary,
        Debug__C__Initial__Debug__A__Ac__Initial,
        Debug__C__Initial__Debug__A__En__Initial,
        Debug__C__Initial__Debug__B__Ac__Initial,
        Debug__C__Initial__boundary,
        Debug__C__OCCUPIED__OCCUPIED__14__Debug__A__Ac__OCCUPIED__OCCUPIED__14,
        Debug__C__OCCUPIED__OCCUPIED__14__Debug__A__En__OCCUPIED,
        Debug__C__OCCUPIED__OCCUPIED__14__Debug__B__Ac__OCCUPIED__OCCUPIED__14,
        Debug__C__OCCUPIED__OCCUPIED__14__Debug__B__Ex__OCCUPIED,
        Debug__C__OCCUPIED__OCCUPIED__14__boundary,
        Debug__C__jam____IDLE__16__Debug__A__Ac__jam____IDLE__16,
        Debug__C__jam____IDLE__16__Debug__A__En__jam____IDLE__16,
        Debug__C__jam____IDLE__16__Debug__B__Ac__jam____IDLE__16,
        Debug__C__jam____IDLE__16__boundary,
        Debug__C__jam____OCCUPIED__13__Debug__A__Ac__jam____OCCUPIED__13,
        Debug__C__jam____OCCUPIED__13__Debug__A__En__jam____OCCUPIED__13,
        Debug__C__jam____OCCUPIED__13__Debug__B__Ac__jam____OCCUPIED__13,
        Debug__C__jam____OCCUPIED__13__boundary,
        Debug__C__reception__Debug__A__Ac__reception,
        Debug__C__reception__Debug__A__En__OCCUPIED,
        Debug__C__reception__Debug__B__Ac__reception,
        Debug__C__reception__Debug__B__Ex__IDLE,
        Debug__C__reception__boundary,
        Debug__C__transmission__Debug__A__Ac__transmission,
        Debug__C__transmission__Debug__B__Ac__transmission,
        Debug__C__transmission__Debug__B__Ex__OCCUPIED,
        Debug__C__transmission__boundary,
        Debug__InitState,
        IDLE,
        OCCUPIED,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[42];
    State currentState;
    State history[7];
    void save_history( State compositeState, State subState );
    bool check_history( State compositeState, State subState );
    void entryaction_____Debug__C__IDLE__IDLE__15__Debug__A__Ac__IDLE__IDLE__15( const UMLRTMessage * msg );
    void entryaction_____Debug__C__IDLE__IDLE__15__Debug__A__En__IDLE( const UMLRTMessage * msg );
    void entryaction_____Debug__C__IDLE__IDLE__15__Debug__B__Ac__IDLE__IDLE__15( const UMLRTMessage * msg );
    void entryaction_____Debug__C__IDLE__IDLE__15__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    void entryaction_____Debug__C__IDLE__IDLE__15__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Initial__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__OCCUPIED__OCCUPIED__14__Debug__A__Ac__OCCUPIED__OCCUPIED__14( const UMLRTMessage * msg );
    void entryaction_____Debug__C__OCCUPIED__OCCUPIED__14__Debug__A__En__OCCUPIED( const UMLRTMessage * msg );
    void entryaction_____Debug__C__OCCUPIED__OCCUPIED__14__Debug__B__Ac__OCCUPIED__OCCUPIED__14( const UMLRTMessage * msg );
    void entryaction_____Debug__C__OCCUPIED__OCCUPIED__14__Debug__B__Ex__OCCUPIED( const UMLRTMessage * msg );
    void entryaction_____Debug__C__OCCUPIED__OCCUPIED__14__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__jam____IDLE__16__Debug__A__Ac__jam____IDLE__16( const UMLRTMessage * msg );
    void entryaction_____Debug__C__jam____IDLE__16__Debug__A__En__jam____IDLE__16( const UMLRTMessage * msg );
    void entryaction_____Debug__C__jam____IDLE__16__Debug__B__Ac__jam____IDLE__16( const UMLRTMessage * msg );
    void entryaction_____Debug__C__jam____IDLE__16__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__jam____OCCUPIED__13__Debug__A__Ac__jam____OCCUPIED__13( const UMLRTMessage * msg );
    void entryaction_____Debug__C__jam____OCCUPIED__13__Debug__A__En__jam____OCCUPIED__13( const UMLRTMessage * msg );
    void entryaction_____Debug__C__jam____OCCUPIED__13__Debug__B__Ac__jam____OCCUPIED__13( const UMLRTMessage * msg );
    void entryaction_____Debug__C__jam____OCCUPIED__13__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__reception__Debug__A__Ac__reception( const UMLRTMessage * msg );
    void entryaction_____Debug__C__reception__Debug__A__En__OCCUPIED( const UMLRTMessage * msg );
    void entryaction_____Debug__C__reception__Debug__B__Ac__reception( const UMLRTMessage * msg );
    void entryaction_____Debug__C__reception__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    void entryaction_____Debug__C__reception__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__transmission__Debug__A__Ac__transmission( const UMLRTMessage * msg );
    void entryaction_____Debug__C__transmission__Debug__B__Ac__transmission( const UMLRTMessage * msg );
    void entryaction_____Debug__C__transmission__Debug__B__Ex__OCCUPIED( const UMLRTMessage * msg );
    void entryaction_____Debug__C__transmission__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__InitState( const UMLRTMessage * msg );
    void entryaction_____IDLE( const UMLRTMessage * msg );
    void entryaction_____OCCUPIED( const UMLRTMessage * msg );
    void exitaction_____Debug__C__IDLE__IDLE__15__Debug__A__Ac__IDLE__IDLE__15( const UMLRTMessage * msg );
    void exitaction_____Debug__C__IDLE__IDLE__15__Debug__A__En__IDLE( const UMLRTMessage * msg );
    void exitaction_____Debug__C__IDLE__IDLE__15__Debug__B__Ac__IDLE__IDLE__15( const UMLRTMessage * msg );
    void exitaction_____Debug__C__IDLE__IDLE__15__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    void exitaction_____Debug__C__IDLE__IDLE__15__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__OCCUPIED__OCCUPIED__14__Debug__A__Ac__OCCUPIED__OCCUPIED__14( const UMLRTMessage * msg );
    void exitaction_____Debug__C__OCCUPIED__OCCUPIED__14__Debug__A__En__OCCUPIED( const UMLRTMessage * msg );
    void exitaction_____Debug__C__OCCUPIED__OCCUPIED__14__Debug__B__Ac__OCCUPIED__OCCUPIED__14( const UMLRTMessage * msg );
    void exitaction_____Debug__C__OCCUPIED__OCCUPIED__14__Debug__B__Ex__OCCUPIED( const UMLRTMessage * msg );
    void exitaction_____Debug__C__OCCUPIED__OCCUPIED__14__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__jam____IDLE__16__Debug__A__Ac__jam____IDLE__16( const UMLRTMessage * msg );
    void exitaction_____Debug__C__jam____IDLE__16__Debug__A__En__jam____IDLE__16( const UMLRTMessage * msg );
    void exitaction_____Debug__C__jam____IDLE__16__Debug__B__Ac__jam____IDLE__16( const UMLRTMessage * msg );
    void exitaction_____Debug__C__jam____IDLE__16__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__jam____OCCUPIED__13__Debug__A__Ac__jam____OCCUPIED__13( const UMLRTMessage * msg );
    void exitaction_____Debug__C__jam____OCCUPIED__13__Debug__A__En__jam____OCCUPIED__13( const UMLRTMessage * msg );
    void exitaction_____Debug__C__jam____OCCUPIED__13__Debug__B__Ac__jam____OCCUPIED__13( const UMLRTMessage * msg );
    void exitaction_____Debug__C__jam____OCCUPIED__13__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__reception__Debug__A__Ac__reception( const UMLRTMessage * msg );
    void exitaction_____Debug__C__reception__Debug__A__En__OCCUPIED( const UMLRTMessage * msg );
    void exitaction_____Debug__C__reception__Debug__B__Ac__reception( const UMLRTMessage * msg );
    void exitaction_____Debug__C__reception__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    void exitaction_____Debug__C__reception__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__transmission__Debug__A__Ac__transmission( const UMLRTMessage * msg );
    void exitaction_____Debug__C__transmission__Debug__B__Ac__transmission( const UMLRTMessage * msg );
    void exitaction_____Debug__C__transmission__Debug__B__Ex__OCCUPIED( const UMLRTMessage * msg );
    void exitaction_____Debug__C__transmission__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__InitState( const UMLRTMessage * msg );
    void exitaction_____IDLE( const UMLRTMessage * msg );
    void exitaction_____OCCUPIED( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__IDLE__IDLE__15__Debug__AC__IDLE__IDLE__15( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__IDLE__IDLE__15__Debug__En__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__IDLE__IDLE__15__Debug__Ex__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__IDLE__IDLE__15__Debug__end__trans__IDLE__IDLE__15( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__IDLE__IDLE__15__Debug__init__trans__IDLE__IDLE__15( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial__Debug__Ac__Initial( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial__Debug__En__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial__Debug__end__trans__Initial( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial__Debug__init__trans__Initial( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__OCCUPIED__OCCUPIED__14__Debug__AC__OCCUPIED__OCCUPIED__14( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__OCCUPIED__OCCUPIED__14__Debug__En__OCCUPIED( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__OCCUPIED__OCCUPIED__14__Debug__Ex__OCCUPIED( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__OCCUPIED__OCCUPIED__14__Debug__end__trans__OCCUPIED__OCCUPIED__14( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__OCCUPIED__OCCUPIED__14__Debug__init__trans__OCCUPIED__OCCUPIED__14( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__jam____IDLE__16__Debug__Ac__jam____IDLE__16( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__jam____IDLE__16__Debug__En__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__jam____IDLE__16__Debug__end__trans__jam____IDLE__16( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__jam____IDLE__16__Debug__init__trans__jam____IDLE__16( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__jam____OCCUPIED__13__Debug__Ac__jam____OCCUPIED__13( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__jam____OCCUPIED__13__Debug__En__OCCUPIED( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__jam____OCCUPIED__13__Debug__end__trans__jam____OCCUPIED__13( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__jam____OCCUPIED__13__Debug__init__trans__jam____OCCUPIED__13( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__reception__Debug__AC__reception( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__reception__Debug__En__OCCUPIED( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__reception__Debug__Ex__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__reception__Debug__end__trans__reception( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__reception__Debug__init__trans__reception( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__transmission__Debug__AC__transmission( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__transmission__Debug__Ex__OCCUPIED( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__transmission__Debug__end__trans__transmission( const UMLRTMessage * msg );
    void transitionaction_____Debug__IDLE__IDLE__15( const UMLRTMessage * msg );
    void transitionaction_____Debug__IDLE__IDLE__15__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__IDLE__IDLE__15__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__IDLE__IDLE__15__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__InitDebug( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__OCCUPIED__OCCUPIED__14( const UMLRTMessage * msg );
    void transitionaction_____Debug__OCCUPIED__OCCUPIED__14__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__OCCUPIED__OCCUPIED__14__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__OCCUPIED__OCCUPIED__14__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__jam____IDLE__16( const UMLRTMessage * msg );
    void transitionaction_____Debug__jam____IDLE__16__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__jam____IDLE__16__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__jam____IDLE__16__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__jam____OCCUPIED__13( const UMLRTMessage * msg );
    void transitionaction_____Debug__jam____OCCUPIED__13__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__jam____OCCUPIED__13__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__jam____OCCUPIED__13__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__reception( const UMLRTMessage * msg );
    void transitionaction_____Debug__reception__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__reception__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__reception__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__transmission( const UMLRTMessage * msg );
    void transitionaction_____Debug__transmission__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__transmission__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__transmission__dbg( const UMLRTMessage * msg );
    void transitionaction_____IDLE__IDLE__15( const UMLRTMessage * msg );
    void transitionaction_____Initial( const UMLRTMessage * msg );
    void transitionaction_____OCCUPIED__OCCUPIED__14( const UMLRTMessage * msg );
    void transitionaction_____jam____IDLE__16( const UMLRTMessage * msg );
    void transitionaction_____jam____OCCUPIED__13( const UMLRTMessage * msg );
    void transitionaction_____reception( const UMLRTMessage * msg );
    void transitionaction_____transmission( const UMLRTMessage * msg );
    bool action_____Debug__IDLE__IDLE__15__S__Debug__GuardIDLE__IDLE__15( const UMLRTMessage * msg );
    bool action_____Debug__Initial__S__Debug__GuardInitial( const UMLRTMessage * msg );
    bool action_____Debug__OCCUPIED__OCCUPIED__14__S__Debug__GuardOCCUPIED__OCCUPIED__14( const UMLRTMessage * msg );
    bool action_____Debug__jam____IDLE__16__S__Debug__Guardjam____IDLE__16( const UMLRTMessage * msg );
    bool action_____Debug__jam____IDLE__16__null( const UMLRTMessage * msg );
    bool action_____Debug__jam____OCCUPIED__13__S__Debug__Guardjam____OCCUPIED__13( const UMLRTMessage * msg );
    bool action_____Debug__jam____OCCUPIED__13__null( const UMLRTMessage * msg );
    bool action_____Debug__reception__S__Debug__Guardreception( const UMLRTMessage * msg );
    bool action_____Debug__transmission__S__Debug__Guardtransmission( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__15__Debug__AC__IDLE__IDLE__15( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__15__Debug__En__IDLE( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__15__Debug__Ex__IDLE( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__15__Debug__end__trans__IDLE__IDLE__15( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__15__Debug__init__trans__IDLE__IDLE__15( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__15__new_transition_37( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__15__new_transition_38( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__15__new_transition_39( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__15__new_transition_40( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__15__new_transition_41_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__15__new_transition_42( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__15__new_transition_43( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__15__new_transition_44( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__15__new_transition_45( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__15__new_transition_46( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__Debug__Ac__Initial( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__Debug__En__IDLE( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__Debug__end__trans__Initial( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__Debug__init__trans__Initial( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_1( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_2( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_3( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_4_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_5( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_6( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_7( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_8( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__14__Debug__AC__OCCUPIED__OCCUPIED__14( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__14__Debug__En__OCCUPIED( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__14__Debug__Ex__OCCUPIED( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__14__Debug__end__trans__OCCUPIED__OCCUPIED__14( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__14__Debug__init__trans__OCCUPIED__OCCUPIED__14( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__14__new_transition_27( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__14__new_transition_28( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__14__new_transition_29( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__14__new_transition_30( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__14__new_transition_31_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__14__new_transition_32( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__14__new_transition_33( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__14__new_transition_34( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__14__new_transition_35( const UMLRTMessage * msg );
    void actionchain_____Debug__C__OCCUPIED__OCCUPIED__14__new_transition_36( const UMLRTMessage * msg );
    void actionchain_____Debug__C__jam____IDLE__16__Debug__Ac__jam____IDLE__16( const UMLRTMessage * msg );
    void actionchain_____Debug__C__jam____IDLE__16__Debug__En__IDLE( const UMLRTMessage * msg );
    void actionchain_____Debug__C__jam____IDLE__16__Debug__end__trans__jam____IDLE__16( const UMLRTMessage * msg );
    void actionchain_____Debug__C__jam____IDLE__16__Debug__init__trans__jam____IDLE__16( const UMLRTMessage * msg );
    void actionchain_____Debug__C__jam____IDLE__16__new_transition_47( const UMLRTMessage * msg );
    void actionchain_____Debug__C__jam____IDLE__16__new_transition_48( const UMLRTMessage * msg );
    void actionchain_____Debug__C__jam____IDLE__16__new_transition_49( const UMLRTMessage * msg );
    void actionchain_____Debug__C__jam____IDLE__16__new_transition_50_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__jam____IDLE__16__new_transition_51( const UMLRTMessage * msg );
    void actionchain_____Debug__C__jam____IDLE__16__new_transition_52( const UMLRTMessage * msg );
    void actionchain_____Debug__C__jam____IDLE__16__new_transition_53( const UMLRTMessage * msg );
    void actionchain_____Debug__C__jam____IDLE__16__new_transition_54( const UMLRTMessage * msg );
    void actionchain_____Debug__C__jam____OCCUPIED__13__Debug__Ac__jam____OCCUPIED__13( const UMLRTMessage * msg );
    void actionchain_____Debug__C__jam____OCCUPIED__13__Debug__En__OCCUPIED( const UMLRTMessage * msg );
    void actionchain_____Debug__C__jam____OCCUPIED__13__Debug__end__trans__jam____OCCUPIED__13( const UMLRTMessage * msg );
    void actionchain_____Debug__C__jam____OCCUPIED__13__Debug__init__trans__jam____OCCUPIED__13( const UMLRTMessage * msg );
    void actionchain_____Debug__C__jam____OCCUPIED__13__new_transition_19( const UMLRTMessage * msg );
    void actionchain_____Debug__C__jam____OCCUPIED__13__new_transition_20( const UMLRTMessage * msg );
    void actionchain_____Debug__C__jam____OCCUPIED__13__new_transition_21( const UMLRTMessage * msg );
    void actionchain_____Debug__C__jam____OCCUPIED__13__new_transition_22_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__jam____OCCUPIED__13__new_transition_23( const UMLRTMessage * msg );
    void actionchain_____Debug__C__jam____OCCUPIED__13__new_transition_24( const UMLRTMessage * msg );
    void actionchain_____Debug__C__jam____OCCUPIED__13__new_transition_25( const UMLRTMessage * msg );
    void actionchain_____Debug__C__jam____OCCUPIED__13__new_transition_26( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__Debug__AC__reception( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__Debug__En__OCCUPIED( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__Debug__Ex__IDLE( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__Debug__end__trans__reception( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__Debug__init__trans__reception( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__new_transition_10( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__new_transition_11( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__new_transition_12( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__new_transition_13_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__new_transition_14( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__new_transition_15( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__new_transition_16( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__new_transition_17( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__new_transition_18( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reception__new_transition_9( const UMLRTMessage * msg );
    void actionchain_____Debug__C__transmission__Debug__AC__transmission( const UMLRTMessage * msg );
    void actionchain_____Debug__C__transmission__Debug__Ex__OCCUPIED( const UMLRTMessage * msg );
    void actionchain_____Debug__C__transmission__Debug__end__trans__transmission( const UMLRTMessage * msg );
    void actionchain_____Debug__C__transmission__Debug__init__trans__transmission( const UMLRTMessage * msg );
    void actionchain_____Debug__C__transmission__new_transition_55( const UMLRTMessage * msg );
    void actionchain_____Debug__C__transmission__new_transition_56( const UMLRTMessage * msg );
    void actionchain_____Debug__C__transmission__new_transition_57( const UMLRTMessage * msg );
    void actionchain_____Debug__C__transmission__new_transition_58_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__transmission__new_transition_59( const UMLRTMessage * msg );
    void actionchain_____Debug__C__transmission__new_transition_60( const UMLRTMessage * msg );
    void actionchain_____Debug__C__transmission__new_transition_61( const UMLRTMessage * msg );
    void actionchain_____Debug__C__transmission__new_transition_62( const UMLRTMessage * msg );
    void actionchain_____Debug__IDLE__IDLE__15( const UMLRTMessage * msg );
    void actionchain_____Debug__IDLE__IDLE__15__E( const UMLRTMessage * msg );
    void actionchain_____Debug__IDLE__IDLE__15__S( const UMLRTMessage * msg );
    void actionchain_____Debug__IDLE__IDLE__15__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__InitDebug( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial__E( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial__S( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__OCCUPIED__OCCUPIED__14( const UMLRTMessage * msg );
    void actionchain_____Debug__OCCUPIED__OCCUPIED__14__E( const UMLRTMessage * msg );
    void actionchain_____Debug__OCCUPIED__OCCUPIED__14__S( const UMLRTMessage * msg );
    void actionchain_____Debug__OCCUPIED__OCCUPIED__14__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__jam____IDLE__16( const UMLRTMessage * msg );
    void actionchain_____Debug__jam____IDLE__16__E( const UMLRTMessage * msg );
    void actionchain_____Debug__jam____IDLE__16__S( const UMLRTMessage * msg );
    void actionchain_____Debug__jam____IDLE__16__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__jam____OCCUPIED__13( const UMLRTMessage * msg );
    void actionchain_____Debug__jam____OCCUPIED__13__E( const UMLRTMessage * msg );
    void actionchain_____Debug__jam____OCCUPIED__13__S( const UMLRTMessage * msg );
    void actionchain_____Debug__jam____OCCUPIED__13__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__reception( const UMLRTMessage * msg );
    void actionchain_____Debug__reception__E( const UMLRTMessage * msg );
    void actionchain_____Debug__reception__S( const UMLRTMessage * msg );
    void actionchain_____Debug__reception__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__transmission( const UMLRTMessage * msg );
    void actionchain_____Debug__transmission__E( const UMLRTMessage * msg );
    void actionchain_____Debug__transmission__S( const UMLRTMessage * msg );
    void actionchain_____Debug__transmission__dbg( const UMLRTMessage * msg );
    void actionchain_____IDLE__IDLE__15( const UMLRTMessage * msg );
    void actionchain_____Initial( const UMLRTMessage * msg );
    void actionchain_____OCCUPIED__OCCUPIED__14( const UMLRTMessage * msg );
    void actionchain_____jam____IDLE__16( const UMLRTMessage * msg );
    void actionchain_____jam____OCCUPIED__13( const UMLRTMessage * msg );
    void actionchain_____reception( const UMLRTMessage * msg );
    void actionchain_____transmission( const UMLRTMessage * msg );
    State junction_____Debug__C__IDLE__IDLE__15__en( const UMLRTMessage * msg );
    State junction_____Debug__C__IDLE__IDLE__15__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__IDLE__IDLE__15__new_exitpoint_5( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__en( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__new_exitpoint_1( const UMLRTMessage * msg );
    State junction_____Debug__C__OCCUPIED__OCCUPIED__14__en( const UMLRTMessage * msg );
    State junction_____Debug__C__OCCUPIED__OCCUPIED__14__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__OCCUPIED__OCCUPIED__14__new_exitpoint_4( const UMLRTMessage * msg );
    State junction_____Debug__C__jam____IDLE__16__en( const UMLRTMessage * msg );
    State junction_____Debug__C__jam____IDLE__16__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__jam____IDLE__16__new_exitpoint_6( const UMLRTMessage * msg );
    State junction_____Debug__C__jam____OCCUPIED__13__en( const UMLRTMessage * msg );
    State junction_____Debug__C__jam____OCCUPIED__13__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__jam____OCCUPIED__13__new_exitpoint_3( const UMLRTMessage * msg );
    State junction_____Debug__C__reception__en( const UMLRTMessage * msg );
    State junction_____Debug__C__reception__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__reception__new_exitpoint_2( const UMLRTMessage * msg );
    State junction_____Debug__C__transmission__en( const UMLRTMessage * msg );
    State junction_____Debug__C__transmission__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__transmission__new_exitpoint_7( const UMLRTMessage * msg );
    State choice_____Debug__C__IDLE__IDLE__15__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__Initial__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__OCCUPIED__OCCUPIED__14__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__jam____IDLE__16__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__jam____OCCUPIED__13__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__reception__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__transmission__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__Path__IDLE__IDLE__15( const UMLRTMessage * msg );
    State choice_____Debug__Path__Initial( const UMLRTMessage * msg );
    State choice_____Debug__Path__OCCUPIED__OCCUPIED__14( const UMLRTMessage * msg );
    State choice_____Debug__Path__jam____IDLE__16( const UMLRTMessage * msg );
    State choice_____Debug__Path__jam____OCCUPIED__13( const UMLRTMessage * msg );
    State choice_____Debug__Path__reception( const UMLRTMessage * msg );
    State choice_____Debug__Path__transmission( const UMLRTMessage * msg );
    State choice_____jam__( const UMLRTMessage * msg );
    State state_____Debug__C__IDLE__IDLE__15__Debug__A__Ac__IDLE__IDLE__15( const UMLRTMessage * msg );
    State state_____Debug__C__IDLE__IDLE__15__Debug__A__En__IDLE( const UMLRTMessage * msg );
    State state_____Debug__C__IDLE__IDLE__15__Debug__B__Ac__IDLE__IDLE__15( const UMLRTMessage * msg );
    State state_____Debug__C__IDLE__IDLE__15__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    State state_____Debug__C__IDLE__IDLE__15__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg );
    State state_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg );
    State state_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg );
    State state_____Debug__C__Initial__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__OCCUPIED__OCCUPIED__14__Debug__A__Ac__OCCUPIED__OCCUPIED__14( const UMLRTMessage * msg );
    State state_____Debug__C__OCCUPIED__OCCUPIED__14__Debug__A__En__OCCUPIED( const UMLRTMessage * msg );
    State state_____Debug__C__OCCUPIED__OCCUPIED__14__Debug__B__Ac__OCCUPIED__OCCUPIED__14( const UMLRTMessage * msg );
    State state_____Debug__C__OCCUPIED__OCCUPIED__14__Debug__B__Ex__OCCUPIED( const UMLRTMessage * msg );
    State state_____Debug__C__OCCUPIED__OCCUPIED__14__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__jam____IDLE__16__Debug__A__Ac__jam____IDLE__16( const UMLRTMessage * msg );
    State state_____Debug__C__jam____IDLE__16__Debug__A__En__jam____IDLE__16( const UMLRTMessage * msg );
    State state_____Debug__C__jam____IDLE__16__Debug__B__Ac__jam____IDLE__16( const UMLRTMessage * msg );
    State state_____Debug__C__jam____IDLE__16__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__jam____OCCUPIED__13__Debug__A__Ac__jam____OCCUPIED__13( const UMLRTMessage * msg );
    State state_____Debug__C__jam____OCCUPIED__13__Debug__A__En__jam____OCCUPIED__13( const UMLRTMessage * msg );
    State state_____Debug__C__jam____OCCUPIED__13__Debug__B__Ac__jam____OCCUPIED__13( const UMLRTMessage * msg );
    State state_____Debug__C__jam____OCCUPIED__13__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__reception__Debug__A__Ac__reception( const UMLRTMessage * msg );
    State state_____Debug__C__reception__Debug__A__En__OCCUPIED( const UMLRTMessage * msg );
    State state_____Debug__C__reception__Debug__B__Ac__reception( const UMLRTMessage * msg );
    State state_____Debug__C__reception__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    State state_____Debug__C__reception__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__transmission__Debug__A__Ac__transmission( const UMLRTMessage * msg );
    State state_____Debug__C__transmission__Debug__B__Ac__transmission( const UMLRTMessage * msg );
    State state_____Debug__C__transmission__Debug__B__Ex__OCCUPIED( const UMLRTMessage * msg );
    State state_____Debug__C__transmission__boundary( const UMLRTMessage * msg );
    State state_____Debug__InitState( const UMLRTMessage * msg );
    State state_____IDLE( const UMLRTMessage * msg );
    State state_____OCCUPIED( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass Chute;

#endif


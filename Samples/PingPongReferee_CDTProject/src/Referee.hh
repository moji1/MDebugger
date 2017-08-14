
#ifndef REFEREE_HH
#define REFEREE_HH

#include "ExtInterface.hh"
#include "StartProtocol.hh"
#include "endProtocol.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtlogprotocol.hh"
#include "umlrtmessage.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

#include "Event.h"

#include "SROManager.h"

class Capsule_Referee : public UMLRTCapsule
{
public:
    Capsule_Referee( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    endProtocol::Conj endPort;
public:
    enum BorderPortId
    {
        borderport_endPort,
        borderport_startPort
    };
protected:
    ExtInterface::Conj extComm;
public:
    enum InternalPortId
    {
        internalport_extComm,
        internalport_refereeTimer,
        internalport_log
    };
protected:
    UMLRTLogProtocol_baserole log;
    UMLRTTimerProtocol_baserole refereeTimer;
    StartProtocol::Base startPort;
public:
    enum PartId
    {
    };
    enum PortId
    {
        port_endPort,
        port_extComm,
        port_log,
        port_refereeTimer,
        port_startPort
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    int round;
    bool Debug__flag;
    char * Debug__variablesData;
    debugEvents::Event Debug__event;
    SROManager Debug__SRO;
    void Debug__recallAllMsg();
    void Debug__variablesView();
    bool Debug__variablesChange( char * varName, char * varValue );
    void Debug__sendEvent( debugEvents::EVENTSOURCEKIND eventSourceKind, debugEvents::EVENTTYPE eventType, const char * instanceName, int capsuleIndex, const char * signalName, const char * capsuleName, char * sourceName, char * reserve1, char * reserve2, const char * reserve3, const char * reserve4 );
    virtual void inject( const UMLRTMessage & message );
    virtual void initialize( const UMLRTMessage & message );
    const char * getCurrentStateString() const;
private:
    enum State
    {
        Debug__C__Initial,
        Debug__C__endRound,
        Debug__C__startRound,
        Debug__C__Initial__Debug__A__Ac__Initial,
        Debug__C__Initial__Debug__A__En__Initial,
        Debug__C__Initial__Debug__B__Ac__Initial,
        Debug__C__Initial__boundary,
        Debug__C__endRound__Debug__A__Ac__endRound,
        Debug__C__endRound__Debug__A__En__STARTING_ROUND,
        Debug__C__endRound__Debug__B__Ac__endRound,
        Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND,
        Debug__C__endRound__boundary,
        Debug__C__startRound__Debug__A__Ac__startRound,
        Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND,
        Debug__C__startRound__Debug__B__Ac__startRound,
        Debug__C__startRound__Debug__B__Ex__STARTING_ROUND,
        Debug__C__startRound__boundary,
        Debug__InitState,
        STARTING_ROUND,
        WAITING_FOR_END_OF_ROUND,
        SPECIAL_INTERNAL_STATE_TOP,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[22];
    State currentState;
    State history[3];
    void save_history( State compositeState, State subState );
    bool check_history( State compositeState, State subState );
    void update_state( State newState );
    void entryaction_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg );
    void entryaction_____Debug__C__endRound__Debug__A__Ac__endRound( const UMLRTMessage * msg );
    void entryaction_____Debug__C__endRound__Debug__A__En__STARTING_ROUND( const UMLRTMessage * msg );
    void entryaction_____Debug__C__endRound__Debug__B__Ac__endRound( const UMLRTMessage * msg );
    void entryaction_____Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND( const UMLRTMessage * msg );
    void entryaction_____Debug__C__startRound__Debug__A__Ac__startRound( const UMLRTMessage * msg );
    void entryaction_____Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND( const UMLRTMessage * msg );
    void entryaction_____Debug__C__startRound__Debug__B__Ac__startRound( const UMLRTMessage * msg );
    void entryaction_____Debug__C__startRound__Debug__B__Ex__STARTING_ROUND( const UMLRTMessage * msg );
    void entryaction_____STARTING_ROUND( const UMLRTMessage * msg );
    void entryaction_____WAITING_FOR_END_OF_ROUND( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg );
    void exitaction_____Debug__C__endRound__Debug__A__Ac__endRound( const UMLRTMessage * msg );
    void exitaction_____Debug__C__endRound__Debug__A__En__STARTING_ROUND( const UMLRTMessage * msg );
    void exitaction_____Debug__C__endRound__Debug__B__Ac__endRound( const UMLRTMessage * msg );
    void exitaction_____Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND( const UMLRTMessage * msg );
    void exitaction_____Debug__C__startRound__Debug__A__Ac__startRound( const UMLRTMessage * msg );
    void exitaction_____Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND( const UMLRTMessage * msg );
    void exitaction_____Debug__C__startRound__Debug__B__Ac__startRound( const UMLRTMessage * msg );
    void exitaction_____Debug__C__startRound__Debug__B__Ex__STARTING_ROUND( const UMLRTMessage * msg );
    void exitaction_____STARTING_ROUND( const UMLRTMessage * msg );
    void exitaction_____WAITING_FOR_END_OF_ROUND( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial__Debug__Ac__Initial( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial__Debug__En__STARTING_ROUND( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial__Debug__end__trans__Initial( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial__Debug__init__trans__Initial( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__endRound__Debug__AC__endRound( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__endRound__Debug__En__STARTING_ROUND( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__endRound__Debug__Ex__WAITING_FOR_END_OF_ROUND( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__endRound__Debug__end__trans__endRound( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__endRound__Debug__init__trans__endRound( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__startRound__Debug__AC__startRound( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__startRound__Debug__En__WAITING_FOR_END_OF_ROUND( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__startRound__Debug__Ex__STARTING_ROUND( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__startRound__Debug__end__trans__startRound( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__startRound__Debug__init__trans__startRound( const UMLRTMessage * msg );
    void transitionaction_____Debug__InitDebug( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial__dbg__dbgDeferMsg( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial__dbg__dbgSetExecMode( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial__dbg__remBreakPoint( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial__dbg__setBreakPoint( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial__dbg__varChange( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial__dbg__viewBreakPoints( const UMLRTMessage * msg );
    void transitionaction_____Debug__endRound( const UMLRTMessage * msg );
    void transitionaction_____Debug__endRound__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__endRound__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__endRound__dbg__dbgDeferMsg( const UMLRTMessage * msg );
    void transitionaction_____Debug__endRound__dbg__dbgSetExecMode( const UMLRTMessage * msg );
    void transitionaction_____Debug__endRound__dbg__remBreakPoint( const UMLRTMessage * msg );
    void transitionaction_____Debug__endRound__dbg__setBreakPoint( const UMLRTMessage * msg );
    void transitionaction_____Debug__endRound__dbg__varChange( const UMLRTMessage * msg );
    void transitionaction_____Debug__endRound__dbg__viewBreakPoints( const UMLRTMessage * msg );
    void transitionaction_____Debug__startRound( const UMLRTMessage * msg );
    void transitionaction_____Debug__startRound__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__startRound__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__startRound__dbg__dbgDeferMsg( const UMLRTMessage * msg );
    void transitionaction_____Debug__startRound__dbg__dbgSetExecMode( const UMLRTMessage * msg );
    void transitionaction_____Debug__startRound__dbg__remBreakPoint( const UMLRTMessage * msg );
    void transitionaction_____Debug__startRound__dbg__setBreakPoint( const UMLRTMessage * msg );
    void transitionaction_____Debug__startRound__dbg__varChange( const UMLRTMessage * msg );
    void transitionaction_____Debug__startRound__dbg__viewBreakPoints( const UMLRTMessage * msg );
    void transitionaction_____Initial( const UMLRTMessage * msg );
    void transitionaction_____endRound( const UMLRTMessage * msg );
    void transitionaction_____startRound( const UMLRTMessage * msg );
    bool guard_____Debug__Initial__S( const UMLRTMessage * msg );
    bool guard_____Debug__endRound__S( const UMLRTMessage * msg );
    bool guard_____Debug__startRound__S( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__Debug__Ac__Initial( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__Debug__En__STARTING_ROUND( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__Debug__end__trans__Initial( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__Debug__init__trans__Initial( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_1( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_10( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_11( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_12( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_13( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_14( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_15( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_16( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_17( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_18( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_19( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_2( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_20( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_21( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_22( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_23( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_24( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_25( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_26( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_27( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_28( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_29( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_3( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_4_to_unvisited_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_5_to_visited_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_6( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_7( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_8( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_9( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__Debug__AC__endRound( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__Debug__En__STARTING_ROUND( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__Debug__Ex__WAITING_FOR_END_OF_ROUND( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__Debug__end__trans__endRound( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__Debug__init__trans__endRound( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_30( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_31( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_32( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_33( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_34_to_unvisited_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_35_to_visited_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_36( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_37( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_38( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_39( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_40( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_41( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_42( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_43( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_44( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_45( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_46( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_47( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_48( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_49( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_50( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_51( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_52( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_53( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_54( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_55( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_56( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_57( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_58( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_59( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_60( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_61( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_62( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_63( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_64( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endRound__new_transition_65( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__Debug__AC__startRound( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__Debug__En__WAITING_FOR_END_OF_ROUND( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__Debug__Ex__STARTING_ROUND( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__Debug__end__trans__startRound( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__Debug__init__trans__startRound( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_100( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_101( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_66( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_67( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_68( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_69( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_70_to_unvisited_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_71_to_visited_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_72( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_73( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_74( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_75( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_76( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_77( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_78( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_79( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_80( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_81( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_82( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_83( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_84( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_85( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_86( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_87( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_88( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_89( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_90( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_91( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_92( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_93( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_94( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_95( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_96( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_97( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_98( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startRound__new_transition_99( const UMLRTMessage * msg );
    void actionchain_____Debug__InitDebug( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial__E( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial__S( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial__dbg__dbgDeferMsg( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial__dbg__dbgSetExecMode( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial__dbg__remBreakPoint( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial__dbg__setBreakPoint( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial__dbg__varChange( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial__dbg__viewBreakPoints( const UMLRTMessage * msg );
    void actionchain_____Debug__endRound( const UMLRTMessage * msg );
    void actionchain_____Debug__endRound__E( const UMLRTMessage * msg );
    void actionchain_____Debug__endRound__S( const UMLRTMessage * msg );
    void actionchain_____Debug__endRound__dbg__dbgDeferMsg( const UMLRTMessage * msg );
    void actionchain_____Debug__endRound__dbg__dbgSetExecMode( const UMLRTMessage * msg );
    void actionchain_____Debug__endRound__dbg__remBreakPoint( const UMLRTMessage * msg );
    void actionchain_____Debug__endRound__dbg__setBreakPoint( const UMLRTMessage * msg );
    void actionchain_____Debug__endRound__dbg__varChange( const UMLRTMessage * msg );
    void actionchain_____Debug__endRound__dbg__viewBreakPoints( const UMLRTMessage * msg );
    void actionchain_____Debug__startRound( const UMLRTMessage * msg );
    void actionchain_____Debug__startRound__E( const UMLRTMessage * msg );
    void actionchain_____Debug__startRound__S( const UMLRTMessage * msg );
    void actionchain_____Debug__startRound__dbg__dbgDeferMsg( const UMLRTMessage * msg );
    void actionchain_____Debug__startRound__dbg__dbgSetExecMode( const UMLRTMessage * msg );
    void actionchain_____Debug__startRound__dbg__remBreakPoint( const UMLRTMessage * msg );
    void actionchain_____Debug__startRound__dbg__setBreakPoint( const UMLRTMessage * msg );
    void actionchain_____Debug__startRound__dbg__varChange( const UMLRTMessage * msg );
    void actionchain_____Debug__startRound__dbg__viewBreakPoints( const UMLRTMessage * msg );
    void actionchain_____Initial( const UMLRTMessage * msg );
    void actionchain_____endRound( const UMLRTMessage * msg );
    void actionchain_____startRound( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__en( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__new_exitpoint_1( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__new_exitpoint_2( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__new_exitpoint_3( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__new_exitpoint_4( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__new_exitpoint_5( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__new_exitpoint_6( const UMLRTMessage * msg );
    State junction_____Debug__C__endRound__en( const UMLRTMessage * msg );
    State junction_____Debug__C__endRound__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__endRound__new_exitpoint_10( const UMLRTMessage * msg );
    State junction_____Debug__C__endRound__new_exitpoint_11( const UMLRTMessage * msg );
    State junction_____Debug__C__endRound__new_exitpoint_12( const UMLRTMessage * msg );
    State junction_____Debug__C__endRound__new_exitpoint_7( const UMLRTMessage * msg );
    State junction_____Debug__C__endRound__new_exitpoint_8( const UMLRTMessage * msg );
    State junction_____Debug__C__endRound__new_exitpoint_9( const UMLRTMessage * msg );
    State junction_____Debug__C__startRound__en( const UMLRTMessage * msg );
    State junction_____Debug__C__startRound__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__startRound__new_exitpoint_13( const UMLRTMessage * msg );
    State junction_____Debug__C__startRound__new_exitpoint_14( const UMLRTMessage * msg );
    State junction_____Debug__C__startRound__new_exitpoint_15( const UMLRTMessage * msg );
    State junction_____Debug__C__startRound__new_exitpoint_16( const UMLRTMessage * msg );
    State junction_____Debug__C__startRound__new_exitpoint_17( const UMLRTMessage * msg );
    State junction_____Debug__C__startRound__new_exitpoint_18( const UMLRTMessage * msg );
    State choice_____Debug__C__Initial__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__endRound__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__startRound__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__Path__Initial( const UMLRTMessage * msg );
    State choice_____Debug__Path__endRound( const UMLRTMessage * msg );
    State choice_____Debug__Path__startRound( const UMLRTMessage * msg );
    State state_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg );
    State state_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg );
    State state_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg );
    State state_____Debug__C__Initial__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__endRound__Debug__A__Ac__endRound( const UMLRTMessage * msg );
    State state_____Debug__C__endRound__Debug__A__En__STARTING_ROUND( const UMLRTMessage * msg );
    State state_____Debug__C__endRound__Debug__B__Ac__endRound( const UMLRTMessage * msg );
    State state_____Debug__C__endRound__Debug__B__Ex__WAITING_FOR_END_OF_ROUND( const UMLRTMessage * msg );
    State state_____Debug__C__endRound__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__startRound__Debug__A__Ac__startRound( const UMLRTMessage * msg );
    State state_____Debug__C__startRound__Debug__A__En__WAITING_FOR_END_OF_ROUND( const UMLRTMessage * msg );
    State state_____Debug__C__startRound__Debug__B__Ac__startRound( const UMLRTMessage * msg );
    State state_____Debug__C__startRound__Debug__B__Ex__STARTING_ROUND( const UMLRTMessage * msg );
    State state_____Debug__C__startRound__boundary( const UMLRTMessage * msg );
    State state_____Debug__InitState( const UMLRTMessage * msg );
    State state_____STARTING_ROUND( const UMLRTMessage * msg );
    State state_____WAITING_FOR_END_OF_ROUND( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass Referee;

#endif


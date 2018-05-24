
#ifndef PONGER_HH
#define PONGER_HH

#include "ExtInterface.hh"
#include "PingPongProtocol.hh"
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

class Capsule_Ponger : public UMLRTCapsule
{
public:
    Capsule_Ponger( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    endProtocol::Base endPort;
public:
    enum BorderPortId
    {
        borderport_endPort,
        borderport_pongPort
    };
protected:
    ExtInterface::Conj extComm;
public:
    enum InternalPortId
    {
        internalport_extComm,
        internalport_pongerTimer,
        internalport_log
    };
protected:
    UMLRTLogProtocol_baserole log;
    PingPongProtocol::Base pongPort;
    UMLRTTimerProtocol_baserole pongerTimer;
public:
    enum PartId
    {
    };
    enum PortId
    {
        port_endPort,
        port_extComm,
        port_log,
        port_pongPort,
        port_pongerTimer
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    int pongsSent;
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
        Debug__C__endOfRound,
        Debug__C__keepPlaying,
        Debug__C__onPing,
        Debug__C__timeout,
        Debug__C__Initial__Debug__A__Ac__Initial,
        Debug__C__Initial__Debug__A__En__Initial,
        Debug__C__Initial__Debug__B__Ac__Initial,
        Debug__C__Initial__boundary,
        Debug__C__endOfRound__Debug__A__Ac__endOfRound,
        Debug__C__endOfRound__Debug__A__En__endOfRound,
        Debug__C__endOfRound__Debug__B__Ac__endOfRound,
        Debug__C__endOfRound__boundary,
        Debug__C__keepPlaying__Debug__A__Ac__keepPlaying,
        Debug__C__keepPlaying__Debug__A__En__keepPlaying,
        Debug__C__keepPlaying__Debug__B__Ac__keepPlaying,
        Debug__C__keepPlaying__boundary,
        Debug__C__onPing__Debug__A__Ac__onPing,
        Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER,
        Debug__C__onPing__Debug__B__Ac__onPing,
        Debug__C__onPing__Debug__B__Ex__PLAYING,
        Debug__C__onPing__boundary,
        Debug__C__timeout__Debug__A__Ac__timeout,
        Debug__C__timeout__Debug__B__Ac__timeout,
        Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER,
        Debug__C__timeout__boundary,
        Debug__InitState,
        PLAYING,
        WAITING_FOR_TIMER,
        SPECIAL_INTERNAL_STATE_TOP,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[31];
    State currentState;
    State history[5];
    void save_history( State compositeState, State subState );
    bool check_history( State compositeState, State subState );
    void update_state( State newState );
    void entryaction_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg );
    void entryaction_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( const UMLRTMessage * msg );
    void entryaction_____Debug__C__endOfRound__Debug__A__En__endOfRound( const UMLRTMessage * msg );
    void entryaction_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( const UMLRTMessage * msg );
    void entryaction_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( const UMLRTMessage * msg );
    void entryaction_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( const UMLRTMessage * msg );
    void entryaction_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( const UMLRTMessage * msg );
    void entryaction_____Debug__C__onPing__Debug__A__Ac__onPing( const UMLRTMessage * msg );
    void entryaction_____Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER( const UMLRTMessage * msg );
    void entryaction_____Debug__C__onPing__Debug__B__Ac__onPing( const UMLRTMessage * msg );
    void entryaction_____Debug__C__onPing__Debug__B__Ex__PLAYING( const UMLRTMessage * msg );
    void entryaction_____Debug__C__timeout__Debug__A__Ac__timeout( const UMLRTMessage * msg );
    void entryaction_____Debug__C__timeout__Debug__B__Ac__timeout( const UMLRTMessage * msg );
    void entryaction_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( const UMLRTMessage * msg );
    void entryaction_____PLAYING( const UMLRTMessage * msg );
    void entryaction_____WAITING_FOR_TIMER( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg );
    void exitaction_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( const UMLRTMessage * msg );
    void exitaction_____Debug__C__endOfRound__Debug__A__En__endOfRound( const UMLRTMessage * msg );
    void exitaction_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( const UMLRTMessage * msg );
    void exitaction_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( const UMLRTMessage * msg );
    void exitaction_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( const UMLRTMessage * msg );
    void exitaction_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( const UMLRTMessage * msg );
    void exitaction_____Debug__C__onPing__Debug__A__Ac__onPing( const UMLRTMessage * msg );
    void exitaction_____Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER( const UMLRTMessage * msg );
    void exitaction_____Debug__C__onPing__Debug__B__Ac__onPing( const UMLRTMessage * msg );
    void exitaction_____Debug__C__onPing__Debug__B__Ex__PLAYING( const UMLRTMessage * msg );
    void exitaction_____Debug__C__timeout__Debug__A__Ac__timeout( const UMLRTMessage * msg );
    void exitaction_____Debug__C__timeout__Debug__B__Ac__timeout( const UMLRTMessage * msg );
    void exitaction_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( const UMLRTMessage * msg );
    void exitaction_____PLAYING( const UMLRTMessage * msg );
    void exitaction_____WAITING_FOR_TIMER( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial__Debug__Ac__Initial( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial__Debug__En__PLAYING( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial__Debug__end__trans__Initial( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial__Debug__init__trans__Initial( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__endOfRound__Debug__Ac__endOfRound( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__endOfRound__Debug__En__PLAYING( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__endOfRound__Debug__end__trans__endOfRound( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__endOfRound__Debug__init__trans__endOfRound( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__keepPlaying__Debug__Ac__keepPlaying( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__keepPlaying__Debug__En__PLAYING( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__keepPlaying__Debug__end__trans__keepPlaying( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__keepPlaying__Debug__init__trans__keepPlaying( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__onPing__Debug__AC__onPing( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__onPing__Debug__En__WAITING_FOR_TIMER( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__onPing__Debug__Ex__PLAYING( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__onPing__Debug__end__trans__onPing( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__onPing__Debug__init__trans__onPing( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__timeout__Debug__AC__timeout( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__timeout__Debug__Ex__WAITING_FOR_TIMER( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__timeout__Debug__end__trans__timeout( const UMLRTMessage * msg );
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
    void transitionaction_____Debug__endOfRound( const UMLRTMessage * msg );
    void transitionaction_____Debug__endOfRound__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__endOfRound__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__endOfRound__dbg__dbgDeferMsg( const UMLRTMessage * msg );
    void transitionaction_____Debug__endOfRound__dbg__dbgSetExecMode( const UMLRTMessage * msg );
    void transitionaction_____Debug__endOfRound__dbg__remBreakPoint( const UMLRTMessage * msg );
    void transitionaction_____Debug__endOfRound__dbg__setBreakPoint( const UMLRTMessage * msg );
    void transitionaction_____Debug__endOfRound__dbg__varChange( const UMLRTMessage * msg );
    void transitionaction_____Debug__endOfRound__dbg__viewBreakPoints( const UMLRTMessage * msg );
    void transitionaction_____Debug__keepPlaying( const UMLRTMessage * msg );
    void transitionaction_____Debug__keepPlaying__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__keepPlaying__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__keepPlaying__dbg__dbgDeferMsg( const UMLRTMessage * msg );
    void transitionaction_____Debug__keepPlaying__dbg__dbgSetExecMode( const UMLRTMessage * msg );
    void transitionaction_____Debug__keepPlaying__dbg__remBreakPoint( const UMLRTMessage * msg );
    void transitionaction_____Debug__keepPlaying__dbg__setBreakPoint( const UMLRTMessage * msg );
    void transitionaction_____Debug__keepPlaying__dbg__varChange( const UMLRTMessage * msg );
    void transitionaction_____Debug__keepPlaying__dbg__viewBreakPoints( const UMLRTMessage * msg );
    void transitionaction_____Debug__onPing( const UMLRTMessage * msg );
    void transitionaction_____Debug__onPing__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__onPing__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__onPing__dbg__dbgDeferMsg( const UMLRTMessage * msg );
    void transitionaction_____Debug__onPing__dbg__dbgSetExecMode( const UMLRTMessage * msg );
    void transitionaction_____Debug__onPing__dbg__remBreakPoint( const UMLRTMessage * msg );
    void transitionaction_____Debug__onPing__dbg__setBreakPoint( const UMLRTMessage * msg );
    void transitionaction_____Debug__onPing__dbg__varChange( const UMLRTMessage * msg );
    void transitionaction_____Debug__onPing__dbg__viewBreakPoints( const UMLRTMessage * msg );
    void transitionaction_____Debug__timeout( const UMLRTMessage * msg );
    void transitionaction_____Debug__timeout__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__timeout__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__timeout__dbg__dbgDeferMsg( const UMLRTMessage * msg );
    void transitionaction_____Debug__timeout__dbg__dbgSetExecMode( const UMLRTMessage * msg );
    void transitionaction_____Debug__timeout__dbg__remBreakPoint( const UMLRTMessage * msg );
    void transitionaction_____Debug__timeout__dbg__setBreakPoint( const UMLRTMessage * msg );
    void transitionaction_____Debug__timeout__dbg__varChange( const UMLRTMessage * msg );
    void transitionaction_____Debug__timeout__dbg__viewBreakPoints( const UMLRTMessage * msg );
    void transitionaction_____Initial( const UMLRTMessage * msg );
    void transitionaction_____endOfRound( const UMLRTMessage * msg );
    void transitionaction_____keepPlaying( const UMLRTMessage * msg );
    void transitionaction_____onPing( const UMLRTMessage * msg );
    void transitionaction_____timeout( const UMLRTMessage * msg );
    bool guard_____Debug__Initial__S( const UMLRTMessage * msg );
    bool guard_____Debug__endOfRound__S( const UMLRTMessage * msg );
    bool guard_____Debug__keepPlaying( const UMLRTMessage * msg );
    bool guard_____Debug__keepPlaying__S( const UMLRTMessage * msg );
    bool guard_____Debug__onPing__S( const UMLRTMessage * msg );
    bool guard_____Debug__timeout__S( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__Debug__Ac__Initial( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__Debug__En__PLAYING( const UMLRTMessage * msg );
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
    void actionchain_____Debug__C__endOfRound__Debug__Ac__endOfRound( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__Debug__En__PLAYING( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__Debug__end__trans__endOfRound( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__Debug__init__trans__endOfRound( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_124( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_125( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_126( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_127_to_unvisited_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_128_to_visited_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_129( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_130( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_131( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_132( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_133( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_134( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_135( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_136( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_137( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_138( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_139( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_140( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_141( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_142( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_143( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_144( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_145( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_146( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_147( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_148( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_149( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_150( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_151( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_152( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__Debug__Ac__keepPlaying( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__Debug__En__PLAYING( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__Debug__end__trans__keepPlaying( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__Debug__init__trans__keepPlaying( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_59( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_60( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_61( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_62_to_unvisited_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_63_to_visited_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_64( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_65( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_66( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_67( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_68( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_69( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_70( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_71( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_72( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_73( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_74( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_75( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_76( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_77( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_78( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_79( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_80( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_81( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_82( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_83( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_84( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_85( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_86( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_87( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__Debug__AC__onPing( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__Debug__En__WAITING_FOR_TIMER( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__Debug__Ex__PLAYING( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__Debug__end__trans__onPing( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__Debug__init__trans__onPing( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_100( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_101( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_102( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_103( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_104( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_105( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_106( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_107( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_108( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_109( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_110( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_111( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_112( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_113( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_114( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_115( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_116( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_117( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_118( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_119( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_120( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_121( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_122( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_123( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_88( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_89( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_90( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_91( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_92_to_unvisited_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_93_to_visited_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_94( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_95( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_96( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_97( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_98( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPing__new_transition_99( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__Debug__AC__timeout( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__Debug__Ex__WAITING_FOR_TIMER( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__Debug__end__trans__timeout( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__Debug__init__trans__timeout( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_30( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_31( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_32( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_33_to_unvisited_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_34_to_visited_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_35( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_36( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_37( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_38( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_39( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_40( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_41( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_42( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_43( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_44( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_45( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_46( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_47( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_48( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_49( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_50( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_51( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_52( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_53( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_54( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_55( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_56( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_57( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_58( const UMLRTMessage * msg );
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
    void actionchain_____Debug__endOfRound( const UMLRTMessage * msg );
    void actionchain_____Debug__endOfRound__E( const UMLRTMessage * msg );
    void actionchain_____Debug__endOfRound__S( const UMLRTMessage * msg );
    void actionchain_____Debug__endOfRound__dbg__dbgDeferMsg( const UMLRTMessage * msg );
    void actionchain_____Debug__endOfRound__dbg__dbgSetExecMode( const UMLRTMessage * msg );
    void actionchain_____Debug__endOfRound__dbg__remBreakPoint( const UMLRTMessage * msg );
    void actionchain_____Debug__endOfRound__dbg__setBreakPoint( const UMLRTMessage * msg );
    void actionchain_____Debug__endOfRound__dbg__varChange( const UMLRTMessage * msg );
    void actionchain_____Debug__endOfRound__dbg__viewBreakPoints( const UMLRTMessage * msg );
    void actionchain_____Debug__keepPlaying( const UMLRTMessage * msg );
    void actionchain_____Debug__keepPlaying__E( const UMLRTMessage * msg );
    void actionchain_____Debug__keepPlaying__S( const UMLRTMessage * msg );
    void actionchain_____Debug__keepPlaying__dbg__dbgDeferMsg( const UMLRTMessage * msg );
    void actionchain_____Debug__keepPlaying__dbg__dbgSetExecMode( const UMLRTMessage * msg );
    void actionchain_____Debug__keepPlaying__dbg__remBreakPoint( const UMLRTMessage * msg );
    void actionchain_____Debug__keepPlaying__dbg__setBreakPoint( const UMLRTMessage * msg );
    void actionchain_____Debug__keepPlaying__dbg__varChange( const UMLRTMessage * msg );
    void actionchain_____Debug__keepPlaying__dbg__viewBreakPoints( const UMLRTMessage * msg );
    void actionchain_____Debug__onPing( const UMLRTMessage * msg );
    void actionchain_____Debug__onPing__E( const UMLRTMessage * msg );
    void actionchain_____Debug__onPing__S( const UMLRTMessage * msg );
    void actionchain_____Debug__onPing__dbg__dbgDeferMsg( const UMLRTMessage * msg );
    void actionchain_____Debug__onPing__dbg__dbgSetExecMode( const UMLRTMessage * msg );
    void actionchain_____Debug__onPing__dbg__remBreakPoint( const UMLRTMessage * msg );
    void actionchain_____Debug__onPing__dbg__setBreakPoint( const UMLRTMessage * msg );
    void actionchain_____Debug__onPing__dbg__varChange( const UMLRTMessage * msg );
    void actionchain_____Debug__onPing__dbg__viewBreakPoints( const UMLRTMessage * msg );
    void actionchain_____Debug__timeout( const UMLRTMessage * msg );
    void actionchain_____Debug__timeout__E( const UMLRTMessage * msg );
    void actionchain_____Debug__timeout__S( const UMLRTMessage * msg );
    void actionchain_____Debug__timeout__dbg__dbgDeferMsg( const UMLRTMessage * msg );
    void actionchain_____Debug__timeout__dbg__dbgSetExecMode( const UMLRTMessage * msg );
    void actionchain_____Debug__timeout__dbg__remBreakPoint( const UMLRTMessage * msg );
    void actionchain_____Debug__timeout__dbg__setBreakPoint( const UMLRTMessage * msg );
    void actionchain_____Debug__timeout__dbg__varChange( const UMLRTMessage * msg );
    void actionchain_____Debug__timeout__dbg__viewBreakPoints( const UMLRTMessage * msg );
    void actionchain_____Initial( const UMLRTMessage * msg );
    void actionchain_____endOfRound( const UMLRTMessage * msg );
    void actionchain_____keepPlaying( const UMLRTMessage * msg );
    void actionchain_____onPing( const UMLRTMessage * msg );
    void actionchain_____timeout( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__en( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__new_exitpoint_1( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__new_exitpoint_2( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__new_exitpoint_3( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__new_exitpoint_4( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__new_exitpoint_5( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__new_exitpoint_6( const UMLRTMessage * msg );
    State junction_____Debug__C__endOfRound__en( const UMLRTMessage * msg );
    State junction_____Debug__C__endOfRound__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__endOfRound__new_exitpoint_25( const UMLRTMessage * msg );
    State junction_____Debug__C__endOfRound__new_exitpoint_26( const UMLRTMessage * msg );
    State junction_____Debug__C__endOfRound__new_exitpoint_27( const UMLRTMessage * msg );
    State junction_____Debug__C__endOfRound__new_exitpoint_28( const UMLRTMessage * msg );
    State junction_____Debug__C__endOfRound__new_exitpoint_29( const UMLRTMessage * msg );
    State junction_____Debug__C__endOfRound__new_exitpoint_30( const UMLRTMessage * msg );
    State junction_____Debug__C__keepPlaying__en( const UMLRTMessage * msg );
    State junction_____Debug__C__keepPlaying__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__keepPlaying__new_exitpoint_13( const UMLRTMessage * msg );
    State junction_____Debug__C__keepPlaying__new_exitpoint_14( const UMLRTMessage * msg );
    State junction_____Debug__C__keepPlaying__new_exitpoint_15( const UMLRTMessage * msg );
    State junction_____Debug__C__keepPlaying__new_exitpoint_16( const UMLRTMessage * msg );
    State junction_____Debug__C__keepPlaying__new_exitpoint_17( const UMLRTMessage * msg );
    State junction_____Debug__C__keepPlaying__new_exitpoint_18( const UMLRTMessage * msg );
    State junction_____Debug__C__onPing__en( const UMLRTMessage * msg );
    State junction_____Debug__C__onPing__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__onPing__new_exitpoint_19( const UMLRTMessage * msg );
    State junction_____Debug__C__onPing__new_exitpoint_20( const UMLRTMessage * msg );
    State junction_____Debug__C__onPing__new_exitpoint_21( const UMLRTMessage * msg );
    State junction_____Debug__C__onPing__new_exitpoint_22( const UMLRTMessage * msg );
    State junction_____Debug__C__onPing__new_exitpoint_23( const UMLRTMessage * msg );
    State junction_____Debug__C__onPing__new_exitpoint_24( const UMLRTMessage * msg );
    State junction_____Debug__C__timeout__en( const UMLRTMessage * msg );
    State junction_____Debug__C__timeout__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__timeout__new_exitpoint_10( const UMLRTMessage * msg );
    State junction_____Debug__C__timeout__new_exitpoint_11( const UMLRTMessage * msg );
    State junction_____Debug__C__timeout__new_exitpoint_12( const UMLRTMessage * msg );
    State junction_____Debug__C__timeout__new_exitpoint_7( const UMLRTMessage * msg );
    State junction_____Debug__C__timeout__new_exitpoint_8( const UMLRTMessage * msg );
    State junction_____Debug__C__timeout__new_exitpoint_9( const UMLRTMessage * msg );
    State choice_____Debug__C__Initial__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__endOfRound__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__keepPlaying__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__onPing__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__timeout__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__Path__Initial( const UMLRTMessage * msg );
    State choice_____Debug__Path__endOfRound( const UMLRTMessage * msg );
    State choice_____Debug__Path__keepPlaying( const UMLRTMessage * msg );
    State choice_____Debug__Path__onPing( const UMLRTMessage * msg );
    State choice_____Debug__Path__timeout( const UMLRTMessage * msg );
    State choice_____ThreePongsSent_( const UMLRTMessage * msg );
    State state_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg );
    State state_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg );
    State state_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg );
    State state_____Debug__C__Initial__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( const UMLRTMessage * msg );
    State state_____Debug__C__endOfRound__Debug__A__En__endOfRound( const UMLRTMessage * msg );
    State state_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( const UMLRTMessage * msg );
    State state_____Debug__C__endOfRound__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( const UMLRTMessage * msg );
    State state_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( const UMLRTMessage * msg );
    State state_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( const UMLRTMessage * msg );
    State state_____Debug__C__keepPlaying__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__onPing__Debug__A__Ac__onPing( const UMLRTMessage * msg );
    State state_____Debug__C__onPing__Debug__A__En__WAITING_FOR_TIMER( const UMLRTMessage * msg );
    State state_____Debug__C__onPing__Debug__B__Ac__onPing( const UMLRTMessage * msg );
    State state_____Debug__C__onPing__Debug__B__Ex__PLAYING( const UMLRTMessage * msg );
    State state_____Debug__C__onPing__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__timeout__Debug__A__Ac__timeout( const UMLRTMessage * msg );
    State state_____Debug__C__timeout__Debug__B__Ac__timeout( const UMLRTMessage * msg );
    State state_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( const UMLRTMessage * msg );
    State state_____Debug__C__timeout__boundary( const UMLRTMessage * msg );
    State state_____Debug__InitState( const UMLRTMessage * msg );
    State state_____PLAYING( const UMLRTMessage * msg );
    State state_____WAITING_FOR_TIMER( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass Ponger;

#endif


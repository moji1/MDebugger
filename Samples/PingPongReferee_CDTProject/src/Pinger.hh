
#ifndef PINGER_HH
#define PINGER_HH

#include "ExtInterface.hh"
#include "PingPongProtocol.hh"
#include "StartProtocol.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtlogprotocol.hh"
#include "umlrtmessage.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

#include "Event.h"

#include "SROManager.h"

class Capsule_Pinger : public UMLRTCapsule
{
public:
    Capsule_Pinger( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    ExtInterface::Conj extComm;
public:
    enum InternalPortId
    {
        internalport_extComm,
        internalport_pingerTimer,
        internalport_log
    };
protected:
    UMLRTLogProtocol_baserole log;
    PingPongProtocol::Conj pingPort;
public:
    enum BorderPortId
    {
        borderport_pingPort,
        borderport_startPort
    };
protected:
    UMLRTTimerProtocol_baserole pingerTimer;
    StartProtocol::Conj startPort;
public:
    enum PartId
    {
    };
    enum PortId
    {
        port_extComm,
        port_log,
        port_pingPort,
        port_pingerTimer,
        port_startPort
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    int pingsSent;
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
        Debug__C__onPong,
        Debug__C__startSignal,
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
        Debug__C__onPong__Debug__A__Ac__onPong,
        Debug__C__onPong__Debug__B__Ac__onPong,
        Debug__C__onPong__Debug__B__Ex__PLAYING,
        Debug__C__onPong__boundary,
        Debug__C__startSignal__Debug__A__Ac__startSignal,
        Debug__C__startSignal__Debug__A__En__PLAYING,
        Debug__C__startSignal__Debug__B__Ac__startSignal,
        Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START,
        Debug__C__startSignal__boundary,
        Debug__C__timeout__Debug__A__Ac__timeout,
        Debug__C__timeout__Debug__A__En__PLAYING,
        Debug__C__timeout__Debug__B__Ac__timeout,
        Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER,
        Debug__C__timeout__boundary,
        Debug__InitState,
        PLAYING,
        WAITING_FOR_TIMER,
        WAITING_TO_START,
        SPECIAL_INTERNAL_STATE_TOP,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[38];
    State currentState;
    State history[6];
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
    void entryaction_____Debug__C__onPong__Debug__A__Ac__onPong( const UMLRTMessage * msg );
    void entryaction_____Debug__C__onPong__Debug__B__Ac__onPong( const UMLRTMessage * msg );
    void entryaction_____Debug__C__onPong__Debug__B__Ex__PLAYING( const UMLRTMessage * msg );
    void entryaction_____Debug__C__startSignal__Debug__A__Ac__startSignal( const UMLRTMessage * msg );
    void entryaction_____Debug__C__startSignal__Debug__A__En__PLAYING( const UMLRTMessage * msg );
    void entryaction_____Debug__C__startSignal__Debug__B__Ac__startSignal( const UMLRTMessage * msg );
    void entryaction_____Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START( const UMLRTMessage * msg );
    void entryaction_____Debug__C__timeout__Debug__A__Ac__timeout( const UMLRTMessage * msg );
    void entryaction_____Debug__C__timeout__Debug__A__En__PLAYING( const UMLRTMessage * msg );
    void entryaction_____Debug__C__timeout__Debug__B__Ac__timeout( const UMLRTMessage * msg );
    void entryaction_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( const UMLRTMessage * msg );
    void entryaction_____PLAYING( const UMLRTMessage * msg );
    void entryaction_____WAITING_FOR_TIMER( const UMLRTMessage * msg );
    void entryaction_____WAITING_TO_START( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg );
    void exitaction_____Debug__C__endOfRound__Debug__A__Ac__endOfRound( const UMLRTMessage * msg );
    void exitaction_____Debug__C__endOfRound__Debug__A__En__endOfRound( const UMLRTMessage * msg );
    void exitaction_____Debug__C__endOfRound__Debug__B__Ac__endOfRound( const UMLRTMessage * msg );
    void exitaction_____Debug__C__keepPlaying__Debug__A__Ac__keepPlaying( const UMLRTMessage * msg );
    void exitaction_____Debug__C__keepPlaying__Debug__A__En__keepPlaying( const UMLRTMessage * msg );
    void exitaction_____Debug__C__keepPlaying__Debug__B__Ac__keepPlaying( const UMLRTMessage * msg );
    void exitaction_____Debug__C__onPong__Debug__A__Ac__onPong( const UMLRTMessage * msg );
    void exitaction_____Debug__C__onPong__Debug__B__Ac__onPong( const UMLRTMessage * msg );
    void exitaction_____Debug__C__onPong__Debug__B__Ex__PLAYING( const UMLRTMessage * msg );
    void exitaction_____Debug__C__startSignal__Debug__A__Ac__startSignal( const UMLRTMessage * msg );
    void exitaction_____Debug__C__startSignal__Debug__A__En__PLAYING( const UMLRTMessage * msg );
    void exitaction_____Debug__C__startSignal__Debug__B__Ac__startSignal( const UMLRTMessage * msg );
    void exitaction_____Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START( const UMLRTMessage * msg );
    void exitaction_____Debug__C__timeout__Debug__A__Ac__timeout( const UMLRTMessage * msg );
    void exitaction_____Debug__C__timeout__Debug__A__En__PLAYING( const UMLRTMessage * msg );
    void exitaction_____Debug__C__timeout__Debug__B__Ac__timeout( const UMLRTMessage * msg );
    void exitaction_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( const UMLRTMessage * msg );
    void exitaction_____PLAYING( const UMLRTMessage * msg );
    void exitaction_____WAITING_FOR_TIMER( const UMLRTMessage * msg );
    void exitaction_____WAITING_TO_START( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial__Debug__Ac__Initial( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial__Debug__En__WAITING_TO_START( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial__Debug__end__trans__Initial( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial__Debug__init__trans__Initial( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__endOfRound__Debug__Ac__endOfRound( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__endOfRound__Debug__En__WAITING_TO_START( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__endOfRound__Debug__end__trans__endOfRound( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__endOfRound__Debug__init__trans__endOfRound( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__keepPlaying__Debug__Ac__keepPlaying( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__keepPlaying__Debug__En__WAITING_FOR_TIMER( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__keepPlaying__Debug__end__trans__keepPlaying( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__keepPlaying__Debug__init__trans__keepPlaying( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__onPong__Debug__AC__onPong( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__onPong__Debug__Ex__PLAYING( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__onPong__Debug__end__trans__onPong( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__startSignal__Debug__AC__startSignal( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__startSignal__Debug__En__PLAYING( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__startSignal__Debug__Ex__WAITING_TO_START( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__startSignal__Debug__end__trans__startSignal( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__startSignal__Debug__init__trans__startSignal( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__timeout__Debug__AC__timeout( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__timeout__Debug__En__PLAYING( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__timeout__Debug__Ex__WAITING_FOR_TIMER( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__timeout__Debug__end__trans__timeout( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__timeout__Debug__init__trans__timeout( const UMLRTMessage * msg );
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
    void transitionaction_____Debug__onPong( const UMLRTMessage * msg );
    void transitionaction_____Debug__onPong__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__onPong__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__onPong__dbg__dbgDeferMsg( const UMLRTMessage * msg );
    void transitionaction_____Debug__onPong__dbg__dbgSetExecMode( const UMLRTMessage * msg );
    void transitionaction_____Debug__onPong__dbg__remBreakPoint( const UMLRTMessage * msg );
    void transitionaction_____Debug__onPong__dbg__setBreakPoint( const UMLRTMessage * msg );
    void transitionaction_____Debug__onPong__dbg__varChange( const UMLRTMessage * msg );
    void transitionaction_____Debug__onPong__dbg__viewBreakPoints( const UMLRTMessage * msg );
    void transitionaction_____Debug__startSignal( const UMLRTMessage * msg );
    void transitionaction_____Debug__startSignal__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__startSignal__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__startSignal__dbg__dbgDeferMsg( const UMLRTMessage * msg );
    void transitionaction_____Debug__startSignal__dbg__dbgSetExecMode( const UMLRTMessage * msg );
    void transitionaction_____Debug__startSignal__dbg__remBreakPoint( const UMLRTMessage * msg );
    void transitionaction_____Debug__startSignal__dbg__setBreakPoint( const UMLRTMessage * msg );
    void transitionaction_____Debug__startSignal__dbg__varChange( const UMLRTMessage * msg );
    void transitionaction_____Debug__startSignal__dbg__viewBreakPoints( const UMLRTMessage * msg );
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
    void transitionaction_____onPong( const UMLRTMessage * msg );
    void transitionaction_____startSignal( const UMLRTMessage * msg );
    void transitionaction_____timeout( const UMLRTMessage * msg );
    bool guard_____Debug__Initial__S( const UMLRTMessage * msg );
    bool guard_____Debug__endOfRound( const UMLRTMessage * msg );
    bool guard_____Debug__endOfRound__S( const UMLRTMessage * msg );
    bool guard_____Debug__keepPlaying__S( const UMLRTMessage * msg );
    bool guard_____Debug__onPong__S( const UMLRTMessage * msg );
    bool guard_____Debug__startSignal__S( const UMLRTMessage * msg );
    bool guard_____Debug__timeout__S( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__Debug__Ac__Initial( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__Debug__En__WAITING_TO_START( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__Debug__end__trans__Initial( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__Debug__init__trans__Initial( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_100( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_101( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_102( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_103( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_104( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_105( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_106( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_107( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_108( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_109( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_110( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_111( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_112( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_113( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_114( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_115( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_116( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_117( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_118( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_119( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_120( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_121( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_122( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_123( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_95( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_96( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_97( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_98_to_unvisited_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_99_to_visited_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__Debug__Ac__endOfRound( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__Debug__En__WAITING_TO_START( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__Debug__end__trans__endOfRound( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__Debug__init__trans__endOfRound( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_1( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_10( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_11( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_12( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_13( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_14( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_15( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_16( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_17( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_18( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_19( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_2( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_20( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_21( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_22( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_23( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_24( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_25( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_26( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_27( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_28( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_29( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_3( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_4_to_unvisited_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_5_to_visited_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_6( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_7( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_8( const UMLRTMessage * msg );
    void actionchain_____Debug__C__endOfRound__new_transition_9( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__Debug__Ac__keepPlaying( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__Debug__En__WAITING_FOR_TIMER( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__Debug__end__trans__keepPlaying( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__Debug__init__trans__keepPlaying( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_124( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_125( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_126( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_127_to_unvisited_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_128_to_visited_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_129( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_130( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_131( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_132( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_133( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_134( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_135( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_136( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_137( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_138( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_139( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_140( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_141( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_142( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_143( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_144( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_145( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_146( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_147( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_148( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_149( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_150( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_151( const UMLRTMessage * msg );
    void actionchain_____Debug__C__keepPlaying__new_transition_152( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__Debug__AC__onPong( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__Debug__Ex__PLAYING( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__Debug__end__trans__onPong( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__Debug__init__trans__onPong( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_66( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_67( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_68( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_69_to_unvisited_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_70_to_visited_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_71( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_72( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_73( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_74( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_75( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_76( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_77( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_78( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_79( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_80( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_81( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_82( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_83( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_84( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_85( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_86( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_87( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_88( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_89( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_90( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_91( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_92( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_93( const UMLRTMessage * msg );
    void actionchain_____Debug__C__onPong__new_transition_94( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__Debug__AC__startSignal( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__Debug__En__PLAYING( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__Debug__Ex__WAITING_TO_START( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__Debug__end__trans__startSignal( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__Debug__init__trans__startSignal( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_153( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_154( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_155( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_156( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_157_to_unvisited_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_158_to_visited_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_159( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_160( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_161( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_162( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_163( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_164( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_165( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_166( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_167( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_168( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_169( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_170( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_171( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_172( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_173( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_174( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_175( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_176( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_177( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_178( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_179( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_180( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_181( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_182( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_183( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_184( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_185( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_186( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_187( const UMLRTMessage * msg );
    void actionchain_____Debug__C__startSignal__new_transition_188( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__Debug__AC__timeout( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__Debug__En__PLAYING( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__Debug__Ex__WAITING_FOR_TIMER( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__Debug__end__trans__timeout( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__Debug__init__trans__timeout( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_30( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_31( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_32( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_33( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_34_to_unvisited_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_35_to_visited_boundary( const UMLRTMessage * msg );
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
    void actionchain_____Debug__C__timeout__new_transition_59( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_60( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_61( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_62( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_63( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_64( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_65( const UMLRTMessage * msg );
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
    void actionchain_____Debug__onPong( const UMLRTMessage * msg );
    void actionchain_____Debug__onPong__E( const UMLRTMessage * msg );
    void actionchain_____Debug__onPong__S( const UMLRTMessage * msg );
    void actionchain_____Debug__onPong__dbg__dbgDeferMsg( const UMLRTMessage * msg );
    void actionchain_____Debug__onPong__dbg__dbgSetExecMode( const UMLRTMessage * msg );
    void actionchain_____Debug__onPong__dbg__remBreakPoint( const UMLRTMessage * msg );
    void actionchain_____Debug__onPong__dbg__setBreakPoint( const UMLRTMessage * msg );
    void actionchain_____Debug__onPong__dbg__varChange( const UMLRTMessage * msg );
    void actionchain_____Debug__onPong__dbg__viewBreakPoints( const UMLRTMessage * msg );
    void actionchain_____Debug__startSignal( const UMLRTMessage * msg );
    void actionchain_____Debug__startSignal__E( const UMLRTMessage * msg );
    void actionchain_____Debug__startSignal__S( const UMLRTMessage * msg );
    void actionchain_____Debug__startSignal__dbg__dbgDeferMsg( const UMLRTMessage * msg );
    void actionchain_____Debug__startSignal__dbg__dbgSetExecMode( const UMLRTMessage * msg );
    void actionchain_____Debug__startSignal__dbg__remBreakPoint( const UMLRTMessage * msg );
    void actionchain_____Debug__startSignal__dbg__setBreakPoint( const UMLRTMessage * msg );
    void actionchain_____Debug__startSignal__dbg__varChange( const UMLRTMessage * msg );
    void actionchain_____Debug__startSignal__dbg__viewBreakPoints( const UMLRTMessage * msg );
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
    void actionchain_____onPong( const UMLRTMessage * msg );
    void actionchain_____startSignal( const UMLRTMessage * msg );
    void actionchain_____timeout( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__en( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__new_exitpoint_19( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__new_exitpoint_20( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__new_exitpoint_21( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__new_exitpoint_22( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__new_exitpoint_23( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__new_exitpoint_24( const UMLRTMessage * msg );
    State junction_____Debug__C__endOfRound__en( const UMLRTMessage * msg );
    State junction_____Debug__C__endOfRound__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__endOfRound__new_exitpoint_1( const UMLRTMessage * msg );
    State junction_____Debug__C__endOfRound__new_exitpoint_2( const UMLRTMessage * msg );
    State junction_____Debug__C__endOfRound__new_exitpoint_3( const UMLRTMessage * msg );
    State junction_____Debug__C__endOfRound__new_exitpoint_4( const UMLRTMessage * msg );
    State junction_____Debug__C__endOfRound__new_exitpoint_5( const UMLRTMessage * msg );
    State junction_____Debug__C__endOfRound__new_exitpoint_6( const UMLRTMessage * msg );
    State junction_____Debug__C__keepPlaying__en( const UMLRTMessage * msg );
    State junction_____Debug__C__keepPlaying__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__keepPlaying__new_exitpoint_25( const UMLRTMessage * msg );
    State junction_____Debug__C__keepPlaying__new_exitpoint_26( const UMLRTMessage * msg );
    State junction_____Debug__C__keepPlaying__new_exitpoint_27( const UMLRTMessage * msg );
    State junction_____Debug__C__keepPlaying__new_exitpoint_28( const UMLRTMessage * msg );
    State junction_____Debug__C__keepPlaying__new_exitpoint_29( const UMLRTMessage * msg );
    State junction_____Debug__C__keepPlaying__new_exitpoint_30( const UMLRTMessage * msg );
    State junction_____Debug__C__onPong__en( const UMLRTMessage * msg );
    State junction_____Debug__C__onPong__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__onPong__new_exitpoint_13( const UMLRTMessage * msg );
    State junction_____Debug__C__onPong__new_exitpoint_14( const UMLRTMessage * msg );
    State junction_____Debug__C__onPong__new_exitpoint_15( const UMLRTMessage * msg );
    State junction_____Debug__C__onPong__new_exitpoint_16( const UMLRTMessage * msg );
    State junction_____Debug__C__onPong__new_exitpoint_17( const UMLRTMessage * msg );
    State junction_____Debug__C__onPong__new_exitpoint_18( const UMLRTMessage * msg );
    State junction_____Debug__C__startSignal__en( const UMLRTMessage * msg );
    State junction_____Debug__C__startSignal__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__startSignal__new_exitpoint_31( const UMLRTMessage * msg );
    State junction_____Debug__C__startSignal__new_exitpoint_32( const UMLRTMessage * msg );
    State junction_____Debug__C__startSignal__new_exitpoint_33( const UMLRTMessage * msg );
    State junction_____Debug__C__startSignal__new_exitpoint_34( const UMLRTMessage * msg );
    State junction_____Debug__C__startSignal__new_exitpoint_35( const UMLRTMessage * msg );
    State junction_____Debug__C__startSignal__new_exitpoint_36( const UMLRTMessage * msg );
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
    State choice_____Debug__C__onPong__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__startSignal__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__timeout__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__Path__Initial( const UMLRTMessage * msg );
    State choice_____Debug__Path__endOfRound( const UMLRTMessage * msg );
    State choice_____Debug__Path__keepPlaying( const UMLRTMessage * msg );
    State choice_____Debug__Path__onPong( const UMLRTMessage * msg );
    State choice_____Debug__Path__startSignal( const UMLRTMessage * msg );
    State choice_____Debug__Path__timeout( const UMLRTMessage * msg );
    State choice_____ThreePingsSent_( const UMLRTMessage * msg );
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
    State state_____Debug__C__onPong__Debug__A__Ac__onPong( const UMLRTMessage * msg );
    State state_____Debug__C__onPong__Debug__B__Ac__onPong( const UMLRTMessage * msg );
    State state_____Debug__C__onPong__Debug__B__Ex__PLAYING( const UMLRTMessage * msg );
    State state_____Debug__C__onPong__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__startSignal__Debug__A__Ac__startSignal( const UMLRTMessage * msg );
    State state_____Debug__C__startSignal__Debug__A__En__PLAYING( const UMLRTMessage * msg );
    State state_____Debug__C__startSignal__Debug__B__Ac__startSignal( const UMLRTMessage * msg );
    State state_____Debug__C__startSignal__Debug__B__Ex__WAITING_TO_START( const UMLRTMessage * msg );
    State state_____Debug__C__startSignal__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__timeout__Debug__A__Ac__timeout( const UMLRTMessage * msg );
    State state_____Debug__C__timeout__Debug__A__En__PLAYING( const UMLRTMessage * msg );
    State state_____Debug__C__timeout__Debug__B__Ac__timeout( const UMLRTMessage * msg );
    State state_____Debug__C__timeout__Debug__B__Ex__WAITING_FOR_TIMER( const UMLRTMessage * msg );
    State state_____Debug__C__timeout__boundary( const UMLRTMessage * msg );
    State state_____Debug__InitState( const UMLRTMessage * msg );
    State state_____PLAYING( const UMLRTMessage * msg );
    State state_____WAITING_FOR_TIMER( const UMLRTMessage * msg );
    State state_____WAITING_TO_START( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass Pinger;

#endif


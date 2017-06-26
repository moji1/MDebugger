
#ifndef ENGINECONTROLLER_HH
#define ENGINECONTROLLER_HH

#include "Engine.hh"
#include "ExtInterface.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtlogprotocol.hh"
#include "umlrtmessage.hh"
#include "umlrttimerid.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

#include "GPIOClass.hh"
#include "Event.h"

#include "SROManager.h"

class Capsule_EngineController : public UMLRTCapsule
{
public:
    Capsule_EngineController( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
    enum BorderPortId
    {
        borderport_engine,
        borderport_extComm,
        borderport_timer,
        borderport_log
    };
protected:
    Engine::Conj engine;
    ExtInterface::Conj extComm;
    UMLRTLogProtocol_baserole log;
    UMLRTTimerProtocol_baserole timer;
public:
    enum PartId
    {
    };
    enum PortId
    {
        port_engine,
        port_extComm,
        port_log,
        port_timer
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    UMLRTTimerId timerId;
    GPIOClass leftMotorForward;
    GPIOClass rightMotorForward;
    GPIOClass rightMotorBackwards;
    GPIOClass leftMotorBackwards;
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
        Debug__C__init,
        Debug__C__move_backwards,
        Debug__C__move_forward,
        Debug__C__stop_moving_backwards,
        Debug__C__stop_moving_forward,
        Debug__C__stop_turning_left,
        Debug__C__stop_turning_right,
        Debug__C__turn_left,
        Debug__C__turn_right,
        Debug__C__init__Debug__A__Ac__init,
        Debug__C__init__Debug__A__En__init,
        Debug__C__init__Debug__B__Ac__init,
        Debug__C__init__boundary,
        Debug__C__move_backwards__Debug__A__Ac__move_backwards,
        Debug__C__move_backwards__Debug__A__En__MOVING_BACKWARDS,
        Debug__C__move_backwards__Debug__B__Ac__move_backwards,
        Debug__C__move_backwards__Debug__B__Ex__IDLE,
        Debug__C__move_backwards__boundary,
        Debug__C__move_forward__Debug__A__Ac__move_forward,
        Debug__C__move_forward__Debug__A__En__MOVING_FORWARD,
        Debug__C__move_forward__Debug__B__Ac__move_forward,
        Debug__C__move_forward__Debug__B__Ex__IDLE,
        Debug__C__move_forward__boundary,
        Debug__C__stop_moving_backwards__Debug__A__Ac__stop_moving_backwards,
        Debug__C__stop_moving_backwards__Debug__A__En__IDLE,
        Debug__C__stop_moving_backwards__Debug__B__Ac__stop_moving_backwards,
        Debug__C__stop_moving_backwards__Debug__B__Ex__MOVING_BACKWARDS,
        Debug__C__stop_moving_backwards__boundary,
        Debug__C__stop_moving_forward__Debug__A__Ac__stop_moving_forward,
        Debug__C__stop_moving_forward__Debug__A__En__IDLE,
        Debug__C__stop_moving_forward__Debug__B__Ac__stop_moving_forward,
        Debug__C__stop_moving_forward__Debug__B__Ex__MOVING_FORWARD,
        Debug__C__stop_moving_forward__boundary,
        Debug__C__stop_turning_left__Debug__A__Ac__stop_turning_left,
        Debug__C__stop_turning_left__Debug__A__En__IDLE,
        Debug__C__stop_turning_left__Debug__B__Ac__stop_turning_left,
        Debug__C__stop_turning_left__Debug__B__Ex__TURNING_LEFT,
        Debug__C__stop_turning_left__boundary,
        Debug__C__stop_turning_right__Debug__A__Ac__stop_turning_right,
        Debug__C__stop_turning_right__Debug__A__En__IDLE,
        Debug__C__stop_turning_right__Debug__B__Ac__stop_turning_right,
        Debug__C__stop_turning_right__Debug__B__Ex__TURNING_RIGHT,
        Debug__C__stop_turning_right__boundary,
        Debug__C__turn_left__Debug__A__Ac__turn_left,
        Debug__C__turn_left__Debug__A__En__TURNING_LEFT,
        Debug__C__turn_left__Debug__B__Ac__turn_left,
        Debug__C__turn_left__Debug__B__Ex__IDLE,
        Debug__C__turn_left__boundary,
        Debug__C__turn_right__Debug__A__Ac__turn_right,
        Debug__C__turn_right__Debug__A__En__TURNING_RIGHT,
        Debug__C__turn_right__Debug__B__Ac__turn_right,
        Debug__C__turn_right__Debug__B__Ex__IDLE,
        Debug__C__turn_right__boundary,
        Debug__InitState,
        IDLE,
        MOVING_BACKWARDS,
        MOVING_FORWARD,
        TURNING_LEFT,
        TURNING_RIGHT,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[60];
    State currentState;
    State history[9];
    void save_history( State compositeState, State subState );
    bool check_history( State compositeState, State subState );
    void entryaction_____Debug__C__init__Debug__A__Ac__init( const UMLRTMessage * msg );
    void entryaction_____Debug__C__init__Debug__A__En__init( const UMLRTMessage * msg );
    void entryaction_____Debug__C__init__Debug__B__Ac__init( const UMLRTMessage * msg );
    void entryaction_____Debug__C__init__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__move_backwards__Debug__A__Ac__move_backwards( const UMLRTMessage * msg );
    void entryaction_____Debug__C__move_backwards__Debug__A__En__MOVING_BACKWARDS( const UMLRTMessage * msg );
    void entryaction_____Debug__C__move_backwards__Debug__B__Ac__move_backwards( const UMLRTMessage * msg );
    void entryaction_____Debug__C__move_backwards__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    void entryaction_____Debug__C__move_backwards__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__move_forward__Debug__A__Ac__move_forward( const UMLRTMessage * msg );
    void entryaction_____Debug__C__move_forward__Debug__A__En__MOVING_FORWARD( const UMLRTMessage * msg );
    void entryaction_____Debug__C__move_forward__Debug__B__Ac__move_forward( const UMLRTMessage * msg );
    void entryaction_____Debug__C__move_forward__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    void entryaction_____Debug__C__move_forward__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stop_moving_backwards__Debug__A__Ac__stop_moving_backwards( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stop_moving_backwards__Debug__A__En__IDLE( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stop_moving_backwards__Debug__B__Ac__stop_moving_backwards( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stop_moving_backwards__Debug__B__Ex__MOVING_BACKWARDS( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stop_moving_backwards__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stop_moving_forward__Debug__A__Ac__stop_moving_forward( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stop_moving_forward__Debug__A__En__IDLE( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stop_moving_forward__Debug__B__Ac__stop_moving_forward( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stop_moving_forward__Debug__B__Ex__MOVING_FORWARD( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stop_moving_forward__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stop_turning_left__Debug__A__Ac__stop_turning_left( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stop_turning_left__Debug__A__En__IDLE( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stop_turning_left__Debug__B__Ac__stop_turning_left( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stop_turning_left__Debug__B__Ex__TURNING_LEFT( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stop_turning_left__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stop_turning_right__Debug__A__Ac__stop_turning_right( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stop_turning_right__Debug__A__En__IDLE( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stop_turning_right__Debug__B__Ac__stop_turning_right( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stop_turning_right__Debug__B__Ex__TURNING_RIGHT( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stop_turning_right__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__turn_left__Debug__A__Ac__turn_left( const UMLRTMessage * msg );
    void entryaction_____Debug__C__turn_left__Debug__A__En__TURNING_LEFT( const UMLRTMessage * msg );
    void entryaction_____Debug__C__turn_left__Debug__B__Ac__turn_left( const UMLRTMessage * msg );
    void entryaction_____Debug__C__turn_left__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    void entryaction_____Debug__C__turn_left__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__turn_right__Debug__A__Ac__turn_right( const UMLRTMessage * msg );
    void entryaction_____Debug__C__turn_right__Debug__A__En__TURNING_RIGHT( const UMLRTMessage * msg );
    void entryaction_____Debug__C__turn_right__Debug__B__Ac__turn_right( const UMLRTMessage * msg );
    void entryaction_____Debug__C__turn_right__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    void entryaction_____Debug__C__turn_right__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__InitState( const UMLRTMessage * msg );
    void entryaction_____IDLE( const UMLRTMessage * msg );
    void entryaction_____MOVING_BACKWARDS( const UMLRTMessage * msg );
    void entryaction_____MOVING_FORWARD( const UMLRTMessage * msg );
    void entryaction_____TURNING_LEFT( const UMLRTMessage * msg );
    void entryaction_____TURNING_RIGHT( const UMLRTMessage * msg );
    void exitaction_____Debug__C__init__Debug__A__Ac__init( const UMLRTMessage * msg );
    void exitaction_____Debug__C__init__Debug__A__En__init( const UMLRTMessage * msg );
    void exitaction_____Debug__C__init__Debug__B__Ac__init( const UMLRTMessage * msg );
    void exitaction_____Debug__C__init__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__move_backwards__Debug__A__Ac__move_backwards( const UMLRTMessage * msg );
    void exitaction_____Debug__C__move_backwards__Debug__A__En__MOVING_BACKWARDS( const UMLRTMessage * msg );
    void exitaction_____Debug__C__move_backwards__Debug__B__Ac__move_backwards( const UMLRTMessage * msg );
    void exitaction_____Debug__C__move_backwards__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    void exitaction_____Debug__C__move_backwards__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__move_forward__Debug__A__Ac__move_forward( const UMLRTMessage * msg );
    void exitaction_____Debug__C__move_forward__Debug__A__En__MOVING_FORWARD( const UMLRTMessage * msg );
    void exitaction_____Debug__C__move_forward__Debug__B__Ac__move_forward( const UMLRTMessage * msg );
    void exitaction_____Debug__C__move_forward__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    void exitaction_____Debug__C__move_forward__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stop_moving_backwards__Debug__A__Ac__stop_moving_backwards( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stop_moving_backwards__Debug__A__En__IDLE( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stop_moving_backwards__Debug__B__Ac__stop_moving_backwards( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stop_moving_backwards__Debug__B__Ex__MOVING_BACKWARDS( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stop_moving_backwards__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stop_moving_forward__Debug__A__Ac__stop_moving_forward( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stop_moving_forward__Debug__A__En__IDLE( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stop_moving_forward__Debug__B__Ac__stop_moving_forward( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stop_moving_forward__Debug__B__Ex__MOVING_FORWARD( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stop_moving_forward__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stop_turning_left__Debug__A__Ac__stop_turning_left( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stop_turning_left__Debug__A__En__IDLE( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stop_turning_left__Debug__B__Ac__stop_turning_left( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stop_turning_left__Debug__B__Ex__TURNING_LEFT( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stop_turning_left__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stop_turning_right__Debug__A__Ac__stop_turning_right( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stop_turning_right__Debug__A__En__IDLE( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stop_turning_right__Debug__B__Ac__stop_turning_right( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stop_turning_right__Debug__B__Ex__TURNING_RIGHT( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stop_turning_right__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__turn_left__Debug__A__Ac__turn_left( const UMLRTMessage * msg );
    void exitaction_____Debug__C__turn_left__Debug__A__En__TURNING_LEFT( const UMLRTMessage * msg );
    void exitaction_____Debug__C__turn_left__Debug__B__Ac__turn_left( const UMLRTMessage * msg );
    void exitaction_____Debug__C__turn_left__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    void exitaction_____Debug__C__turn_left__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__turn_right__Debug__A__Ac__turn_right( const UMLRTMessage * msg );
    void exitaction_____Debug__C__turn_right__Debug__A__En__TURNING_RIGHT( const UMLRTMessage * msg );
    void exitaction_____Debug__C__turn_right__Debug__B__Ac__turn_right( const UMLRTMessage * msg );
    void exitaction_____Debug__C__turn_right__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    void exitaction_____Debug__C__turn_right__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__InitState( const UMLRTMessage * msg );
    void exitaction_____IDLE( const UMLRTMessage * msg );
    void exitaction_____MOVING_BACKWARDS( const UMLRTMessage * msg );
    void exitaction_____MOVING_FORWARD( const UMLRTMessage * msg );
    void exitaction_____TURNING_LEFT( const UMLRTMessage * msg );
    void exitaction_____TURNING_RIGHT( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__init__Debug__Ac__init( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__init__Debug__En__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__init__Debug__end__trans__init( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__init__Debug__init__trans__init( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__move_backwards__Debug__AC__move_backwards( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__move_backwards__Debug__En__MOVING_BACKWARDS( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__move_backwards__Debug__Ex__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__move_backwards__Debug__end__trans__move_backwards( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__move_backwards__Debug__init__trans__move_backwards( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__move_forward__Debug__AC__move_forward( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__move_forward__Debug__En__MOVING_FORWARD( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__move_forward__Debug__Ex__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__move_forward__Debug__end__trans__move_forward( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__move_forward__Debug__init__trans__move_forward( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stop_moving_backwards__Debug__AC__stop_moving_backwards( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stop_moving_backwards__Debug__En__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stop_moving_backwards__Debug__Ex__MOVING_BACKWARDS( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stop_moving_backwards__Debug__end__trans__stop_moving_backwards( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stop_moving_backwards__Debug__init__trans__stop_moving_backwards( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stop_moving_forward__Debug__AC__stop_moving_forward( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stop_moving_forward__Debug__En__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stop_moving_forward__Debug__Ex__MOVING_FORWARD( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stop_moving_forward__Debug__end__trans__stop_moving_forward( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stop_moving_forward__Debug__init__trans__stop_moving_forward( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stop_turning_left__Debug__AC__stop_turning_left( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stop_turning_left__Debug__En__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stop_turning_left__Debug__Ex__TURNING_LEFT( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stop_turning_left__Debug__end__trans__stop_turning_left( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stop_turning_left__Debug__init__trans__stop_turning_left( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stop_turning_right__Debug__AC__stop_turning_right( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stop_turning_right__Debug__En__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stop_turning_right__Debug__Ex__TURNING_RIGHT( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stop_turning_right__Debug__end__trans__stop_turning_right( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stop_turning_right__Debug__init__trans__stop_turning_right( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__turn_left__Debug__AC__turn_left( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__turn_left__Debug__En__TURNING_LEFT( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__turn_left__Debug__Ex__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__turn_left__Debug__end__trans__turn_left( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__turn_left__Debug__init__trans__turn_left( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__turn_right__Debug__AC__turn_right( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__turn_right__Debug__En__TURNING_RIGHT( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__turn_right__Debug__Ex__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__turn_right__Debug__end__trans__turn_right( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__turn_right__Debug__init__trans__turn_right( const UMLRTMessage * msg );
    void transitionaction_____Debug__InitDebug( const UMLRTMessage * msg );
    void transitionaction_____Debug__init( const UMLRTMessage * msg );
    void transitionaction_____Debug__init__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__init__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__init__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__move_backwards( const UMLRTMessage * msg );
    void transitionaction_____Debug__move_backwards__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__move_backwards__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__move_backwards__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__move_forward( const UMLRTMessage * msg );
    void transitionaction_____Debug__move_forward__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__move_forward__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__move_forward__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__stop_moving_backwards( const UMLRTMessage * msg );
    void transitionaction_____Debug__stop_moving_backwards__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__stop_moving_backwards__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__stop_moving_backwards__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__stop_moving_forward( const UMLRTMessage * msg );
    void transitionaction_____Debug__stop_moving_forward__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__stop_moving_forward__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__stop_moving_forward__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__stop_turning_left( const UMLRTMessage * msg );
    void transitionaction_____Debug__stop_turning_left__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__stop_turning_left__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__stop_turning_left__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__stop_turning_right( const UMLRTMessage * msg );
    void transitionaction_____Debug__stop_turning_right__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__stop_turning_right__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__stop_turning_right__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__turn_left( const UMLRTMessage * msg );
    void transitionaction_____Debug__turn_left__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__turn_left__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__turn_left__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__turn_right( const UMLRTMessage * msg );
    void transitionaction_____Debug__turn_right__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__turn_right__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__turn_right__dbg( const UMLRTMessage * msg );
    void transitionaction_____init( const UMLRTMessage * msg );
    void transitionaction_____move_backwards( const UMLRTMessage * msg );
    void transitionaction_____move_forward( const UMLRTMessage * msg );
    void transitionaction_____stop_moving_backwards( const UMLRTMessage * msg );
    void transitionaction_____stop_moving_forward( const UMLRTMessage * msg );
    void transitionaction_____stop_turning_left( const UMLRTMessage * msg );
    void transitionaction_____stop_turning_right( const UMLRTMessage * msg );
    void transitionaction_____turn_left( const UMLRTMessage * msg );
    void transitionaction_____turn_right( const UMLRTMessage * msg );
    bool action_____Debug__init__S__Debug__Guardinit( const UMLRTMessage * msg );
    bool action_____Debug__move_backwards__S__Debug__Guardmove_backwards( const UMLRTMessage * msg );
    bool action_____Debug__move_forward__S__Debug__Guardmove_forward( const UMLRTMessage * msg );
    bool action_____Debug__stop_moving_backwards__S__Debug__Guardstop_moving_backwards( const UMLRTMessage * msg );
    bool action_____Debug__stop_moving_forward__S__Debug__Guardstop_moving_forward( const UMLRTMessage * msg );
    bool action_____Debug__stop_turning_left__S__Debug__Guardstop_turning_left( const UMLRTMessage * msg );
    bool action_____Debug__stop_turning_right__S__Debug__Guardstop_turning_right( const UMLRTMessage * msg );
    bool action_____Debug__turn_left__S__Debug__Guardturn_left( const UMLRTMessage * msg );
    bool action_____Debug__turn_right__S__Debug__Guardturn_right( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__Debug__Ac__init( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__Debug__En__IDLE( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__Debug__end__trans__init( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__Debug__init__trans__init( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__new_transition_61( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__new_transition_62( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__new_transition_63( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__new_transition_64_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__new_transition_65( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__new_transition_66( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__new_transition_67( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__new_transition_68( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_backwards__Debug__AC__move_backwards( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_backwards__Debug__En__MOVING_BACKWARDS( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_backwards__Debug__Ex__IDLE( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_backwards__Debug__end__trans__move_backwards( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_backwards__Debug__init__trans__move_backwards( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_backwards__new_transition_79( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_backwards__new_transition_80( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_backwards__new_transition_81( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_backwards__new_transition_82( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_backwards__new_transition_83_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_backwards__new_transition_84( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_backwards__new_transition_85( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_backwards__new_transition_86( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_backwards__new_transition_87( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_backwards__new_transition_88( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_forward__Debug__AC__move_forward( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_forward__Debug__En__MOVING_FORWARD( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_forward__Debug__Ex__IDLE( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_forward__Debug__end__trans__move_forward( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_forward__Debug__init__trans__move_forward( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_forward__new_transition_31( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_forward__new_transition_32( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_forward__new_transition_33( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_forward__new_transition_34( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_forward__new_transition_35_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_forward__new_transition_36( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_forward__new_transition_37( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_forward__new_transition_38( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_forward__new_transition_39( const UMLRTMessage * msg );
    void actionchain_____Debug__C__move_forward__new_transition_40( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_backwards__Debug__AC__stop_moving_backwards( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_backwards__Debug__En__IDLE( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_backwards__Debug__Ex__MOVING_BACKWARDS( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_backwards__Debug__end__trans__stop_moving_backwards( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_backwards__Debug__init__trans__stop_moving_backwards( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_backwards__new_transition_41( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_backwards__new_transition_42( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_backwards__new_transition_43( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_backwards__new_transition_44( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_backwards__new_transition_45_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_backwards__new_transition_46( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_backwards__new_transition_47( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_backwards__new_transition_48( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_backwards__new_transition_49( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_backwards__new_transition_50( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_forward__Debug__AC__stop_moving_forward( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_forward__Debug__En__IDLE( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_forward__Debug__Ex__MOVING_FORWARD( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_forward__Debug__end__trans__stop_moving_forward( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_forward__Debug__init__trans__stop_moving_forward( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_forward__new_transition_21( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_forward__new_transition_22( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_forward__new_transition_23( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_forward__new_transition_24( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_forward__new_transition_25_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_forward__new_transition_26( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_forward__new_transition_27( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_forward__new_transition_28( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_forward__new_transition_29( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_moving_forward__new_transition_30( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_left__Debug__AC__stop_turning_left( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_left__Debug__En__IDLE( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_left__Debug__Ex__TURNING_LEFT( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_left__Debug__end__trans__stop_turning_left( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_left__Debug__init__trans__stop_turning_left( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_left__new_transition_51( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_left__new_transition_52( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_left__new_transition_53( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_left__new_transition_54( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_left__new_transition_55_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_left__new_transition_56( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_left__new_transition_57( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_left__new_transition_58( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_left__new_transition_59( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_left__new_transition_60( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_right__Debug__AC__stop_turning_right( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_right__Debug__En__IDLE( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_right__Debug__Ex__TURNING_RIGHT( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_right__Debug__end__trans__stop_turning_right( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_right__Debug__init__trans__stop_turning_right( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_right__new_transition_11( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_right__new_transition_12( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_right__new_transition_13( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_right__new_transition_14( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_right__new_transition_15_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_right__new_transition_16( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_right__new_transition_17( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_right__new_transition_18( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_right__new_transition_19( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_turning_right__new_transition_20( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_left__Debug__AC__turn_left( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_left__Debug__En__TURNING_LEFT( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_left__Debug__Ex__IDLE( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_left__Debug__end__trans__turn_left( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_left__Debug__init__trans__turn_left( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_left__new_transition_1( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_left__new_transition_10( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_left__new_transition_2( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_left__new_transition_3( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_left__new_transition_4( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_left__new_transition_5_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_left__new_transition_6( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_left__new_transition_7( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_left__new_transition_8( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_left__new_transition_9( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_right__Debug__AC__turn_right( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_right__Debug__En__TURNING_RIGHT( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_right__Debug__Ex__IDLE( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_right__Debug__end__trans__turn_right( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_right__Debug__init__trans__turn_right( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_right__new_transition_69( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_right__new_transition_70( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_right__new_transition_71( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_right__new_transition_72( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_right__new_transition_73_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_right__new_transition_74( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_right__new_transition_75( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_right__new_transition_76( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_right__new_transition_77( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turn_right__new_transition_78( const UMLRTMessage * msg );
    void actionchain_____Debug__InitDebug( const UMLRTMessage * msg );
    void actionchain_____Debug__init( const UMLRTMessage * msg );
    void actionchain_____Debug__init__E( const UMLRTMessage * msg );
    void actionchain_____Debug__init__S( const UMLRTMessage * msg );
    void actionchain_____Debug__init__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__move_backwards( const UMLRTMessage * msg );
    void actionchain_____Debug__move_backwards__E( const UMLRTMessage * msg );
    void actionchain_____Debug__move_backwards__S( const UMLRTMessage * msg );
    void actionchain_____Debug__move_backwards__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__move_forward( const UMLRTMessage * msg );
    void actionchain_____Debug__move_forward__E( const UMLRTMessage * msg );
    void actionchain_____Debug__move_forward__S( const UMLRTMessage * msg );
    void actionchain_____Debug__move_forward__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__stop_moving_backwards( const UMLRTMessage * msg );
    void actionchain_____Debug__stop_moving_backwards__E( const UMLRTMessage * msg );
    void actionchain_____Debug__stop_moving_backwards__S( const UMLRTMessage * msg );
    void actionchain_____Debug__stop_moving_backwards__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__stop_moving_forward( const UMLRTMessage * msg );
    void actionchain_____Debug__stop_moving_forward__E( const UMLRTMessage * msg );
    void actionchain_____Debug__stop_moving_forward__S( const UMLRTMessage * msg );
    void actionchain_____Debug__stop_moving_forward__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__stop_turning_left( const UMLRTMessage * msg );
    void actionchain_____Debug__stop_turning_left__E( const UMLRTMessage * msg );
    void actionchain_____Debug__stop_turning_left__S( const UMLRTMessage * msg );
    void actionchain_____Debug__stop_turning_left__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__stop_turning_right( const UMLRTMessage * msg );
    void actionchain_____Debug__stop_turning_right__E( const UMLRTMessage * msg );
    void actionchain_____Debug__stop_turning_right__S( const UMLRTMessage * msg );
    void actionchain_____Debug__stop_turning_right__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__turn_left( const UMLRTMessage * msg );
    void actionchain_____Debug__turn_left__E( const UMLRTMessage * msg );
    void actionchain_____Debug__turn_left__S( const UMLRTMessage * msg );
    void actionchain_____Debug__turn_left__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__turn_right( const UMLRTMessage * msg );
    void actionchain_____Debug__turn_right__E( const UMLRTMessage * msg );
    void actionchain_____Debug__turn_right__S( const UMLRTMessage * msg );
    void actionchain_____Debug__turn_right__dbg( const UMLRTMessage * msg );
    void actionchain_____init( const UMLRTMessage * msg );
    void actionchain_____move_backwards( const UMLRTMessage * msg );
    void actionchain_____move_forward( const UMLRTMessage * msg );
    void actionchain_____stop_moving_backwards( const UMLRTMessage * msg );
    void actionchain_____stop_moving_forward( const UMLRTMessage * msg );
    void actionchain_____stop_turning_left( const UMLRTMessage * msg );
    void actionchain_____stop_turning_right( const UMLRTMessage * msg );
    void actionchain_____turn_left( const UMLRTMessage * msg );
    void actionchain_____turn_right( const UMLRTMessage * msg );
    State junction_____Debug__C__init__en( const UMLRTMessage * msg );
    State junction_____Debug__C__init__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__init__new_exitpoint_7( const UMLRTMessage * msg );
    State junction_____Debug__C__move_backwards__en( const UMLRTMessage * msg );
    State junction_____Debug__C__move_backwards__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__move_backwards__new_exitpoint_9( const UMLRTMessage * msg );
    State junction_____Debug__C__move_forward__en( const UMLRTMessage * msg );
    State junction_____Debug__C__move_forward__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__move_forward__new_exitpoint_4( const UMLRTMessage * msg );
    State junction_____Debug__C__stop_moving_backwards__en( const UMLRTMessage * msg );
    State junction_____Debug__C__stop_moving_backwards__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__stop_moving_backwards__new_exitpoint_5( const UMLRTMessage * msg );
    State junction_____Debug__C__stop_moving_forward__en( const UMLRTMessage * msg );
    State junction_____Debug__C__stop_moving_forward__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__stop_moving_forward__new_exitpoint_3( const UMLRTMessage * msg );
    State junction_____Debug__C__stop_turning_left__en( const UMLRTMessage * msg );
    State junction_____Debug__C__stop_turning_left__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__stop_turning_left__new_exitpoint_6( const UMLRTMessage * msg );
    State junction_____Debug__C__stop_turning_right__en( const UMLRTMessage * msg );
    State junction_____Debug__C__stop_turning_right__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__stop_turning_right__new_exitpoint_2( const UMLRTMessage * msg );
    State junction_____Debug__C__turn_left__en( const UMLRTMessage * msg );
    State junction_____Debug__C__turn_left__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__turn_left__new_exitpoint_1( const UMLRTMessage * msg );
    State junction_____Debug__C__turn_right__en( const UMLRTMessage * msg );
    State junction_____Debug__C__turn_right__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__turn_right__new_exitpoint_8( const UMLRTMessage * msg );
    State choice_____Debug__C__init__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__move_backwards__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__move_forward__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__stop_moving_backwards__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__stop_moving_forward__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__stop_turning_left__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__stop_turning_right__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__turn_left__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__turn_right__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__Path__init( const UMLRTMessage * msg );
    State choice_____Debug__Path__move_backwards( const UMLRTMessage * msg );
    State choice_____Debug__Path__move_forward( const UMLRTMessage * msg );
    State choice_____Debug__Path__stop_moving_backwards( const UMLRTMessage * msg );
    State choice_____Debug__Path__stop_moving_forward( const UMLRTMessage * msg );
    State choice_____Debug__Path__stop_turning_left( const UMLRTMessage * msg );
    State choice_____Debug__Path__stop_turning_right( const UMLRTMessage * msg );
    State choice_____Debug__Path__turn_left( const UMLRTMessage * msg );
    State choice_____Debug__Path__turn_right( const UMLRTMessage * msg );
    State state_____Debug__C__init__Debug__A__Ac__init( const UMLRTMessage * msg );
    State state_____Debug__C__init__Debug__A__En__init( const UMLRTMessage * msg );
    State state_____Debug__C__init__Debug__B__Ac__init( const UMLRTMessage * msg );
    State state_____Debug__C__init__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__move_backwards__Debug__A__Ac__move_backwards( const UMLRTMessage * msg );
    State state_____Debug__C__move_backwards__Debug__A__En__MOVING_BACKWARDS( const UMLRTMessage * msg );
    State state_____Debug__C__move_backwards__Debug__B__Ac__move_backwards( const UMLRTMessage * msg );
    State state_____Debug__C__move_backwards__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    State state_____Debug__C__move_backwards__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__move_forward__Debug__A__Ac__move_forward( const UMLRTMessage * msg );
    State state_____Debug__C__move_forward__Debug__A__En__MOVING_FORWARD( const UMLRTMessage * msg );
    State state_____Debug__C__move_forward__Debug__B__Ac__move_forward( const UMLRTMessage * msg );
    State state_____Debug__C__move_forward__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    State state_____Debug__C__move_forward__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__stop_moving_backwards__Debug__A__Ac__stop_moving_backwards( const UMLRTMessage * msg );
    State state_____Debug__C__stop_moving_backwards__Debug__A__En__IDLE( const UMLRTMessage * msg );
    State state_____Debug__C__stop_moving_backwards__Debug__B__Ac__stop_moving_backwards( const UMLRTMessage * msg );
    State state_____Debug__C__stop_moving_backwards__Debug__B__Ex__MOVING_BACKWARDS( const UMLRTMessage * msg );
    State state_____Debug__C__stop_moving_backwards__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__stop_moving_forward__Debug__A__Ac__stop_moving_forward( const UMLRTMessage * msg );
    State state_____Debug__C__stop_moving_forward__Debug__A__En__IDLE( const UMLRTMessage * msg );
    State state_____Debug__C__stop_moving_forward__Debug__B__Ac__stop_moving_forward( const UMLRTMessage * msg );
    State state_____Debug__C__stop_moving_forward__Debug__B__Ex__MOVING_FORWARD( const UMLRTMessage * msg );
    State state_____Debug__C__stop_moving_forward__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__stop_turning_left__Debug__A__Ac__stop_turning_left( const UMLRTMessage * msg );
    State state_____Debug__C__stop_turning_left__Debug__A__En__IDLE( const UMLRTMessage * msg );
    State state_____Debug__C__stop_turning_left__Debug__B__Ac__stop_turning_left( const UMLRTMessage * msg );
    State state_____Debug__C__stop_turning_left__Debug__B__Ex__TURNING_LEFT( const UMLRTMessage * msg );
    State state_____Debug__C__stop_turning_left__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__stop_turning_right__Debug__A__Ac__stop_turning_right( const UMLRTMessage * msg );
    State state_____Debug__C__stop_turning_right__Debug__A__En__IDLE( const UMLRTMessage * msg );
    State state_____Debug__C__stop_turning_right__Debug__B__Ac__stop_turning_right( const UMLRTMessage * msg );
    State state_____Debug__C__stop_turning_right__Debug__B__Ex__TURNING_RIGHT( const UMLRTMessage * msg );
    State state_____Debug__C__stop_turning_right__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__turn_left__Debug__A__Ac__turn_left( const UMLRTMessage * msg );
    State state_____Debug__C__turn_left__Debug__A__En__TURNING_LEFT( const UMLRTMessage * msg );
    State state_____Debug__C__turn_left__Debug__B__Ac__turn_left( const UMLRTMessage * msg );
    State state_____Debug__C__turn_left__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    State state_____Debug__C__turn_left__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__turn_right__Debug__A__Ac__turn_right( const UMLRTMessage * msg );
    State state_____Debug__C__turn_right__Debug__A__En__TURNING_RIGHT( const UMLRTMessage * msg );
    State state_____Debug__C__turn_right__Debug__B__Ac__turn_right( const UMLRTMessage * msg );
    State state_____Debug__C__turn_right__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    State state_____Debug__C__turn_right__boundary( const UMLRTMessage * msg );
    State state_____Debug__InitState( const UMLRTMessage * msg );
    State state_____IDLE( const UMLRTMessage * msg );
    State state_____MOVING_BACKWARDS( const UMLRTMessage * msg );
    State state_____MOVING_FORWARD( const UMLRTMessage * msg );
    State state_____TURNING_LEFT( const UMLRTMessage * msg );
    State state_____TURNING_RIGHT( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass EngineController;

#endif


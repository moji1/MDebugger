
#ifndef CONTROLSOFTWARE_HH
#define CONTROLSOFTWARE_HH

#include "Detection.hh"
#include "Engine.hh"
#include "ExtInterface.hh"
#include "Temperature.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtlogprotocol.hh"
#include "umlrtmessage.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

#include "Event.h"

#include "SROManager.h"

class Capsule_ControlSoftware : public UMLRTCapsule
{
public:
    Capsule_ControlSoftware( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    Detection::Base detection;
public:
    enum BorderPortId
    {
        borderport_detection,
        borderport_engine,
        borderport_extComm,
        borderport_temperature,
        borderport_timer,
        borderport_log
    };
protected:
    Engine::Base engine;
    ExtInterface::Conj extComm;
    UMLRTLogProtocol_baserole log;
    Temperature::Base temperature;
    UMLRTTimerProtocol_baserole timer;
public:
    enum PartId
    {
    };
    enum PortId
    {
        port_detection,
        port_engine,
        port_extComm,
        port_log,
        port_temperature,
        port_timer
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    double threshold;
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
        Debug__C__lowerThanThreshold,
        Debug__C__moving_forward,
        Debug__C__stopped,
        Debug__C__stopped_moving_backwards,
        Debug__C__timeout,
        Debug__C__turnedRight,
        Debug__C__greaterThan,
        Debug__C__init__Debug__A__Ac__init,
        Debug__C__init__Debug__A__En__init,
        Debug__C__init__Debug__B__Ac__init,
        Debug__C__init__boundary,
        Debug__C__lowerThanThreshold__Debug__A__Ac__lowerThanThreshold,
        Debug__C__lowerThanThreshold__Debug__A__En__STOPPING_MOVING_FORWARD,
        Debug__C__lowerThanThreshold__Debug__B__Ac__lowerThanThreshold,
        Debug__C__lowerThanThreshold__Debug__B__Ex__MOVING_FORWARD,
        Debug__C__lowerThanThreshold__boundary,
        Debug__C__moving_forward__Debug__A__Ac__moving_forward,
        Debug__C__moving_forward__Debug__A__En__MOVING_FORWARD,
        Debug__C__moving_forward__Debug__B__Ac__moving_forward,
        Debug__C__moving_forward__Debug__B__Ex__STANDBY,
        Debug__C__moving_forward__boundary,
        Debug__C__stopped_moving_backwards__Debug__A__Ac__stopped_moving_backwards,
        Debug__C__stopped_moving_backwards__Debug__A__En__ROTATING,
        Debug__C__stopped_moving_backwards__Debug__B__Ac__stopped_moving_backwards,
        Debug__C__stopped_moving_backwards__Debug__B__Ex__STOPPING_MOVING_BACKWARDS,
        Debug__C__stopped_moving_backwards__boundary,
        Debug__C__stopped__Debug__A__Ac__stopped,
        Debug__C__stopped__Debug__A__En__MOVING_BACKWARDS,
        Debug__C__stopped__Debug__B__Ac__stopped,
        Debug__C__stopped__Debug__B__Ex__STOPPING_MOVING_FORWARD,
        Debug__C__stopped__boundary,
        Debug__C__timeout__Debug__A__Ac__timeout,
        Debug__C__timeout__Debug__A__En__STOPPING_MOVING_BACKWARDS,
        Debug__C__timeout__Debug__B__Ac__timeout,
        Debug__C__timeout__Debug__B__Ex__MOVING_BACKWARDS,
        Debug__C__timeout__boundary,
        Debug__C__turnedRight__Debug__A__Ac__turnedRight,
        Debug__C__turnedRight__Debug__A__En__MOVING_FORWARD,
        Debug__C__turnedRight__Debug__B__Ac__turnedRight,
        Debug__C__turnedRight__Debug__B__Ex__ROTATING,
        Debug__C__turnedRight__boundary,
        Debug__InitState,
        MOVING_BACKWARDS,
        MOVING_FORWARD,
        ROTATING,
        STANDBY,
        STOPPING_MOVING_BACKWARDS,
        STOPPING_MOVING_FORWARD,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[50];
    State currentState;
    State history[7];
    void save_history( State compositeState, State subState );
    bool check_history( State compositeState, State subState );
    void entryaction_____Debug__C__greaterThan( const UMLRTMessage * msg );
    void entryaction_____Debug__C__init__Debug__A__Ac__init( const UMLRTMessage * msg );
    void entryaction_____Debug__C__init__Debug__A__En__init( const UMLRTMessage * msg );
    void entryaction_____Debug__C__init__Debug__B__Ac__init( const UMLRTMessage * msg );
    void entryaction_____Debug__C__init__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__lowerThanThreshold__Debug__A__Ac__lowerThanThreshold( const UMLRTMessage * msg );
    void entryaction_____Debug__C__lowerThanThreshold__Debug__A__En__STOPPING_MOVING_FORWARD( const UMLRTMessage * msg );
    void entryaction_____Debug__C__lowerThanThreshold__Debug__B__Ac__lowerThanThreshold( const UMLRTMessage * msg );
    void entryaction_____Debug__C__lowerThanThreshold__Debug__B__Ex__MOVING_FORWARD( const UMLRTMessage * msg );
    void entryaction_____Debug__C__lowerThanThreshold__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__moving_forward__Debug__A__Ac__moving_forward( const UMLRTMessage * msg );
    void entryaction_____Debug__C__moving_forward__Debug__A__En__MOVING_FORWARD( const UMLRTMessage * msg );
    void entryaction_____Debug__C__moving_forward__Debug__B__Ac__moving_forward( const UMLRTMessage * msg );
    void entryaction_____Debug__C__moving_forward__Debug__B__Ex__STANDBY( const UMLRTMessage * msg );
    void entryaction_____Debug__C__moving_forward__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stopped__Debug__A__Ac__stopped( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stopped__Debug__A__En__MOVING_BACKWARDS( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stopped__Debug__B__Ac__stopped( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stopped__Debug__B__Ex__STOPPING_MOVING_FORWARD( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stopped__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stopped_moving_backwards__Debug__A__Ac__stopped_moving_backwards( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stopped_moving_backwards__Debug__A__En__ROTATING( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stopped_moving_backwards__Debug__B__Ac__stopped_moving_backwards( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stopped_moving_backwards__Debug__B__Ex__STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stopped_moving_backwards__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__timeout__Debug__A__Ac__timeout( const UMLRTMessage * msg );
    void entryaction_____Debug__C__timeout__Debug__A__En__STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg );
    void entryaction_____Debug__C__timeout__Debug__B__Ac__timeout( const UMLRTMessage * msg );
    void entryaction_____Debug__C__timeout__Debug__B__Ex__MOVING_BACKWARDS( const UMLRTMessage * msg );
    void entryaction_____Debug__C__timeout__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__turnedRight__Debug__A__Ac__turnedRight( const UMLRTMessage * msg );
    void entryaction_____Debug__C__turnedRight__Debug__A__En__MOVING_FORWARD( const UMLRTMessage * msg );
    void entryaction_____Debug__C__turnedRight__Debug__B__Ac__turnedRight( const UMLRTMessage * msg );
    void entryaction_____Debug__C__turnedRight__Debug__B__Ex__ROTATING( const UMLRTMessage * msg );
    void entryaction_____Debug__C__turnedRight__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__InitState( const UMLRTMessage * msg );
    void entryaction_____MOVING_BACKWARDS( const UMLRTMessage * msg );
    void entryaction_____MOVING_FORWARD( const UMLRTMessage * msg );
    void entryaction_____ROTATING( const UMLRTMessage * msg );
    void entryaction_____STANDBY( const UMLRTMessage * msg );
    void entryaction_____STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg );
    void entryaction_____STOPPING_MOVING_FORWARD( const UMLRTMessage * msg );
    void exitaction_____Debug__C__greaterThan( const UMLRTMessage * msg );
    void exitaction_____Debug__C__init__Debug__A__Ac__init( const UMLRTMessage * msg );
    void exitaction_____Debug__C__init__Debug__A__En__init( const UMLRTMessage * msg );
    void exitaction_____Debug__C__init__Debug__B__Ac__init( const UMLRTMessage * msg );
    void exitaction_____Debug__C__init__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__lowerThanThreshold__Debug__A__Ac__lowerThanThreshold( const UMLRTMessage * msg );
    void exitaction_____Debug__C__lowerThanThreshold__Debug__A__En__STOPPING_MOVING_FORWARD( const UMLRTMessage * msg );
    void exitaction_____Debug__C__lowerThanThreshold__Debug__B__Ac__lowerThanThreshold( const UMLRTMessage * msg );
    void exitaction_____Debug__C__lowerThanThreshold__Debug__B__Ex__MOVING_FORWARD( const UMLRTMessage * msg );
    void exitaction_____Debug__C__lowerThanThreshold__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__moving_forward__Debug__A__Ac__moving_forward( const UMLRTMessage * msg );
    void exitaction_____Debug__C__moving_forward__Debug__A__En__MOVING_FORWARD( const UMLRTMessage * msg );
    void exitaction_____Debug__C__moving_forward__Debug__B__Ac__moving_forward( const UMLRTMessage * msg );
    void exitaction_____Debug__C__moving_forward__Debug__B__Ex__STANDBY( const UMLRTMessage * msg );
    void exitaction_____Debug__C__moving_forward__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stopped__Debug__A__Ac__stopped( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stopped__Debug__A__En__MOVING_BACKWARDS( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stopped__Debug__B__Ac__stopped( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stopped__Debug__B__Ex__STOPPING_MOVING_FORWARD( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stopped__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stopped_moving_backwards__Debug__A__Ac__stopped_moving_backwards( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stopped_moving_backwards__Debug__A__En__ROTATING( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stopped_moving_backwards__Debug__B__Ac__stopped_moving_backwards( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stopped_moving_backwards__Debug__B__Ex__STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stopped_moving_backwards__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__timeout__Debug__A__Ac__timeout( const UMLRTMessage * msg );
    void exitaction_____Debug__C__timeout__Debug__A__En__STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg );
    void exitaction_____Debug__C__timeout__Debug__B__Ac__timeout( const UMLRTMessage * msg );
    void exitaction_____Debug__C__timeout__Debug__B__Ex__MOVING_BACKWARDS( const UMLRTMessage * msg );
    void exitaction_____Debug__C__timeout__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__turnedRight__Debug__A__Ac__turnedRight( const UMLRTMessage * msg );
    void exitaction_____Debug__C__turnedRight__Debug__A__En__MOVING_FORWARD( const UMLRTMessage * msg );
    void exitaction_____Debug__C__turnedRight__Debug__B__Ac__turnedRight( const UMLRTMessage * msg );
    void exitaction_____Debug__C__turnedRight__Debug__B__Ex__ROTATING( const UMLRTMessage * msg );
    void exitaction_____Debug__C__turnedRight__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__InitState( const UMLRTMessage * msg );
    void exitaction_____MOVING_BACKWARDS( const UMLRTMessage * msg );
    void exitaction_____MOVING_FORWARD( const UMLRTMessage * msg );
    void exitaction_____ROTATING( const UMLRTMessage * msg );
    void exitaction_____STANDBY( const UMLRTMessage * msg );
    void exitaction_____STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg );
    void exitaction_____STOPPING_MOVING_FORWARD( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__init__Debug__Ac__init( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__init__Debug__En__STANDBY( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__init__Debug__end__trans__init( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__init__Debug__init__trans__init( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__lowerThanThreshold__Debug__AC__lowerThanThreshold( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__lowerThanThreshold__Debug__En__STOPPING_MOVING_FORWARD( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__lowerThanThreshold__Debug__Ex__MOVING_FORWARD( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__lowerThanThreshold__Debug__end__trans__lowerThanThreshold( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__lowerThanThreshold__Debug__init__trans__lowerThanThreshold( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__moving_forward__Debug__AC__moving_forward( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__moving_forward__Debug__En__MOVING_FORWARD( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__moving_forward__Debug__Ex__STANDBY( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__moving_forward__Debug__end__trans__moving_forward( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__moving_forward__Debug__init__trans__moving_forward( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stopped__Debug__AC__stopped( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stopped__Debug__En__MOVING_BACKWARDS( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stopped__Debug__Ex__STOPPING_MOVING_FORWARD( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stopped__Debug__end__trans__stopped( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stopped__Debug__init__trans__stopped( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stopped_moving_backwards__Debug__AC__stopped_moving_backwards( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stopped_moving_backwards__Debug__En__ROTATING( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stopped_moving_backwards__Debug__Ex__STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stopped_moving_backwards__Debug__end__trans__stopped_moving_backwards( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stopped_moving_backwards__Debug__init__trans__stopped_moving_backwards( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__timeout__Debug__AC__timeout( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__timeout__Debug__En__STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__timeout__Debug__Ex__MOVING_BACKWARDS( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__timeout__Debug__end__trans__timeout( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__timeout__Debug__init__trans__timeout( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__turnedRight__Debug__AC__turnedRight( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__turnedRight__Debug__En__MOVING_FORWARD( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__turnedRight__Debug__Ex__ROTATING( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__turnedRight__Debug__end__trans__turnedRight( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__turnedRight__Debug__init__trans__turnedRight( const UMLRTMessage * msg );
    void transitionaction_____Debug__InitDebug( const UMLRTMessage * msg );
    void transitionaction_____Debug__greaterThan( const UMLRTMessage * msg );
    void transitionaction_____Debug__greaterThan__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__greaterThan__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__greaterThan__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__init( const UMLRTMessage * msg );
    void transitionaction_____Debug__init__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__init__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__init__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__lowerThanThreshold( const UMLRTMessage * msg );
    void transitionaction_____Debug__lowerThanThreshold__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__lowerThanThreshold__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__lowerThanThreshold__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__moving_forward( const UMLRTMessage * msg );
    void transitionaction_____Debug__moving_forward__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__moving_forward__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__moving_forward__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__stopped( const UMLRTMessage * msg );
    void transitionaction_____Debug__stopped__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__stopped__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__stopped__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__stopped_moving_backwards( const UMLRTMessage * msg );
    void transitionaction_____Debug__stopped_moving_backwards__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__stopped_moving_backwards__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__stopped_moving_backwards__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__timeout( const UMLRTMessage * msg );
    void transitionaction_____Debug__timeout__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__timeout__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__timeout__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__turnedRight( const UMLRTMessage * msg );
    void transitionaction_____Debug__turnedRight__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__turnedRight__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__turnedRight__dbg( const UMLRTMessage * msg );
    void transitionaction_____greaterThan( const UMLRTMessage * msg );
    void transitionaction_____init( const UMLRTMessage * msg );
    void transitionaction_____lowerThanThreshold( const UMLRTMessage * msg );
    void transitionaction_____moving_forward( const UMLRTMessage * msg );
    void transitionaction_____stopped( const UMLRTMessage * msg );
    void transitionaction_____stopped_moving_backwards( const UMLRTMessage * msg );
    void transitionaction_____timeout( const UMLRTMessage * msg );
    void transitionaction_____turnedRight( const UMLRTMessage * msg );
    bool action_____Debug__greaterThan__S__Debug__GuardgreaterThan( const UMLRTMessage * msg );
    bool action_____Debug__greaterThan__greaterThanThreshold( const UMLRTMessage * msg );
    bool action_____Debug__init__S__Debug__Guardinit( const UMLRTMessage * msg );
    bool action_____Debug__lowerThanThreshold__S__Debug__GuardlowerThanThreshold( const UMLRTMessage * msg );
    bool action_____Debug__lowerThanThreshold__lessThanThreshold( const UMLRTMessage * msg );
    bool action_____Debug__moving_forward__S__Debug__Guardmoving_forward( const UMLRTMessage * msg );
    bool action_____Debug__stopped__S__Debug__Guardstopped( const UMLRTMessage * msg );
    bool action_____Debug__stopped_moving_backwards__S__Debug__Guardstopped_moving_backwards( const UMLRTMessage * msg );
    bool action_____Debug__timeout__S__Debug__Guardtimeout( const UMLRTMessage * msg );
    bool action_____Debug__turnedRight__S__Debug__GuardturnedRight( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__Debug__Ac__init( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__Debug__En__STANDBY( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__Debug__end__trans__init( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__Debug__init__trans__init( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__new_transition_21( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__new_transition_22( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__new_transition_23( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__new_transition_24_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__new_transition_25( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__new_transition_26( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__new_transition_27( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__new_transition_28( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lowerThanThreshold__Debug__AC__lowerThanThreshold( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lowerThanThreshold__Debug__En__STOPPING_MOVING_FORWARD( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lowerThanThreshold__Debug__Ex__MOVING_FORWARD( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lowerThanThreshold__Debug__end__trans__lowerThanThreshold( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lowerThanThreshold__Debug__init__trans__lowerThanThreshold( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lowerThanThreshold__new_transition_29( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lowerThanThreshold__new_transition_30( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lowerThanThreshold__new_transition_31( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lowerThanThreshold__new_transition_32( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lowerThanThreshold__new_transition_33_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lowerThanThreshold__new_transition_34( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lowerThanThreshold__new_transition_35( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lowerThanThreshold__new_transition_36( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lowerThanThreshold__new_transition_37( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lowerThanThreshold__new_transition_38( const UMLRTMessage * msg );
    void actionchain_____Debug__C__moving_forward__Debug__AC__moving_forward( const UMLRTMessage * msg );
    void actionchain_____Debug__C__moving_forward__Debug__En__MOVING_FORWARD( const UMLRTMessage * msg );
    void actionchain_____Debug__C__moving_forward__Debug__Ex__STANDBY( const UMLRTMessage * msg );
    void actionchain_____Debug__C__moving_forward__Debug__end__trans__moving_forward( const UMLRTMessage * msg );
    void actionchain_____Debug__C__moving_forward__Debug__init__trans__moving_forward( const UMLRTMessage * msg );
    void actionchain_____Debug__C__moving_forward__new_transition_59( const UMLRTMessage * msg );
    void actionchain_____Debug__C__moving_forward__new_transition_60( const UMLRTMessage * msg );
    void actionchain_____Debug__C__moving_forward__new_transition_61( const UMLRTMessage * msg );
    void actionchain_____Debug__C__moving_forward__new_transition_62( const UMLRTMessage * msg );
    void actionchain_____Debug__C__moving_forward__new_transition_63_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__moving_forward__new_transition_64( const UMLRTMessage * msg );
    void actionchain_____Debug__C__moving_forward__new_transition_65( const UMLRTMessage * msg );
    void actionchain_____Debug__C__moving_forward__new_transition_66( const UMLRTMessage * msg );
    void actionchain_____Debug__C__moving_forward__new_transition_67( const UMLRTMessage * msg );
    void actionchain_____Debug__C__moving_forward__new_transition_68( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped__Debug__AC__stopped( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped__Debug__En__MOVING_BACKWARDS( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped__Debug__Ex__STOPPING_MOVING_FORWARD( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped__Debug__end__trans__stopped( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped__Debug__init__trans__stopped( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped__new_transition_1( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped__new_transition_10( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped__new_transition_2( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped__new_transition_3( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped__new_transition_4( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped__new_transition_5_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped__new_transition_6( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped__new_transition_7( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped__new_transition_8( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped__new_transition_9( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped_moving_backwards__Debug__AC__stopped_moving_backwards( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped_moving_backwards__Debug__En__ROTATING( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped_moving_backwards__Debug__Ex__STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped_moving_backwards__Debug__end__trans__stopped_moving_backwards( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped_moving_backwards__Debug__init__trans__stopped_moving_backwards( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped_moving_backwards__new_transition_11( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped_moving_backwards__new_transition_12( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped_moving_backwards__new_transition_13( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped_moving_backwards__new_transition_14( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped_moving_backwards__new_transition_15_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped_moving_backwards__new_transition_16( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped_moving_backwards__new_transition_17( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped_moving_backwards__new_transition_18( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped_moving_backwards__new_transition_19( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stopped_moving_backwards__new_transition_20( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__Debug__AC__timeout( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__Debug__En__STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__Debug__Ex__MOVING_BACKWARDS( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__Debug__end__trans__timeout( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__Debug__init__trans__timeout( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_39( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_40( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_41( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_42( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_43_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_44( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_45( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_46( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_47( const UMLRTMessage * msg );
    void actionchain_____Debug__C__timeout__new_transition_48( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turnedRight__Debug__AC__turnedRight( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turnedRight__Debug__En__MOVING_FORWARD( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turnedRight__Debug__Ex__ROTATING( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turnedRight__Debug__end__trans__turnedRight( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turnedRight__Debug__init__trans__turnedRight( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turnedRight__new_transition_49( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turnedRight__new_transition_50( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turnedRight__new_transition_51( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turnedRight__new_transition_52( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turnedRight__new_transition_53_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turnedRight__new_transition_54( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turnedRight__new_transition_55( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turnedRight__new_transition_56( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turnedRight__new_transition_57( const UMLRTMessage * msg );
    void actionchain_____Debug__C__turnedRight__new_transition_58( const UMLRTMessage * msg );
    void actionchain_____Debug__InitDebug( const UMLRTMessage * msg );
    void actionchain_____Debug__greaterThan( const UMLRTMessage * msg );
    void actionchain_____Debug__greaterThan__E( const UMLRTMessage * msg );
    void actionchain_____Debug__greaterThan__S( const UMLRTMessage * msg );
    void actionchain_____Debug__greaterThan__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__init( const UMLRTMessage * msg );
    void actionchain_____Debug__init__E( const UMLRTMessage * msg );
    void actionchain_____Debug__init__S( const UMLRTMessage * msg );
    void actionchain_____Debug__init__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__lowerThanThreshold( const UMLRTMessage * msg );
    void actionchain_____Debug__lowerThanThreshold__E( const UMLRTMessage * msg );
    void actionchain_____Debug__lowerThanThreshold__S( const UMLRTMessage * msg );
    void actionchain_____Debug__lowerThanThreshold__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__moving_forward( const UMLRTMessage * msg );
    void actionchain_____Debug__moving_forward__E( const UMLRTMessage * msg );
    void actionchain_____Debug__moving_forward__S( const UMLRTMessage * msg );
    void actionchain_____Debug__moving_forward__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__stopped( const UMLRTMessage * msg );
    void actionchain_____Debug__stopped__E( const UMLRTMessage * msg );
    void actionchain_____Debug__stopped__S( const UMLRTMessage * msg );
    void actionchain_____Debug__stopped__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__stopped_moving_backwards( const UMLRTMessage * msg );
    void actionchain_____Debug__stopped_moving_backwards__E( const UMLRTMessage * msg );
    void actionchain_____Debug__stopped_moving_backwards__S( const UMLRTMessage * msg );
    void actionchain_____Debug__stopped_moving_backwards__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__timeout( const UMLRTMessage * msg );
    void actionchain_____Debug__timeout__E( const UMLRTMessage * msg );
    void actionchain_____Debug__timeout__S( const UMLRTMessage * msg );
    void actionchain_____Debug__timeout__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__turnedRight( const UMLRTMessage * msg );
    void actionchain_____Debug__turnedRight__E( const UMLRTMessage * msg );
    void actionchain_____Debug__turnedRight__S( const UMLRTMessage * msg );
    void actionchain_____Debug__turnedRight__dbg( const UMLRTMessage * msg );
    void actionchain_____greaterThan( const UMLRTMessage * msg );
    void actionchain_____init( const UMLRTMessage * msg );
    void actionchain_____lowerThanThreshold( const UMLRTMessage * msg );
    void actionchain_____moving_forward( const UMLRTMessage * msg );
    void actionchain_____stopped( const UMLRTMessage * msg );
    void actionchain_____stopped_moving_backwards( const UMLRTMessage * msg );
    void actionchain_____timeout( const UMLRTMessage * msg );
    void actionchain_____turnedRight( const UMLRTMessage * msg );
    State junction_____Debug__C__init__en( const UMLRTMessage * msg );
    State junction_____Debug__C__init__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__init__new_exitpoint_3( const UMLRTMessage * msg );
    State junction_____Debug__C__lowerThanThreshold__en( const UMLRTMessage * msg );
    State junction_____Debug__C__lowerThanThreshold__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__lowerThanThreshold__new_exitpoint_4( const UMLRTMessage * msg );
    State junction_____Debug__C__moving_forward__en( const UMLRTMessage * msg );
    State junction_____Debug__C__moving_forward__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__moving_forward__new_exitpoint_7( const UMLRTMessage * msg );
    State junction_____Debug__C__stopped__en( const UMLRTMessage * msg );
    State junction_____Debug__C__stopped__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__stopped__new_exitpoint_1( const UMLRTMessage * msg );
    State junction_____Debug__C__stopped_moving_backwards__en( const UMLRTMessage * msg );
    State junction_____Debug__C__stopped_moving_backwards__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__stopped_moving_backwards__new_exitpoint_2( const UMLRTMessage * msg );
    State junction_____Debug__C__timeout__en( const UMLRTMessage * msg );
    State junction_____Debug__C__timeout__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__timeout__new_exitpoint_5( const UMLRTMessage * msg );
    State junction_____Debug__C__turnedRight__en( const UMLRTMessage * msg );
    State junction_____Debug__C__turnedRight__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__turnedRight__new_exitpoint_6( const UMLRTMessage * msg );
    State choice_____Debug__C__init__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__lowerThanThreshold__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__moving_forward__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__stopped__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__stopped_moving_backwards__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__timeout__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__turnedRight__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__Path__greaterThan( const UMLRTMessage * msg );
    State choice_____Debug__Path__init( const UMLRTMessage * msg );
    State choice_____Debug__Path__lowerThanThreshold( const UMLRTMessage * msg );
    State choice_____Debug__Path__moving_forward( const UMLRTMessage * msg );
    State choice_____Debug__Path__stopped( const UMLRTMessage * msg );
    State choice_____Debug__Path__stopped_moving_backwards( const UMLRTMessage * msg );
    State choice_____Debug__Path__timeout( const UMLRTMessage * msg );
    State choice_____Debug__Path__turnedRight( const UMLRTMessage * msg );
    State state_____Debug__C__greaterThan( const UMLRTMessage * msg );
    State state_____Debug__C__init__Debug__A__Ac__init( const UMLRTMessage * msg );
    State state_____Debug__C__init__Debug__A__En__init( const UMLRTMessage * msg );
    State state_____Debug__C__init__Debug__B__Ac__init( const UMLRTMessage * msg );
    State state_____Debug__C__init__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__lowerThanThreshold__Debug__A__Ac__lowerThanThreshold( const UMLRTMessage * msg );
    State state_____Debug__C__lowerThanThreshold__Debug__A__En__STOPPING_MOVING_FORWARD( const UMLRTMessage * msg );
    State state_____Debug__C__lowerThanThreshold__Debug__B__Ac__lowerThanThreshold( const UMLRTMessage * msg );
    State state_____Debug__C__lowerThanThreshold__Debug__B__Ex__MOVING_FORWARD( const UMLRTMessage * msg );
    State state_____Debug__C__lowerThanThreshold__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__moving_forward__Debug__A__Ac__moving_forward( const UMLRTMessage * msg );
    State state_____Debug__C__moving_forward__Debug__A__En__MOVING_FORWARD( const UMLRTMessage * msg );
    State state_____Debug__C__moving_forward__Debug__B__Ac__moving_forward( const UMLRTMessage * msg );
    State state_____Debug__C__moving_forward__Debug__B__Ex__STANDBY( const UMLRTMessage * msg );
    State state_____Debug__C__moving_forward__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__stopped__Debug__A__Ac__stopped( const UMLRTMessage * msg );
    State state_____Debug__C__stopped__Debug__A__En__MOVING_BACKWARDS( const UMLRTMessage * msg );
    State state_____Debug__C__stopped__Debug__B__Ac__stopped( const UMLRTMessage * msg );
    State state_____Debug__C__stopped__Debug__B__Ex__STOPPING_MOVING_FORWARD( const UMLRTMessage * msg );
    State state_____Debug__C__stopped__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__stopped_moving_backwards__Debug__A__Ac__stopped_moving_backwards( const UMLRTMessage * msg );
    State state_____Debug__C__stopped_moving_backwards__Debug__A__En__ROTATING( const UMLRTMessage * msg );
    State state_____Debug__C__stopped_moving_backwards__Debug__B__Ac__stopped_moving_backwards( const UMLRTMessage * msg );
    State state_____Debug__C__stopped_moving_backwards__Debug__B__Ex__STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg );
    State state_____Debug__C__stopped_moving_backwards__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__timeout__Debug__A__Ac__timeout( const UMLRTMessage * msg );
    State state_____Debug__C__timeout__Debug__A__En__STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg );
    State state_____Debug__C__timeout__Debug__B__Ac__timeout( const UMLRTMessage * msg );
    State state_____Debug__C__timeout__Debug__B__Ex__MOVING_BACKWARDS( const UMLRTMessage * msg );
    State state_____Debug__C__timeout__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__turnedRight__Debug__A__Ac__turnedRight( const UMLRTMessage * msg );
    State state_____Debug__C__turnedRight__Debug__A__En__MOVING_FORWARD( const UMLRTMessage * msg );
    State state_____Debug__C__turnedRight__Debug__B__Ac__turnedRight( const UMLRTMessage * msg );
    State state_____Debug__C__turnedRight__Debug__B__Ex__ROTATING( const UMLRTMessage * msg );
    State state_____Debug__C__turnedRight__boundary( const UMLRTMessage * msg );
    State state_____Debug__InitState( const UMLRTMessage * msg );
    State state_____MOVING_BACKWARDS( const UMLRTMessage * msg );
    State state_____MOVING_FORWARD( const UMLRTMessage * msg );
    State state_____ROTATING( const UMLRTMessage * msg );
    State state_____STANDBY( const UMLRTMessage * msg );
    State state_____STOPPING_MOVING_BACKWARDS( const UMLRTMessage * msg );
    State state_____STOPPING_MOVING_FORWARD( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass ControlSoftware;

#endif


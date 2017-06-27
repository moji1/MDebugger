
#ifndef DETECTIONSENSOR_HH
#define DETECTIONSENSOR_HH

#include "Detection.hh"
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

class Capsule_DetectionSensor : public UMLRTCapsule
{
public:
    Capsule_DetectionSensor( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
    enum BorderPortId
    {
        borderport_detection,
        borderport_extComm,
        borderport_timer,
        borderport_log
    };
protected:
    Detection::Conj detection;
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
        port_extComm,
        port_log,
        port_timer
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    UMLRTTimerId timerId;
    GPIOClass pinTrig;
    GPIOClass pinEcho;
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
        Debug__C__start_detecting,
        Debug__C__stop_detecting,
        DETECTING,
        Debug__C__detecting,
        Debug__C__init__Debug__A__Ac__init,
        Debug__C__init__Debug__A__En__init,
        Debug__C__init__Debug__B__Ac__init,
        Debug__C__init__boundary,
        Debug__C__start_detecting__Debug__A__Ac__start_detecting,
        Debug__C__start_detecting__Debug__A__En__DETECTING,
        Debug__C__start_detecting__Debug__B__Ac__start_detecting,
        Debug__C__start_detecting__Debug__B__Ex__IDLE,
        Debug__C__start_detecting__boundary,
        Debug__C__stop_detecting__Debug__A__Ac__stop_detecting,
        Debug__C__stop_detecting__Debug__A__En__IDLE,
        Debug__C__stop_detecting__Debug__B__Ac__stop_detecting,
        Debug__C__stop_detecting__Debug__B__Ex__DETECTING,
        Debug__C__stop_detecting__boundary,
        Debug__InitState,
        IDLE,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[22];
    State currentState;
    State history[3];
    void save_history( State compositeState, State subState );
    bool check_history( State compositeState, State subState );
    void entryaction_____DETECTING( const UMLRTMessage * msg );
    void entryaction_____Debug__C__detecting( const UMLRTMessage * msg );
    void entryaction_____Debug__C__init__Debug__A__Ac__init( const UMLRTMessage * msg );
    void entryaction_____Debug__C__init__Debug__A__En__init( const UMLRTMessage * msg );
    void entryaction_____Debug__C__init__Debug__B__Ac__init( const UMLRTMessage * msg );
    void entryaction_____Debug__C__init__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__start_detecting__Debug__A__Ac__start_detecting( const UMLRTMessage * msg );
    void entryaction_____Debug__C__start_detecting__Debug__A__En__DETECTING( const UMLRTMessage * msg );
    void entryaction_____Debug__C__start_detecting__Debug__B__Ac__start_detecting( const UMLRTMessage * msg );
    void entryaction_____Debug__C__start_detecting__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    void entryaction_____Debug__C__start_detecting__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stop_detecting__Debug__A__Ac__stop_detecting( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stop_detecting__Debug__A__En__IDLE( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stop_detecting__Debug__B__Ac__stop_detecting( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stop_detecting__Debug__B__Ex__DETECTING( const UMLRTMessage * msg );
    void entryaction_____Debug__C__stop_detecting__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__InitState( const UMLRTMessage * msg );
    void entryaction_____IDLE( const UMLRTMessage * msg );
    void exitaction_____DETECTING( const UMLRTMessage * msg );
    void exitaction_____Debug__C__detecting( const UMLRTMessage * msg );
    void exitaction_____Debug__C__init__Debug__A__Ac__init( const UMLRTMessage * msg );
    void exitaction_____Debug__C__init__Debug__A__En__init( const UMLRTMessage * msg );
    void exitaction_____Debug__C__init__Debug__B__Ac__init( const UMLRTMessage * msg );
    void exitaction_____Debug__C__init__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__start_detecting__Debug__A__Ac__start_detecting( const UMLRTMessage * msg );
    void exitaction_____Debug__C__start_detecting__Debug__A__En__DETECTING( const UMLRTMessage * msg );
    void exitaction_____Debug__C__start_detecting__Debug__B__Ac__start_detecting( const UMLRTMessage * msg );
    void exitaction_____Debug__C__start_detecting__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    void exitaction_____Debug__C__start_detecting__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stop_detecting__Debug__A__Ac__stop_detecting( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stop_detecting__Debug__A__En__IDLE( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stop_detecting__Debug__B__Ac__stop_detecting( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stop_detecting__Debug__B__Ex__DETECTING( const UMLRTMessage * msg );
    void exitaction_____Debug__C__stop_detecting__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__InitState( const UMLRTMessage * msg );
    void exitaction_____IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__init__Debug__Ac__init( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__init__Debug__En__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__init__Debug__end__trans__init( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__init__Debug__init__trans__init( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__start_detecting__Debug__AC__start_detecting( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__start_detecting__Debug__En__DETECTING( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__start_detecting__Debug__Ex__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__start_detecting__Debug__end__trans__start_detecting( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__start_detecting__Debug__init__trans__start_detecting( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stop_detecting__Debug__AC__stop_detecting( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stop_detecting__Debug__En__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stop_detecting__Debug__Ex__DETECTING( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stop_detecting__Debug__end__trans__stop_detecting( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__stop_detecting__Debug__init__trans__stop_detecting( const UMLRTMessage * msg );
    void transitionaction_____Debug__InitDebug( const UMLRTMessage * msg );
    void transitionaction_____Debug__detecting( const UMLRTMessage * msg );
    void transitionaction_____Debug__detecting__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__detecting__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__detecting__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__init( const UMLRTMessage * msg );
    void transitionaction_____Debug__init__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__init__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__init__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__start_detecting( const UMLRTMessage * msg );
    void transitionaction_____Debug__start_detecting__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__start_detecting__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__start_detecting__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__stop_detecting( const UMLRTMessage * msg );
    void transitionaction_____Debug__stop_detecting__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__stop_detecting__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__stop_detecting__dbg( const UMLRTMessage * msg );
    void transitionaction_____detecting( const UMLRTMessage * msg );
    void transitionaction_____init( const UMLRTMessage * msg );
    void transitionaction_____start_detecting( const UMLRTMessage * msg );
    void transitionaction_____stop_detecting( const UMLRTMessage * msg );
    bool action_____Debug__detecting__S__Debug__Guarddetecting( const UMLRTMessage * msg );
    bool action_____Debug__init__S__Debug__Guardinit( const UMLRTMessage * msg );
    bool action_____Debug__start_detecting__S__Debug__Guardstart_detecting( const UMLRTMessage * msg );
    bool action_____Debug__stop_detecting__S__Debug__Guardstop_detecting( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__Debug__Ac__init( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__Debug__En__IDLE( const UMLRTMessage * msg );
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
    void actionchain_____Debug__C__start_detecting__Debug__AC__start_detecting( const UMLRTMessage * msg );
    void actionchain_____Debug__C__start_detecting__Debug__En__DETECTING( const UMLRTMessage * msg );
    void actionchain_____Debug__C__start_detecting__Debug__Ex__IDLE( const UMLRTMessage * msg );
    void actionchain_____Debug__C__start_detecting__Debug__end__trans__start_detecting( const UMLRTMessage * msg );
    void actionchain_____Debug__C__start_detecting__Debug__init__trans__start_detecting( const UMLRTMessage * msg );
    void actionchain_____Debug__C__start_detecting__new_transition_1( const UMLRTMessage * msg );
    void actionchain_____Debug__C__start_detecting__new_transition_10( const UMLRTMessage * msg );
    void actionchain_____Debug__C__start_detecting__new_transition_2( const UMLRTMessage * msg );
    void actionchain_____Debug__C__start_detecting__new_transition_3( const UMLRTMessage * msg );
    void actionchain_____Debug__C__start_detecting__new_transition_4( const UMLRTMessage * msg );
    void actionchain_____Debug__C__start_detecting__new_transition_5_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__start_detecting__new_transition_6( const UMLRTMessage * msg );
    void actionchain_____Debug__C__start_detecting__new_transition_7( const UMLRTMessage * msg );
    void actionchain_____Debug__C__start_detecting__new_transition_8( const UMLRTMessage * msg );
    void actionchain_____Debug__C__start_detecting__new_transition_9( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_detecting__Debug__AC__stop_detecting( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_detecting__Debug__En__IDLE( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_detecting__Debug__Ex__DETECTING( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_detecting__Debug__end__trans__stop_detecting( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_detecting__Debug__init__trans__stop_detecting( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_detecting__new_transition_11( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_detecting__new_transition_12( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_detecting__new_transition_13( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_detecting__new_transition_14( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_detecting__new_transition_15_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_detecting__new_transition_16( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_detecting__new_transition_17( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_detecting__new_transition_18( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_detecting__new_transition_19( const UMLRTMessage * msg );
    void actionchain_____Debug__C__stop_detecting__new_transition_20( const UMLRTMessage * msg );
    void actionchain_____Debug__InitDebug( const UMLRTMessage * msg );
    void actionchain_____Debug__detecting( const UMLRTMessage * msg );
    void actionchain_____Debug__detecting__E( const UMLRTMessage * msg );
    void actionchain_____Debug__detecting__S( const UMLRTMessage * msg );
    void actionchain_____Debug__detecting__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__init( const UMLRTMessage * msg );
    void actionchain_____Debug__init__E( const UMLRTMessage * msg );
    void actionchain_____Debug__init__S( const UMLRTMessage * msg );
    void actionchain_____Debug__init__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__start_detecting( const UMLRTMessage * msg );
    void actionchain_____Debug__start_detecting__E( const UMLRTMessage * msg );
    void actionchain_____Debug__start_detecting__S( const UMLRTMessage * msg );
    void actionchain_____Debug__start_detecting__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__stop_detecting( const UMLRTMessage * msg );
    void actionchain_____Debug__stop_detecting__E( const UMLRTMessage * msg );
    void actionchain_____Debug__stop_detecting__S( const UMLRTMessage * msg );
    void actionchain_____Debug__stop_detecting__dbg( const UMLRTMessage * msg );
    void actionchain_____detecting( const UMLRTMessage * msg );
    void actionchain_____init( const UMLRTMessage * msg );
    void actionchain_____start_detecting( const UMLRTMessage * msg );
    void actionchain_____stop_detecting( const UMLRTMessage * msg );
    State junction_____Debug__C__init__en( const UMLRTMessage * msg );
    State junction_____Debug__C__init__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__init__new_exitpoint_3( const UMLRTMessage * msg );
    State junction_____Debug__C__start_detecting__en( const UMLRTMessage * msg );
    State junction_____Debug__C__start_detecting__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__start_detecting__new_exitpoint_1( const UMLRTMessage * msg );
    State junction_____Debug__C__stop_detecting__en( const UMLRTMessage * msg );
    State junction_____Debug__C__stop_detecting__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__stop_detecting__new_exitpoint_2( const UMLRTMessage * msg );
    State choice_____Debug__C__init__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__start_detecting__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__stop_detecting__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__Path__detecting( const UMLRTMessage * msg );
    State choice_____Debug__Path__init( const UMLRTMessage * msg );
    State choice_____Debug__Path__start_detecting( const UMLRTMessage * msg );
    State choice_____Debug__Path__stop_detecting( const UMLRTMessage * msg );
    State state_____DETECTING( const UMLRTMessage * msg );
    State state_____Debug__C__detecting( const UMLRTMessage * msg );
    State state_____Debug__C__init__Debug__A__Ac__init( const UMLRTMessage * msg );
    State state_____Debug__C__init__Debug__A__En__init( const UMLRTMessage * msg );
    State state_____Debug__C__init__Debug__B__Ac__init( const UMLRTMessage * msg );
    State state_____Debug__C__init__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__start_detecting__Debug__A__Ac__start_detecting( const UMLRTMessage * msg );
    State state_____Debug__C__start_detecting__Debug__A__En__DETECTING( const UMLRTMessage * msg );
    State state_____Debug__C__start_detecting__Debug__B__Ac__start_detecting( const UMLRTMessage * msg );
    State state_____Debug__C__start_detecting__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    State state_____Debug__C__start_detecting__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__stop_detecting__Debug__A__Ac__stop_detecting( const UMLRTMessage * msg );
    State state_____Debug__C__stop_detecting__Debug__A__En__IDLE( const UMLRTMessage * msg );
    State state_____Debug__C__stop_detecting__Debug__B__Ac__stop_detecting( const UMLRTMessage * msg );
    State state_____Debug__C__stop_detecting__Debug__B__Ex__DETECTING( const UMLRTMessage * msg );
    State state_____Debug__C__stop_detecting__boundary( const UMLRTMessage * msg );
    State state_____Debug__InitState( const UMLRTMessage * msg );
    State state_____IDLE( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass DetectionSensor;

#endif



#ifndef GEN_HH
#define GEN_HH

#include "ExtInterface.hh"
#include "Parcel.hh"
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

class Capsule_Gen : public UMLRTCapsule
{
public:
    Capsule_Gen( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    transmission::Base enter;
public:
    enum BorderPortId
    {
        borderport_enter,
        borderport_extComm,
        borderport_timer,
        borderport_log
    };
protected:
    ExtInterface::Conj extComm;
    UMLRTLogProtocol_baserole log;
    UMLRTTimerProtocol_baserole timer;
public:
    enum PartId
    {
    };
    enum PortId
    {
        port_enter,
        port_extComm,
        port_log,
        port_timer
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    Parcel parcel;
    int delay;
    bool successorFree;
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
        Debug__C__GENERATING__GENERATING__17,
        Debug__C__GENERATING__GENERATING__19,
        Debug__C__Initial,
        Debug__C__GENERATING__GENERATING__17__Debug__A__Ac__GENERATING__GENERATING__17,
        Debug__C__GENERATING__GENERATING__17__Debug__A__En__GENERATING,
        Debug__C__GENERATING__GENERATING__17__Debug__B__Ac__GENERATING__GENERATING__17,
        Debug__C__GENERATING__GENERATING__17__Debug__B__Ex__GENERATING,
        Debug__C__GENERATING__GENERATING__17__boundary,
        Debug__C__GENERATING__GENERATING__19__Debug__A__Ac__GENERATING__GENERATING__19,
        Debug__C__GENERATING__GENERATING__19__Debug__A__En__GENERATING,
        Debug__C__GENERATING__GENERATING__19__Debug__B__Ac__GENERATING__GENERATING__19,
        Debug__C__GENERATING__GENERATING__19__Debug__B__Ex__GENERATING,
        Debug__C__GENERATING__GENERATING__19__boundary,
        Debug__C__Initial__Debug__A__Ac__Initial,
        Debug__C__Initial__Debug__A__En__Initial,
        Debug__C__Initial__Debug__B__Ac__Initial,
        Debug__C__Initial__boundary,
        Debug__InitState,
        GENERATING,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[20];
    State currentState;
    State history[3];
    void save_history( State compositeState, State subState );
    bool check_history( State compositeState, State subState );
    void entryaction_____Debug__C__GENERATING__GENERATING__17__Debug__A__Ac__GENERATING__GENERATING__17( const UMLRTMessage * msg );
    void entryaction_____Debug__C__GENERATING__GENERATING__17__Debug__A__En__GENERATING( const UMLRTMessage * msg );
    void entryaction_____Debug__C__GENERATING__GENERATING__17__Debug__B__Ac__GENERATING__GENERATING__17( const UMLRTMessage * msg );
    void entryaction_____Debug__C__GENERATING__GENERATING__17__Debug__B__Ex__GENERATING( const UMLRTMessage * msg );
    void entryaction_____Debug__C__GENERATING__GENERATING__17__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__GENERATING__GENERATING__19__Debug__A__Ac__GENERATING__GENERATING__19( const UMLRTMessage * msg );
    void entryaction_____Debug__C__GENERATING__GENERATING__19__Debug__A__En__GENERATING( const UMLRTMessage * msg );
    void entryaction_____Debug__C__GENERATING__GENERATING__19__Debug__B__Ac__GENERATING__GENERATING__19( const UMLRTMessage * msg );
    void entryaction_____Debug__C__GENERATING__GENERATING__19__Debug__B__Ex__GENERATING( const UMLRTMessage * msg );
    void entryaction_____Debug__C__GENERATING__GENERATING__19__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Initial__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__InitState( const UMLRTMessage * msg );
    void entryaction_____GENERATING( const UMLRTMessage * msg );
    void exitaction_____Debug__C__GENERATING__GENERATING__17__Debug__A__Ac__GENERATING__GENERATING__17( const UMLRTMessage * msg );
    void exitaction_____Debug__C__GENERATING__GENERATING__17__Debug__A__En__GENERATING( const UMLRTMessage * msg );
    void exitaction_____Debug__C__GENERATING__GENERATING__17__Debug__B__Ac__GENERATING__GENERATING__17( const UMLRTMessage * msg );
    void exitaction_____Debug__C__GENERATING__GENERATING__17__Debug__B__Ex__GENERATING( const UMLRTMessage * msg );
    void exitaction_____Debug__C__GENERATING__GENERATING__17__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__GENERATING__GENERATING__19__Debug__A__Ac__GENERATING__GENERATING__19( const UMLRTMessage * msg );
    void exitaction_____Debug__C__GENERATING__GENERATING__19__Debug__A__En__GENERATING( const UMLRTMessage * msg );
    void exitaction_____Debug__C__GENERATING__GENERATING__19__Debug__B__Ac__GENERATING__GENERATING__19( const UMLRTMessage * msg );
    void exitaction_____Debug__C__GENERATING__GENERATING__19__Debug__B__Ex__GENERATING( const UMLRTMessage * msg );
    void exitaction_____Debug__C__GENERATING__GENERATING__19__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__InitState( const UMLRTMessage * msg );
    void exitaction_____GENERATING( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__GENERATING__GENERATING__17__Debug__AC__GENERATING__GENERATING__17( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__GENERATING__GENERATING__17__Debug__En__GENERATING( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__GENERATING__GENERATING__17__Debug__Ex__GENERATING( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__GENERATING__GENERATING__17__Debug__end__trans__GENERATING__GENERATING__17( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__GENERATING__GENERATING__17__Debug__init__trans__GENERATING__GENERATING__17( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__GENERATING__GENERATING__19__Debug__AC__GENERATING__GENERATING__19( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__GENERATING__GENERATING__19__Debug__En__GENERATING( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__GENERATING__GENERATING__19__Debug__Ex__GENERATING( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__GENERATING__GENERATING__19__Debug__end__trans__GENERATING__GENERATING__19( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__GENERATING__GENERATING__19__Debug__init__trans__GENERATING__GENERATING__19( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial__Debug__Ac__Initial( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial__Debug__En__GENERATING( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial__Debug__end__trans__Initial( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial__Debug__init__trans__Initial( const UMLRTMessage * msg );
    void transitionaction_____Debug__GENERATING__GENERATING__17( const UMLRTMessage * msg );
    void transitionaction_____Debug__GENERATING__GENERATING__17__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__GENERATING__GENERATING__17__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__GENERATING__GENERATING__17__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__GENERATING__GENERATING__19( const UMLRTMessage * msg );
    void transitionaction_____Debug__GENERATING__GENERATING__19__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__GENERATING__GENERATING__19__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__GENERATING__GENERATING__19__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__InitDebug( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial__dbg( const UMLRTMessage * msg );
    void transitionaction_____GENERATING__GENERATING__17( const UMLRTMessage * msg );
    void transitionaction_____GENERATING__GENERATING__19( const UMLRTMessage * msg );
    void transitionaction_____Initial( const UMLRTMessage * msg );
    bool action_____Debug__GENERATING__GENERATING__17__S__Debug__GuardGENERATING__GENERATING__17( const UMLRTMessage * msg );
    bool action_____Debug__GENERATING__GENERATING__19__S__Debug__GuardGENERATING__GENERATING__19( const UMLRTMessage * msg );
    bool action_____Debug__Initial__S__Debug__GuardInitial( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__17__Debug__AC__GENERATING__GENERATING__17( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__17__Debug__En__GENERATING( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__17__Debug__Ex__GENERATING( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__17__Debug__end__trans__GENERATING__GENERATING__17( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__17__Debug__init__trans__GENERATING__GENERATING__17( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__17__new_transition_1( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__17__new_transition_10( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__17__new_transition_2( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__17__new_transition_3( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__17__new_transition_4( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__17__new_transition_5_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__17__new_transition_6( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__17__new_transition_7( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__17__new_transition_8( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__17__new_transition_9( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__19__Debug__AC__GENERATING__GENERATING__19( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__19__Debug__En__GENERATING( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__19__Debug__Ex__GENERATING( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__19__Debug__end__trans__GENERATING__GENERATING__19( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__19__Debug__init__trans__GENERATING__GENERATING__19( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__19__new_transition_19( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__19__new_transition_20( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__19__new_transition_21( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__19__new_transition_22( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__19__new_transition_23_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__19__new_transition_24( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__19__new_transition_25( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__19__new_transition_26( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__19__new_transition_27( const UMLRTMessage * msg );
    void actionchain_____Debug__C__GENERATING__GENERATING__19__new_transition_28( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__Debug__Ac__Initial( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__Debug__En__GENERATING( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__Debug__end__trans__Initial( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__Debug__init__trans__Initial( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_11( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_12( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_13( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_14_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_15( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_16( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_17( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial__new_transition_18( const UMLRTMessage * msg );
    void actionchain_____Debug__GENERATING__GENERATING__17( const UMLRTMessage * msg );
    void actionchain_____Debug__GENERATING__GENERATING__17__E( const UMLRTMessage * msg );
    void actionchain_____Debug__GENERATING__GENERATING__17__S( const UMLRTMessage * msg );
    void actionchain_____Debug__GENERATING__GENERATING__17__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__GENERATING__GENERATING__19( const UMLRTMessage * msg );
    void actionchain_____Debug__GENERATING__GENERATING__19__E( const UMLRTMessage * msg );
    void actionchain_____Debug__GENERATING__GENERATING__19__S( const UMLRTMessage * msg );
    void actionchain_____Debug__GENERATING__GENERATING__19__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__InitDebug( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial__E( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial__S( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial__dbg( const UMLRTMessage * msg );
    void actionchain_____GENERATING__GENERATING__17( const UMLRTMessage * msg );
    void actionchain_____GENERATING__GENERATING__19( const UMLRTMessage * msg );
    void actionchain_____Initial( const UMLRTMessage * msg );
    State junction_____Debug__C__GENERATING__GENERATING__17__en( const UMLRTMessage * msg );
    State junction_____Debug__C__GENERATING__GENERATING__17__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__GENERATING__GENERATING__17__new_exitpoint_1( const UMLRTMessage * msg );
    State junction_____Debug__C__GENERATING__GENERATING__19__en( const UMLRTMessage * msg );
    State junction_____Debug__C__GENERATING__GENERATING__19__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__GENERATING__GENERATING__19__new_exitpoint_3( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__en( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__new_exitpoint_2( const UMLRTMessage * msg );
    State choice_____Debug__C__GENERATING__GENERATING__17__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__GENERATING__GENERATING__19__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__Initial__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__Path__GENERATING__GENERATING__17( const UMLRTMessage * msg );
    State choice_____Debug__Path__GENERATING__GENERATING__19( const UMLRTMessage * msg );
    State choice_____Debug__Path__Initial( const UMLRTMessage * msg );
    State state_____Debug__C__GENERATING__GENERATING__17__Debug__A__Ac__GENERATING__GENERATING__17( const UMLRTMessage * msg );
    State state_____Debug__C__GENERATING__GENERATING__17__Debug__A__En__GENERATING( const UMLRTMessage * msg );
    State state_____Debug__C__GENERATING__GENERATING__17__Debug__B__Ac__GENERATING__GENERATING__17( const UMLRTMessage * msg );
    State state_____Debug__C__GENERATING__GENERATING__17__Debug__B__Ex__GENERATING( const UMLRTMessage * msg );
    State state_____Debug__C__GENERATING__GENERATING__17__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__GENERATING__GENERATING__19__Debug__A__Ac__GENERATING__GENERATING__19( const UMLRTMessage * msg );
    State state_____Debug__C__GENERATING__GENERATING__19__Debug__A__En__GENERATING( const UMLRTMessage * msg );
    State state_____Debug__C__GENERATING__GENERATING__19__Debug__B__Ac__GENERATING__GENERATING__19( const UMLRTMessage * msg );
    State state_____Debug__C__GENERATING__GENERATING__19__Debug__B__Ex__GENERATING( const UMLRTMessage * msg );
    State state_____Debug__C__GENERATING__GENERATING__19__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg );
    State state_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg );
    State state_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg );
    State state_____Debug__C__Initial__boundary( const UMLRTMessage * msg );
    State state_____Debug__InitState( const UMLRTMessage * msg );
    State state_____GENERATING( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass Gen;

#endif


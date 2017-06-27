
#ifndef BIN_HH
#define BIN_HH

#include "ExtInterface.hh"
#include "Parcel.hh"
#include "transmission.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtlogprotocol.hh"
#include "umlrtmessage.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

#include "Event.h"

#include "SROManager.h"

class Capsule_Bin : public UMLRTCapsule
{
public:
    Capsule_Bin( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    transmission::Conj enter;
public:
    enum BorderPortId
    {
        borderport_enter,
        borderport_extComm,
        borderport_log
    };
protected:
    ExtInterface::Conj extComm;
    UMLRTLogProtocol_baserole log;
public:
    enum PartId
    {
    };
    enum PortId
    {
        port_enter,
        port_extComm,
        port_log
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    Parcel parcels;
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
        Debug__C__IDLE__IDLE__8,
        Debug__C__Initial,
        Debug__C__IDLE__IDLE__8__Debug__A__Ac__IDLE__IDLE__8,
        Debug__C__IDLE__IDLE__8__Debug__A__En__IDLE,
        Debug__C__IDLE__IDLE__8__Debug__B__Ac__IDLE__IDLE__8,
        Debug__C__IDLE__IDLE__8__Debug__B__Ex__IDLE,
        Debug__C__IDLE__IDLE__8__boundary,
        Debug__C__Initial__Debug__A__Ac__Initial,
        Debug__C__Initial__Debug__A__En__Initial,
        Debug__C__Initial__Debug__B__Ac__Initial,
        Debug__C__Initial__boundary,
        Debug__InitState,
        IDLE,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[14];
    State currentState;
    State history[2];
    void save_history( State compositeState, State subState );
    bool check_history( State compositeState, State subState );
    void entryaction_____Debug__C__IDLE__IDLE__8__Debug__A__Ac__IDLE__IDLE__8( const UMLRTMessage * msg );
    void entryaction_____Debug__C__IDLE__IDLE__8__Debug__A__En__IDLE( const UMLRTMessage * msg );
    void entryaction_____Debug__C__IDLE__IDLE__8__Debug__B__Ac__IDLE__IDLE__8( const UMLRTMessage * msg );
    void entryaction_____Debug__C__IDLE__IDLE__8__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    void entryaction_____Debug__C__IDLE__IDLE__8__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Initial__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__InitState( const UMLRTMessage * msg );
    void entryaction_____IDLE( const UMLRTMessage * msg );
    void exitaction_____Debug__C__IDLE__IDLE__8__Debug__A__Ac__IDLE__IDLE__8( const UMLRTMessage * msg );
    void exitaction_____Debug__C__IDLE__IDLE__8__Debug__A__En__IDLE( const UMLRTMessage * msg );
    void exitaction_____Debug__C__IDLE__IDLE__8__Debug__B__Ac__IDLE__IDLE__8( const UMLRTMessage * msg );
    void exitaction_____Debug__C__IDLE__IDLE__8__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    void exitaction_____Debug__C__IDLE__IDLE__8__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__InitState( const UMLRTMessage * msg );
    void exitaction_____IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__IDLE__IDLE__8__Debug__AC__IDLE__IDLE__8( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__IDLE__IDLE__8__Debug__En__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__IDLE__IDLE__8__Debug__Ex__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__IDLE__IDLE__8__Debug__end__trans__IDLE__IDLE__8( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__IDLE__IDLE__8__Debug__init__trans__IDLE__IDLE__8( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial__Debug__Ac__Initial( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial__Debug__En__IDLE( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial__Debug__end__trans__Initial( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial__Debug__init__trans__Initial( const UMLRTMessage * msg );
    void transitionaction_____Debug__IDLE__IDLE__8( const UMLRTMessage * msg );
    void transitionaction_____Debug__IDLE__IDLE__8__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__IDLE__IDLE__8__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__IDLE__IDLE__8__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__InitDebug( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial__dbg( const UMLRTMessage * msg );
    void transitionaction_____IDLE__IDLE__8( const UMLRTMessage * msg );
    void transitionaction_____Initial( const UMLRTMessage * msg );
    bool action_____Debug__IDLE__IDLE__8__S__Debug__GuardIDLE__IDLE__8( const UMLRTMessage * msg );
    bool action_____Debug__Initial__S__Debug__GuardInitial( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__8__Debug__AC__IDLE__IDLE__8( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__8__Debug__En__IDLE( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__8__Debug__Ex__IDLE( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__8__Debug__end__trans__IDLE__IDLE__8( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__8__Debug__init__trans__IDLE__IDLE__8( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__8__new_transition_10( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__8__new_transition_11( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__8__new_transition_12( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__8__new_transition_13_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__8__new_transition_14( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__8__new_transition_15( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__8__new_transition_16( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__8__new_transition_17( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__8__new_transition_18( const UMLRTMessage * msg );
    void actionchain_____Debug__C__IDLE__IDLE__8__new_transition_9( const UMLRTMessage * msg );
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
    void actionchain_____Debug__IDLE__IDLE__8( const UMLRTMessage * msg );
    void actionchain_____Debug__IDLE__IDLE__8__E( const UMLRTMessage * msg );
    void actionchain_____Debug__IDLE__IDLE__8__S( const UMLRTMessage * msg );
    void actionchain_____Debug__IDLE__IDLE__8__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__InitDebug( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial__E( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial__S( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial__dbg( const UMLRTMessage * msg );
    void actionchain_____IDLE__IDLE__8( const UMLRTMessage * msg );
    void actionchain_____Initial( const UMLRTMessage * msg );
    State junction_____Debug__C__IDLE__IDLE__8__en( const UMLRTMessage * msg );
    State junction_____Debug__C__IDLE__IDLE__8__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__IDLE__IDLE__8__new_exitpoint_2( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__en( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial__new_exitpoint_1( const UMLRTMessage * msg );
    State choice_____Debug__C__IDLE__IDLE__8__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__Initial__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__Path__IDLE__IDLE__8( const UMLRTMessage * msg );
    State choice_____Debug__Path__Initial( const UMLRTMessage * msg );
    State state_____Debug__C__IDLE__IDLE__8__Debug__A__Ac__IDLE__IDLE__8( const UMLRTMessage * msg );
    State state_____Debug__C__IDLE__IDLE__8__Debug__A__En__IDLE( const UMLRTMessage * msg );
    State state_____Debug__C__IDLE__IDLE__8__Debug__B__Ac__IDLE__IDLE__8( const UMLRTMessage * msg );
    State state_____Debug__C__IDLE__IDLE__8__Debug__B__Ex__IDLE( const UMLRTMessage * msg );
    State state_____Debug__C__IDLE__IDLE__8__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__Initial__Debug__A__Ac__Initial( const UMLRTMessage * msg );
    State state_____Debug__C__Initial__Debug__A__En__Initial( const UMLRTMessage * msg );
    State state_____Debug__C__Initial__Debug__B__Ac__Initial( const UMLRTMessage * msg );
    State state_____Debug__C__Initial__boundary( const UMLRTMessage * msg );
    State state_____Debug__InitState( const UMLRTMessage * msg );
    State state_____IDLE( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass Bin;

#endif


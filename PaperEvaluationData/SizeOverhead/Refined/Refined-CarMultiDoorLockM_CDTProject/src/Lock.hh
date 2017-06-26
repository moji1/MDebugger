
#ifndef LOCK_HH
#define LOCK_HH

#include "ExtInterface.hh"
#include "Locking.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtmessage.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

#include<stdio.h>
#include<iostream>
#include "Event.h"

#include "SROManager.h"

class Capsule_Lock : public UMLRTCapsule
{
public:
    Capsule_Lock( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
    enum BorderPortId
    {
        borderport_lockPort,
        borderport_extComm
    };
protected:
    ExtInterface::Conj extComm;
    Locking::Base lockPort;
public:
    enum PartId
    {
    };
    enum PortId
    {
        port_extComm,
        port_lockPort
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
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
        Debug__C__lock,
        Debug__C__twiceLock,
        Debug__C__twiceUnlock,
        Debug__C__unlock,
        Debug__C__init__Debug__A__Ac__init,
        Debug__C__init__Debug__A__En__init,
        Debug__C__init__Debug__B__Ac__init,
        Debug__C__init__boundary,
        Debug__C__lock__Debug__A__Ac__lock,
        Debug__C__lock__Debug__A__En__locked,
        Debug__C__lock__Debug__B__Ac__lock,
        Debug__C__lock__Debug__B__Ex__unlocked,
        Debug__C__lock__boundary,
        Debug__C__twiceLock__Debug__A__Ac__twiceLock,
        Debug__C__twiceLock__Debug__A__En__locked,
        Debug__C__twiceLock__Debug__B__Ac__twiceLock,
        Debug__C__twiceLock__Debug__B__Ex__locked,
        Debug__C__twiceLock__boundary,
        Debug__C__twiceUnlock__Debug__A__Ac__twiceUnlock,
        Debug__C__twiceUnlock__Debug__A__En__unlocked,
        Debug__C__twiceUnlock__Debug__B__Ac__twiceUnlock,
        Debug__C__twiceUnlock__Debug__B__Ex__unlocked,
        Debug__C__twiceUnlock__boundary,
        Debug__C__unlock__Debug__A__Ac__unlock,
        Debug__C__unlock__Debug__A__En__unlocked,
        Debug__C__unlock__Debug__B__Ac__unlock,
        Debug__C__unlock__Debug__B__Ex__locked,
        Debug__C__unlock__boundary,
        Debug__InitState,
        locked,
        unlocked,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[33];
    State currentState;
    State history[5];
    void save_history( State compositeState, State subState );
    bool check_history( State compositeState, State subState );
    void entryaction_____Debug__C__init__Debug__A__Ac__init( const UMLRTMessage * msg );
    void entryaction_____Debug__C__init__Debug__A__En__init( const UMLRTMessage * msg );
    void entryaction_____Debug__C__init__Debug__B__Ac__init( const UMLRTMessage * msg );
    void entryaction_____Debug__C__init__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__lock__Debug__A__Ac__lock( const UMLRTMessage * msg );
    void entryaction_____Debug__C__lock__Debug__A__En__locked( const UMLRTMessage * msg );
    void entryaction_____Debug__C__lock__Debug__B__Ac__lock( const UMLRTMessage * msg );
    void entryaction_____Debug__C__lock__Debug__B__Ex__unlocked( const UMLRTMessage * msg );
    void entryaction_____Debug__C__lock__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__twiceLock__Debug__A__Ac__twiceLock( const UMLRTMessage * msg );
    void entryaction_____Debug__C__twiceLock__Debug__A__En__locked( const UMLRTMessage * msg );
    void entryaction_____Debug__C__twiceLock__Debug__B__Ac__twiceLock( const UMLRTMessage * msg );
    void entryaction_____Debug__C__twiceLock__Debug__B__Ex__locked( const UMLRTMessage * msg );
    void entryaction_____Debug__C__twiceLock__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__twiceUnlock__Debug__A__Ac__twiceUnlock( const UMLRTMessage * msg );
    void entryaction_____Debug__C__twiceUnlock__Debug__A__En__unlocked( const UMLRTMessage * msg );
    void entryaction_____Debug__C__twiceUnlock__Debug__B__Ac__twiceUnlock( const UMLRTMessage * msg );
    void entryaction_____Debug__C__twiceUnlock__Debug__B__Ex__unlocked( const UMLRTMessage * msg );
    void entryaction_____Debug__C__twiceUnlock__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__unlock__Debug__A__Ac__unlock( const UMLRTMessage * msg );
    void entryaction_____Debug__C__unlock__Debug__A__En__unlocked( const UMLRTMessage * msg );
    void entryaction_____Debug__C__unlock__Debug__B__Ac__unlock( const UMLRTMessage * msg );
    void entryaction_____Debug__C__unlock__Debug__B__Ex__locked( const UMLRTMessage * msg );
    void entryaction_____Debug__C__unlock__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__InitState( const UMLRTMessage * msg );
    void entryaction_____locked( const UMLRTMessage * msg );
    void entryaction_____unlocked( const UMLRTMessage * msg );
    void exitaction_____Debug__C__init__Debug__A__Ac__init( const UMLRTMessage * msg );
    void exitaction_____Debug__C__init__Debug__A__En__init( const UMLRTMessage * msg );
    void exitaction_____Debug__C__init__Debug__B__Ac__init( const UMLRTMessage * msg );
    void exitaction_____Debug__C__init__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__lock__Debug__A__Ac__lock( const UMLRTMessage * msg );
    void exitaction_____Debug__C__lock__Debug__A__En__locked( const UMLRTMessage * msg );
    void exitaction_____Debug__C__lock__Debug__B__Ac__lock( const UMLRTMessage * msg );
    void exitaction_____Debug__C__lock__Debug__B__Ex__unlocked( const UMLRTMessage * msg );
    void exitaction_____Debug__C__lock__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__twiceLock__Debug__A__Ac__twiceLock( const UMLRTMessage * msg );
    void exitaction_____Debug__C__twiceLock__Debug__A__En__locked( const UMLRTMessage * msg );
    void exitaction_____Debug__C__twiceLock__Debug__B__Ac__twiceLock( const UMLRTMessage * msg );
    void exitaction_____Debug__C__twiceLock__Debug__B__Ex__locked( const UMLRTMessage * msg );
    void exitaction_____Debug__C__twiceLock__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__twiceUnlock__Debug__A__Ac__twiceUnlock( const UMLRTMessage * msg );
    void exitaction_____Debug__C__twiceUnlock__Debug__A__En__unlocked( const UMLRTMessage * msg );
    void exitaction_____Debug__C__twiceUnlock__Debug__B__Ac__twiceUnlock( const UMLRTMessage * msg );
    void exitaction_____Debug__C__twiceUnlock__Debug__B__Ex__unlocked( const UMLRTMessage * msg );
    void exitaction_____Debug__C__twiceUnlock__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__unlock__Debug__A__Ac__unlock( const UMLRTMessage * msg );
    void exitaction_____Debug__C__unlock__Debug__A__En__unlocked( const UMLRTMessage * msg );
    void exitaction_____Debug__C__unlock__Debug__B__Ac__unlock( const UMLRTMessage * msg );
    void exitaction_____Debug__C__unlock__Debug__B__Ex__locked( const UMLRTMessage * msg );
    void exitaction_____Debug__C__unlock__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__InitState( const UMLRTMessage * msg );
    void exitaction_____locked( const UMLRTMessage * msg );
    void exitaction_____unlocked( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__init__Debug__Ac__init( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__init__Debug__En__unlocked( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__init__Debug__end__trans__init( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__init__Debug__init__trans__init( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__lock__Debug__AC__lock( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__lock__Debug__En__locked( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__lock__Debug__Ex__unlocked( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__lock__Debug__end__trans__lock( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__lock__Debug__init__trans__lock( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__twiceLock__Debug__AC__twiceLock( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__twiceLock__Debug__En__locked( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__twiceLock__Debug__Ex__locked( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__twiceLock__Debug__end__trans__twiceLock( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__twiceLock__Debug__init__trans__twiceLock( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__twiceUnlock__Debug__AC__twiceUnlock( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__twiceUnlock__Debug__En__unlocked( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__twiceUnlock__Debug__Ex__unlocked( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__twiceUnlock__Debug__end__trans__twiceUnlock( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__twiceUnlock__Debug__init__trans__twiceUnlock( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__unlock__Debug__AC__unlock( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__unlock__Debug__En__unlocked( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__unlock__Debug__Ex__locked( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__unlock__Debug__end__trans__unlock( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__unlock__Debug__init__trans__unlock( const UMLRTMessage * msg );
    void transitionaction_____Debug__InitDebug( const UMLRTMessage * msg );
    void transitionaction_____Debug__init( const UMLRTMessage * msg );
    void transitionaction_____Debug__init__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__init__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__init__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__lock( const UMLRTMessage * msg );
    void transitionaction_____Debug__lock__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__lock__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__lock__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__twiceLock( const UMLRTMessage * msg );
    void transitionaction_____Debug__twiceLock__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__twiceLock__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__twiceLock__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__twiceUnlock( const UMLRTMessage * msg );
    void transitionaction_____Debug__twiceUnlock__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__twiceUnlock__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__twiceUnlock__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__unlock( const UMLRTMessage * msg );
    void transitionaction_____Debug__unlock__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__unlock__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__unlock__dbg( const UMLRTMessage * msg );
    void transitionaction_____init( const UMLRTMessage * msg );
    void transitionaction_____lock( const UMLRTMessage * msg );
    void transitionaction_____twiceLock( const UMLRTMessage * msg );
    void transitionaction_____twiceUnlock( const UMLRTMessage * msg );
    void transitionaction_____unlock( const UMLRTMessage * msg );
    bool action_____Debug__init__S__Debug__Guardinit( const UMLRTMessage * msg );
    bool action_____Debug__lock__S__Debug__Guardlock( const UMLRTMessage * msg );
    bool action_____Debug__twiceLock__S__Debug__GuardtwiceLock( const UMLRTMessage * msg );
    bool action_____Debug__twiceUnlock__S__Debug__GuardtwiceUnlock( const UMLRTMessage * msg );
    bool action_____Debug__unlock__S__Debug__Guardunlock( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__Debug__Ac__init( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__Debug__En__unlocked( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__Debug__end__trans__init( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__Debug__init__trans__init( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__new_transition_41( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__new_transition_42( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__new_transition_43( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__new_transition_44_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__new_transition_45( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__new_transition_46( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__new_transition_47( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__new_transition_48( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lock__Debug__AC__lock( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lock__Debug__En__locked( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lock__Debug__Ex__unlocked( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lock__Debug__end__trans__lock( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lock__Debug__init__trans__lock( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lock__new_transition_1( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lock__new_transition_10( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lock__new_transition_2( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lock__new_transition_3( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lock__new_transition_4( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lock__new_transition_5_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lock__new_transition_6( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lock__new_transition_7( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lock__new_transition_8( const UMLRTMessage * msg );
    void actionchain_____Debug__C__lock__new_transition_9( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceLock__Debug__AC__twiceLock( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceLock__Debug__En__locked( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceLock__Debug__Ex__locked( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceLock__Debug__end__trans__twiceLock( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceLock__Debug__init__trans__twiceLock( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceLock__new_transition_21( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceLock__new_transition_22( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceLock__new_transition_23( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceLock__new_transition_24( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceLock__new_transition_25_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceLock__new_transition_26( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceLock__new_transition_27( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceLock__new_transition_28( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceLock__new_transition_29( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceLock__new_transition_30( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceUnlock__Debug__AC__twiceUnlock( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceUnlock__Debug__En__unlocked( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceUnlock__Debug__Ex__unlocked( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceUnlock__Debug__end__trans__twiceUnlock( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceUnlock__Debug__init__trans__twiceUnlock( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceUnlock__new_transition_31( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceUnlock__new_transition_32( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceUnlock__new_transition_33( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceUnlock__new_transition_34( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceUnlock__new_transition_35_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceUnlock__new_transition_36( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceUnlock__new_transition_37( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceUnlock__new_transition_38( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceUnlock__new_transition_39( const UMLRTMessage * msg );
    void actionchain_____Debug__C__twiceUnlock__new_transition_40( const UMLRTMessage * msg );
    void actionchain_____Debug__C__unlock__Debug__AC__unlock( const UMLRTMessage * msg );
    void actionchain_____Debug__C__unlock__Debug__En__unlocked( const UMLRTMessage * msg );
    void actionchain_____Debug__C__unlock__Debug__Ex__locked( const UMLRTMessage * msg );
    void actionchain_____Debug__C__unlock__Debug__end__trans__unlock( const UMLRTMessage * msg );
    void actionchain_____Debug__C__unlock__Debug__init__trans__unlock( const UMLRTMessage * msg );
    void actionchain_____Debug__C__unlock__new_transition_11( const UMLRTMessage * msg );
    void actionchain_____Debug__C__unlock__new_transition_12( const UMLRTMessage * msg );
    void actionchain_____Debug__C__unlock__new_transition_13( const UMLRTMessage * msg );
    void actionchain_____Debug__C__unlock__new_transition_14( const UMLRTMessage * msg );
    void actionchain_____Debug__C__unlock__new_transition_15_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__unlock__new_transition_16( const UMLRTMessage * msg );
    void actionchain_____Debug__C__unlock__new_transition_17( const UMLRTMessage * msg );
    void actionchain_____Debug__C__unlock__new_transition_18( const UMLRTMessage * msg );
    void actionchain_____Debug__C__unlock__new_transition_19( const UMLRTMessage * msg );
    void actionchain_____Debug__C__unlock__new_transition_20( const UMLRTMessage * msg );
    void actionchain_____Debug__InitDebug( const UMLRTMessage * msg );
    void actionchain_____Debug__init( const UMLRTMessage * msg );
    void actionchain_____Debug__init__E( const UMLRTMessage * msg );
    void actionchain_____Debug__init__S( const UMLRTMessage * msg );
    void actionchain_____Debug__init__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__lock( const UMLRTMessage * msg );
    void actionchain_____Debug__lock__E( const UMLRTMessage * msg );
    void actionchain_____Debug__lock__S( const UMLRTMessage * msg );
    void actionchain_____Debug__lock__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__twiceLock( const UMLRTMessage * msg );
    void actionchain_____Debug__twiceLock__E( const UMLRTMessage * msg );
    void actionchain_____Debug__twiceLock__S( const UMLRTMessage * msg );
    void actionchain_____Debug__twiceLock__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__twiceUnlock( const UMLRTMessage * msg );
    void actionchain_____Debug__twiceUnlock__E( const UMLRTMessage * msg );
    void actionchain_____Debug__twiceUnlock__S( const UMLRTMessage * msg );
    void actionchain_____Debug__twiceUnlock__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__unlock( const UMLRTMessage * msg );
    void actionchain_____Debug__unlock__E( const UMLRTMessage * msg );
    void actionchain_____Debug__unlock__S( const UMLRTMessage * msg );
    void actionchain_____Debug__unlock__dbg( const UMLRTMessage * msg );
    void actionchain_____init( const UMLRTMessage * msg );
    void actionchain_____lock( const UMLRTMessage * msg );
    void actionchain_____twiceLock( const UMLRTMessage * msg );
    void actionchain_____twiceUnlock( const UMLRTMessage * msg );
    void actionchain_____unlock( const UMLRTMessage * msg );
    State junction_____Debug__C__init__en( const UMLRTMessage * msg );
    State junction_____Debug__C__init__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__init__new_exitpoint_5( const UMLRTMessage * msg );
    State junction_____Debug__C__lock__en( const UMLRTMessage * msg );
    State junction_____Debug__C__lock__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__lock__new_exitpoint_1( const UMLRTMessage * msg );
    State junction_____Debug__C__twiceLock__en( const UMLRTMessage * msg );
    State junction_____Debug__C__twiceLock__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__twiceLock__new_exitpoint_3( const UMLRTMessage * msg );
    State junction_____Debug__C__twiceUnlock__en( const UMLRTMessage * msg );
    State junction_____Debug__C__twiceUnlock__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__twiceUnlock__new_exitpoint_4( const UMLRTMessage * msg );
    State junction_____Debug__C__unlock__en( const UMLRTMessage * msg );
    State junction_____Debug__C__unlock__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__unlock__new_exitpoint_2( const UMLRTMessage * msg );
    State choice_____Debug__C__init__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__lock__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__twiceLock__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__twiceUnlock__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__unlock__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__Path__init( const UMLRTMessage * msg );
    State choice_____Debug__Path__lock( const UMLRTMessage * msg );
    State choice_____Debug__Path__twiceLock( const UMLRTMessage * msg );
    State choice_____Debug__Path__twiceUnlock( const UMLRTMessage * msg );
    State choice_____Debug__Path__unlock( const UMLRTMessage * msg );
    State state_____Debug__C__init__Debug__A__Ac__init( const UMLRTMessage * msg );
    State state_____Debug__C__init__Debug__A__En__init( const UMLRTMessage * msg );
    State state_____Debug__C__init__Debug__B__Ac__init( const UMLRTMessage * msg );
    State state_____Debug__C__init__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__lock__Debug__A__Ac__lock( const UMLRTMessage * msg );
    State state_____Debug__C__lock__Debug__A__En__locked( const UMLRTMessage * msg );
    State state_____Debug__C__lock__Debug__B__Ac__lock( const UMLRTMessage * msg );
    State state_____Debug__C__lock__Debug__B__Ex__unlocked( const UMLRTMessage * msg );
    State state_____Debug__C__lock__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__twiceLock__Debug__A__Ac__twiceLock( const UMLRTMessage * msg );
    State state_____Debug__C__twiceLock__Debug__A__En__locked( const UMLRTMessage * msg );
    State state_____Debug__C__twiceLock__Debug__B__Ac__twiceLock( const UMLRTMessage * msg );
    State state_____Debug__C__twiceLock__Debug__B__Ex__locked( const UMLRTMessage * msg );
    State state_____Debug__C__twiceLock__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__twiceUnlock__Debug__A__Ac__twiceUnlock( const UMLRTMessage * msg );
    State state_____Debug__C__twiceUnlock__Debug__A__En__unlocked( const UMLRTMessage * msg );
    State state_____Debug__C__twiceUnlock__Debug__B__Ac__twiceUnlock( const UMLRTMessage * msg );
    State state_____Debug__C__twiceUnlock__Debug__B__Ex__unlocked( const UMLRTMessage * msg );
    State state_____Debug__C__twiceUnlock__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__unlock__Debug__A__Ac__unlock( const UMLRTMessage * msg );
    State state_____Debug__C__unlock__Debug__A__En__unlocked( const UMLRTMessage * msg );
    State state_____Debug__C__unlock__Debug__B__Ac__unlock( const UMLRTMessage * msg );
    State state_____Debug__C__unlock__Debug__B__Ex__locked( const UMLRTMessage * msg );
    State state_____Debug__C__unlock__boundary( const UMLRTMessage * msg );
    State state_____Debug__InitState( const UMLRTMessage * msg );
    State state_____locked( const UMLRTMessage * msg );
    State state_____unlocked( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass Lock;

#endif



#ifndef CENTRALLOCK_HH
#define CENTRALLOCK_HH

#include "ExtInterface.hh"
#include "Locking.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtmessage.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

#include<stdio.h>
#include<iostream>


#include "Event.h"

#include "SROManager.h"

class Capsule_CentralLock : public UMLRTCapsule
{
public:
    Capsule_CentralLock( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    ExtInterface::Conj extComm;
public:
    enum BorderPortId
    {
        borderport_extComm,
        borderport_lockPort,
        borderport_startupTimer
    };
protected:
    Locking::Conj lockPort;
    UMLRTTimerProtocol_baserole startupTimer;
public:
    enum PartId
    {
    };
    enum PortId
    {
        port_extComm,
        port_lockPort,
        port_startupTimer
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    int tmpInt;
    int locksCount;
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
        Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8,
        Debug__C__AllDoorClosed__doorsClosed__1,
        Debug__C__Choice1__WaitAllDoorBeOpened__7,
        Debug__C__Choice1__doorsOpen__5,
        Debug__C__Initial1__StartingUp__3,
        Debug__C__StartingUp__doorsOpen__10,
        Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9,
        Debug__C__WaitAllDoorBeOpened__Choice1__6,
        Debug__C__doorsClosed__WaitAllDoorBeOpened__4,
        Debug__C__doorsOpen__WaitAllDoorBeClosed__2,
        Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__Ac__AllDoorClosed__WaitAllDoorBeClosed__8,
        Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__En__AllDoorClosed__WaitAllDoorBeClosed__8,
        Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__B__Ac__AllDoorClosed__WaitAllDoorBeClosed__8,
        Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__boundary,
        Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__Ac__AllDoorClosed__doorsClosed__1,
        Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__En__AllDoorClosed__doorsClosed__1,
        Debug__C__AllDoorClosed__doorsClosed__1__Debug__B__Ac__AllDoorClosed__doorsClosed__1,
        Debug__C__AllDoorClosed__doorsClosed__1__boundary,
        Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__Ac__Choice1__WaitAllDoorBeOpened__7,
        Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__En__Choice1__WaitAllDoorBeOpened__7,
        Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__B__Ac__Choice1__WaitAllDoorBeOpened__7,
        Debug__C__Choice1__WaitAllDoorBeOpened__7__boundary,
        Debug__C__Choice1__doorsOpen__5__Debug__A__Ac__Choice1__doorsOpen__5,
        Debug__C__Choice1__doorsOpen__5__Debug__A__En__Choice1__doorsOpen__5,
        Debug__C__Choice1__doorsOpen__5__Debug__B__Ac__Choice1__doorsOpen__5,
        Debug__C__Choice1__doorsOpen__5__boundary,
        Debug__C__Initial1__StartingUp__3__Debug__A__Ac__Initial1__StartingUp__3,
        Debug__C__Initial1__StartingUp__3__Debug__A__En__Initial1__StartingUp__3,
        Debug__C__Initial1__StartingUp__3__Debug__B__Ac__Initial1__StartingUp__3,
        Debug__C__Initial1__StartingUp__3__boundary,
        Debug__C__StartingUp__doorsOpen__10__Debug__A__Ac__StartingUp__doorsOpen__10,
        Debug__C__StartingUp__doorsOpen__10__Debug__A__En__doorsOpen,
        Debug__C__StartingUp__doorsOpen__10__Debug__B__Ac__StartingUp__doorsOpen__10,
        Debug__C__StartingUp__doorsOpen__10__Debug__B__Ex__StartingUp,
        Debug__C__StartingUp__doorsOpen__10__boundary,
        Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__A__Ac__WaitAllDoorBeClosed__AllDoorClosed__9,
        Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ac__WaitAllDoorBeClosed__AllDoorClosed__9,
        Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ex__WaitAllDoorBeClosed,
        Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__boundary,
        Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__A__Ac__WaitAllDoorBeOpened__Choice1__6,
        Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ac__WaitAllDoorBeOpened__Choice1__6,
        Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ex__WaitAllDoorBeOpened,
        Debug__C__WaitAllDoorBeOpened__Choice1__6__boundary,
        Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__Ac__doorsClosed__WaitAllDoorBeOpened__4,
        Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__En__WaitAllDoorBeOpened,
        Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ac__doorsClosed__WaitAllDoorBeOpened__4,
        Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ex__doorsClosed,
        Debug__C__doorsClosed__WaitAllDoorBeOpened__4__boundary,
        Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__Ac__doorsOpen__WaitAllDoorBeClosed__2,
        Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__En__WaitAllDoorBeClosed,
        Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ac__doorsOpen__WaitAllDoorBeClosed__2,
        Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ex__doorsOpen,
        Debug__C__doorsOpen__WaitAllDoorBeClosed__2__boundary,
        Debug__InitState,
        StartingUp,
        WaitAllDoorBeClosed,
        WaitAllDoorBeOpened,
        doorsClosed,
        doorsOpen,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[60];
    State currentState;
    State history[10];
    void save_history( State compositeState, State subState );
    bool check_history( State compositeState, State subState );
    void entryaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__Ac__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg );
    void entryaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__En__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg );
    void entryaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__B__Ac__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg );
    void entryaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__Ac__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg );
    void entryaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__En__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg );
    void entryaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__B__Ac__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg );
    void entryaction_____Debug__C__AllDoorClosed__doorsClosed__1__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__Ac__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__En__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__B__Ac__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Choice1__doorsOpen__5__Debug__A__Ac__Choice1__doorsOpen__5( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Choice1__doorsOpen__5__Debug__A__En__Choice1__doorsOpen__5( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Choice1__doorsOpen__5__Debug__B__Ac__Choice1__doorsOpen__5( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Choice1__doorsOpen__5__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Initial1__StartingUp__3__Debug__A__Ac__Initial1__StartingUp__3( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Initial1__StartingUp__3__Debug__A__En__Initial1__StartingUp__3( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Initial1__StartingUp__3__Debug__B__Ac__Initial1__StartingUp__3( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Initial1__StartingUp__3__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__StartingUp__doorsOpen__10__Debug__A__Ac__StartingUp__doorsOpen__10( const UMLRTMessage * msg );
    void entryaction_____Debug__C__StartingUp__doorsOpen__10__Debug__A__En__doorsOpen( const UMLRTMessage * msg );
    void entryaction_____Debug__C__StartingUp__doorsOpen__10__Debug__B__Ac__StartingUp__doorsOpen__10( const UMLRTMessage * msg );
    void entryaction_____Debug__C__StartingUp__doorsOpen__10__Debug__B__Ex__StartingUp( const UMLRTMessage * msg );
    void entryaction_____Debug__C__StartingUp__doorsOpen__10__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__A__Ac__WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg );
    void entryaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ac__WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg );
    void entryaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ex__WaitAllDoorBeClosed( const UMLRTMessage * msg );
    void entryaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__A__Ac__WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg );
    void entryaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ac__WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg );
    void entryaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ex__WaitAllDoorBeOpened( const UMLRTMessage * msg );
    void entryaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__Ac__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg );
    void entryaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__En__WaitAllDoorBeOpened( const UMLRTMessage * msg );
    void entryaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ac__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg );
    void entryaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ex__doorsClosed( const UMLRTMessage * msg );
    void entryaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__Ac__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg );
    void entryaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__En__WaitAllDoorBeClosed( const UMLRTMessage * msg );
    void entryaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ac__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg );
    void entryaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ex__doorsOpen( const UMLRTMessage * msg );
    void entryaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__InitState( const UMLRTMessage * msg );
    void entryaction_____StartingUp( const UMLRTMessage * msg );
    void entryaction_____WaitAllDoorBeClosed( const UMLRTMessage * msg );
    void entryaction_____WaitAllDoorBeOpened( const UMLRTMessage * msg );
    void entryaction_____doorsClosed( const UMLRTMessage * msg );
    void entryaction_____doorsOpen( const UMLRTMessage * msg );
    void exitaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__Ac__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg );
    void exitaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__En__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg );
    void exitaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__B__Ac__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg );
    void exitaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__Ac__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg );
    void exitaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__En__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg );
    void exitaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__B__Ac__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg );
    void exitaction_____Debug__C__AllDoorClosed__doorsClosed__1__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__Ac__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__En__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__B__Ac__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Choice1__doorsOpen__5__Debug__A__Ac__Choice1__doorsOpen__5( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Choice1__doorsOpen__5__Debug__A__En__Choice1__doorsOpen__5( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Choice1__doorsOpen__5__Debug__B__Ac__Choice1__doorsOpen__5( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Choice1__doorsOpen__5__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial1__StartingUp__3__Debug__A__Ac__Initial1__StartingUp__3( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial1__StartingUp__3__Debug__A__En__Initial1__StartingUp__3( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial1__StartingUp__3__Debug__B__Ac__Initial1__StartingUp__3( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Initial1__StartingUp__3__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__StartingUp__doorsOpen__10__Debug__A__Ac__StartingUp__doorsOpen__10( const UMLRTMessage * msg );
    void exitaction_____Debug__C__StartingUp__doorsOpen__10__Debug__A__En__doorsOpen( const UMLRTMessage * msg );
    void exitaction_____Debug__C__StartingUp__doorsOpen__10__Debug__B__Ac__StartingUp__doorsOpen__10( const UMLRTMessage * msg );
    void exitaction_____Debug__C__StartingUp__doorsOpen__10__Debug__B__Ex__StartingUp( const UMLRTMessage * msg );
    void exitaction_____Debug__C__StartingUp__doorsOpen__10__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__A__Ac__WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg );
    void exitaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ac__WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg );
    void exitaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ex__WaitAllDoorBeClosed( const UMLRTMessage * msg );
    void exitaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__A__Ac__WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg );
    void exitaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ac__WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg );
    void exitaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ex__WaitAllDoorBeOpened( const UMLRTMessage * msg );
    void exitaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__Ac__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg );
    void exitaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__En__WaitAllDoorBeOpened( const UMLRTMessage * msg );
    void exitaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ac__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg );
    void exitaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ex__doorsClosed( const UMLRTMessage * msg );
    void exitaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__Ac__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg );
    void exitaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__En__WaitAllDoorBeClosed( const UMLRTMessage * msg );
    void exitaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ac__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg );
    void exitaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ex__doorsOpen( const UMLRTMessage * msg );
    void exitaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__InitState( const UMLRTMessage * msg );
    void exitaction_____StartingUp( const UMLRTMessage * msg );
    void exitaction_____WaitAllDoorBeClosed( const UMLRTMessage * msg );
    void exitaction_____WaitAllDoorBeOpened( const UMLRTMessage * msg );
    void exitaction_____doorsClosed( const UMLRTMessage * msg );
    void exitaction_____doorsOpen( const UMLRTMessage * msg );
    void transitionaction_____AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg );
    void transitionaction_____AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg );
    void transitionaction_____Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg );
    void transitionaction_____Choice1__doorsOpen__5( const UMLRTMessage * msg );
    void transitionaction_____Debug__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg );
    void transitionaction_____Debug__AllDoorClosed__WaitAllDoorBeClosed__8__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__AllDoorClosed__WaitAllDoorBeClosed__8__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__AllDoorClosed__WaitAllDoorBeClosed__8__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg );
    void transitionaction_____Debug__AllDoorClosed__doorsClosed__1__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__AllDoorClosed__doorsClosed__1__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__AllDoorClosed__doorsClosed__1__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__Ac__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__En__WaitAllDoorBeClosed( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__end__trans__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__init__trans__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__Ac__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__En__doorsClosed( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__end__trans__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__init__trans__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__Ac__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__En__WaitAllDoorBeOpened( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__end__trans__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__init__trans__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Choice1__doorsOpen__5__Debug__Ac__Choice1__doorsOpen__5( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Choice1__doorsOpen__5__Debug__En__doorsOpen( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Choice1__doorsOpen__5__Debug__end__trans__Choice1__doorsOpen__5( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Choice1__doorsOpen__5__Debug__init__trans__Choice1__doorsOpen__5( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial1__StartingUp__3__Debug__Ac__Initial1__StartingUp__3( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial1__StartingUp__3__Debug__En__StartingUp( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial1__StartingUp__3__Debug__end__trans__Initial1__StartingUp__3( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Initial1__StartingUp__3__Debug__init__trans__Initial1__StartingUp__3( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__StartingUp__doorsOpen__10__Debug__AC__StartingUp__doorsOpen__10( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__StartingUp__doorsOpen__10__Debug__En__doorsOpen( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__StartingUp__doorsOpen__10__Debug__Ex__StartingUp( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__StartingUp__doorsOpen__10__Debug__end__trans__StartingUp__doorsOpen__10( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__StartingUp__doorsOpen__10__Debug__init__trans__StartingUp__doorsOpen__10( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__AC__WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__Ex__WaitAllDoorBeClosed( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__end__trans__WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__AC__WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__Ex__WaitAllDoorBeOpened( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__end__trans__WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__AC__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__En__WaitAllDoorBeOpened( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__Ex__doorsClosed( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__end__trans__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__init__trans__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__AC__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__En__WaitAllDoorBeClosed( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__Ex__doorsOpen( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__end__trans__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__init__trans__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg );
    void transitionaction_____Debug__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg );
    void transitionaction_____Debug__Choice1__WaitAllDoorBeOpened__7__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__Choice1__WaitAllDoorBeOpened__7__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__Choice1__WaitAllDoorBeOpened__7__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__Choice1__doorsOpen__5( const UMLRTMessage * msg );
    void transitionaction_____Debug__Choice1__doorsOpen__5__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__Choice1__doorsOpen__5__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__Choice1__doorsOpen__5__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__InitDebug( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial1__StartingUp__3( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial1__StartingUp__3__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial1__StartingUp__3__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__Initial1__StartingUp__3__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__StartingUp__doorsOpen__10( const UMLRTMessage * msg );
    void transitionaction_____Debug__StartingUp__doorsOpen__10__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__StartingUp__doorsOpen__10__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__StartingUp__doorsOpen__10__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg );
    void transitionaction_____Debug__WaitAllDoorBeClosed__AllDoorClosed__9__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__WaitAllDoorBeClosed__AllDoorClosed__9__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__WaitAllDoorBeClosed__AllDoorClosed__9__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg );
    void transitionaction_____Debug__WaitAllDoorBeOpened__Choice1__6__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__WaitAllDoorBeOpened__Choice1__6__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__WaitAllDoorBeOpened__Choice1__6__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg );
    void transitionaction_____Debug__doorsClosed__WaitAllDoorBeOpened__4__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__doorsClosed__WaitAllDoorBeOpened__4__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__doorsClosed__WaitAllDoorBeOpened__4__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg );
    void transitionaction_____Debug__doorsOpen__WaitAllDoorBeClosed__2__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__doorsOpen__WaitAllDoorBeClosed__2__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__doorsOpen__WaitAllDoorBeClosed__2__dbg( const UMLRTMessage * msg );
    void transitionaction_____Initial1__StartingUp__3( const UMLRTMessage * msg );
    void transitionaction_____StartingUp__doorsOpen__10( const UMLRTMessage * msg );
    void transitionaction_____WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg );
    void transitionaction_____WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg );
    void transitionaction_____doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg );
    void transitionaction_____doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg );
    bool action_____Debug__AllDoorClosed__WaitAllDoorBeClosed__8__S__Debug__GuardAllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg );
    bool action_____Debug__AllDoorClosed__doorsClosed__1__S__Debug__GuardAllDoorClosed__doorsClosed__1( const UMLRTMessage * msg );
    bool action_____Debug__AllDoorClosed__doorsClosed__1__null( const UMLRTMessage * msg );
    bool action_____Debug__Choice1__WaitAllDoorBeOpened__7__S__Debug__GuardChoice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg );
    bool action_____Debug__Choice1__doorsOpen__5__S__Debug__GuardChoice1__doorsOpen__5( const UMLRTMessage * msg );
    bool action_____Debug__Choice1__doorsOpen__5__null( const UMLRTMessage * msg );
    bool action_____Debug__Initial1__StartingUp__3__S__Debug__GuardInitial1__StartingUp__3( const UMLRTMessage * msg );
    bool action_____Debug__StartingUp__doorsOpen__10__S__Debug__GuardStartingUp__doorsOpen__10( const UMLRTMessage * msg );
    bool action_____Debug__WaitAllDoorBeClosed__AllDoorClosed__9__S__Debug__GuardWaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg );
    bool action_____Debug__WaitAllDoorBeOpened__Choice1__6__S__Debug__GuardWaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg );
    bool action_____Debug__doorsClosed__WaitAllDoorBeOpened__4__S__Debug__GuarddoorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg );
    bool action_____Debug__doorsOpen__WaitAllDoorBeClosed__2__S__Debug__GuarddoorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg );
    void actionchain_____AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg );
    void actionchain_____AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg );
    void actionchain_____Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg );
    void actionchain_____Choice1__doorsOpen__5( const UMLRTMessage * msg );
    void actionchain_____Debug__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg );
    void actionchain_____Debug__AllDoorClosed__WaitAllDoorBeClosed__8__E( const UMLRTMessage * msg );
    void actionchain_____Debug__AllDoorClosed__WaitAllDoorBeClosed__8__S( const UMLRTMessage * msg );
    void actionchain_____Debug__AllDoorClosed__WaitAllDoorBeClosed__8__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg );
    void actionchain_____Debug__AllDoorClosed__doorsClosed__1__E( const UMLRTMessage * msg );
    void actionchain_____Debug__AllDoorClosed__doorsClosed__1__S( const UMLRTMessage * msg );
    void actionchain_____Debug__AllDoorClosed__doorsClosed__1__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__Ac__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg );
    void actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__En__WaitAllDoorBeClosed( const UMLRTMessage * msg );
    void actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__end__trans__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg );
    void actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__init__trans__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg );
    void actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_transition_61( const UMLRTMessage * msg );
    void actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_transition_62( const UMLRTMessage * msg );
    void actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_transition_63( const UMLRTMessage * msg );
    void actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_transition_64_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_transition_65( const UMLRTMessage * msg );
    void actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_transition_66( const UMLRTMessage * msg );
    void actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_transition_67( const UMLRTMessage * msg );
    void actionchain_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_transition_68( const UMLRTMessage * msg );
    void actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__Ac__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg );
    void actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__En__doorsClosed( const UMLRTMessage * msg );
    void actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__end__trans__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg );
    void actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__init__trans__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg );
    void actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__new_transition_1( const UMLRTMessage * msg );
    void actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__new_transition_2( const UMLRTMessage * msg );
    void actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__new_transition_3( const UMLRTMessage * msg );
    void actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__new_transition_4_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__new_transition_5( const UMLRTMessage * msg );
    void actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__new_transition_6( const UMLRTMessage * msg );
    void actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__new_transition_7( const UMLRTMessage * msg );
    void actionchain_____Debug__C__AllDoorClosed__doorsClosed__1__new_transition_8( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__Ac__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__En__WaitAllDoorBeOpened( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__end__trans__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__init__trans__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_transition_53( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_transition_54( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_transition_55( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_transition_56_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_transition_57( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_transition_58( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_transition_59( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_transition_60( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Choice1__doorsOpen__5__Debug__Ac__Choice1__doorsOpen__5( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Choice1__doorsOpen__5__Debug__En__doorsOpen( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Choice1__doorsOpen__5__Debug__end__trans__Choice1__doorsOpen__5( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Choice1__doorsOpen__5__Debug__init__trans__Choice1__doorsOpen__5( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Choice1__doorsOpen__5__new_transition_37( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Choice1__doorsOpen__5__new_transition_38( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Choice1__doorsOpen__5__new_transition_39( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Choice1__doorsOpen__5__new_transition_40_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Choice1__doorsOpen__5__new_transition_41( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Choice1__doorsOpen__5__new_transition_42( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Choice1__doorsOpen__5__new_transition_43( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Choice1__doorsOpen__5__new_transition_44( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial1__StartingUp__3__Debug__Ac__Initial1__StartingUp__3( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial1__StartingUp__3__Debug__En__StartingUp( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial1__StartingUp__3__Debug__end__trans__Initial1__StartingUp__3( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial1__StartingUp__3__Debug__init__trans__Initial1__StartingUp__3( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial1__StartingUp__3__new_transition_19( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial1__StartingUp__3__new_transition_20( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial1__StartingUp__3__new_transition_21( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial1__StartingUp__3__new_transition_22_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial1__StartingUp__3__new_transition_23( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial1__StartingUp__3__new_transition_24( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial1__StartingUp__3__new_transition_25( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Initial1__StartingUp__3__new_transition_26( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StartingUp__doorsOpen__10__Debug__AC__StartingUp__doorsOpen__10( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StartingUp__doorsOpen__10__Debug__En__doorsOpen( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StartingUp__doorsOpen__10__Debug__Ex__StartingUp( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StartingUp__doorsOpen__10__Debug__end__trans__StartingUp__doorsOpen__10( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StartingUp__doorsOpen__10__Debug__init__trans__StartingUp__doorsOpen__10( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_77( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_78( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_79( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_80( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_81_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_82( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_83( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_84( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_85( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StartingUp__doorsOpen__10__new_transition_86( const UMLRTMessage * msg );
    void actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__AC__WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg );
    void actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__Ex__WaitAllDoorBeClosed( const UMLRTMessage * msg );
    void actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__end__trans__WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg );
    void actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__init__trans__WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg );
    void actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_transition_69( const UMLRTMessage * msg );
    void actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_transition_70( const UMLRTMessage * msg );
    void actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_transition_71( const UMLRTMessage * msg );
    void actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_transition_72_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_transition_73( const UMLRTMessage * msg );
    void actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_transition_74( const UMLRTMessage * msg );
    void actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_transition_75( const UMLRTMessage * msg );
    void actionchain_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_transition_76( const UMLRTMessage * msg );
    void actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__AC__WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg );
    void actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__Ex__WaitAllDoorBeOpened( const UMLRTMessage * msg );
    void actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__end__trans__WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg );
    void actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__init__trans__WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg );
    void actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_transition_45( const UMLRTMessage * msg );
    void actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_transition_46( const UMLRTMessage * msg );
    void actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_transition_47( const UMLRTMessage * msg );
    void actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_transition_48_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_transition_49( const UMLRTMessage * msg );
    void actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_transition_50( const UMLRTMessage * msg );
    void actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_transition_51( const UMLRTMessage * msg );
    void actionchain_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_transition_52( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__AC__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__En__WaitAllDoorBeOpened( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__Ex__doorsClosed( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__end__trans__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__init__trans__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_27( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_28( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_29( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_30( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_31_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_32( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_33( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_34( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_35( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_transition_36( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__AC__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__En__WaitAllDoorBeClosed( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__Ex__doorsOpen( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__end__trans__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__init__trans__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_10( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_11( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_12( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_13_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_14( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_15( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_16( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_17( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_18( const UMLRTMessage * msg );
    void actionchain_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_transition_9( const UMLRTMessage * msg );
    void actionchain_____Debug__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg );
    void actionchain_____Debug__Choice1__WaitAllDoorBeOpened__7__E( const UMLRTMessage * msg );
    void actionchain_____Debug__Choice1__WaitAllDoorBeOpened__7__S( const UMLRTMessage * msg );
    void actionchain_____Debug__Choice1__WaitAllDoorBeOpened__7__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__Choice1__doorsOpen__5( const UMLRTMessage * msg );
    void actionchain_____Debug__Choice1__doorsOpen__5__E( const UMLRTMessage * msg );
    void actionchain_____Debug__Choice1__doorsOpen__5__S( const UMLRTMessage * msg );
    void actionchain_____Debug__Choice1__doorsOpen__5__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__InitDebug( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial1__StartingUp__3( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial1__StartingUp__3__E( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial1__StartingUp__3__S( const UMLRTMessage * msg );
    void actionchain_____Debug__Initial1__StartingUp__3__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__StartingUp__doorsOpen__10( const UMLRTMessage * msg );
    void actionchain_____Debug__StartingUp__doorsOpen__10__E( const UMLRTMessage * msg );
    void actionchain_____Debug__StartingUp__doorsOpen__10__S( const UMLRTMessage * msg );
    void actionchain_____Debug__StartingUp__doorsOpen__10__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg );
    void actionchain_____Debug__WaitAllDoorBeClosed__AllDoorClosed__9__E( const UMLRTMessage * msg );
    void actionchain_____Debug__WaitAllDoorBeClosed__AllDoorClosed__9__S( const UMLRTMessage * msg );
    void actionchain_____Debug__WaitAllDoorBeClosed__AllDoorClosed__9__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg );
    void actionchain_____Debug__WaitAllDoorBeOpened__Choice1__6__E( const UMLRTMessage * msg );
    void actionchain_____Debug__WaitAllDoorBeOpened__Choice1__6__S( const UMLRTMessage * msg );
    void actionchain_____Debug__WaitAllDoorBeOpened__Choice1__6__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg );
    void actionchain_____Debug__doorsClosed__WaitAllDoorBeOpened__4__E( const UMLRTMessage * msg );
    void actionchain_____Debug__doorsClosed__WaitAllDoorBeOpened__4__S( const UMLRTMessage * msg );
    void actionchain_____Debug__doorsClosed__WaitAllDoorBeOpened__4__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg );
    void actionchain_____Debug__doorsOpen__WaitAllDoorBeClosed__2__E( const UMLRTMessage * msg );
    void actionchain_____Debug__doorsOpen__WaitAllDoorBeClosed__2__S( const UMLRTMessage * msg );
    void actionchain_____Debug__doorsOpen__WaitAllDoorBeClosed__2__dbg( const UMLRTMessage * msg );
    void actionchain_____Initial1__StartingUp__3( const UMLRTMessage * msg );
    void actionchain_____StartingUp__doorsOpen__10( const UMLRTMessage * msg );
    void actionchain_____WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg );
    void actionchain_____WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg );
    void actionchain_____doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg );
    void actionchain_____doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg );
    State junction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__en( const UMLRTMessage * msg );
    State junction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__new_exitpoint_8( const UMLRTMessage * msg );
    State junction_____Debug__C__AllDoorClosed__doorsClosed__1__en( const UMLRTMessage * msg );
    State junction_____Debug__C__AllDoorClosed__doorsClosed__1__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__AllDoorClosed__doorsClosed__1__new_exitpoint_1( const UMLRTMessage * msg );
    State junction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__en( const UMLRTMessage * msg );
    State junction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__Choice1__WaitAllDoorBeOpened__7__new_exitpoint_7( const UMLRTMessage * msg );
    State junction_____Debug__C__Choice1__doorsOpen__5__en( const UMLRTMessage * msg );
    State junction_____Debug__C__Choice1__doorsOpen__5__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__Choice1__doorsOpen__5__new_exitpoint_5( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial1__StartingUp__3__en( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial1__StartingUp__3__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__Initial1__StartingUp__3__new_exitpoint_3( const UMLRTMessage * msg );
    State junction_____Debug__C__StartingUp__doorsOpen__10__en( const UMLRTMessage * msg );
    State junction_____Debug__C__StartingUp__doorsOpen__10__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__StartingUp__doorsOpen__10__new_exitpoint_10( const UMLRTMessage * msg );
    State junction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__en( const UMLRTMessage * msg );
    State junction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__new_exitpoint_9( const UMLRTMessage * msg );
    State junction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__en( const UMLRTMessage * msg );
    State junction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__WaitAllDoorBeOpened__Choice1__6__new_exitpoint_6( const UMLRTMessage * msg );
    State junction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__en( const UMLRTMessage * msg );
    State junction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__new_exitpoint_4( const UMLRTMessage * msg );
    State junction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__en( const UMLRTMessage * msg );
    State junction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__new_exitpoint_2( const UMLRTMessage * msg );
    State choice_____AllDoorClosed( const UMLRTMessage * msg );
    State choice_____Choice1( const UMLRTMessage * msg );
    State choice_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__AllDoorClosed__doorsClosed__1__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__Choice1__WaitAllDoorBeOpened__7__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__Choice1__doorsOpen__5__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__Initial1__StartingUp__3__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__StartingUp__doorsOpen__10__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__WaitAllDoorBeOpened__Choice1__6__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__Path__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg );
    State choice_____Debug__Path__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg );
    State choice_____Debug__Path__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg );
    State choice_____Debug__Path__Choice1__doorsOpen__5( const UMLRTMessage * msg );
    State choice_____Debug__Path__Initial1__StartingUp__3( const UMLRTMessage * msg );
    State choice_____Debug__Path__StartingUp__doorsOpen__10( const UMLRTMessage * msg );
    State choice_____Debug__Path__WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg );
    State choice_____Debug__Path__WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg );
    State choice_____Debug__Path__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg );
    State choice_____Debug__Path__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg );
    State state_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__Ac__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg );
    State state_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__A__En__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg );
    State state_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__Debug__B__Ac__AllDoorClosed__WaitAllDoorBeClosed__8( const UMLRTMessage * msg );
    State state_____Debug__C__AllDoorClosed__WaitAllDoorBeClosed__8__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__Ac__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg );
    State state_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__A__En__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg );
    State state_____Debug__C__AllDoorClosed__doorsClosed__1__Debug__B__Ac__AllDoorClosed__doorsClosed__1( const UMLRTMessage * msg );
    State state_____Debug__C__AllDoorClosed__doorsClosed__1__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__Ac__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg );
    State state_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__A__En__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg );
    State state_____Debug__C__Choice1__WaitAllDoorBeOpened__7__Debug__B__Ac__Choice1__WaitAllDoorBeOpened__7( const UMLRTMessage * msg );
    State state_____Debug__C__Choice1__WaitAllDoorBeOpened__7__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__Choice1__doorsOpen__5__Debug__A__Ac__Choice1__doorsOpen__5( const UMLRTMessage * msg );
    State state_____Debug__C__Choice1__doorsOpen__5__Debug__A__En__Choice1__doorsOpen__5( const UMLRTMessage * msg );
    State state_____Debug__C__Choice1__doorsOpen__5__Debug__B__Ac__Choice1__doorsOpen__5( const UMLRTMessage * msg );
    State state_____Debug__C__Choice1__doorsOpen__5__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__Initial1__StartingUp__3__Debug__A__Ac__Initial1__StartingUp__3( const UMLRTMessage * msg );
    State state_____Debug__C__Initial1__StartingUp__3__Debug__A__En__Initial1__StartingUp__3( const UMLRTMessage * msg );
    State state_____Debug__C__Initial1__StartingUp__3__Debug__B__Ac__Initial1__StartingUp__3( const UMLRTMessage * msg );
    State state_____Debug__C__Initial1__StartingUp__3__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__StartingUp__doorsOpen__10__Debug__A__Ac__StartingUp__doorsOpen__10( const UMLRTMessage * msg );
    State state_____Debug__C__StartingUp__doorsOpen__10__Debug__A__En__doorsOpen( const UMLRTMessage * msg );
    State state_____Debug__C__StartingUp__doorsOpen__10__Debug__B__Ac__StartingUp__doorsOpen__10( const UMLRTMessage * msg );
    State state_____Debug__C__StartingUp__doorsOpen__10__Debug__B__Ex__StartingUp( const UMLRTMessage * msg );
    State state_____Debug__C__StartingUp__doorsOpen__10__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__A__Ac__WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg );
    State state_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ac__WaitAllDoorBeClosed__AllDoorClosed__9( const UMLRTMessage * msg );
    State state_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__Debug__B__Ex__WaitAllDoorBeClosed( const UMLRTMessage * msg );
    State state_____Debug__C__WaitAllDoorBeClosed__AllDoorClosed__9__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__A__Ac__WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg );
    State state_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ac__WaitAllDoorBeOpened__Choice1__6( const UMLRTMessage * msg );
    State state_____Debug__C__WaitAllDoorBeOpened__Choice1__6__Debug__B__Ex__WaitAllDoorBeOpened( const UMLRTMessage * msg );
    State state_____Debug__C__WaitAllDoorBeOpened__Choice1__6__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__Ac__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg );
    State state_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__A__En__WaitAllDoorBeOpened( const UMLRTMessage * msg );
    State state_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ac__doorsClosed__WaitAllDoorBeOpened__4( const UMLRTMessage * msg );
    State state_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__Debug__B__Ex__doorsClosed( const UMLRTMessage * msg );
    State state_____Debug__C__doorsClosed__WaitAllDoorBeOpened__4__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__Ac__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg );
    State state_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__A__En__WaitAllDoorBeClosed( const UMLRTMessage * msg );
    State state_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ac__doorsOpen__WaitAllDoorBeClosed__2( const UMLRTMessage * msg );
    State state_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__Debug__B__Ex__doorsOpen( const UMLRTMessage * msg );
    State state_____Debug__C__doorsOpen__WaitAllDoorBeClosed__2__boundary( const UMLRTMessage * msg );
    State state_____Debug__InitState( const UMLRTMessage * msg );
    State state_____StartingUp( const UMLRTMessage * msg );
    State state_____WaitAllDoorBeClosed( const UMLRTMessage * msg );
    State state_____WaitAllDoorBeOpened( const UMLRTMessage * msg );
    State state_____doorsClosed( const UMLRTMessage * msg );
    State state_____doorsOpen( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass CentralLock;

#endif


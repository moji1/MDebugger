
#ifndef CENTRALLOCK_HH
#define CENTRALLOCK_HH

#include "Locking.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtmessage.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

#include<stdio.h>
#include<iostream>

class Capsule_CentralLock : public UMLRTCapsule
{
public:
    Capsule_CentralLock( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    Locking::Conj lockPort;
public:
    enum BorderPortId
    {
        borderport_lockPort,
        borderport_startupTimer
    };
protected:
    UMLRTTimerProtocol_baserole startupTimer;
public:
    enum PartId
    {
    };
    enum PortId
    {
        port_lockPort,
        port_startupTimer
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    int tmpInt;
    int locksCount;
    virtual void inject( const UMLRTMessage & message );
    virtual void initialize( const UMLRTMessage & message );
    const char * getCurrentStateString() const;
private:
    enum State
    {
        StartingUp,
        WaitAllDoorBeClosed,
        WaitAllDoorBeOpened,
        doorsClosed,
        doorsOpen,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[6];
    State currentState;
    void entryaction_____StartingUp( const UMLRTMessage * msg );
    void entryaction_____WaitAllDoorBeClosed( const UMLRTMessage * msg );
    void entryaction_____WaitAllDoorBeOpened( const UMLRTMessage * msg );
    void entryaction_____doorsClosed( const UMLRTMessage * msg );
    void entryaction_____doorsOpen( const UMLRTMessage * msg );
    void exitaction_____StartingUp( const UMLRTMessage * msg );
    void exitaction_____WaitAllDoorBeClosed( const UMLRTMessage * msg );
    void exitaction_____WaitAllDoorBeOpened( const UMLRTMessage * msg );
    void exitaction_____doorsClosed( const UMLRTMessage * msg );
    void exitaction_____doorsOpen( const UMLRTMessage * msg );
    bool action_____TransitionAction5__null( const UMLRTMessage * msg );
    bool action_____TransitionAction8__null( const UMLRTMessage * msg );
    void actionchain_____TransitionAction0( const UMLRTMessage * msg );
    void actionchain_____TransitionAction1( const UMLRTMessage * msg );
    void actionchain_____TransitionAction2( const UMLRTMessage * msg );
    void actionchain_____TransitionAction3( const UMLRTMessage * msg );
    void actionchain_____TransitionAction4( const UMLRTMessage * msg );
    void actionchain_____TransitionAction5( const UMLRTMessage * msg );
    void actionchain_____TransitionAction6( const UMLRTMessage * msg );
    void actionchain_____TransitionAction7( const UMLRTMessage * msg );
    void actionchain_____TransitionAction8( const UMLRTMessage * msg );
    void actionchain_____TransitionAction9( const UMLRTMessage * msg );
    State choice_____AllDoorClosed( const UMLRTMessage * msg );
    State choice_____Choice1( const UMLRTMessage * msg );
    State state_____StartingUp( const UMLRTMessage * msg );
    State state_____WaitAllDoorBeClosed( const UMLRTMessage * msg );
    State state_____WaitAllDoorBeOpened( const UMLRTMessage * msg );
    State state_____doorsClosed( const UMLRTMessage * msg );
    State state_____doorsOpen( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass CentralLock;

#endif


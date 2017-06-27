
#ifndef LOCK_HH
#define LOCK_HH

#include "Locking.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtmessage.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

#include<stdio.h>
#include<iostream>

class Capsule_Lock : public UMLRTCapsule
{
public:
    Capsule_Lock( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
    enum BorderPortId
    {
        borderport_lockPort
    };
protected:
    Locking::Base lockPort;
public:
    enum PartId
    {
    };
    enum PortId
    {
        port_lockPort
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    virtual void inject( const UMLRTMessage & message );
    virtual void initialize( const UMLRTMessage & message );
    const char * getCurrentStateString() const;
private:
    enum State
    {
        locked,
        unlocked,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[3];
    State currentState;
    void entryaction_____locked( const UMLRTMessage * msg );
    void entryaction_____unlocked( const UMLRTMessage * msg );
    void exitaction_____locked( const UMLRTMessage * msg );
    void exitaction_____unlocked( const UMLRTMessage * msg );
    void transitionaction_____init( const UMLRTMessage * msg );
    void transitionaction_____lock( const UMLRTMessage * msg );
    void transitionaction_____twiceLock( const UMLRTMessage * msg );
    void transitionaction_____twiceUnlock( const UMLRTMessage * msg );
    void transitionaction_____unlock( const UMLRTMessage * msg );
    void actionchain_____init( const UMLRTMessage * msg );
    void actionchain_____lock( const UMLRTMessage * msg );
    void actionchain_____twiceLock( const UMLRTMessage * msg );
    void actionchain_____twiceUnlock( const UMLRTMessage * msg );
    void actionchain_____unlock( const UMLRTMessage * msg );
    State state_____locked( const UMLRTMessage * msg );
    State state_____unlocked( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass Lock;

#endif


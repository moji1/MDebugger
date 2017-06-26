
#ifndef COUNTER_HH
#define COUNTER_HH

#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtmessage.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

#include <iostream>

class Capsule_Counter : public UMLRTCapsule
{
public:
    Capsule_Counter( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
    enum PortId
    {
        port_timer1
    };
    virtual void inject( const UMLRTMessage & message );
    virtual void initialize( const UMLRTMessage & message );
    const char * getCurrentStateString() const;
private:
    enum State
    {
        State1,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[2];
    State currentState;
    void entryaction_____State1( const UMLRTMessage * msg );
    void exitaction_____State1( const UMLRTMessage * msg );
    void transitionaction_____intittrans( const UMLRTMessage * msg );
    void transitionaction_____trans1( const UMLRTMessage * msg );
    void actionchain_____intittrans( const UMLRTMessage * msg );
    void actionchain_____trans1( const UMLRTMessage * msg );
    State state_____State1( const UMLRTMessage * msg );
protected:
    UMLRTTimerProtocol_baserole timer1;
public:
    enum BorderPortId
    {
        borderport_timer1
    };
    enum PartId
    {
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    int Attribute1;
    int counter;
};
extern const UMLRTCapsuleClass Counter;

#endif


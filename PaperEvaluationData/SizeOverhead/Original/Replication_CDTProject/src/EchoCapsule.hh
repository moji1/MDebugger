
#ifndef ECHOCAPSULE_HH
#define ECHOCAPSULE_HH

#include "Echo.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtmessage.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

class Capsule_EchoCapsule : public UMLRTCapsule
{
public:
    Capsule_EchoCapsule( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    Echo::Base Echo;
public:
    enum BorderPortId
    {
        borderport_Echo
    };
    enum PartId
    {
    };
    enum PortId
    {
        port_Echo
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    virtual void inject( const UMLRTMessage & message );
    virtual void initialize( const UMLRTMessage & message );
    const char * getCurrentStateString() const;
private:
    enum State
    {
        WaitForEcho,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[2];
    State currentState;
    void entryaction_____WaitForEcho( const UMLRTMessage * msg );
    void exitaction_____WaitForEcho( const UMLRTMessage * msg );
    void transitionaction_____DoEcho( const UMLRTMessage * msg );
    void transitionaction_____TransitionAction0( const UMLRTMessage * msg );
    void actionchain_____DoEcho( const UMLRTMessage * msg );
    void actionchain_____TransitionAction0( const UMLRTMessage * msg );
    State state_____WaitForEcho( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass EchoCapsule;

#endif


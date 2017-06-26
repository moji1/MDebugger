
#ifndef GEN_HH
#define GEN_HH

#include "Parcel.hh"
#include "transmission.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtlogprotocol.hh"
#include "umlrtmessage.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

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
        borderport_timer,
        borderport_log
    };
protected:
    UMLRTLogProtocol_baserole log;
    UMLRTTimerProtocol_baserole timer;
public:
    enum PartId
    {
    };
    enum PortId
    {
        port_enter,
        port_log,
        port_timer
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    Parcel parcel;
    int delay;
    bool successorFree;
    virtual void inject( const UMLRTMessage & message );
    virtual void initialize( const UMLRTMessage & message );
    const char * getCurrentStateString() const;
private:
    enum State
    {
        GENERATING,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[2];
    State currentState;
    void entryaction_____GENERATING( const UMLRTMessage * msg );
    void exitaction_____GENERATING( const UMLRTMessage * msg );
    void transitionaction_____Initial( const UMLRTMessage * msg );
    void transitionaction_____TransitionAction1( const UMLRTMessage * msg );
    void transitionaction_____TransitionAction2( const UMLRTMessage * msg );
    void actionchain_____Initial( const UMLRTMessage * msg );
    void actionchain_____TransitionAction1( const UMLRTMessage * msg );
    void actionchain_____TransitionAction2( const UMLRTMessage * msg );
    State state_____GENERATING( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass Gen;

#endif


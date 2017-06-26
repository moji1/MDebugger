
#ifndef CHUTE_HH
#define CHUTE_HH

#include "Parcel.hh"
#include "detection.hh"
#include "transmission.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtlogprotocol.hh"
#include "umlrtmessage.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

class Capsule_Chute : public UMLRTCapsule
{
public:
    Capsule_Chute( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
    enum BorderPortId
    {
        borderport_enter,
        borderport_detection,
        borderport_exit,
        borderport_timer,
        borderport_log
    };
protected:
    detection::Base detection;
    transmission::Conj enter;
    transmission::Base exit;
    UMLRTLogProtocol_baserole log;
    UMLRTTimerProtocol_baserole timer;
public:
    enum PartId
    {
    };
    enum PortId
    {
        port_detection,
        port_enter,
        port_exit,
        port_log,
        port_timer
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    Parcel parcel;
    bool successorFree;
    int delay;
    virtual void inject( const UMLRTMessage & message );
    virtual void initialize( const UMLRTMessage & message );
    const char * getCurrentStateString() const;
private:
    enum State
    {
        IDLE,
        OCCUPIED,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[3];
    State currentState;
    void entryaction_____IDLE( const UMLRTMessage * msg );
    void entryaction_____OCCUPIED( const UMLRTMessage * msg );
    void exitaction_____IDLE( const UMLRTMessage * msg );
    void exitaction_____OCCUPIED( const UMLRTMessage * msg );
    void transitionaction_____TransitionAction2( const UMLRTMessage * msg );
    void transitionaction_____TransitionAction4( const UMLRTMessage * msg );
    void transitionaction_____TransitionAction5( const UMLRTMessage * msg );
    void transitionaction_____TransitionAction6( const UMLRTMessage * msg );
    void transitionaction_____reception( const UMLRTMessage * msg );
    bool action_____TransitionAction5__null( const UMLRTMessage * msg );
    bool action_____TransitionAction6__null( const UMLRTMessage * msg );
    void actionchain_____Initial( const UMLRTMessage * msg );
    void actionchain_____TransitionAction2( const UMLRTMessage * msg );
    void actionchain_____TransitionAction4( const UMLRTMessage * msg );
    void actionchain_____TransitionAction5( const UMLRTMessage * msg );
    void actionchain_____TransitionAction6( const UMLRTMessage * msg );
    void actionchain_____reception( const UMLRTMessage * msg );
    void actionchain_____transmission( const UMLRTMessage * msg );
    State choice_____jam__( const UMLRTMessage * msg );
    State state_____IDLE( const UMLRTMessage * msg );
    State state_____OCCUPIED( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass Chute;

#endif



#ifndef SWITCHER_HH
#define SWITCHER_HH

#include "Parcel.hh"
#include "switchProtocol.hh"
#include "transmission.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtlogprotocol.hh"
#include "umlrtmessage.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

class Capsule_Switcher : public UMLRTCapsule
{
public:
    Capsule_Switcher( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
    enum BorderPortId
    {
        borderport_left,
        borderport_right,
        borderport_enter,
        borderport_switchProtocol,
        borderport_timer,
        borderport_log
    };
protected:
    transmission::Conj enter;
    transmission::Base left;
    UMLRTLogProtocol_baserole log;
    transmission::Base right;
    switchProtocol::Conj switchProtocol;
    UMLRTTimerProtocol_baserole timer;
public:
    enum PartId
    {
    };
    enum PortId
    {
        port_enter,
        port_left,
        port_log,
        port_right,
        port_switchProtocol,
        port_timer
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    int choice;
    Parcel parcel;
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
    void transitionaction_____TransitionAction1( const UMLRTMessage * msg );
    void transitionaction_____TransitionAction4( const UMLRTMessage * msg );
    void transitionaction_____reception( const UMLRTMessage * msg );
    void transitionaction_____transmission( const UMLRTMessage * msg );
    void actionchain_____Initial( const UMLRTMessage * msg );
    void actionchain_____TransitionAction1( const UMLRTMessage * msg );
    void actionchain_____TransitionAction4( const UMLRTMessage * msg );
    void actionchain_____reception( const UMLRTMessage * msg );
    void actionchain_____transmission( const UMLRTMessage * msg );
    State state_____IDLE( const UMLRTMessage * msg );
    State state_____OCCUPIED( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass Switcher;

#endif


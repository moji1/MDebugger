
#ifndef DETECTIONSENSOR_HH
#define DETECTIONSENSOR_HH

#include "Detection.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtlogprotocol.hh"
#include "umlrtmessage.hh"
#include "umlrttimerid.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

#include "GPIOClass.hh"

class Capsule_DetectionSensor : public UMLRTCapsule
{
public:
    Capsule_DetectionSensor( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
    enum BorderPortId
    {
        borderport_detection,
        borderport_timer,
        borderport_log
    };
protected:
    Detection::Conj detection;
    UMLRTLogProtocol_baserole log;
    UMLRTTimerProtocol_baserole timer;
public:
    enum PartId
    {
    };
    enum PortId
    {
        port_detection,
        port_log,
        port_timer
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    UMLRTTimerId timerId;
    GPIOClass pinTrig;
    GPIOClass pinEcho;
    virtual void inject( const UMLRTMessage & message );
    virtual void initialize( const UMLRTMessage & message );
    const char * getCurrentStateString() const;
private:
    enum State
    {
        DETECTING,
        IDLE,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[3];
    State currentState;
    void entryaction_____DETECTING( const UMLRTMessage * msg );
    void entryaction_____IDLE( const UMLRTMessage * msg );
    void exitaction_____DETECTING( const UMLRTMessage * msg );
    void exitaction_____IDLE( const UMLRTMessage * msg );
    void transitionaction_____detecting( const UMLRTMessage * msg );
    void transitionaction_____init( const UMLRTMessage * msg );
    void transitionaction_____start_detecting( const UMLRTMessage * msg );
    void transitionaction_____stop_detecting( const UMLRTMessage * msg );
    void actionchain_____detecting( const UMLRTMessage * msg );
    void actionchain_____init( const UMLRTMessage * msg );
    void actionchain_____start_detecting( const UMLRTMessage * msg );
    void actionchain_____stop_detecting( const UMLRTMessage * msg );
    State state_____DETECTING( const UMLRTMessage * msg );
    State state_____IDLE( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass DetectionSensor;

#endif



#ifndef CLIENT_HH
#define CLIENT_HH

#include "ConfigProtocol.hh"
#include "Host.hh"
#include "Services.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtmessage.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

class Capsule_Client : public Capsule_Host
{
public:
    Capsule_Client( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    ConfigProtocol::Base ConfigComm;
public:
    enum BorderPortId
    {
        borderport_ConfigComm,
        borderport_ConfigTimer,
        borderport_RequestTimer,
        borderport_ResponseTimer,
        borderport_Server1Comm,
        borderport_Server2Comm,
        borderport_Timer
    };
protected:
    UMLRTTimerProtocol_baserole ConfigTimer;
    UMLRTTimerProtocol_baserole RequestTimer;
    UMLRTTimerProtocol_baserole ResponseTimer;
    Services::Base Server1Comm;
    Services::Base Server2Comm;
    UMLRTTimerProtocol_baserole Timer;
public:
    enum PartId
    {
    };
    enum PortId
    {
        port_ConfigComm,
        port_ConfigTimer,
        port_RequestTimer,
        port_ResponseTimer,
        port_Server1Comm,
        port_Server2Comm,
        port_Timer
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    virtual void inject( const UMLRTMessage & message );
    virtual void initialize( const UMLRTMessage & message );
    const char * getCurrentStateString() const;
private:
    enum State
    {
        ProcessResponse,
        Ready,
        Retry,
        StandBY,
        WaitingForReply,
        getMasterName,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[7];
    State currentState;
    void entryaction_____ProcessResponse( const UMLRTMessage * msg );
    void entryaction_____Ready( const UMLRTMessage * msg );
    void entryaction_____Retry( const UMLRTMessage * msg );
    void entryaction_____StandBY( const UMLRTMessage * msg );
    void entryaction_____WaitingForReply( const UMLRTMessage * msg );
    void entryaction_____getMasterName( const UMLRTMessage * msg );
    void exitaction_____ProcessResponse( const UMLRTMessage * msg );
    void exitaction_____Ready( const UMLRTMessage * msg );
    void exitaction_____Retry( const UMLRTMessage * msg );
    void exitaction_____StandBY( const UMLRTMessage * msg );
    void exitaction_____WaitingForReply( const UMLRTMessage * msg );
    void exitaction_____getMasterName( const UMLRTMessage * msg );
    void transitionaction_____NoResponseFromServer( const UMLRTMessage * msg );
    void transitionaction_____ReqFlowDone( const UMLRTMessage * msg );
    void transitionaction_____ServiceResult( const UMLRTMessage * msg );
    void transitionaction_____StarupTransition( const UMLRTMessage * msg );
    void transitionaction_____TransitionAction0( const UMLRTMessage * msg );
    void transitionaction_____reqService( const UMLRTMessage * msg );
    bool action_____reqService__MasterIsAvailable( const UMLRTMessage * msg );
    void actionchain_____NoMaster( const UMLRTMessage * msg );
    void actionchain_____NoResponseFromServer( const UMLRTMessage * msg );
    void actionchain_____ReqFlowDone( const UMLRTMessage * msg );
    void actionchain_____Retry( const UMLRTMessage * msg );
    void actionchain_____ServiceResult( const UMLRTMessage * msg );
    void actionchain_____StarupTransition( const UMLRTMessage * msg );
    void actionchain_____TransitionAction0( const UMLRTMessage * msg );
    void actionchain_____TransitionAction3( const UMLRTMessage * msg );
    void actionchain_____reqFlowInit( const UMLRTMessage * msg );
    void actionchain_____reqService( const UMLRTMessage * msg );
    State choice_____checkConfig( const UMLRTMessage * msg );
    State state_____ProcessResponse( const UMLRTMessage * msg );
    State state_____Ready( const UMLRTMessage * msg );
    State state_____Retry( const UMLRTMessage * msg );
    State state_____StandBY( const UMLRTMessage * msg );
    State state_____WaitingForReply( const UMLRTMessage * msg );
    State state_____getMasterName( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass Client;

#endif


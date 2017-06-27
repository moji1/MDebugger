
#ifndef CLIENT_HH
#define CLIENT_HH

#include "Config.hh"
#include "ExtInterface.hh"
#include "Host.hh"
#include "Services.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtmessage.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

#include "Event.h"

#include "SROManager.h"

class Capsule_Client : public Capsule_Host
{
public:
    Capsule_Client( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    Config::Base ConfigComm;
public:
    enum BorderPortId
    {
        borderport_ConfigComm,
        borderport_ConfigTimer,
        borderport_RequestTimer,
        borderport_ResponseTimer,
        borderport_Server1Comm,
        borderport_Server2Comm,
        borderport_Timer,
        borderport_extComm
    };
protected:
    UMLRTTimerProtocol_baserole ConfigTimer;
    UMLRTTimerProtocol_baserole RequestTimer;
    UMLRTTimerProtocol_baserole ResponseTimer;
    Services::Base Server1Comm;
    Services::Base Server2Comm;
    UMLRTTimerProtocol_baserole Timer;
    ExtInterface::Conj extComm;
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
        port_Timer,
        port_extComm
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
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
        Debug__C__NoMaster,
        Debug__C__NoResponseFromServer,
        Debug__C__ReqFlowDone,
        Debug__C__Retry,
        Debug__C__ServiceResult,
        Debug__C__StarupTransition,
        Debug__C__getMasterName__checkConfig__7,
        Debug__C__init__StandBY__6,
        Debug__C__reqFlowInit,
        Debug__C__reqService,
        Debug__C__NoMaster__Debug__A__Ac__NoMaster,
        Debug__C__NoMaster__Debug__A__En__NoMaster,
        Debug__C__NoMaster__Debug__B__Ac__NoMaster,
        Debug__C__NoMaster__boundary,
        Debug__C__NoResponseFromServer__Debug__A__Ac__NoResponseFromServer,
        Debug__C__NoResponseFromServer__Debug__A__En__Ready,
        Debug__C__NoResponseFromServer__Debug__B__Ac__NoResponseFromServer,
        Debug__C__NoResponseFromServer__Debug__B__Ex__WaitingForReply,
        Debug__C__NoResponseFromServer__boundary,
        Debug__C__ReqFlowDone__Debug__A__Ac__ReqFlowDone,
        Debug__C__ReqFlowDone__Debug__A__En__Ready,
        Debug__C__ReqFlowDone__Debug__B__Ac__ReqFlowDone,
        Debug__C__ReqFlowDone__Debug__B__Ex__ProcessResponse,
        Debug__C__ReqFlowDone__boundary,
        Debug__C__Retry__Debug__A__Ac__Retry,
        Debug__C__Retry__Debug__A__En__getMasterName,
        Debug__C__Retry__Debug__B__Ac__Retry,
        Debug__C__Retry__Debug__B__Ex__Retry,
        Debug__C__Retry__boundary,
        Debug__C__ServiceResult__Debug__A__Ac__ServiceResult,
        Debug__C__ServiceResult__Debug__A__En__ProcessResponse,
        Debug__C__ServiceResult__Debug__B__Ac__ServiceResult,
        Debug__C__ServiceResult__Debug__B__Ex__WaitingForReply,
        Debug__C__ServiceResult__boundary,
        Debug__C__StarupTransition__Debug__A__Ac__StarupTransition,
        Debug__C__StarupTransition__Debug__A__En__Ready,
        Debug__C__StarupTransition__Debug__B__Ac__StarupTransition,
        Debug__C__StarupTransition__Debug__B__Ex__StandBY,
        Debug__C__StarupTransition__boundary,
        Debug__C__getMasterName__checkConfig__7__Debug__A__Ac__getMasterName__checkConfig__7,
        Debug__C__getMasterName__checkConfig__7__Debug__B__Ac__getMasterName__checkConfig__7,
        Debug__C__getMasterName__checkConfig__7__Debug__B__Ex__getMasterName,
        Debug__C__getMasterName__checkConfig__7__boundary,
        Debug__C__init__StandBY__6__Debug__A__Ac__init__StandBY__6,
        Debug__C__init__StandBY__6__Debug__A__En__init__StandBY__6,
        Debug__C__init__StandBY__6__Debug__B__Ac__init__StandBY__6,
        Debug__C__init__StandBY__6__boundary,
        Debug__C__reqFlowInit__Debug__A__Ac__reqFlowInit,
        Debug__C__reqFlowInit__Debug__A__En__getMasterName,
        Debug__C__reqFlowInit__Debug__B__Ac__reqFlowInit,
        Debug__C__reqFlowInit__Debug__B__Ex__Ready,
        Debug__C__reqFlowInit__boundary,
        Debug__C__reqService__Debug__A__Ac__reqService,
        Debug__C__reqService__Debug__A__En__reqService,
        Debug__C__reqService__Debug__B__Ac__reqService,
        Debug__C__reqService__boundary,
        Debug__InitState,
        ProcessResponse,
        Ready,
        Retry,
        StandBY,
        WaitingForReply,
        getMasterName,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[64];
    State currentState;
    State history[10];
    void save_history( State compositeState, State subState );
    bool check_history( State compositeState, State subState );
    void entryaction_____Debug__C__NoMaster__Debug__A__Ac__NoMaster( const UMLRTMessage * msg );
    void entryaction_____Debug__C__NoMaster__Debug__A__En__NoMaster( const UMLRTMessage * msg );
    void entryaction_____Debug__C__NoMaster__Debug__B__Ac__NoMaster( const UMLRTMessage * msg );
    void entryaction_____Debug__C__NoMaster__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__NoResponseFromServer__Debug__A__Ac__NoResponseFromServer( const UMLRTMessage * msg );
    void entryaction_____Debug__C__NoResponseFromServer__Debug__A__En__Ready( const UMLRTMessage * msg );
    void entryaction_____Debug__C__NoResponseFromServer__Debug__B__Ac__NoResponseFromServer( const UMLRTMessage * msg );
    void entryaction_____Debug__C__NoResponseFromServer__Debug__B__Ex__WaitingForReply( const UMLRTMessage * msg );
    void entryaction_____Debug__C__NoResponseFromServer__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__ReqFlowDone__Debug__A__Ac__ReqFlowDone( const UMLRTMessage * msg );
    void entryaction_____Debug__C__ReqFlowDone__Debug__A__En__Ready( const UMLRTMessage * msg );
    void entryaction_____Debug__C__ReqFlowDone__Debug__B__Ac__ReqFlowDone( const UMLRTMessage * msg );
    void entryaction_____Debug__C__ReqFlowDone__Debug__B__Ex__ProcessResponse( const UMLRTMessage * msg );
    void entryaction_____Debug__C__ReqFlowDone__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Retry__Debug__A__Ac__Retry( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Retry__Debug__A__En__getMasterName( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Retry__Debug__B__Ac__Retry( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Retry__Debug__B__Ex__Retry( const UMLRTMessage * msg );
    void entryaction_____Debug__C__Retry__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__ServiceResult__Debug__A__Ac__ServiceResult( const UMLRTMessage * msg );
    void entryaction_____Debug__C__ServiceResult__Debug__A__En__ProcessResponse( const UMLRTMessage * msg );
    void entryaction_____Debug__C__ServiceResult__Debug__B__Ac__ServiceResult( const UMLRTMessage * msg );
    void entryaction_____Debug__C__ServiceResult__Debug__B__Ex__WaitingForReply( const UMLRTMessage * msg );
    void entryaction_____Debug__C__ServiceResult__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__StarupTransition__Debug__A__Ac__StarupTransition( const UMLRTMessage * msg );
    void entryaction_____Debug__C__StarupTransition__Debug__A__En__Ready( const UMLRTMessage * msg );
    void entryaction_____Debug__C__StarupTransition__Debug__B__Ac__StarupTransition( const UMLRTMessage * msg );
    void entryaction_____Debug__C__StarupTransition__Debug__B__Ex__StandBY( const UMLRTMessage * msg );
    void entryaction_____Debug__C__StarupTransition__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__getMasterName__checkConfig__7__Debug__A__Ac__getMasterName__checkConfig__7( const UMLRTMessage * msg );
    void entryaction_____Debug__C__getMasterName__checkConfig__7__Debug__B__Ac__getMasterName__checkConfig__7( const UMLRTMessage * msg );
    void entryaction_____Debug__C__getMasterName__checkConfig__7__Debug__B__Ex__getMasterName( const UMLRTMessage * msg );
    void entryaction_____Debug__C__getMasterName__checkConfig__7__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__init__StandBY__6__Debug__A__Ac__init__StandBY__6( const UMLRTMessage * msg );
    void entryaction_____Debug__C__init__StandBY__6__Debug__A__En__init__StandBY__6( const UMLRTMessage * msg );
    void entryaction_____Debug__C__init__StandBY__6__Debug__B__Ac__init__StandBY__6( const UMLRTMessage * msg );
    void entryaction_____Debug__C__init__StandBY__6__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__reqFlowInit__Debug__A__Ac__reqFlowInit( const UMLRTMessage * msg );
    void entryaction_____Debug__C__reqFlowInit__Debug__A__En__getMasterName( const UMLRTMessage * msg );
    void entryaction_____Debug__C__reqFlowInit__Debug__B__Ac__reqFlowInit( const UMLRTMessage * msg );
    void entryaction_____Debug__C__reqFlowInit__Debug__B__Ex__Ready( const UMLRTMessage * msg );
    void entryaction_____Debug__C__reqFlowInit__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__C__reqService__Debug__A__Ac__reqService( const UMLRTMessage * msg );
    void entryaction_____Debug__C__reqService__Debug__A__En__reqService( const UMLRTMessage * msg );
    void entryaction_____Debug__C__reqService__Debug__B__Ac__reqService( const UMLRTMessage * msg );
    void entryaction_____Debug__C__reqService__boundary( const UMLRTMessage * msg );
    void entryaction_____Debug__InitState( const UMLRTMessage * msg );
    void entryaction_____ProcessResponse( const UMLRTMessage * msg );
    void entryaction_____Ready( const UMLRTMessage * msg );
    void entryaction_____Retry( const UMLRTMessage * msg );
    void entryaction_____StandBY( const UMLRTMessage * msg );
    void entryaction_____WaitingForReply( const UMLRTMessage * msg );
    void entryaction_____getMasterName( const UMLRTMessage * msg );
    void exitaction_____Debug__C__NoMaster__Debug__A__Ac__NoMaster( const UMLRTMessage * msg );
    void exitaction_____Debug__C__NoMaster__Debug__A__En__NoMaster( const UMLRTMessage * msg );
    void exitaction_____Debug__C__NoMaster__Debug__B__Ac__NoMaster( const UMLRTMessage * msg );
    void exitaction_____Debug__C__NoMaster__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__NoResponseFromServer__Debug__A__Ac__NoResponseFromServer( const UMLRTMessage * msg );
    void exitaction_____Debug__C__NoResponseFromServer__Debug__A__En__Ready( const UMLRTMessage * msg );
    void exitaction_____Debug__C__NoResponseFromServer__Debug__B__Ac__NoResponseFromServer( const UMLRTMessage * msg );
    void exitaction_____Debug__C__NoResponseFromServer__Debug__B__Ex__WaitingForReply( const UMLRTMessage * msg );
    void exitaction_____Debug__C__NoResponseFromServer__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__ReqFlowDone__Debug__A__Ac__ReqFlowDone( const UMLRTMessage * msg );
    void exitaction_____Debug__C__ReqFlowDone__Debug__A__En__Ready( const UMLRTMessage * msg );
    void exitaction_____Debug__C__ReqFlowDone__Debug__B__Ac__ReqFlowDone( const UMLRTMessage * msg );
    void exitaction_____Debug__C__ReqFlowDone__Debug__B__Ex__ProcessResponse( const UMLRTMessage * msg );
    void exitaction_____Debug__C__ReqFlowDone__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Retry__Debug__A__Ac__Retry( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Retry__Debug__A__En__getMasterName( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Retry__Debug__B__Ac__Retry( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Retry__Debug__B__Ex__Retry( const UMLRTMessage * msg );
    void exitaction_____Debug__C__Retry__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__ServiceResult__Debug__A__Ac__ServiceResult( const UMLRTMessage * msg );
    void exitaction_____Debug__C__ServiceResult__Debug__A__En__ProcessResponse( const UMLRTMessage * msg );
    void exitaction_____Debug__C__ServiceResult__Debug__B__Ac__ServiceResult( const UMLRTMessage * msg );
    void exitaction_____Debug__C__ServiceResult__Debug__B__Ex__WaitingForReply( const UMLRTMessage * msg );
    void exitaction_____Debug__C__ServiceResult__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__StarupTransition__Debug__A__Ac__StarupTransition( const UMLRTMessage * msg );
    void exitaction_____Debug__C__StarupTransition__Debug__A__En__Ready( const UMLRTMessage * msg );
    void exitaction_____Debug__C__StarupTransition__Debug__B__Ac__StarupTransition( const UMLRTMessage * msg );
    void exitaction_____Debug__C__StarupTransition__Debug__B__Ex__StandBY( const UMLRTMessage * msg );
    void exitaction_____Debug__C__StarupTransition__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__getMasterName__checkConfig__7__Debug__A__Ac__getMasterName__checkConfig__7( const UMLRTMessage * msg );
    void exitaction_____Debug__C__getMasterName__checkConfig__7__Debug__B__Ac__getMasterName__checkConfig__7( const UMLRTMessage * msg );
    void exitaction_____Debug__C__getMasterName__checkConfig__7__Debug__B__Ex__getMasterName( const UMLRTMessage * msg );
    void exitaction_____Debug__C__getMasterName__checkConfig__7__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__init__StandBY__6__Debug__A__Ac__init__StandBY__6( const UMLRTMessage * msg );
    void exitaction_____Debug__C__init__StandBY__6__Debug__A__En__init__StandBY__6( const UMLRTMessage * msg );
    void exitaction_____Debug__C__init__StandBY__6__Debug__B__Ac__init__StandBY__6( const UMLRTMessage * msg );
    void exitaction_____Debug__C__init__StandBY__6__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__reqFlowInit__Debug__A__Ac__reqFlowInit( const UMLRTMessage * msg );
    void exitaction_____Debug__C__reqFlowInit__Debug__A__En__getMasterName( const UMLRTMessage * msg );
    void exitaction_____Debug__C__reqFlowInit__Debug__B__Ac__reqFlowInit( const UMLRTMessage * msg );
    void exitaction_____Debug__C__reqFlowInit__Debug__B__Ex__Ready( const UMLRTMessage * msg );
    void exitaction_____Debug__C__reqFlowInit__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__C__reqService__Debug__A__Ac__reqService( const UMLRTMessage * msg );
    void exitaction_____Debug__C__reqService__Debug__A__En__reqService( const UMLRTMessage * msg );
    void exitaction_____Debug__C__reqService__Debug__B__Ac__reqService( const UMLRTMessage * msg );
    void exitaction_____Debug__C__reqService__boundary( const UMLRTMessage * msg );
    void exitaction_____Debug__InitState( const UMLRTMessage * msg );
    void exitaction_____ProcessResponse( const UMLRTMessage * msg );
    void exitaction_____Ready( const UMLRTMessage * msg );
    void exitaction_____Retry( const UMLRTMessage * msg );
    void exitaction_____StandBY( const UMLRTMessage * msg );
    void exitaction_____WaitingForReply( const UMLRTMessage * msg );
    void exitaction_____getMasterName( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__NoMaster__Debug__Ac__NoMaster( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__NoMaster__Debug__En__Retry( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__NoMaster__Debug__end__trans__NoMaster( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__NoMaster__Debug__init__trans__NoMaster( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__NoResponseFromServer__Debug__AC__NoResponseFromServer( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__NoResponseFromServer__Debug__En__Ready( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__NoResponseFromServer__Debug__Ex__WaitingForReply( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__NoResponseFromServer__Debug__end__trans__NoResponseFromServer( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__NoResponseFromServer__Debug__init__trans__NoResponseFromServer( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__ReqFlowDone__Debug__AC__ReqFlowDone( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__ReqFlowDone__Debug__En__Ready( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__ReqFlowDone__Debug__Ex__ProcessResponse( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__ReqFlowDone__Debug__end__trans__ReqFlowDone( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__ReqFlowDone__Debug__init__trans__ReqFlowDone( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Retry__Debug__AC__Retry( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Retry__Debug__En__getMasterName( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Retry__Debug__Ex__Retry( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Retry__Debug__end__trans__Retry( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__Retry__Debug__init__trans__Retry( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__ServiceResult__Debug__AC__ServiceResult( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__ServiceResult__Debug__En__ProcessResponse( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__ServiceResult__Debug__Ex__WaitingForReply( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__ServiceResult__Debug__end__trans__ServiceResult( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__ServiceResult__Debug__init__trans__ServiceResult( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__StarupTransition__Debug__AC__StarupTransition( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__StarupTransition__Debug__En__Ready( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__StarupTransition__Debug__Ex__StandBY( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__StarupTransition__Debug__end__trans__StarupTransition( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__StarupTransition__Debug__init__trans__StarupTransition( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__getMasterName__checkConfig__7__Debug__AC__getMasterName__checkConfig__7( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__getMasterName__checkConfig__7__Debug__Ex__getMasterName( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__getMasterName__checkConfig__7__Debug__end__trans__getMasterName__checkConfig__7( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__init__StandBY__6__Debug__Ac__init__StandBY__6( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__init__StandBY__6__Debug__En__StandBY( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__init__StandBY__6__Debug__end__trans__init__StandBY__6( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__init__StandBY__6__Debug__init__trans__init__StandBY__6( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__reqFlowInit__Debug__AC__reqFlowInit( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__reqFlowInit__Debug__En__getMasterName( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__reqFlowInit__Debug__Ex__Ready( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__reqFlowInit__Debug__end__trans__reqFlowInit( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__reqFlowInit__Debug__init__trans__reqFlowInit( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__reqService__Debug__Ac__reqService( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__reqService__Debug__En__WaitingForReply( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__reqService__Debug__end__trans__reqService( const UMLRTMessage * msg );
    void transitionaction_____Debug__C__reqService__Debug__init__trans__reqService( const UMLRTMessage * msg );
    void transitionaction_____Debug__InitDebug( const UMLRTMessage * msg );
    void transitionaction_____Debug__NoMaster( const UMLRTMessage * msg );
    void transitionaction_____Debug__NoMaster__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__NoMaster__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__NoMaster__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__NoResponseFromServer( const UMLRTMessage * msg );
    void transitionaction_____Debug__NoResponseFromServer__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__NoResponseFromServer__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__NoResponseFromServer__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__ReqFlowDone( const UMLRTMessage * msg );
    void transitionaction_____Debug__ReqFlowDone__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__ReqFlowDone__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__ReqFlowDone__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__Retry( const UMLRTMessage * msg );
    void transitionaction_____Debug__Retry__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__Retry__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__Retry__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__ServiceResult( const UMLRTMessage * msg );
    void transitionaction_____Debug__ServiceResult__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__ServiceResult__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__ServiceResult__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__StarupTransition( const UMLRTMessage * msg );
    void transitionaction_____Debug__StarupTransition__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__StarupTransition__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__StarupTransition__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__getMasterName__checkConfig__7( const UMLRTMessage * msg );
    void transitionaction_____Debug__getMasterName__checkConfig__7__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__getMasterName__checkConfig__7__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__getMasterName__checkConfig__7__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__init__StandBY__6( const UMLRTMessage * msg );
    void transitionaction_____Debug__init__StandBY__6__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__init__StandBY__6__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__init__StandBY__6__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__reqFlowInit( const UMLRTMessage * msg );
    void transitionaction_____Debug__reqFlowInit__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__reqFlowInit__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__reqFlowInit__dbg( const UMLRTMessage * msg );
    void transitionaction_____Debug__reqService( const UMLRTMessage * msg );
    void transitionaction_____Debug__reqService__E( const UMLRTMessage * msg );
    void transitionaction_____Debug__reqService__S( const UMLRTMessage * msg );
    void transitionaction_____Debug__reqService__dbg( const UMLRTMessage * msg );
    void transitionaction_____NoMaster( const UMLRTMessage * msg );
    void transitionaction_____NoResponseFromServer( const UMLRTMessage * msg );
    void transitionaction_____ReqFlowDone( const UMLRTMessage * msg );
    void transitionaction_____Retry( const UMLRTMessage * msg );
    void transitionaction_____ServiceResult( const UMLRTMessage * msg );
    void transitionaction_____StarupTransition( const UMLRTMessage * msg );
    void transitionaction_____getMasterName__checkConfig__7( const UMLRTMessage * msg );
    void transitionaction_____init__StandBY__6( const UMLRTMessage * msg );
    void transitionaction_____reqFlowInit( const UMLRTMessage * msg );
    void transitionaction_____reqService( const UMLRTMessage * msg );
    bool action_____Debug__NoMaster__S__Debug__GuardNoMaster( const UMLRTMessage * msg );
    bool action_____Debug__NoResponseFromServer__S__Debug__GuardNoResponseFromServer( const UMLRTMessage * msg );
    bool action_____Debug__ReqFlowDone__S__Debug__GuardReqFlowDone( const UMLRTMessage * msg );
    bool action_____Debug__Retry__S__Debug__GuardRetry( const UMLRTMessage * msg );
    bool action_____Debug__ServiceResult__S__Debug__GuardServiceResult( const UMLRTMessage * msg );
    bool action_____Debug__StarupTransition__S__Debug__GuardStarupTransition( const UMLRTMessage * msg );
    bool action_____Debug__getMasterName__checkConfig__7__S__Debug__GuardgetMasterName__checkConfig__7( const UMLRTMessage * msg );
    bool action_____Debug__init__StandBY__6__S__Debug__Guardinit__StandBY__6( const UMLRTMessage * msg );
    bool action_____Debug__reqFlowInit__S__Debug__GuardreqFlowInit( const UMLRTMessage * msg );
    bool action_____Debug__reqService__MasterIsAvailable( const UMLRTMessage * msg );
    bool action_____Debug__reqService__S__Debug__GuardreqService( const UMLRTMessage * msg );
    void actionchain_____Debug__C__NoMaster__Debug__Ac__NoMaster( const UMLRTMessage * msg );
    void actionchain_____Debug__C__NoMaster__Debug__En__Retry( const UMLRTMessage * msg );
    void actionchain_____Debug__C__NoMaster__Debug__end__trans__NoMaster( const UMLRTMessage * msg );
    void actionchain_____Debug__C__NoMaster__Debug__init__trans__NoMaster( const UMLRTMessage * msg );
    void actionchain_____Debug__C__NoMaster__new_transition_21( const UMLRTMessage * msg );
    void actionchain_____Debug__C__NoMaster__new_transition_22( const UMLRTMessage * msg );
    void actionchain_____Debug__C__NoMaster__new_transition_23( const UMLRTMessage * msg );
    void actionchain_____Debug__C__NoMaster__new_transition_24_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__NoMaster__new_transition_25( const UMLRTMessage * msg );
    void actionchain_____Debug__C__NoMaster__new_transition_26( const UMLRTMessage * msg );
    void actionchain_____Debug__C__NoMaster__new_transition_27( const UMLRTMessage * msg );
    void actionchain_____Debug__C__NoMaster__new_transition_28( const UMLRTMessage * msg );
    void actionchain_____Debug__C__NoResponseFromServer__Debug__AC__NoResponseFromServer( const UMLRTMessage * msg );
    void actionchain_____Debug__C__NoResponseFromServer__Debug__En__Ready( const UMLRTMessage * msg );
    void actionchain_____Debug__C__NoResponseFromServer__Debug__Ex__WaitingForReply( const UMLRTMessage * msg );
    void actionchain_____Debug__C__NoResponseFromServer__Debug__end__trans__NoResponseFromServer( const UMLRTMessage * msg );
    void actionchain_____Debug__C__NoResponseFromServer__Debug__init__trans__NoResponseFromServer( const UMLRTMessage * msg );
    void actionchain_____Debug__C__NoResponseFromServer__new_transition_29( const UMLRTMessage * msg );
    void actionchain_____Debug__C__NoResponseFromServer__new_transition_30( const UMLRTMessage * msg );
    void actionchain_____Debug__C__NoResponseFromServer__new_transition_31( const UMLRTMessage * msg );
    void actionchain_____Debug__C__NoResponseFromServer__new_transition_32( const UMLRTMessage * msg );
    void actionchain_____Debug__C__NoResponseFromServer__new_transition_33_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__NoResponseFromServer__new_transition_34( const UMLRTMessage * msg );
    void actionchain_____Debug__C__NoResponseFromServer__new_transition_35( const UMLRTMessage * msg );
    void actionchain_____Debug__C__NoResponseFromServer__new_transition_36( const UMLRTMessage * msg );
    void actionchain_____Debug__C__NoResponseFromServer__new_transition_37( const UMLRTMessage * msg );
    void actionchain_____Debug__C__NoResponseFromServer__new_transition_38( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ReqFlowDone__Debug__AC__ReqFlowDone( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ReqFlowDone__Debug__En__Ready( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ReqFlowDone__Debug__Ex__ProcessResponse( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ReqFlowDone__Debug__end__trans__ReqFlowDone( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ReqFlowDone__Debug__init__trans__ReqFlowDone( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ReqFlowDone__new_transition_39( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ReqFlowDone__new_transition_40( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ReqFlowDone__new_transition_41( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ReqFlowDone__new_transition_42( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ReqFlowDone__new_transition_43_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ReqFlowDone__new_transition_44( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ReqFlowDone__new_transition_45( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ReqFlowDone__new_transition_46( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ReqFlowDone__new_transition_47( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ReqFlowDone__new_transition_48( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Retry__Debug__AC__Retry( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Retry__Debug__En__getMasterName( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Retry__Debug__Ex__Retry( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Retry__Debug__end__trans__Retry( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Retry__Debug__init__trans__Retry( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Retry__new_transition_11( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Retry__new_transition_12( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Retry__new_transition_13( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Retry__new_transition_14( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Retry__new_transition_15_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Retry__new_transition_16( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Retry__new_transition_17( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Retry__new_transition_18( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Retry__new_transition_19( const UMLRTMessage * msg );
    void actionchain_____Debug__C__Retry__new_transition_20( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServiceResult__Debug__AC__ServiceResult( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServiceResult__Debug__En__ProcessResponse( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServiceResult__Debug__Ex__WaitingForReply( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServiceResult__Debug__end__trans__ServiceResult( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServiceResult__Debug__init__trans__ServiceResult( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServiceResult__new_transition_75( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServiceResult__new_transition_76( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServiceResult__new_transition_77( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServiceResult__new_transition_78( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServiceResult__new_transition_79_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServiceResult__new_transition_80( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServiceResult__new_transition_81( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServiceResult__new_transition_82( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServiceResult__new_transition_83( const UMLRTMessage * msg );
    void actionchain_____Debug__C__ServiceResult__new_transition_84( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StarupTransition__Debug__AC__StarupTransition( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StarupTransition__Debug__En__Ready( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StarupTransition__Debug__Ex__StandBY( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StarupTransition__Debug__end__trans__StarupTransition( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StarupTransition__Debug__init__trans__StarupTransition( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StarupTransition__new_transition_1( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StarupTransition__new_transition_10( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StarupTransition__new_transition_2( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StarupTransition__new_transition_3( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StarupTransition__new_transition_4( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StarupTransition__new_transition_5_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StarupTransition__new_transition_6( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StarupTransition__new_transition_7( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StarupTransition__new_transition_8( const UMLRTMessage * msg );
    void actionchain_____Debug__C__StarupTransition__new_transition_9( const UMLRTMessage * msg );
    void actionchain_____Debug__C__getMasterName__checkConfig__7__Debug__AC__getMasterName__checkConfig__7( const UMLRTMessage * msg );
    void actionchain_____Debug__C__getMasterName__checkConfig__7__Debug__Ex__getMasterName( const UMLRTMessage * msg );
    void actionchain_____Debug__C__getMasterName__checkConfig__7__Debug__end__trans__getMasterName__checkConfig__7( const UMLRTMessage * msg );
    void actionchain_____Debug__C__getMasterName__checkConfig__7__Debug__init__trans__getMasterName__checkConfig__7( const UMLRTMessage * msg );
    void actionchain_____Debug__C__getMasterName__checkConfig__7__new_transition_57( const UMLRTMessage * msg );
    void actionchain_____Debug__C__getMasterName__checkConfig__7__new_transition_58( const UMLRTMessage * msg );
    void actionchain_____Debug__C__getMasterName__checkConfig__7__new_transition_59( const UMLRTMessage * msg );
    void actionchain_____Debug__C__getMasterName__checkConfig__7__new_transition_60_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__getMasterName__checkConfig__7__new_transition_61( const UMLRTMessage * msg );
    void actionchain_____Debug__C__getMasterName__checkConfig__7__new_transition_62( const UMLRTMessage * msg );
    void actionchain_____Debug__C__getMasterName__checkConfig__7__new_transition_63( const UMLRTMessage * msg );
    void actionchain_____Debug__C__getMasterName__checkConfig__7__new_transition_64( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__StandBY__6__Debug__Ac__init__StandBY__6( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__StandBY__6__Debug__En__StandBY( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__StandBY__6__Debug__end__trans__init__StandBY__6( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__StandBY__6__Debug__init__trans__init__StandBY__6( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__StandBY__6__new_transition_49( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__StandBY__6__new_transition_50( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__StandBY__6__new_transition_51( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__StandBY__6__new_transition_52_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__StandBY__6__new_transition_53( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__StandBY__6__new_transition_54( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__StandBY__6__new_transition_55( const UMLRTMessage * msg );
    void actionchain_____Debug__C__init__StandBY__6__new_transition_56( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reqFlowInit__Debug__AC__reqFlowInit( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reqFlowInit__Debug__En__getMasterName( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reqFlowInit__Debug__Ex__Ready( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reqFlowInit__Debug__end__trans__reqFlowInit( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reqFlowInit__Debug__init__trans__reqFlowInit( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reqFlowInit__new_transition_65( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reqFlowInit__new_transition_66( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reqFlowInit__new_transition_67( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reqFlowInit__new_transition_68( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reqFlowInit__new_transition_69_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reqFlowInit__new_transition_70( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reqFlowInit__new_transition_71( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reqFlowInit__new_transition_72( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reqFlowInit__new_transition_73( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reqFlowInit__new_transition_74( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reqService__Debug__Ac__reqService( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reqService__Debug__En__WaitingForReply( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reqService__Debug__end__trans__reqService( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reqService__Debug__init__trans__reqService( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reqService__new_transition_85( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reqService__new_transition_86( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reqService__new_transition_87( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reqService__new_transition_88_to_boundary( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reqService__new_transition_89( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reqService__new_transition_90( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reqService__new_transition_91( const UMLRTMessage * msg );
    void actionchain_____Debug__C__reqService__new_transition_92( const UMLRTMessage * msg );
    void actionchain_____Debug__InitDebug( const UMLRTMessage * msg );
    void actionchain_____Debug__NoMaster( const UMLRTMessage * msg );
    void actionchain_____Debug__NoMaster__E( const UMLRTMessage * msg );
    void actionchain_____Debug__NoMaster__S( const UMLRTMessage * msg );
    void actionchain_____Debug__NoMaster__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__NoResponseFromServer( const UMLRTMessage * msg );
    void actionchain_____Debug__NoResponseFromServer__E( const UMLRTMessage * msg );
    void actionchain_____Debug__NoResponseFromServer__S( const UMLRTMessage * msg );
    void actionchain_____Debug__NoResponseFromServer__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__ReqFlowDone( const UMLRTMessage * msg );
    void actionchain_____Debug__ReqFlowDone__E( const UMLRTMessage * msg );
    void actionchain_____Debug__ReqFlowDone__S( const UMLRTMessage * msg );
    void actionchain_____Debug__ReqFlowDone__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__Retry( const UMLRTMessage * msg );
    void actionchain_____Debug__Retry__E( const UMLRTMessage * msg );
    void actionchain_____Debug__Retry__S( const UMLRTMessage * msg );
    void actionchain_____Debug__Retry__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__ServiceResult( const UMLRTMessage * msg );
    void actionchain_____Debug__ServiceResult__E( const UMLRTMessage * msg );
    void actionchain_____Debug__ServiceResult__S( const UMLRTMessage * msg );
    void actionchain_____Debug__ServiceResult__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__StarupTransition( const UMLRTMessage * msg );
    void actionchain_____Debug__StarupTransition__E( const UMLRTMessage * msg );
    void actionchain_____Debug__StarupTransition__S( const UMLRTMessage * msg );
    void actionchain_____Debug__StarupTransition__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__getMasterName__checkConfig__7( const UMLRTMessage * msg );
    void actionchain_____Debug__getMasterName__checkConfig__7__E( const UMLRTMessage * msg );
    void actionchain_____Debug__getMasterName__checkConfig__7__S( const UMLRTMessage * msg );
    void actionchain_____Debug__getMasterName__checkConfig__7__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__init__StandBY__6( const UMLRTMessage * msg );
    void actionchain_____Debug__init__StandBY__6__E( const UMLRTMessage * msg );
    void actionchain_____Debug__init__StandBY__6__S( const UMLRTMessage * msg );
    void actionchain_____Debug__init__StandBY__6__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__reqFlowInit( const UMLRTMessage * msg );
    void actionchain_____Debug__reqFlowInit__E( const UMLRTMessage * msg );
    void actionchain_____Debug__reqFlowInit__S( const UMLRTMessage * msg );
    void actionchain_____Debug__reqFlowInit__dbg( const UMLRTMessage * msg );
    void actionchain_____Debug__reqService( const UMLRTMessage * msg );
    void actionchain_____Debug__reqService__E( const UMLRTMessage * msg );
    void actionchain_____Debug__reqService__S( const UMLRTMessage * msg );
    void actionchain_____Debug__reqService__dbg( const UMLRTMessage * msg );
    void actionchain_____NoMaster( const UMLRTMessage * msg );
    void actionchain_____NoResponseFromServer( const UMLRTMessage * msg );
    void actionchain_____ReqFlowDone( const UMLRTMessage * msg );
    void actionchain_____Retry( const UMLRTMessage * msg );
    void actionchain_____ServiceResult( const UMLRTMessage * msg );
    void actionchain_____StarupTransition( const UMLRTMessage * msg );
    void actionchain_____getMasterName__checkConfig__7( const UMLRTMessage * msg );
    void actionchain_____init__StandBY__6( const UMLRTMessage * msg );
    void actionchain_____reqFlowInit( const UMLRTMessage * msg );
    void actionchain_____reqService( const UMLRTMessage * msg );
    State junction_____Debug__C__NoMaster__en( const UMLRTMessage * msg );
    State junction_____Debug__C__NoMaster__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__NoMaster__new_exitpoint_3( const UMLRTMessage * msg );
    State junction_____Debug__C__NoResponseFromServer__en( const UMLRTMessage * msg );
    State junction_____Debug__C__NoResponseFromServer__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__NoResponseFromServer__new_exitpoint_4( const UMLRTMessage * msg );
    State junction_____Debug__C__ReqFlowDone__en( const UMLRTMessage * msg );
    State junction_____Debug__C__ReqFlowDone__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__ReqFlowDone__new_exitpoint_5( const UMLRTMessage * msg );
    State junction_____Debug__C__Retry__en( const UMLRTMessage * msg );
    State junction_____Debug__C__Retry__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__Retry__new_exitpoint_2( const UMLRTMessage * msg );
    State junction_____Debug__C__ServiceResult__en( const UMLRTMessage * msg );
    State junction_____Debug__C__ServiceResult__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__ServiceResult__new_exitpoint_9( const UMLRTMessage * msg );
    State junction_____Debug__C__StarupTransition__en( const UMLRTMessage * msg );
    State junction_____Debug__C__StarupTransition__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__StarupTransition__new_exitpoint_1( const UMLRTMessage * msg );
    State junction_____Debug__C__getMasterName__checkConfig__7__en( const UMLRTMessage * msg );
    State junction_____Debug__C__getMasterName__checkConfig__7__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__getMasterName__checkConfig__7__new_exitpoint_7( const UMLRTMessage * msg );
    State junction_____Debug__C__init__StandBY__6__en( const UMLRTMessage * msg );
    State junction_____Debug__C__init__StandBY__6__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__init__StandBY__6__new_exitpoint_6( const UMLRTMessage * msg );
    State junction_____Debug__C__reqFlowInit__en( const UMLRTMessage * msg );
    State junction_____Debug__C__reqFlowInit__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__reqFlowInit__new_exitpoint_8( const UMLRTMessage * msg );
    State junction_____Debug__C__reqService__en( const UMLRTMessage * msg );
    State junction_____Debug__C__reqService__ex( const UMLRTMessage * msg );
    State junction_____Debug__C__reqService__new_exitpoint_10( const UMLRTMessage * msg );
    State choice_____Debug__C__NoMaster__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__NoResponseFromServer__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__ReqFlowDone__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__Retry__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__ServiceResult__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__StarupTransition__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__getMasterName__checkConfig__7__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__init__StandBY__6__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__reqFlowInit__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__C__reqService__deephistory( const UMLRTMessage * msg );
    State choice_____Debug__Path__NoMaster( const UMLRTMessage * msg );
    State choice_____Debug__Path__NoResponseFromServer( const UMLRTMessage * msg );
    State choice_____Debug__Path__ReqFlowDone( const UMLRTMessage * msg );
    State choice_____Debug__Path__Retry( const UMLRTMessage * msg );
    State choice_____Debug__Path__ServiceResult( const UMLRTMessage * msg );
    State choice_____Debug__Path__StarupTransition( const UMLRTMessage * msg );
    State choice_____Debug__Path__getMasterName__checkConfig__7( const UMLRTMessage * msg );
    State choice_____Debug__Path__init__StandBY__6( const UMLRTMessage * msg );
    State choice_____Debug__Path__reqFlowInit( const UMLRTMessage * msg );
    State choice_____Debug__Path__reqService( const UMLRTMessage * msg );
    State choice_____checkConfig( const UMLRTMessage * msg );
    State state_____Debug__C__NoMaster__Debug__A__Ac__NoMaster( const UMLRTMessage * msg );
    State state_____Debug__C__NoMaster__Debug__A__En__NoMaster( const UMLRTMessage * msg );
    State state_____Debug__C__NoMaster__Debug__B__Ac__NoMaster( const UMLRTMessage * msg );
    State state_____Debug__C__NoMaster__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__NoResponseFromServer__Debug__A__Ac__NoResponseFromServer( const UMLRTMessage * msg );
    State state_____Debug__C__NoResponseFromServer__Debug__A__En__Ready( const UMLRTMessage * msg );
    State state_____Debug__C__NoResponseFromServer__Debug__B__Ac__NoResponseFromServer( const UMLRTMessage * msg );
    State state_____Debug__C__NoResponseFromServer__Debug__B__Ex__WaitingForReply( const UMLRTMessage * msg );
    State state_____Debug__C__NoResponseFromServer__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__ReqFlowDone__Debug__A__Ac__ReqFlowDone( const UMLRTMessage * msg );
    State state_____Debug__C__ReqFlowDone__Debug__A__En__Ready( const UMLRTMessage * msg );
    State state_____Debug__C__ReqFlowDone__Debug__B__Ac__ReqFlowDone( const UMLRTMessage * msg );
    State state_____Debug__C__ReqFlowDone__Debug__B__Ex__ProcessResponse( const UMLRTMessage * msg );
    State state_____Debug__C__ReqFlowDone__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__Retry__Debug__A__Ac__Retry( const UMLRTMessage * msg );
    State state_____Debug__C__Retry__Debug__A__En__getMasterName( const UMLRTMessage * msg );
    State state_____Debug__C__Retry__Debug__B__Ac__Retry( const UMLRTMessage * msg );
    State state_____Debug__C__Retry__Debug__B__Ex__Retry( const UMLRTMessage * msg );
    State state_____Debug__C__Retry__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__ServiceResult__Debug__A__Ac__ServiceResult( const UMLRTMessage * msg );
    State state_____Debug__C__ServiceResult__Debug__A__En__ProcessResponse( const UMLRTMessage * msg );
    State state_____Debug__C__ServiceResult__Debug__B__Ac__ServiceResult( const UMLRTMessage * msg );
    State state_____Debug__C__ServiceResult__Debug__B__Ex__WaitingForReply( const UMLRTMessage * msg );
    State state_____Debug__C__ServiceResult__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__StarupTransition__Debug__A__Ac__StarupTransition( const UMLRTMessage * msg );
    State state_____Debug__C__StarupTransition__Debug__A__En__Ready( const UMLRTMessage * msg );
    State state_____Debug__C__StarupTransition__Debug__B__Ac__StarupTransition( const UMLRTMessage * msg );
    State state_____Debug__C__StarupTransition__Debug__B__Ex__StandBY( const UMLRTMessage * msg );
    State state_____Debug__C__StarupTransition__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__getMasterName__checkConfig__7__Debug__A__Ac__getMasterName__checkConfig__7( const UMLRTMessage * msg );
    State state_____Debug__C__getMasterName__checkConfig__7__Debug__B__Ac__getMasterName__checkConfig__7( const UMLRTMessage * msg );
    State state_____Debug__C__getMasterName__checkConfig__7__Debug__B__Ex__getMasterName( const UMLRTMessage * msg );
    State state_____Debug__C__getMasterName__checkConfig__7__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__init__StandBY__6__Debug__A__Ac__init__StandBY__6( const UMLRTMessage * msg );
    State state_____Debug__C__init__StandBY__6__Debug__A__En__init__StandBY__6( const UMLRTMessage * msg );
    State state_____Debug__C__init__StandBY__6__Debug__B__Ac__init__StandBY__6( const UMLRTMessage * msg );
    State state_____Debug__C__init__StandBY__6__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__reqFlowInit__Debug__A__Ac__reqFlowInit( const UMLRTMessage * msg );
    State state_____Debug__C__reqFlowInit__Debug__A__En__getMasterName( const UMLRTMessage * msg );
    State state_____Debug__C__reqFlowInit__Debug__B__Ac__reqFlowInit( const UMLRTMessage * msg );
    State state_____Debug__C__reqFlowInit__Debug__B__Ex__Ready( const UMLRTMessage * msg );
    State state_____Debug__C__reqFlowInit__boundary( const UMLRTMessage * msg );
    State state_____Debug__C__reqService__Debug__A__Ac__reqService( const UMLRTMessage * msg );
    State state_____Debug__C__reqService__Debug__A__En__reqService( const UMLRTMessage * msg );
    State state_____Debug__C__reqService__Debug__B__Ac__reqService( const UMLRTMessage * msg );
    State state_____Debug__C__reqService__boundary( const UMLRTMessage * msg );
    State state_____Debug__InitState( const UMLRTMessage * msg );
    State state_____ProcessResponse( const UMLRTMessage * msg );
    State state_____Ready( const UMLRTMessage * msg );
    State state_____Retry( const UMLRTMessage * msg );
    State state_____StandBY( const UMLRTMessage * msg );
    State state_____WaitingForReply( const UMLRTMessage * msg );
    State state_____getMasterName( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass Client;

#endif


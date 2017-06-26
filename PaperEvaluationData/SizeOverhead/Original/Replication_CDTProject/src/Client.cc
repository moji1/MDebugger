
#include "Client.hh"

#include "ConfigProtocol.hh"
#include "Host.hh"
#include "Services.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include "umlrttimerprotocol.hh"
#include <cstddef>
#include "SystemConfig.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

#include <iostream>
#include <cstdlib>

Capsule_Client::Capsule_Client( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: Capsule_Host( cd, st, border, internal, isStat )
, ConfigComm( borderPorts[borderport_ConfigComm] )
, ConfigTimer( borderPorts[borderport_ConfigTimer] )
, RequestTimer( borderPorts[borderport_RequestTimer] )
, ResponseTimer( borderPorts[borderport_ResponseTimer] )
, Server1Comm( borderPorts[borderport_Server1Comm] )
, Server2Comm( borderPorts[borderport_Server2Comm] )
, Timer( borderPorts[borderport_Timer] )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[ProcessResponse] = "ProcessResponse";
    stateNames[Ready] = "Ready";
    stateNames[Retry] = "Retry";
    stateNames[StandBY] = "StandBY";
    stateNames[WaitingForReply] = "WaitingForReply";
    stateNames[getMasterName] = "getMasterName";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
}











void Capsule_Client::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_Server1Comm:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_Server1Comm, index, true );
            break;
        case borderport_Server2Comm:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_Server2Comm, index, true );
            break;
        }
}

void Capsule_Client::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_Server1Comm:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_Server1Comm, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_Server1Comm], index );
            break;
        case borderport_Server2Comm:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_Server2Comm, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_Server2Comm], index );
            break;
        }
}

void Capsule_Client::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case StandBY:
        currentState = state_____StandBY( &message );
        break;
    case Ready:
        currentState = state_____Ready( &message );
        break;
    case getMasterName:
        currentState = state_____getMasterName( &message );
        break;
    case WaitingForReply:
        currentState = state_____WaitingForReply( &message );
        break;
    case ProcessResponse:
        currentState = state_____ProcessResponse( &message );
        break;
    case Retry:
        currentState = state_____Retry( &message );
        break;
    default:
        break;
    }
}

void Capsule_Client::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____TransitionAction0( &message );
    currentState = StandBY;
}

const char * Capsule_Client::getCurrentStateString() const
{
    return stateNames[currentState];
}




void Capsule_Client::entryaction_____ProcessResponse( const UMLRTMessage * msg )
{
    #define umlrtparam_Result ( *(int *)msg->getParam( 0 ) )
    #define rtdata ( (int *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Client::ProcessResponse entry  */
    std::cout<<this->getName()<<this->getIndex()<<" : Processing Response .....\n";
    //int r=rand()%10;

    Timer.informIn(UMLRTTimespec(0,500),4);
    //messageID=messageID+1; 
    ts.getclock(ts);
    if (logfile.is_open())
    logfile<<this->getName()<<",MessageProcessed,"<<messageID<<","<<ts.tv_sec<<","<<ts.tv_nsec<<"\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_Result
}

void Capsule_Client::entryaction_____Ready( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const SystemConfig * )msg->getParam( 0 ) )
    #define rtdata ( (const SystemConfig * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Client::Ready entry  */
    std::cout<<this->getName()<<this->getIndex()<<": is in Ready State\n";
    //int r=rand()%11;
    int r=1;
    RequestTimer.informIn(UMLRTTimespec(0,1000),4);
    std::cout<<this->getName()<<this->getIndex()<<": will try to request service after "<< r<<" second \n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

void Capsule_Client::entryaction_____Retry( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Client::Retry entry  */
    int r=rand()%5;
    std::cout<<this->getName()<<this->getIndex()<<": The master is not available, retry in "<<r<< " second\n";
    Timer.informIn(UMLRTTimespec(r,0),4);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____StandBY( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Client::StandBY entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____WaitingForReply( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Client::WaitingForReply entry  */

    std::cout<<this->getName()<<this->getIndex()<<": Waiting for Response, The timeout is 60 Second\n";
    TimerId=ResponseTimer.informIn(UMLRTTimespec(60,0),4);
    ts.getclock(ts);
    if (logfile.is_open())
    logfile<<this->getName()<<",MessageSent,"<<messageID<<","<<ts.tv_sec<<","<<ts.tv_nsec<<"\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::entryaction_____getMasterName( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Client::getMasterName entry  */
    std::cout<<this->getName()<<this->getIndex()<<":  Request Master Information from ENV\n";
    ConfigComm.QueryConfig().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____ProcessResponse( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Client::ProcessResponse exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Ready( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Client::Ready exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____Retry( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Client::Retry exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::exitaction_____StandBY( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const SystemConfig * )msg->getParam( 0 ) )
    #define rtdata ( (const SystemConfig * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Client::StandBY exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

void Capsule_Client::exitaction_____WaitingForReply( const UMLRTMessage * msg )
{
    #define umlrtparam_Result ( *(int *)msg->getParam( 0 ) )
    #define rtdata ( (int *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Client::WaitingForReply exit  */
    ResponseTimer.cancelTimer(TimerId);
    messageID=messageID+1; 
    ts.getclock(ts);
    if (logfile.is_open())
    logfile<<this->getName()<<",ProcessingMessage,"<<messageID<<","<<ts.tv_sec<<","<<ts.tv_nsec<<"\n";   
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_Result
}

void Capsule_Client::exitaction_____getMasterName( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const SystemConfig * )msg->getParam( 0 ) )
    #define rtdata ( (const SystemConfig * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Client::getMasterName exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

void Capsule_Client::transitionaction_____NoResponseFromServer( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Client transition WaitingForReply,Ready,timeout:ResponseTimer */
    std::cout<<this->getName()<<this->getIndex()<<": Service Failur.....\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____ReqFlowDone( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Client transition ProcessResponse,Ready,timeout:Timer */
    std::cout<<this->getName()<<this->getIndex()<<": The service Request has been done sucessfully\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____ServiceResult( const UMLRTMessage * msg )
{
    #define umlrtparam_Result ( *(int *)msg->getParam( 0 ) )
    #define rtdata ( (int *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Client transition WaitingForReply,ProcessResponse,Reply:Server1Comm:Server2Comm */
    std::cout<<this->getName()<<this->getIndex()<<": got reponse from server, go to process response state\n";
    int j=0;
    for (int i=0;i<=100000;i++)
    j=j+1;
    std::cout<<j;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_Result
}

void Capsule_Client::transitionaction_____StarupTransition( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const SystemConfig * )msg->getParam( 0 ) )
    #define rtdata ( (const SystemConfig * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Client transition StandBY,Ready,StartUp:ConfigComm */
    std::cout<<this->getName()<<this->getIndex()<<" Client is startingUP \n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

void Capsule_Client::transitionaction_____TransitionAction0( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Client transition init,StandBY */
    std::cout<<this->getName()<<this->getIndex()<<": Intialization\n";
    //logfile.open(this->getName());
    char s[10];
    sprintf(s,"%s%d","client",this->getIndex());
    logfile.open(s);
    logfile<<"capsuleName"<<",messageType,"<<"messageID"<<","<<"second"<<","<<"nano"<<"\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____reqService( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Client transition checkConfig,WaitingForReply */

    messageID=messageID+1;
    ts.getclock(ts);
    if (logfile.is_open())
    logfile<<this->getName()<<",SendingMessage,"<<messageID<<","<<ts.tv_sec<<","<<ts.tv_nsec<<"\n";
    if (config.MasterList[0] && config.MasterList[1])
    {
    int r=rand()%2;
    if (r==0)
    {
    Server1Comm.Request(0).send();
    std::cout<<this->getName()<<this->getIndex()<<": sending Request to Server1\n";
    }
    else{
    Server2Comm.Request(0).send();
    std::cout<<this->getName()<<this->getIndex()<<": sending Request to Server2\n";
    }
    }
    else if (config.MasterList[0]){
    Server1Comm.Request(0).send();
    std::cout<<this->getName()<<this->getIndex()<<": sending Request to Server1\n";
    }
    else
    {
    Server2Comm.Request(0).send();
    std::cout<<this->getName()<<this->getIndex()<<": sending Request to Server2\n";
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Client::action_____reqService__MasterIsAvailable( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const SystemConfig * )msg->getParam( 0 ) )
    #define rtdata ( (const SystemConfig * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Client guard checkConfig,WaitingForReply */
    config=umlrtparam_config;
    if (config.MasterList[0] || config.MasterList[1])
    return true;
    else 
    return false;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

void Capsule_Client::actionchain_____NoMaster( const UMLRTMessage * msg )
{
    entryaction_____Retry( msg );
}

void Capsule_Client::actionchain_____NoResponseFromServer( const UMLRTMessage * msg )
{
    exitaction_____WaitingForReply( msg );
    transitionaction_____NoResponseFromServer( msg );
    entryaction_____Ready( msg );
}

void Capsule_Client::actionchain_____ReqFlowDone( const UMLRTMessage * msg )
{
    exitaction_____ProcessResponse( msg );
    transitionaction_____ReqFlowDone( msg );
    entryaction_____Ready( msg );
}

void Capsule_Client::actionchain_____Retry( const UMLRTMessage * msg )
{
    exitaction_____Retry( msg );
    entryaction_____getMasterName( msg );
}

void Capsule_Client::actionchain_____ServiceResult( const UMLRTMessage * msg )
{
    exitaction_____WaitingForReply( msg );
    transitionaction_____ServiceResult( msg );
    entryaction_____ProcessResponse( msg );
}

void Capsule_Client::actionchain_____StarupTransition( const UMLRTMessage * msg )
{
    exitaction_____StandBY( msg );
    transitionaction_____StarupTransition( msg );
    entryaction_____Ready( msg );
}

void Capsule_Client::actionchain_____TransitionAction0( const UMLRTMessage * msg )
{
    transitionaction_____TransitionAction0( msg );
    entryaction_____StandBY( msg );
}

void Capsule_Client::actionchain_____TransitionAction3( const UMLRTMessage * msg )
{
    exitaction_____getMasterName( msg );
}

void Capsule_Client::actionchain_____reqFlowInit( const UMLRTMessage * msg )
{
    exitaction_____Ready( msg );
    entryaction_____getMasterName( msg );
}

void Capsule_Client::actionchain_____reqService( const UMLRTMessage * msg )
{
    transitionaction_____reqService( msg );
    entryaction_____WaitingForReply( msg );
}

Capsule_Client::State Capsule_Client::choice_____checkConfig( const UMLRTMessage * msg )
{
    if( action_____reqService__MasterIsAvailable( msg ) )
    {
        actionchain_____reqService( msg );
        return WaitingForReply;
    }
    else
    {
        actionchain_____NoMaster( msg );
        return Retry;
    }
    return currentState;
}

Capsule_Client::State Capsule_Client::state_____ProcessResponse( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_Timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____ReqFlowDone( msg );
            return Ready;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Client::State Capsule_Client::state_____Ready( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_RequestTimer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____reqFlowInit( msg );
            return getMasterName;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Client::State Capsule_Client::state_____Retry( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_Timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____Retry( msg );
            return getMasterName;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Client::State Capsule_Client::state_____StandBY( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_ConfigComm:
        switch( msg->getSignalId() )
        {
        case ConfigProtocol::signal_StartUp:
            actionchain_____StarupTransition( msg );
            return Ready;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Client::State Capsule_Client::state_____WaitingForReply( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_Server1Comm:
        switch( msg->getSignalId() )
        {
        case Services::signal_Reply:
            actionchain_____ServiceResult( msg );
            return ProcessResponse;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_Server2Comm:
        switch( msg->getSignalId() )
        {
        case Services::signal_Reply:
            actionchain_____ServiceResult( msg );
            return ProcessResponse;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_ResponseTimer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____NoResponseFromServer( msg );
            return Ready;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Client::State Capsule_Client::state_____getMasterName( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_ConfigComm:
        switch( msg->getSignalId() )
        {
        case ConfigProtocol::signal_ReplyConfig:
            actionchain_____TransitionAction3( msg );
            return choice_____checkConfig( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}


static const UMLRTCommsPortRole portroles_border[] = 
{
    {
        Capsule_Client::port_ConfigComm,
        "ConfigProtocol",
        "ConfigComm",
        "",
        1,
        true,
        false,
        false,
        false,
        true,
        false,
        false
    },
    {
        Capsule_Client::port_ConfigTimer,
        "Timing",
        "ConfigTimer",
        "",
        1,
        true,
        false,
        false,
        false,
        true,
        false,
        false
    },
    {
        Capsule_Client::port_RequestTimer,
        "Timing",
        "RequestTimer",
        "",
        1,
        true,
        false,
        false,
        false,
        true,
        false,
        false
    },
    {
        Capsule_Client::port_ResponseTimer,
        "Timing",
        "ResponseTimer",
        "",
        1,
        true,
        false,
        false,
        false,
        true,
        false,
        false
    },
    {
        Capsule_Client::port_Server1Comm,
        "Services",
        "Server1Comm",
        "",
        1,
        true,
        false,
        false,
        false,
        false,
        false,
        true
    },
    {
        Capsule_Client::port_Server2Comm,
        "Services",
        "Server2Comm",
        "",
        1,
        true,
        false,
        false,
        false,
        false,
        false,
        true
    },
    {
        Capsule_Client::port_Timer,
        "Timing",
        "Timer",
        "",
        1,
        true,
        false,
        false,
        false,
        true,
        false,
        false
    }
};

static void instantiate_Client( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    slot->capsule = new Capsule_Client( &Client, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass Client = 
{
    "Client",
    &Host,
    instantiate_Client,
    0,
    NULL,
    7,
    portroles_border,
    0,
    NULL
};


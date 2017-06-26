
#include "GateWay.hh"

#include "ExtInterface.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include "umlrttimerprotocol.hh"
#include <cstddef>
#include "umlrtcapsuleclass.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

Capsule_GateWay::Capsule_GateWay( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
, commandTimer( borderPorts[borderport_commandTimer] )
, configTimer( borderPorts[borderport_configTimer] )
, extComm( borderPorts[borderport_extComm] )
{
    stateNames[commWithSharedMem] = "commWithSharedMem";
    stateNames[configLoad] = "configLoad";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
}


void Capsule_GateWay::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case configLoad:
        currentState = state_____configLoad( &message );
        break;
    case commWithSharedMem:
        currentState = state_____commWithSharedMem( &message );
        break;
    default:
        break;
    }
}

void Capsule_GateWay::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____init( &message );
    currentState = configLoad;
}

const char * Capsule_GateWay::getCurrentStateString() const
{
    return stateNames[currentState];
}




void Capsule_GateWay::entryaction_____commWithSharedMem( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CommGateWay/model.uml GateWay::commWithSharedMem entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_GateWay::entryaction_____configLoad( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CommGateWay/model.uml GateWay::configLoad entry  */
    //init the time for config read 
    configTimer.informAt(UMLRTTimespec(1,0),4);
    // include read config
    config.loadConfig();
    ///
    std::string tempStr ="";
    tempStr=config.getConfig("eventareaname");
    if (tempStr!="")
    eventSharedMemory.setName(tempStr);
    tempStr=config.getConfig("eventqname");
    if (tempStr!="")
    eventSharedMemory.setQueueName(tempStr);
    tempStr=config.getConfig("eventareasize");
    if (tempStr!="")
    eventSharedMemory.setSize(atoi(tempStr.c_str()));
    /////
    tempStr=config.getConfig("commandareaname");
    if (tempStr!="")
    commandSharedMemory.setName(tempStr);
    tempStr=config.getConfig("commandqname");
    if (tempStr!="")
    commandSharedMemory.setQueueName(tempStr);
    tempStr=config.getConfig("commandareasize");
    if (tempStr!="")
    commandSharedMemory.setSize(atoi(tempStr.c_str()));
    std::cout<<config;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_GateWay::transitionaction_____extCommand( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CommGateWay/model.uml GateWay transition commWithSharedMem,commWithSharedMem,timeout:commandTimer */
    //std::cout<<"Observer: Try read command\n";
    std::string tempStr;
    tempStr=commandSharedMemory.safePopFrontString();
    if (tempStr!=""){
    std::cout<<this->getName()<<": External Command= "<<tempStr<<"\n";
    mdebugger::DebugCommand cmd;
    cmd.deserialize(tempStr);
    std::cout<<"The capsule id is:"<<cmd.getCapsuleId()<<"\n";
    for (std::map<std::string,int>::const_iterator it1=registeredCapsules.begin() ;  it1!=registeredCapsules.end();it1++)
    std::cout<<"Registerd capsule:"<<it1->first<<"\n";
    switch (cmd.getCmdId()){
    case mdebugger::dbgCmd::EXEC:
    if (registeredCapsules.count(cmd.getCapsuleId()))
    extComm.dbgExec().sendAt(registeredCapsules[cmd.getCapsuleId()]);
    else
    std::cout<<this->getName()<<": Error the capsule name is not registration table, message ignored"<<"\n";
    break;
    case mdebugger::dbgCmd::VARCHANGE:
    if (registeredCapsules.count(cmd.getCapsuleId())){
    char varName[256];
    char varValue[1024];
    for (std::map<std::string,std::string>::const_iterator it1=cmd.getCmdParams().begin(); it1!=cmd.getCmdParams().end();it1++){
    sprintf(varName,"%s",it1->first.c_str());
    sprintf(varValue,"%s",it1->second.c_str());
    extComm.dbgVarChange(varName,varValue).sendAt(registeredCapsules[cmd.getCapsuleId()]);
    }
    }
    else
    std::cout<<this->getName()<<": Error the capsule name is not registration table, message ignored"<<"\n";
    break;
    }
    }
    commandTimer.informIn(UMLRTTimespec(1,0),4);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_GateWay::transitionaction_____init( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CommGateWay/model.uml GateWay transition InitObserver,configLoad */
    // instantiate the configutility class 
    std::cout<<this->getName()<<" is Starting\n";
    config.setCommentStr("#");
    config.setFieldSeperaor("=");
    config.setConfigFileName("config");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_GateWay::transitionaction_____processAndForwardEvent( const UMLRTMessage * msg )
{
    #define umlrtparam_eventInfo ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CommGateWay/model.uml GateWay transition commWithSharedMem,commWithSharedMem,event:extComm */
    std::string tempS="";
    tempS.append(umlrtparam_eventInfo);
    std::cout<<"New message from capsule:"<<tempS<<"\n";
    eventSharedMemory.safePushBackString(tempS);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_eventInfo
}

void Capsule_GateWay::transitionaction_____registerCapsule( const UMLRTMessage * msg )
{
    #define umlrtparam_capsuleInstanceName ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CommGateWay/model.uml GateWay transition commWithSharedMem,commWithSharedMem,registerToControl:extComm */
    std::cout<<this->getName()<<": Registration Message come at channel= \""<<msg->sapIndex0_<<"\" from capsule instance="<<std::string(umlrtparam_capsuleInstanceName)<<"\n";
    std::string tempS="";
    tempS.append(umlrtparam_capsuleInstanceName);
    //std::stringstream ss;
    //ss<<msg->sapIndex0_;
    //tempS.append(ss.str());
    registeredCapsules[tempS] = msg->sapIndex0_;
    std::cout<<this->getName()<<": Number of registered capsules is="<<registeredCapsules.size()<<"\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_capsuleInstanceName
}

void Capsule_GateWay::transitionaction_____replySelfExec( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CommGateWay/model.uml GateWay transition commWithSharedMem,commWithSharedMem,selfExec:extComm */
    extComm.dbgExec().sendAt(msg->sapIndex0_);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_GateWay::transitionaction_____setupSharedMem( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/CommGateWay/model.uml GateWay transition configLoad,commWithSharedMem,timeout:configTimer */
    // set shared memory as a server
    eventSharedMemory.setUp(server);
    commandSharedMemory.setUp(server);
    std::cout<<this->getName()<<" works with SHM"<<"\n";
    commandTimer.informIn(UMLRTTimespec(1,0),4);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_GateWay::actionchain_____extCommand( const UMLRTMessage * msg )
{
    transitionaction_____extCommand( msg );
    entryaction_____commWithSharedMem( msg );
}

void Capsule_GateWay::actionchain_____init( const UMLRTMessage * msg )
{
    transitionaction_____init( msg );
    entryaction_____configLoad( msg );
}

void Capsule_GateWay::actionchain_____processAndForwardEvent( const UMLRTMessage * msg )
{
    transitionaction_____processAndForwardEvent( msg );
    entryaction_____commWithSharedMem( msg );
}

void Capsule_GateWay::actionchain_____reconfigSHM( const UMLRTMessage * msg )
{
    entryaction_____configLoad( msg );
}

void Capsule_GateWay::actionchain_____registerCapsule( const UMLRTMessage * msg )
{
    transitionaction_____registerCapsule( msg );
    entryaction_____commWithSharedMem( msg );
}

void Capsule_GateWay::actionchain_____replySelfExec( const UMLRTMessage * msg )
{
    transitionaction_____replySelfExec( msg );
    entryaction_____commWithSharedMem( msg );
}

void Capsule_GateWay::actionchain_____setupSharedMem( const UMLRTMessage * msg )
{
    transitionaction_____setupSharedMem( msg );
    entryaction_____commWithSharedMem( msg );
}

Capsule_GateWay::State Capsule_GateWay::state_____commWithSharedMem( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_extComm:
        switch( msg->getSignalId() )
        {
        case ExtInterface::signal_event:
            actionchain_____processAndForwardEvent( msg );
            return commWithSharedMem;
        case ExtInterface::signal_registerToControl:
            actionchain_____registerCapsule( msg );
            return commWithSharedMem;
        case ExtInterface::signal_selfExec:
            actionchain_____replySelfExec( msg );
            return commWithSharedMem;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_commandTimer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____extCommand( msg );
            return commWithSharedMem;
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

Capsule_GateWay::State Capsule_GateWay::state_____configLoad( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_configTimer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____setupSharedMem( msg );
            return commWithSharedMem;
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






void Capsule_GateWay::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_commandTimer:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_commandTimer, index, true );
            break;
        case borderport_configTimer:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_configTimer, index, true );
            break;
        }
}

void Capsule_GateWay::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_commandTimer:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_commandTimer, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_commandTimer], index );
            break;
        case borderport_configTimer:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_configTimer, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_configTimer], index );
            break;
        }
}






static const UMLRTCommsPortRole portroles_border[] = 
{
    {
        Capsule_GateWay::port_commandTimer,
        "Timing",
        "commandTimer",
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
        Capsule_GateWay::port_configTimer,
        "Timing",
        "configTimer",
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
        Capsule_GateWay::port_extComm,
        "ExtInterface",
        "extComm",
        "",
        50,
        true,
        false,
        false,
        false,
        false,
        true,
        false
    }
};

static void instantiate_GateWay( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    slot->capsule = new Capsule_GateWay( &GateWay, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass GateWay = 
{
    "GateWay",
    NULL,
    instantiate_GateWay,
    0,
    NULL,
    3,
    portroles_border,
    0,
    NULL
};


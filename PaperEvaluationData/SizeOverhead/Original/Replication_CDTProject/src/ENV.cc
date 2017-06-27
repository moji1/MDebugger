
#include "ENV.hh"

#include "ConfigProtocol.hh"
#include "FailOver.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include "umlrttimerprotocol.hh"
#include <cstddef>
class UMLRTRtsInterface;
struct UMLRTCommsPort;

#include<iostream>

Capsule_ENV::Capsule_ENV( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, AnnouncmentServer1( borderPorts[borderport_AnnouncmentServer1] )
, AnnouncmentServer2( borderPorts[borderport_AnnouncmentServer2] )
, BITTimer( borderPorts[borderport_BITTimer] )
, ConfigComm( borderPorts[borderport_ConfigComm] )
, FailureTimer( borderPorts[borderport_FailureTimer] )
, GeneralTimer( borderPorts[borderport_GeneralTimer] )
, configTimer( borderPorts[borderport_configTimer] )
, AnnouncmentServerTimeout( 6 )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[ConfigFailure] = "ConfigFailure";
    stateNames[ReadConfig] = "ReadConfig";
    stateNames[Running] = "Running";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
}











void Capsule_ENV::bindPort( bool isBorder, int portId, int index )
{
}

void Capsule_ENV::unbindPort( bool isBorder, int portId, int index )
{
}





void Capsule_ENV::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case ReadConfig:
        currentState = state_____ReadConfig( &message );
        break;
    case Running:
        currentState = state_____Running( &message );
        break;
    case ConfigFailure:
        currentState = state_____ConfigFailure( &message );
        break;
    default:
        break;
    }
}

void Capsule_ENV::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____TransitionAction0( &message );
    currentState = ReadConfig;
}

const char * Capsule_ENV::getCurrentStateString() const
{
    return stateNames[currentState];
}




void Capsule_ENV::entryaction_____ConfigFailure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::ENV::ENV::ConfigFailure entry  */
    std::cout<<"ENV: The system is in Failure State, try to reload the config after 10 second\n";
    FailureTimer.informIn(UMLRTTimespec(10,0),4);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____ReadConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::ENV::ENV::ReadConfig entry  */
    std::cout<<"ENV: Reading the configuration \n";
    configTimer.informIn(UMLRTTimespec(3,0));
    systemConfig.loadConfig();
    std::cout<<"ENV: Reading the configuration was done\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::entryaction_____Running( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::ENV::ENV::Running entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____ConfigFailure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::ENV::ENV::ConfigFailure exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____ReadConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::ENV::ENV::ReadConfig exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::exitaction_____Running( const UMLRTMessage * msg )
{
    #define umlrtparam_MasterName ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::ENV::ENV::Running exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_MasterName
}

void Capsule_ENV::transitionaction_____ConfigNOK( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::ENV::ENV transition Config,ConfigFailure */
    std::cout<<"ENV: The configuration is not OK, the transition configCheck-> ConfigFailure was taken\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____MasterAnnouncment( const UMLRTMessage * msg )
{
    #define umlrtparam_MasterName ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::ENV::ENV transition Running,Running,IAMMaster:ConfigComm */
    std::cout<<this->getName()<<": Master Annoucment from "<< umlrtparam_MasterName<<"\n";
    if (strcmp((char *)umlrtparam_MasterName,"server1")==0)
    {
    systemConfig.MasterList[0]=true;
    if (AnnouncementServer1Id.isValid())
    AnnouncmentServer1.cancelTimer(AnnouncementServer1Id);
    AnnouncementServer1Id=AnnouncmentServer1.informEvery(UMLRTTimespec(AnnouncmentServerTimeout,0),4);
    }
    else if (strcmp((char *)umlrtparam_MasterName,"server2")==0)
    {
    systemConfig.MasterList[1]=true;
    if (AnnouncementServer2Id.isValid())
    AnnouncmentServer2.cancelTimer(AnnouncementServer2Id);
    AnnouncementServer2Id=AnnouncmentServer2.informEvery(UMLRTTimespec(AnnouncmentServerTimeout,0),4);
    }
    // the following code has been generated
    if ((systemConfig.RunningMode==1)&& (systemConfig.MasterList[0] ) && (systemConfig.MasterList[1]))
    std::cout<<this->getName()<<": Violation, there are 2 master in passive mode\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_MasterName
}

void Capsule_ENV::transitionaction_____QueryConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::ENV::ENV transition Running,Running,QueryConfig:ConfigComm */
    std::cout<<"ENV: The Config request replied at index" << msg->sapIndex0_<< "\n";
    int tempid=msg->sapIndex0_;
    ConfigComm.ReplyConfig(systemConfig).sendAt(tempid);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____RetryConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::ENV::ENV transition ConfigFailure,ReadConfig,timeout:FailureTimer */
    std::cout<<"ENV: retrying configuation, The transtion Failure -> readConfig was taken \n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____Server1Failure( const UMLRTMessage * msg )
{
    #define umlrtparam_ServerName ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::ENV::ENV transition Running,Running,IAmAlive:AnnouncmentServer1 */
    std::cout<<"ENV: No announcment from server1, remove server1 from masters list\n";
    systemConfig.MasterList[0]=false;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_ServerName
}

void Capsule_ENV::transitionaction_____TransitionAction0( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::ENV::ENV transition Init,ReadConfig */
    std::cout<<"ENV: Intialization\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____configLoaded( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::ENV::ENV transition ReadConfig,Config,timeout:configTimer */
    std::cout<<"ENV: The transition from ReadConfig -> Config was taken\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____configOK( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::ENV::ENV transition Config,Running */
    std::cout<<"ENV: The configuration is OK, the transition config-> Running was taken, sending signal to servers and clients \n";
    ConfigComm.StartUp(this->systemConfig).send();
    std::cout<<"ENV: ENV is in  Running State\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::transitionaction_____server2Failure( const UMLRTMessage * msg )
{
    #define umlrtparam_ServerName ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::ENV::ENV transition Running,Running,IAmAlive:AnnouncmentServer2 */
    std::cout<<"ENV: No announcment from server2, remove Server2 from masters list\n";
    systemConfig.MasterList[1]=false;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_ServerName
}

bool Capsule_ENV::action_____configOK__checkConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::ENV::ENV guard Config,Running */
    return systemConfig.ConfigOK;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_ENV::actionchain_____ConfigNOK( const UMLRTMessage * msg )
{
    transitionaction_____ConfigNOK( msg );
    entryaction_____ConfigFailure( msg );
}

void Capsule_ENV::actionchain_____MasterAnnouncment( const UMLRTMessage * msg )
{
    exitaction_____Running( msg );
    transitionaction_____MasterAnnouncment( msg );
    entryaction_____Running( msg );
}

void Capsule_ENV::actionchain_____QueryConfig( const UMLRTMessage * msg )
{
    exitaction_____Running( msg );
    transitionaction_____QueryConfig( msg );
    entryaction_____Running( msg );
}

void Capsule_ENV::actionchain_____RetryConfig( const UMLRTMessage * msg )
{
    exitaction_____ConfigFailure( msg );
    transitionaction_____RetryConfig( msg );
    entryaction_____ReadConfig( msg );
}

void Capsule_ENV::actionchain_____Server1Failure( const UMLRTMessage * msg )
{
    exitaction_____Running( msg );
    transitionaction_____Server1Failure( msg );
    entryaction_____Running( msg );
}

void Capsule_ENV::actionchain_____TransitionAction0( const UMLRTMessage * msg )
{
    transitionaction_____TransitionAction0( msg );
    entryaction_____ReadConfig( msg );
}

void Capsule_ENV::actionchain_____configLoaded( const UMLRTMessage * msg )
{
    exitaction_____ReadConfig( msg );
    transitionaction_____configLoaded( msg );
}

void Capsule_ENV::actionchain_____configOK( const UMLRTMessage * msg )
{
    transitionaction_____configOK( msg );
    entryaction_____Running( msg );
}

void Capsule_ENV::actionchain_____server2Failure( const UMLRTMessage * msg )
{
    exitaction_____Running( msg );
    transitionaction_____server2Failure( msg );
    entryaction_____Running( msg );
}

Capsule_ENV::State Capsule_ENV::choice_____Config( const UMLRTMessage * msg )
{
    if( action_____configOK__checkConfig( msg ) )
    {
        actionchain_____configOK( msg );
        return Running;
    }
    else
    {
        actionchain_____ConfigNOK( msg );
        return ConfigFailure;
    }
    return currentState;
}

Capsule_ENV::State Capsule_ENV::state_____ConfigFailure( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_FailureTimer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____RetryConfig( msg );
            return ReadConfig;
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

Capsule_ENV::State Capsule_ENV::state_____ReadConfig( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_configTimer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____configLoaded( msg );
            return choice_____Config( msg );
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

Capsule_ENV::State Capsule_ENV::state_____Running( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_ConfigComm:
        switch( msg->getSignalId() )
        {
        case ConfigProtocol::signal_IAMMaster:
            actionchain_____MasterAnnouncment( msg );
            return Running;
        case ConfigProtocol::signal_QueryConfig:
            actionchain_____QueryConfig( msg );
            return Running;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_AnnouncmentServer1:
        switch( msg->getSignalId() )
        {
        case FailOver::signal_IAmAlive:
            actionchain_____Server1Failure( msg );
            return Running;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_AnnouncmentServer2:
        switch( msg->getSignalId() )
        {
        case FailOver::signal_IAmAlive:
            actionchain_____server2Failure( msg );
            return Running;
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
        Capsule_ENV::port_AnnouncmentServer1,
        "Timing",
        "AnnouncmentServer1",
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
        Capsule_ENV::port_AnnouncmentServer2,
        "Timing",
        "AnnouncmentServer2",
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
        Capsule_ENV::port_BITTimer,
        "Timing",
        "BITTimer",
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
        Capsule_ENV::port_ConfigComm,
        "ConfigProtocol",
        "ConfigComm",
        "",
        7,
        true,
        true,
        false,
        false,
        false,
        true,
        false
    },
    {
        Capsule_ENV::port_FailureTimer,
        "Timing",
        "FailureTimer",
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
        Capsule_ENV::port_GeneralTimer,
        "Timing",
        "GeneralTimer",
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
        Capsule_ENV::port_configTimer,
        "Timing",
        "configTimer",
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

static void instantiate_ENV( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    slot->capsule = new Capsule_ENV( &ENV, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass ENV = 
{
    "ENV",
    NULL,
    instantiate_ENV,
    0,
    NULL,
    7,
    portroles_border,
    0,
    NULL
};



#include "Server.hh"

#include "ConfigProtocol.hh"
#include "FailOver.hh"
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

Capsule_Server::Capsule_Server( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: Capsule_Host( cd, st, border, internal, isStat )
, ConfigComm( borderPorts[borderport_ConfigComm] )
, KeepAliveTimer( borderPorts[borderport_KeepAliveTimer] )
, Master( borderPorts[borderport_Master] )
, MasterAnnounceTimer( borderPorts[borderport_MasterAnnounceTimer] )
, ServerComm( borderPorts[borderport_ServerComm] )
, Slave( borderPorts[borderport_Slave] )
, Timer( borderPorts[borderport_Timer] )
, KeepAliveTimeOut( 5 )
, AnnouncementTimeOut( 4 )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[Backup] = "Backup";
    stateNames[Backup__RunAsSlave] = "Backup__RunAsSlave";
    stateNames[Backup__TryBeMaster] = "Backup__TryBeMaster";
    stateNames[Failure] = "Failure";
    stateNames[RunAsMaster] = "RunAsMaster";
    stateNames[StandBy] = "StandBy";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
    int i = 0;
    while( i < 1 )
        history[i++] = SPECIAL_INTERNAL_STATE_UNVISITED;
}











void Capsule_Server::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_Master:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_Master, index, true );
            break;
        case borderport_ServerComm:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_ServerComm, index, true );
            break;
        case borderport_Slave:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_Slave, index, true );
            break;
        }
}

void Capsule_Server::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_Master:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_Master, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_Master], index );
            break;
        case borderport_ServerComm:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_ServerComm, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_ServerComm], index );
            break;
        case borderport_Slave:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_Slave, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_Slave], index );
            break;
        }
}





void Capsule_Server::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case StandBy:
        currentState = state_____StandBy( &message );
        break;
    case RunAsMaster:
        currentState = state_____RunAsMaster( &message );
        break;
    case Failure:
        currentState = state_____Failure( &message );
        break;
    case Backup__TryBeMaster:
        currentState = state_____Backup__TryBeMaster( &message );
        break;
    case Backup__RunAsSlave:
        currentState = state_____Backup__RunAsSlave( &message );
        break;
    default:
        break;
    }
}

void Capsule_Server::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____TransitionAction8( &message );
    currentState = StandBy;
}

const char * Capsule_Server::getCurrentStateString() const
{
    return stateNames[currentState];
}





void Capsule_Server::save_history( Capsule_Server::State compositeState, Capsule_Server::State subState )
{
    history[compositeState] = subState;
}

bool Capsule_Server::check_history( Capsule_Server::State compositeState, Capsule_Server::State subState )
{
    return history[compositeState] == subState;
}

void Capsule_Server::entryaction_____Backup( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Server::Backup entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__RunAsSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Server::Backup::RunAsSlave entry  */
    std::cout<<this->getName()<<": Running as Slave now\n";
    //if (KeepAliveTimerId.isValid())
    //	KeepAliveTimer.cancelTimer(KeepAliveTimerId);
    KeepAliveTimerId=KeepAliveTimer.informIn(UMLRTTimespec(6,0),4);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Backup__TryBeMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Server::Backup::TryBeMaster entry  */
    //std::cout<<this->getName()<<": trying to Be Master ------------\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Server::Failure entry  */
    //------
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____RunAsMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Server::RunAsMaster entry  */

    std::cout<<this->getName()<<": Run as Master now\n";
    ConfigComm.IAMMaster((char *)this->getName()).send();
    ts.getclock(ts);
    //messageID=messageID+1;
    if (logfile.is_open())
    logfile<<this->getName()<<",TranstionEnd,"<<messageID<<","<<ts.tv_sec<<","<<ts.tv_nsec<<"\n";
    logfile.flush();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::entryaction_____StandBy( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Server::StandBy entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Server::Backup exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__RunAsSlave( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Server::Backup::RunAsSlave exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____Backup__TryBeMaster( const UMLRTMessage * msg )
{
    #define umlrtparam_ServerName ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Server::Backup::TryBeMaster exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_ServerName
}

void Capsule_Server::exitaction_____Failure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Server::Failure exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____RunAsMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Server::RunAsMaster exit  */
    ts.getclock(ts);
    messageID=messageID+1;
    if (logfile.is_open())
    logfile<<this->getName()<<",TranstionStart,"<<messageID<<","<<ts.tv_sec<<","<<ts.tv_nsec<<"\n";
    //logfile.flush();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::exitaction_____StandBy( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const SystemConfig * )msg->getParam( 0 ) )
    #define rtdata ( (const SystemConfig * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Server::StandBy exit  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

void Capsule_Server::transitionaction_____Backup__BackToSlave( const UMLRTMessage * msg )
{
    #define umlrtparam_ServerName ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::TryBeMaster,Backup::Slave,IAmAlive */
    //std::cout<<this->getName()<<": The Master recovered itself, backing to slave mode\n";
    //if (TimerId.isValid())
    //	Timer.cancelTimer(TimerId);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_ServerName
}

void Capsule_Server::transitionaction_____Backup__KeepAliveMsg( const UMLRTMessage * msg )
{
    #define umlrtparam_ServerName ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::RunAsSlave,Backup::RunAsSlave,IAmAlive:Slave */
    std::cout<<this->getName()<<": Keep Alive Message from "<< umlrtparam_ServerName<<"\n";
    //if (KeepAliveTimerId.isValid())
    //	KeepAliveTimer.cancelTimer(KeepAliveTimerId);
    //KeepAliveTimerId=KeepAliveTimer.informEvery(UMLRTTimespec(6,0),4);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_ServerName
}

void Capsule_Server::transitionaction_____Backup__NokeepAlive( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Server::Backup transition Backup::RunAsSlave,Backup::TryBeMaster,timeout:KeepAliveTimer */
    //if (KeepAliveTimerId.isValid())
    //	KeepAliveTimer.cancelTimer(KeepAliveTimerId);
    std::cout<<this->getName()<<": No keep Alive message from Master, Try to be Master-------\n";
    //TimerId=Timer.informEvery(UMLRTTimespec(2,0),4);
    ConfigComm.QueryConfig().send();
    //std::cout<<this->getName()<<": trying to be Master\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____BeingMaster( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Server transition BeMaster,RunAsMaster */
    int r=random()%30+5;
    std::cout<<this->getName()<<": will go fail state after "<< r << "second\n";
    //TimerId=Timer.informEvery(360000);
    TimerId=Timer.informEvery(UMLRTTimespec(3600000,0),4);
    KeepAliveTimerId=KeepAliveTimer.informEvery(UMLRTTimespec(KeepAliveTimeOut,0),4);
    AnnouncementTimerId=MasterAnnounceTimer.informEvery(UMLRTTimespec(AnnouncementTimeOut,0),4);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____KeepAlive( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Server transition RunAsMaster,RunAsMaster,timeout:KeepAliveTimer */
    if (KeepAliveTimerId.isValid())
    KeepAliveTimer.cancelTimer(KeepAliveTimerId);
    KeepAliveTimerId=KeepAliveTimer.informEvery(UMLRTTimespec(KeepAliveTimeOut,0),4);
    if (config.RunningMode==1)
    Master.IAmAlive((char *)this->getName()).send();
    std::cout<<"Master: Keep Alive is sent\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____MasterAnnounce( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Server transition RunAsMaster,RunAsMaster,timeout:MasterAnnounceTimer */
    //messageID=messageID+1;
    ts.getclock(ts);
    if (logfile.is_open())
    logfile<<"keepAliveStart,"<<messageID<<",,"<<"\n";
    if (AnnouncementTimerId.isValid())
    MasterAnnounceTimer.cancelTimer(AnnouncementTimerId);
    AnnouncementTimerId=MasterAnnounceTimer.informEvery(UMLRTTimespec(AnnouncementTimeOut,0),4);
    int j=1;
    for (int i=0;i<=19000000;i++)
    j=j+1;
    j=j+1;
    std::cout<<j<<"\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____Recover( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Server transition Failure,Choice1,timeout:Timer */
    std::cout<<this->getName()<<": is recovering\n";
    if (TimerId.isValid())
    Timer.cancelTimer(TimerId);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____ServerFaliure( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Server transition RunAsMaster,Failure,timeout:Timer */
    if (KeepAliveTimerId.isValid())
    KeepAliveTimer.cancelTimer(KeepAliveTimerId);
    if (AnnouncementTimerId.isValid())
    MasterAnnounceTimer.cancelTimer(AnnouncementTimerId);
    if (TimerId.isValid())
    Timer.cancelTimer(TimerId);
    int r=random()%30+5;
    Timer.informEvery(UMLRTTimespec(r,0),4);
    std::cout<<this->getName()<<": Failure,  will recover after " << r << " seconds\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____ServiceRequest( const UMLRTMessage * msg )
{
    #define umlrtparam_ServiceID ( *(int *)msg->getParam( 0 ) )
    #define rtdata ( (int *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Server transition RunAsMaster,RunAsMaster,Request:ServerComm */
    //messageID=messageID+1;
    ts.getclock(ts);
    if (logfile.is_open())
    logfile<<this->getName()<<",ClientRequest,"<<messageID<<",,"<<"\n";
    std::cout<<this->getName()<<": Message from client replied at index "<<msg->sapIndex0_<<"\n";
    int tempid=msg->sapIndex0_;
    ServerComm.Reply(0).sendAt(tempid);
    int j=1;
    for (int i=0;i<=19000000;i++)
    j=j+1;
    j=j+1;
    std::cout<<j<<"\n";
    //ts.getclock(ts);
    //if (logfile.is_open())
    //logfile<<"CleintReply,"<<messageID<<","<<ts.tv_sec<<","<<ts.tv_nsec<<"\n";
    //logfile.flush();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_ServiceID
}

void Capsule_Server::transitionaction_____TransitionAction8( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Server transition Init,StandBy */
    std::cout<<this->getName()<<this->getIndex()<<": Intialization\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____TransitionAction9( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const SystemConfig * )msg->getParam( 0 ) )
    #define rtdata ( (const SystemConfig * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Server transition StandBy,CheckConfig,StartUp:ConfigComm */
    std::cout<<this->getName()<<": StartingUp\n";
    this->config=umlrtparam_config;
    std::cout<<this->getName()<<": Configuration is:"<< config.RunningMode<<"\n";
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

void Capsule_Server::transitionaction_____initTimer( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Server transition CheckConfig,RunAsMaster,timeout:MasterAnnounceTimer */
    logfile<<"capsuleName"<<",messageType,"<<"messageID"<<","<<"second"<<","<<"nano"<<"\n";    
    //UMLRTTimespec ts;
    //ts.getclock(ts);
    //this->setTimePointSecond();
    logfile.open(this->getName());
    //if (logfile.is_open())
    //	logfile<<ts.tv_sec<<":"<<ts.tv_nsec<<"\n";
    //logfile.close();
    int r=random()%30+5;
    std::cout<<this->getName()<<": will go fail state after "<< r << "second\n";
    //TimerId=Timer.informEvery(UMLRTTimespec(r,0),4);
    TimerId=Timer.informEvery(UMLRTTimespec(3600000,0),4);
    KeepAliveTimerId=KeepAliveTimer.informEvery(UMLRTTimespec(KeepAliveTimeOut,0),4);
    AnnouncementTimerId=MasterAnnounceTimer.informEvery(UMLRTTimespec(AnnouncementTimeOut,0),4);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Server::action_____ActiveMode__checkConfig( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Server guard Choice1,BeMaster */
    if (config.RunningMode==0)
    return true;
    else return false;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_Server::action_____Backup__CheckNoMaster__CheckNoServer( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const SystemConfig * )msg->getParam( 0 ) )
    #define rtdata ( (const SystemConfig * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Server::Backup guard Backup::Choice2,Backup::ExitPoint1 */
    std::cout<<"00000----------------------------------------------------000000\n";
    this->config=umlrtparam_config;
    if (!(this->config.MasterList[0] || this->config.MasterList[1]))
    {
    //Echo.Echo().send();
    //Timer.cancelTimer(TimerId);
    std::cout<<this->getName()<<": No one is Master, I am going to Be master\n";
    return true;
    }
    else if ((strcmp((char*)this->getName(),"server1")==0) && (config.MasterList[1]==false))
    {
    //Echo.Echo().send();
    //Timer.cancelTimer(TimerId);
    std::cout<<this->getName()<<": No one is Master, I am going to Be master\n";
    return true;
    }
    else if ((strcmp((char *)this->getName(),"server2"))==0 && (config.MasterList[0]==false))
    {
    //Echo.Echo().send();
    //Timer.cancelTimer(TimerId);
    std::cout<<this->getName()<<": No one is Master, I am going to Be master\n";
    return true;
    }
    std::cout<<"11111111-----------------------------------------111111111111\n";
    return false;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

bool Capsule_Server::action_____initTimer__CheckConfig( const UMLRTMessage * msg )
{
    #define umlrtparam_config ( *(const SystemConfig * )msg->getParam( 0 ) )
    #define rtdata ( (const SystemConfig * )msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Hosts::Server guard CheckConfig,RunAsMaster,timeout:MasterAnnounceTimer */
    if ((config.RunningMode==0) ||
    ((config.RunningMode==1) && (strcmp(config.MasterName,this->getName())==0)))
    return true;
    else 
    return false;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef umlrtparam_config
}

void Capsule_Server::actionchain_____Backup__BackToSlave( const UMLRTMessage * msg )
{
    exitaction_____Backup__TryBeMaster( msg );
    transitionaction_____Backup__BackToSlave( msg );
}

void Capsule_Server::actionchain_____Backup__KeepAliveMsg( const UMLRTMessage * msg )
{
    exitaction_____Backup__RunAsSlave( msg );
    transitionaction_____Backup__KeepAliveMsg( msg );
    entryaction_____Backup__RunAsSlave( msg );
}

void Capsule_Server::actionchain_____Backup__NokeepAlive( const UMLRTMessage * msg )
{
    exitaction_____Backup__RunAsSlave( msg );
    transitionaction_____Backup__NokeepAlive( msg );
    entryaction_____Backup__TryBeMaster( msg );
}

void Capsule_Server::actionchain_____Backup__ReplyConfig( const UMLRTMessage * msg )
{
    exitaction_____Backup__TryBeMaster( msg );
    save_history( Backup, Backup__TryBeMaster );
}

void Capsule_Server::actionchain_____Backup__backtoslave( const UMLRTMessage * msg )
{
    entryaction_____Backup__RunAsSlave( msg );
}

void Capsule_Server::actionchain_____Backup__new_transition_1( const UMLRTMessage * msg )
{
    entryaction_____Backup__TryBeMaster( msg );
}

void Capsule_Server::actionchain_____Backup__new_transition_2( const UMLRTMessage * msg )
{
    entryaction_____Backup__RunAsSlave( msg );
}

void Capsule_Server::actionchain_____Backup__new_transition_3( const UMLRTMessage * msg )
{
    entryaction_____Backup__RunAsSlave( msg );
}

void Capsule_Server::actionchain_____BeSlave( const UMLRTMessage * msg )
{
    entryaction_____Backup( msg );
}

void Capsule_Server::actionchain_____BeingMaster( const UMLRTMessage * msg )
{
    transitionaction_____BeingMaster( msg );
    entryaction_____RunAsMaster( msg );
}

void Capsule_Server::actionchain_____KeepAlive( const UMLRTMessage * msg )
{
    exitaction_____RunAsMaster( msg );
    transitionaction_____KeepAlive( msg );
    entryaction_____RunAsMaster( msg );
}

void Capsule_Server::actionchain_____MasterAnnounce( const UMLRTMessage * msg )
{
    exitaction_____RunAsMaster( msg );
    transitionaction_____MasterAnnounce( msg );
    entryaction_____RunAsMaster( msg );
}

void Capsule_Server::actionchain_____PassiveMode( const UMLRTMessage * msg )
{
    entryaction_____Backup( msg );
}

void Capsule_Server::actionchain_____Recover( const UMLRTMessage * msg )
{
    exitaction_____Failure( msg );
    transitionaction_____Recover( msg );
}

void Capsule_Server::actionchain_____ServerFaliure( const UMLRTMessage * msg )
{
    exitaction_____RunAsMaster( msg );
    transitionaction_____ServerFaliure( msg );
    entryaction_____Failure( msg );
}

void Capsule_Server::actionchain_____ServiceRequest( const UMLRTMessage * msg )
{
    exitaction_____RunAsMaster( msg );
    transitionaction_____ServiceRequest( msg );
    entryaction_____RunAsMaster( msg );
}

void Capsule_Server::actionchain_____TransitionAction21( const UMLRTMessage * msg )
{
    exitaction_____Backup( msg );
}

void Capsule_Server::actionchain_____TransitionAction8( const UMLRTMessage * msg )
{
    transitionaction_____TransitionAction8( msg );
    entryaction_____StandBy( msg );
}

void Capsule_Server::actionchain_____TransitionAction9( const UMLRTMessage * msg )
{
    exitaction_____StandBy( msg );
    transitionaction_____TransitionAction9( msg );
}

void Capsule_Server::actionchain_____initTimer( const UMLRTMessage * msg )
{
    transitionaction_____initTimer( msg );
    entryaction_____RunAsMaster( msg );
}

void Capsule_Server::actionchain_____purgeotherMessage( const UMLRTMessage * msg )
{
    exitaction_____Failure( msg );
    entryaction_____Failure( msg );
}

Capsule_Server::State Capsule_Server::junction_____Backup__ExitPoint1( const UMLRTMessage * msg )
{
    actionchain_____TransitionAction21( msg );
    return junction_____BeMaster( msg );
}

Capsule_Server::State Capsule_Server::junction_____Backup__Slave( const UMLRTMessage * msg )
{
    actionchain_____Backup__backtoslave( msg );
    return Backup__RunAsSlave;
}

Capsule_Server::State Capsule_Server::junction_____BeMaster( const UMLRTMessage * msg )
{
    actionchain_____BeingMaster( msg );
    return RunAsMaster;
}

Capsule_Server::State Capsule_Server::choice_____Backup__Choice2( const UMLRTMessage * msg )
{
    if( action_____Backup__CheckNoMaster__CheckNoServer( msg ) )
        return junction_____Backup__ExitPoint1( msg );
    else
        return junction_____Backup__Slave( msg );
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Backup__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Backup, Backup__TryBeMaster ) )
    {
        actionchain_____Backup__new_transition_1( msg );
        return Backup__TryBeMaster;
    }
    else if( check_history( Backup, Backup__RunAsSlave ) )
    {
        actionchain_____Backup__new_transition_2( msg );
        return Backup__RunAsSlave;
    }
    else if( check_history( Backup, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Backup__new_transition_3( msg );
        return Backup__RunAsSlave;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____CheckConfig( const UMLRTMessage * msg )
{
    if( action_____initTimer__CheckConfig( msg ) )
    {
        actionchain_____initTimer( msg );
        return RunAsMaster;
    }
    else
    {
        actionchain_____BeSlave( msg );
        return choice_____Backup__deephistory( msg );
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::choice_____Choice1( const UMLRTMessage * msg )
{
    if( action_____ActiveMode__checkConfig( msg ) )
        return junction_____BeMaster( msg );
    else
    {
        actionchain_____PassiveMode( msg );
        return choice_____Backup__deephistory( msg );
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::state_____Backup__RunAsSlave( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_KeepAliveTimer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____Backup__NokeepAlive( msg );
            return Backup__TryBeMaster;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_Slave:
        switch( msg->getSignalId() )
        {
        case FailOver::signal_IAmAlive:
            actionchain_____Backup__KeepAliveMsg( msg );
            return Backup__RunAsSlave;
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

Capsule_Server::State Capsule_Server::state_____Backup__TryBeMaster( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_ConfigComm:
        switch( msg->getSignalId() )
        {
        case ConfigProtocol::signal_ReplyConfig:
            actionchain_____Backup__ReplyConfig( msg );
            return choice_____Backup__Choice2( msg );
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

Capsule_Server::State Capsule_Server::state_____Failure( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_Timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____Recover( msg );
            return choice_____Choice1( msg );
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_ServerComm:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____purgeotherMessage( msg );
            return Failure;
        }
        return currentState;
    case port_Master:
        switch( msg->getSignalId() )
        {
        default:
            actionchain_____purgeotherMessage( msg );
            return Failure;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::state_____RunAsMaster( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_Timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____ServerFaliure( msg );
            return Failure;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_ServerComm:
        switch( msg->getSignalId() )
        {
        case Services::signal_Request:
            actionchain_____ServiceRequest( msg );
            return RunAsMaster;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_MasterAnnounceTimer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____MasterAnnounce( msg );
            return RunAsMaster;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_KeepAliveTimer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____KeepAlive( msg );
            return RunAsMaster;
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

Capsule_Server::State Capsule_Server::state_____StandBy( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_ConfigComm:
        switch( msg->getSignalId() )
        {
        case ConfigProtocol::signal_StartUp:
            actionchain_____TransitionAction9( msg );
            return choice_____CheckConfig( msg );
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
        Capsule_Server::port_ConfigComm,
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
        Capsule_Server::port_KeepAliveTimer,
        "Timing",
        "KeepAliveTimer",
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
        Capsule_Server::port_Master,
        "FailOver",
        "Master",
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
        Capsule_Server::port_MasterAnnounceTimer,
        "Timing",
        "MasterAnnounceTimer",
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
        Capsule_Server::port_ServerComm,
        "Services",
        "ServerComm",
        "",
        5,
        true,
        true,
        false,
        false,
        false,
        false,
        true
    },
    {
        Capsule_Server::port_Slave,
        "FailOver",
        "Slave",
        "",
        1,
        true,
        true,
        false,
        false,
        false,
        false,
        true
    },
    {
        Capsule_Server::port_Timer,
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

static void instantiate_Server( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    slot->capsule = new Capsule_Server( &Server, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass Server = 
{
    "Server",
    &Host,
    instantiate_Server,
    0,
    NULL,
    7,
    portroles_border,
    0,
    NULL
};


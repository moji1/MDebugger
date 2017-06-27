
#include "Simulator.hh"

#include "Client.hh"
#include "ENV.hh"
#include "Server.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtcapsulepart.hh"
#include "umlrtcommsport.hh"
#include "umlrtframeservice.hh"
#include "umlrtslot.hh"
#include <cstddef>
#include "umlrtcapsulerole.hh"
class UMLRTRtsInterface;

Capsule_Simulator::Capsule_Simulator( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, ENV( &slot->parts[part_ENV] )
, client( &slot->parts[part_client] )
, server1( &slot->parts[part_server1] )
, server2( &slot->parts[part_server2] )
{
}






void Capsule_Simulator::bindPort( bool isBorder, int portId, int index )
{
}

void Capsule_Simulator::unbindPort( bool isBorder, int portId, int index )
{
}

void Capsule_Simulator::initialize( const UMLRTMessage & msg )
{
}

void Capsule_Simulator::inject( const UMLRTMessage & msg )
{
}


static const UMLRTCapsuleRole roles[] = 
{
    {
        "ENV",
        &ENV,
        1,
        1,
        false,
        false
    },
    {
        "client",
        &Client,
        5,
        5,
        false,
        false
    },
    {
        "server1",
        &Server,
        1,
        1,
        false,
        false
    },
    {
        "server2",
        &Server,
        1,
        1,
        false,
        false
    }
};

static void instantiate_Simulator( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Simulator::part_client].slots[0]->ports[Capsule_Client::borderport_Server1Comm], 0, &slot->parts[Capsule_Simulator::part_server1].slots[0]->ports[Capsule_Server::borderport_ServerComm], 0 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Simulator::part_client].slots[0]->ports[Capsule_Client::borderport_Server2Comm], 0, &slot->parts[Capsule_Simulator::part_server2].slots[0]->ports[Capsule_Server::borderport_ServerComm], 0 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Simulator::part_client].slots[1]->ports[Capsule_Client::borderport_Server1Comm], 0, &slot->parts[Capsule_Simulator::part_server1].slots[0]->ports[Capsule_Server::borderport_ServerComm], 1 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Simulator::part_client].slots[1]->ports[Capsule_Client::borderport_Server2Comm], 0, &slot->parts[Capsule_Simulator::part_server2].slots[0]->ports[Capsule_Server::borderport_ServerComm], 1 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Simulator::part_client].slots[2]->ports[Capsule_Client::borderport_Server1Comm], 0, &slot->parts[Capsule_Simulator::part_server1].slots[0]->ports[Capsule_Server::borderport_ServerComm], 2 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Simulator::part_client].slots[2]->ports[Capsule_Client::borderport_Server2Comm], 0, &slot->parts[Capsule_Simulator::part_server2].slots[0]->ports[Capsule_Server::borderport_ServerComm], 2 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Simulator::part_client].slots[3]->ports[Capsule_Client::borderport_Server1Comm], 0, &slot->parts[Capsule_Simulator::part_server1].slots[0]->ports[Capsule_Server::borderport_ServerComm], 3 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Simulator::part_client].slots[3]->ports[Capsule_Client::borderport_Server2Comm], 0, &slot->parts[Capsule_Simulator::part_server2].slots[0]->ports[Capsule_Server::borderport_ServerComm], 3 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Simulator::part_client].slots[4]->ports[Capsule_Client::borderport_Server1Comm], 0, &slot->parts[Capsule_Simulator::part_server1].slots[0]->ports[Capsule_Server::borderport_ServerComm], 4 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Simulator::part_client].slots[4]->ports[Capsule_Client::borderport_Server2Comm], 0, &slot->parts[Capsule_Simulator::part_server2].slots[0]->ports[Capsule_Server::borderport_ServerComm], 4 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Simulator::part_server1].slots[0]->ports[Capsule_Server::borderport_Master], 0, &slot->parts[Capsule_Simulator::part_server2].slots[0]->ports[Capsule_Server::borderport_Slave], 0 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Simulator::part_server1].slots[0]->ports[Capsule_Server::borderport_Slave], 0, &slot->parts[Capsule_Simulator::part_server2].slots[0]->ports[Capsule_Server::borderport_Master], 0 );
    ENV.instantiate( NULL, slot->parts[Capsule_Simulator::part_ENV].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Simulator::part_ENV].slots[0], ENV.numPortRolesBorder ) );
    Client.instantiate( NULL, slot->parts[Capsule_Simulator::part_client].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Simulator::part_client].slots[0], Client.numPortRolesBorder ) );
    Client.instantiate( NULL, slot->parts[Capsule_Simulator::part_client].slots[1], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Simulator::part_client].slots[1], Client.numPortRolesBorder ) );
    Client.instantiate( NULL, slot->parts[Capsule_Simulator::part_client].slots[2], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Simulator::part_client].slots[2], Client.numPortRolesBorder ) );
    Client.instantiate( NULL, slot->parts[Capsule_Simulator::part_client].slots[3], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Simulator::part_client].slots[3], Client.numPortRolesBorder ) );
    Client.instantiate( NULL, slot->parts[Capsule_Simulator::part_client].slots[4], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Simulator::part_client].slots[4], Client.numPortRolesBorder ) );
    Server.instantiate( NULL, slot->parts[Capsule_Simulator::part_server1].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Simulator::part_server1].slots[0], Server.numPortRolesBorder ) );
    Server.instantiate( NULL, slot->parts[Capsule_Simulator::part_server2].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Simulator::part_server2].slots[0], Server.numPortRolesBorder ) );
    slot->capsule = new Capsule_Simulator( &Simulator, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass Simulator = 
{
    "Simulator",
    NULL,
    instantiate_Simulator,
    4,
    roles,
    0,
    NULL,
    0,
    NULL
};


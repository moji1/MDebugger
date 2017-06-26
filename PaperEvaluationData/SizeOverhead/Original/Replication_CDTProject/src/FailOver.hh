
#ifndef FAILOVER_HH
#define FAILOVER_HH

#include "umlrtoutsignal.hh"
#include "umlrtprotocol.hh"
#include "umlrtsignal.hh"
struct UMLRTCommsPort;

namespace FailOver
{
    enum SignalId
    {
        signal_IAmAlive = UMLRTSignal::FIRST_PROTOCOL_SIGNAL_ID
    };
    class Base : public UMLRTProtocol
    {
    public:
        Base( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal IAmAlive( char * ServerName ) const;
    };
    class Conj : public UMLRTProtocol
    {
    public:
        Conj( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal IAmAlive( char * ServerName ) const;
    };
};

#endif


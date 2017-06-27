
#ifndef SERVICES_HH
#define SERVICES_HH

#include "umlrtoutsignal.hh"
#include "umlrtprotocol.hh"
#include "umlrtsignal.hh"
struct UMLRTCommsPort;

namespace Services
{
    class Conj : public UMLRTProtocol
    {
    public:
        Conj( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal Reply( int Result ) const;
    };
    enum SignalId
    {
        signal_Reply = UMLRTSignal::FIRST_PROTOCOL_SIGNAL_ID,
        signal_Request
    };
    class Base : public UMLRTProtocol
    {
    public:
        Base( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal Request( int ServiceID ) const;
    };
};

#endif


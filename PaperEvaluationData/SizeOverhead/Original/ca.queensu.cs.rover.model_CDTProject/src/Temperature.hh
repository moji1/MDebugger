
#ifndef TEMPERATURE_HH
#define TEMPERATURE_HH

#include "umlrtoutsignal.hh"
#include "umlrtprotocol.hh"
#include "umlrtsignal.hh"
struct UMLRTCommsPort;

namespace Temperature
{
    class Base : public UMLRTProtocol
    {
    public:
        Base( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal startCollecting() const;
        UMLRTOutSignal stopCollecting() const;
    };
    class Conj : public UMLRTProtocol
    {
    public:
        Conj( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal dataCollected( void * value ) const;
    };
    enum SignalId
    {
        signal_dataCollected = UMLRTSignal::FIRST_PROTOCOL_SIGNAL_ID,
        signal_startCollecting,
        signal_stopCollecting
    };
};

#endif


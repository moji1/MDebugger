
#ifndef ECHO_HH
#define ECHO_HH

#include "umlrtoutsignal.hh"
#include "umlrtprotocol.hh"
#include "umlrtsignal.hh"
struct UMLRTCommsPort;

namespace Echo
{
    class Base : public UMLRTProtocol
    {
    public:
        Base( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal Echo() const;
    };
    class Conj : public UMLRTProtocol
    {
    public:
        Conj( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal Echo() const;
    };
    enum SignalId
    {
        signal_Echo = UMLRTSignal::FIRST_PROTOCOL_SIGNAL_ID
    };
};

#endif


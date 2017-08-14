
#ifndef ENDPROTOCOL_HH
#define ENDPROTOCOL_HH

#include "umlrtoutsignal.hh"
#include "umlrtprotocol.hh"
#include "umlrtsignal.hh"
struct UMLRTCommsPort;

namespace endProtocol
{
    class Base : public UMLRTProtocol
    {
    public:
        Base( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal end() const;
    };
    class Conj : public UMLRTProtocol
    {
    public:
        Conj( const UMLRTCommsPort * & srcPort );
    };
    enum SignalId
    {
        signal_end = UMLRTSignal::FIRST_PROTOCOL_SIGNAL_ID
    };
};

#endif


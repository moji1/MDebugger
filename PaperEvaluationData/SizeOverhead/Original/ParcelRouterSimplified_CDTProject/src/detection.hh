
#ifndef DETECTION_HH
#define DETECTION_HH

#include "Parcel.hh"
#include "umlrtoutsignal.hh"
#include "umlrtprotocol.hh"
#include "umlrtsignal.hh"
struct UMLRTCommsPort;

namespace detection
{
    class Base : public UMLRTProtocol
    {
    public:
        Base( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal detect( const Parcel & p ) const;
    };
    class Conj : public UMLRTProtocol
    {
    public:
        Conj( const UMLRTCommsPort * & srcPort );
    };
    enum SignalId
    {
        signal_detect = UMLRTSignal::FIRST_PROTOCOL_SIGNAL_ID
    };
};

#endif



#ifndef DETECTION_HH
#define DETECTION_HH

#include "umlrtoutsignal.hh"
#include "umlrtprotocol.hh"
#include "umlrtsignal.hh"
struct UMLRTCommsPort;

namespace Detection
{
    class Base : public UMLRTProtocol
    {
    public:
        Base( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal startDetection() const;
        UMLRTOutSignal stopDetection() const;
    };
    enum SignalId
    {
        signal_obstacleDetected = UMLRTSignal::FIRST_PROTOCOL_SIGNAL_ID,
        signal_startDetection,
        signal_stopDetection
    };
    class Conj : public UMLRTProtocol
    {
    public:
        Conj( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal obstacleDetected( double distance ) const;
    };
};

#endif


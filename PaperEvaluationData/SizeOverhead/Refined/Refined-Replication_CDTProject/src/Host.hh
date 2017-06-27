
#ifndef HOST_HH
#define HOST_HH

#include "Configuration.hh"
#include "HostInfo.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtmessage.hh"
#include "umlrttimerid.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

class Capsule_Host : public UMLRTCapsule
{
public:
    Capsule_Host( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
    enum PartId
    {
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    HostInfo hostInfo;
    Configuration config;
    UMLRTTimerId TimerId;
    HostInfo hostinfo;
    Configuration configuration;
    virtual void initialize( const UMLRTMessage & msg );
    virtual void inject( const UMLRTMessage & msg );
};
extern const UMLRTCapsuleClass Host;

#endif


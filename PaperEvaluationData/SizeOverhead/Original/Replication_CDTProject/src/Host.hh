
#ifndef HOST_HH
#define HOST_HH

#include "HostInfo.hh"
#include "SystemConfig.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtmessage.hh"
#include "umlrttimerid.hh"
#include "umlrttimespec.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

#include <fstream>

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
    SystemConfig config;
    UMLRTTimerId TimerId;
    HostInfo hostinfo;
    SystemConfig configuration;
    std::ofstream logfile;
    UMLRTTimespec ts;
    double messageID;
    virtual void initialize( const UMLRTMessage & msg );
    virtual void inject( const UMLRTMessage & msg );
};
extern const UMLRTCapsuleClass Host;

#endif


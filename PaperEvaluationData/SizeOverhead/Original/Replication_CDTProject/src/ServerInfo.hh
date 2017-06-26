
#ifndef SERVERINFO_HH
#define SERVERINFO_HH

#include "HostInfo.hh"
#include "ServerRole.hh"
#include "umlrtobjectclass.hh"

class ServerInfo : public HostInfo
{
public:
    ServerRole role;
    static const UMLRTObject_field fields[];
};
extern const UMLRTObject_class UMLRTType_ServerInfo;

#endif


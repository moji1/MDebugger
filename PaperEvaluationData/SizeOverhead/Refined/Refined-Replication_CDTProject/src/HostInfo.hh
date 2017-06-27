
#ifndef HOSTINFO_HH
#define HOSTINFO_HH

#include "HostStatus.hh"
#include "HostType.hh"
#include "umlrtobjectclass.hh"

class HostInfo
{
public:
    HostType hostType;
    HostStatus status;
    static const UMLRTObject_field fields[];
};
extern const UMLRTObject_class UMLRTType_HostInfo;

#endif


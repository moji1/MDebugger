
#include "HostInfo.hh"

#include "umlrtobjectclass.hh"
#include "umlrtobjectclassgeneric.hh"
#include <cstddef>

const UMLRTObject_field HostInfo::fields[] = 
{
    {
        "hostType",
        &UMLRTType_int,
        offsetof( HostInfo, hostType ),
        1,
        0
    },
    {
        "status",
        &UMLRTType_int,
        offsetof( HostInfo, status ),
        1,
        0
    }
};




const UMLRTObject_class UMLRTType_HostInfo = 
{
    UMLRTObjectInitialize<HostInfo>,
    UMLRTObjectCopy<HostInfo>,
    UMLRTObject_decode,
    UMLRTObject_encode,
    UMLRTObjectDestroy<HostInfo>,
    UMLRTObject_fprintf,
    "HostInfo",
    NULL,
    {
        sizeof( HostInfo ),
        2,
        HostInfo::fields
    },
    UMLRTOBJECTCLASS_DEFAULT_VERSION,
    UMLRTOBJECTCLASS_DEFAULT_BACKWARDS
};


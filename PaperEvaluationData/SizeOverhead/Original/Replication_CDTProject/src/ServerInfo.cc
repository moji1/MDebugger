
#include "ServerInfo.hh"

#include "umlrtobjectclass.hh"
#include "umlrtobjectclassgeneric.hh"
#include <cstddef>

const UMLRTObject_field ServerInfo::fields[] = 
{
    {
        "role",
        &UMLRTType_int,
        offsetof( ServerInfo, role ),
        1,
        0
    }
};



const UMLRTObject_class UMLRTType_ServerInfo = 
{
    UMLRTObjectInitialize<ServerInfo>,
    UMLRTObjectCopy<ServerInfo>,
    UMLRTObject_decode,
    UMLRTObject_encode,
    UMLRTObjectDestroy<ServerInfo>,
    UMLRTObject_fprintf,
    "ServerInfo",
    NULL,
    {
        sizeof( ServerInfo ),
        1,
        ServerInfo::fields
    },
    UMLRTOBJECTCLASS_DEFAULT_VERSION,
    UMLRTOBJECTCLASS_DEFAULT_BACKWARDS
};


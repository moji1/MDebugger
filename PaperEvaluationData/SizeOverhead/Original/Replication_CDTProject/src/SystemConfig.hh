
#ifndef SYSTEMCONFIG_HH
#define SYSTEMCONFIG_HH

#include "umlrtobjectclass.hh"

class SystemConfig
{
public:
    bool ConfigOK;
    int RunningMode;
    int MasterId;
    char * MasterName;
    bool MasterList[2];
    void loadConfig();
    static const UMLRTObject_field fields[];
};
extern const UMLRTObject_class UMLRTType_SystemConfig;

#endif


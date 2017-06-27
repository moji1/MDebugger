
#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include "umlrtobjectclass.hh"

class Configuration
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
extern const UMLRTObject_class UMLRTType_Configuration;

#endif


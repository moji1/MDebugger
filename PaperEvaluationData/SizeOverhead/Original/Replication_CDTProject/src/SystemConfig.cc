
#include "SystemConfig.hh"

#include "umlrtobjectclass.hh"
#include "umlrtobjectclassgeneric.hh"
#include <cstddef>

#include <iostream>
#include <fstream>
#include <limits.h>
#include <unistd.h>
using namespace std;

const UMLRTObject_field SystemConfig::fields[] = 
{
    {
        "ConfigOK",
        &UMLRTType_bool,
        offsetof( SystemConfig, ConfigOK ),
        1,
        0
    },
    {
        "RunningMode",
        &UMLRTType_int,
        offsetof( SystemConfig, RunningMode ),
        1,
        0
    },
    {
        "MasterId",
        &UMLRTType_int,
        offsetof( SystemConfig, MasterId ),
        1,
        0
    },
    {
        "MasterName",
        &UMLRTType_charptr,
        offsetof( SystemConfig, MasterName ),
        1,
        0
    },
    {
        "MasterList",
        &UMLRTType_bool,
        offsetof( SystemConfig, MasterList ),
        2,
        0
    }
};





void SystemConfig::loadConfig()
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::SystemConfig operation loadConfig */
    {
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Replication/Replication.uml Replication::Configuration operation loadConfig */
    std::cout<<"Config Class: load configuration from file\n";
    char result[PATH_MAX];
    readlink( "/proc/self/exe", result, PATH_MAX );
    string temps=string(result);
    size_t tempP=temps.rfind('/');
    if (tempP>0)
    {
    temps=temps.substr(0,tempP);
    }
    else
    temps="";
    string MasterConfigFileName="./Master.config";
    string RunningModeConfigFileName="./RunningMode.config";
    string MasterConfigPath=temps+MasterConfigFileName;
    string RunningModeConfigPath=temps+RunningModeConfigFileName;
    cout << RunningModeConfigPath << endl;
    //ifstream RunningModeConfigFile(RunningModeConfigPath.c_str());
    ifstream RunningModeConfigFile("./RunningMode.config");
    string line;
    if (RunningModeConfigFile.is_open())
    {
    (getline(RunningModeConfigFile,line));
    {
    if (atoi(line.c_str())==0)
    {
    this->RunningMode=0;
    this->ConfigOK=true;
    RunningModeConfigFile.close();
    cout<<"Configuration Loaded successfully, the running mode is active\n";
    //            			return true;
    }
    else if (atoi(line.c_str())==1)
    {
    this->RunningMode=1;
    //ifstream MasterConfigFile(MasterConfigPath.c_str());
    ifstream MasterConfigFile("Master.config");
    if (MasterConfigFile.is_open() && (getline(MasterConfigFile,line)))
    if (line=="server1" || line=="server2")
    {
    this->MasterName= new char[line.size()+1];
    strcpy(this->MasterName,line.c_str());
    cout <<"Master Name is:"<< this->MasterName<<endl;
    this->ConfigOK=true;
    cout << "configuration Loaded successfully, the running mode is passive|"
    <<" Master name is : "<<this->MasterName<<endl;
    RunningModeConfigFile.close();
    MasterConfigFile.close();
    //           					return true;
    }
    else
    {
    cout<<"Master Name is wrong, please fix it\n";
    this->ConfigOK=false;
    //           					return false;
    }
    else
    {
    cout<<"Master config file(Master.config) cann't be loaded, please fix it\n";
    this->ConfigOK=false;
    //         				return false;
    }
    }
    else
    {
    cout<< "The running mode value is incorrect, please fix that\n";
    this->ConfigOK=false;
    //       			return false;
    }
    }
    }
    else
    {
    cout<<"The Running Mode config(RunningMode.config) file can't be loaded, please fix it\n";
    this->ConfigOK=false;
    //     	return false;
    }/* UMLRTGEN-USERREGION-END */
    }
    /* UMLRTGEN-USERREGION-END */
}



const UMLRTObject_class UMLRTType_SystemConfig = 
{
    UMLRTObjectInitialize<SystemConfig>,
    UMLRTObjectCopy<SystemConfig>,
    UMLRTObject_decode,
    UMLRTObject_encode,
    UMLRTObjectDestroy<SystemConfig>,
    UMLRTObject_fprintf,
    "SystemConfig",
    NULL,
    {
        sizeof( SystemConfig ),
        5,
        SystemConfig::fields
    },
    UMLRTOBJECTCLASS_DEFAULT_VERSION,
    UMLRTOBJECTCLASS_DEFAULT_BACKWARDS
};


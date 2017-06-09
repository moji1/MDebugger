# Welcome to MDebugger Page
MDebugger is a model-level debugger of [PapyrysRT](https://eclipse.org/papyrus-rt/) (Papyrus for Real-time). Papyrus-RT is an Eclipse-based, open-source modelling development environment for UML-RT systems. It allows the generation of complete, executable code from models and advances the state-of-art via support for model representation with mixed graphical/textual notations and an extensible code generator. Uisng MDebugger, we can debug the UML-RT models on the target platfrom without using program debugger or refering to the generated code. The core of the MDebugger is developed at model-level uisng model transformation techniques. The more information about how MDebugger is developed can be found in our [FSE 2017] paper.


## Starting Guide:
### Virtual Machine

To facilitate the researchers and developers to use MDebugger, we prepare a virtual machine (VirtualBox VM) which including MDebugger source  and all required software (e.g., PapyrusRT).

We set up the credential, “osboxes” as the username and “osboxes.org” as the password, for the VM. The source code directory of MDebugger is /home/osboxes/MDebugger/... 
The PapyrusRT is insatled at /home/.../../

All the source are configured as Eclipse project and can be accessed by running PapyrusRT(/home/../). You can change and build the code using inside PapyrusRT.

## Running
Please note that we assume that you download the VM and successfully started the VM.
- Step 0 : Run The Eclipse
The eclipse IDE is located t /home/osbox/...,, use command line or explorer to run that using default workspace. After loading the Eclipse press the run bottom which will open a new Eclipse IDE. Inside the the new Eclipse IDE, you should see the  PingPong and counter model which can be used to test the debugging. 

- Step 1 : Generate the code for debugging
Righ click on the model that you want to debug and select the MDebugger menu. inside that use generate ... to generate the code.
- Step 2 : Buinld The generated code
- Step 3 : Debug the code using command line interface:
- Step 4 : Use the GUI interface:
### Developer Guide:
### Other Resources


### Support or Contact


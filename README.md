# Welcome to MDebugger Page
MDebugger is a model-level debugger of [PapyrysRT](https://eclipse.org/papyrus-rt/) (Papyrus for Real-time). Papyrus-RT is an Eclipse-based, open-source modelling development environment for UML-RT systems. It allows the generation of complete, executable code from models and advances the state-of-art via support for model representation with mixed graphical/textual notations and an extensible code generator. Uisng MDebugger, we can debug the UML-RT models on the target platfrom without using program debugger or refering to the generated code. The core of the MDebugger is developed at model-level uisng model transformation techniques. The more information about how MDebugger is developed can be found in our [FSE 2017] paper.


## Starting Guide:
### Virtual Machine

To facilitate the researchers and developers to use MDebugger, we prepare a [virtual machine](http://mase.cs.queensu.ca/fse-artifact/MDebugger.ova) uisng Oracle VirtualBox. It includes MDebugger source  and all required software (e.g., PapyrusRT). The virtual machine can be downloaded from the following link:
http://mase.cs.queensu.ca/fse-artifact/MDebugger.ova

[Here](https://www.youtube.com/watch?v=ZCfRtQ7-bh8 ) you can find out how to import the OVA file in Oracle Virtualbox. 


We set up the credential, “osboxes” as the username and “osboxes.org” as the password, for the VM. The source code directory of MDebugger is ```/home/osboxes/MDebugger``` and PapyrusRT is insatled at ```/home/osboxes/papyrus-rt-devtest-latest/Papyrus-RT/``` and can be run uisng ```/home/osboxes/papyrus-rt-devtest-latest/Papyrus-RT/eclipse```


## Running
Please note that we assume that you download the VM and successfully started the VM.
- Step 0 (Run PapyrusRT):
    1. Open a terminal and execute  ```/home/osboxes/papyrus-rt-devtest-latest/Papyrus-RT/eclipse```. 
    2. The Eclipse launcher will be shown, use the default workspace (i.e., /home/osboxes/workspace) and press the Launch.
  
    You can run the Eclipse from the lanucher menu at the left side of the desktop.

- Step 1  (Generate debuggable code)
    -For the purpose of evaluation, we have defined two sample models (PingPong and Counter) in the default workspace. To         generated  debuggable code for the model, frist open the models by double clicking on them, then right click on the root element and select generate code for debugging as shown in the following figure.
    
     you can create the modeling project based on the UML-RT language and generate the executable C++ code. you may find a tourial and detail information here.  

Righ click on the model that you want to debug and select the MDebugger menu. inside that use generate ... to generate the code.
- Step 2 : Buinld The generated code

- Step 3 : Debug the code using command line interface:

- Step 4 : Use the GUI interface:

### Developer Guide:
### Other Resources


### Support or Contact


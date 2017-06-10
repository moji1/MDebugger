# MDebugger Eclipse Integration
MDebugger can be used within Eclipse. To do so, we have provided an integration with the Eclipse debugger API.

## Running
This part assumes that you already [know how to run the MDebugger program in command-line](https://github.com/moji1/MDebugger), and that the steps 1 to 3 are performed, i.e., the instrumented code of the sample model (PingPong model or Counter model) has been generated using “generate code (Debug)“, and the instrumented code has been compiled. The following steps are performed in the second Eclipse instance.

- Step 1 (Execute the instrumented model)
  1. First, run the debuggable program of the counter model using the following command:
    
         ```
         cd /home/osboxes/runtime-MDebugger/Counter_CDTProject/src
         ./Debug__TopMain
         ```
     Upon successful execution, the following result should be shown in terminal.  
            ![alt text](screenshots/run-debuggable.png)
  2. This time, the MDebugger CLI tool will be only used as a wrapper. It only intends to interact with the Eclipse debugger interface. For convenience purpose, we have created a debug configuration that can be launched by selecting “Run / Run History / Counter-Debug“ in the Eclipse menubar. This debug configuration will execute sequentially two steps
      1. It first runs a debug target used for 
            

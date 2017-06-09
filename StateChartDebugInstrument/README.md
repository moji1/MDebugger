### Goal of the project
This project includes code which instruements the UML-RT model for the purpose of model-level debugging, 

Transformation rules used for instrumenting the models are implemented using the 
[Epsilon Object Language (EOL)](https://www.eclipse.org/epsilon/doc/eol/). 
EOL is a base language used by every tool of the Epsilon Modeling Suite. 
It supports a set of instructions to create, query, and modify models expressed in
languages described with the Eclipse Modeling Framework (EMF). 
Besides, as an imperative modeling language, it provides support for programming 
constructs and the Object Constraint Language. 

### Short description of the source code structure
```
│   ├── EOLScripts   --> contains all the developed script for the model transformation
│   │   ├── DetailTracing.eol      --> This script includes functions to add tracing statement to the models
│   │   ├── LTTngInstrument.eol    --> This script includes functions to add tracing statement compatible with [LTTNg tracing framework](http://lttng.org/)
│   │   ├── ModelClone.eol         --> This script includes functions to manage the clonning of UML-RT model, it is not complete.
│   │   ├── SRORule.eol            --> This script includes functions to apply the transformations are required to manage the execution of the model during debugging.
│   │   ├── SRORulev0.1.eol        --> The new optimized version of the SRORule, under development.
│   │   ├── UMLRTCodeGenUtil.eol   --> This script includes functions to generate code for debugging. 
│   │   ├── UMLRTCodeReflection.eol --> This script includes functions to generate code for veriable view and change. 
│   │   ├── UMLRTElementOperation.eol --> This script includes functions to create, and copy of the UML-RT model's element.
│   │   ├── UMLRTInstrument.eol       --> The older version of the MLRTInstrumentv0.1.eol.
│   │   ├── UMLRTInstrumentv0.1.eol   --> The is the main transformation file which manages the execution of the transformation for the whole model.
│   │   ├── UMLRTProfilesOperations.eol  --> This script includes functions to apply and query UML-RT related profiles, stereotypes.
│   │   ├── UMLRTQuery.eol     --> This script includes functions to execute different queries for the UML-RT models.
│   │   ├── modelQuery.eol     --> model query script
│   │   └── querySample.eol    --> --> sample script
│   ├── MetaModels         --> This folder includes all required metamodels for executing the transformation, usually these metamodels are installed with PapyrusRT.
│   │   ├── Ecore.ecore
│   │   ├── RTCppProperties.ecore
│   │   ├── RTCppProperties.profile.uml
│   │   ├── UML.ecore
│   │   ├── UMLPrimitiveType.uml
│   │   ├── UMLRT-RTS.uml
│   │   ├── UMLRTStateMachines.ecore
│   │   ├── UMLRealTime.ecore
│   │   ├── UMLRealTimeSM-addendum.dsmlvalidation.uml
│   │   ├── UMLRealTimeSM-addendum.profile.uml
│   │   ├── UMLRealTimeSM.genmodel
│   │   ├── default.ecore
│   │   ├── uml-rt.dsmlvalidation.uml
│   │   ├── uml-rt.genmodel
│   │   └── uml-rt.profile.uml
│   ├── ReadMe  --> readme of the project
│   └── SampleModels  --> contains sample model to test the scripts.
│       └── newtest3.uml

```

#### Main loop of the transformation
```
1 addGateWay () ;
2 refineStructure () ;
3 for ( SM in allStateMachines ){
4   refineForSRO ( SM );
5   for (s in allStates ) {
6     s.addTrace ( traceType );
7     s.guardCodes () ;
8   }
9  }
```

The above code shows the main function for instrumenting the
state machine of all capsules of the user-defined model. The
addGateway function is responsible for enabling the model
to interface with the debugger. It adds a UML-RT port to
each capsule. These ports are typed with a specific protocol
used for debugging purposes. The refineStructure function
adds required attributes and methods to each capsule
to support debugging. An example of attributes is a map used 
for maintaining breakpoint information, required by
the isDebug method during debugging. Examples of methods
added are the isDebug method and a set of methods
for supporting attribute view and change operations. The
isDebug method returns a boolean value indicating whether
a debugging session is opened or needs to be opened according
to the current state and the next transition about
to be taken. The generation of self-reflection methods was
inspired by work on physics engine development [1].  These
methods provide support for viewing and changing attribute
values. To do so, the refineStructure function iterates
over all attributes of each capsule and generates the corresponding
helper functions, such as getters and setters. The
refineForSRO function applies the four transformation rules
explained in Section 3 of our FSE paper [2]. For each transition chain, a helper
function is used in order to determine which instrumentation
rule needs to be applied, based on the kinds of source
and target states. Based on the result, the refineForSRO
calls the proper transformation rule. The addTrace function
adds support for detailed tracing operations to each state.
Finally, the guardCodes function adds a guard to every entry
and exit code to prevent them from being executed when
the capsule is being debugged.


### Standalone testing of the transformation scripts
The transformations scripts are called by other project to perfrom the required transformation, however it is possible to modify and  execute this script in standalone mode. Execute the trasformation script inside the Eclipse IDE, follow the below instruction:
- Righ click on the "UMLRTInstrumentv0.1.eol" and select Run as -> Run configuration 
![alt text](https://github.com/moji1/MDebugger/blob/master/StateChartDebugInstrument/Screenshots/Step1.png)
- Create a new configuration under EOL program and make sure the source is set to "UMLRTInstrumentv0.1.eol"
![alt text](https://github.com/moji1/MDebugger/blob/master/StateChartDebugInstrument/Screenshots/Step2.png)
- Select a Models tab in the dialog and add two model
![alt text](https://github.com/moji1/MDebugger/blob/master/StateChartDebugInstrument/Screenshots/Step3.png)
- The DebugginAgent model always should have the following configuraion
![alt text](https://github.com/moji1/MDebugger/blob/master/StateChartDebugInstrument/Screenshots/Step4.png)
- Configure the UMLRTModel to the model that you want to be transformed for debugging
![alt text](https://github.com/moji1/MDebugger/blob/master/StateChartDebugInstrument/Screenshots/Step5.png)

- Finally, press the run and see the result in the eclipse console and result model.


### Refrences
[1] http://media.steampowered.com/apps/valve/2014/Sergiy_Migdalskiy_Debugging_Techniques.pdf

[2] https://github.com/moji1/MDebugger/blob/master/FSE2017-Paper-182.pdf



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
to support debugging. An example of attributes is a map 


### Standalone testing of the transformation scripts


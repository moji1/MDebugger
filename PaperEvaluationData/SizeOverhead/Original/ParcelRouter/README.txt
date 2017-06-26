Name: Parcel Router with jam control
Author: Nicolas Hili <hili@cs.queensu.ca>
Version: 0.1
Last edited: February, 6, 2017
Papyrus-RT C++ Code Generator: 0.8.0.201612210512
Eclipse SDK: Neon.2 (4.6.2)
Operating System: Linux / Ubuntu 16.04.1 LTS 

Description:

    This models is a parcel router example. It generates a parcel every T
    seconds. The parcel is redirected by switchers to the correct bin.  Every
    parcel has to pass through different stages, composed of two chutes, one
    sensor and one switcher. Time spent on chutes and switchers are
    non-negligeable. Time spent for the detector to detect the parcel number is
    negligeable. All times are represented by capsule attributes and can be
    changed at run-time. Depending on the values set for timers, parcel jam can
    appear.  This model supports jam control and prevents new parcel from being
    generated / transfered from one chute to another if jam occurs in the
    following chute.


Change log:

0.1: initial version. 


Trace output:

Controller "DefaultController" running.
generating a parcel 1 on stage 0
Chute chute1 of stage 0 becomes occupied
Chute chute1 of stage 0 is now free
At stage sensor (2), turn left.
Chute chute2 of stage 0 becomes occupied
Chute chute2 of stage 0 is now free
Switcher switcher of stage 0 becomes occupied
Switcher switcher of stage 0 is now free
Chute chute1 of stage 1 becomes occupied
generating a parcel 1 on stage 0
Chute chute1 of stage 0 becomes occupied
Chute chute1 of stage 1 is now free
At stage sensor (1), turn right.
Chute chute2 of stage 1 becomes occupied
Chute chute1 of stage 0 is now free
At stage sensor (2), turn left.
Chute chute2 of stage 0 becomes occupied
Chute chute2 of stage 1 is now free
Switcher switcher of stage 1 becomes occupied
Chute chute2 of stage 0 is now free
Switcher switcher of stage 0 becomes occupied
Switcher switcher of stage 1 is now free
bin1 received Parcel (1)

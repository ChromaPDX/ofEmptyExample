## OpenFrameworks Empty Example
#### single environment for Android and iOS development
------
with sample code to boot and log orientation sensors

### development logs

`main.cpp` `testApp.h` and `testApp.cpp` merged and functions separated using `#if TARGET_OS_IPHONE` and `#ifdef TARGET_ANDROID`

#### iOS project:

testApp.cpp and main.cpp registered to compile as __ObjectiveC++__

#### Android project:

`config.make` includes `PROJECT_EXTERNAL_SOURCE_PATHS = ../src`

shared `src` folder location points to `${PARENT-1-PROJECT_LOC}/src`

look at `OFActivity.java` for sensor data pipeline

------
project inhabits an OpenFrameworks/apps folder of merged iOS and Android frameworks
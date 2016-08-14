#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=avr-gcc
CCC=avr-c++
CXX=avr-c++
FC=gfortran
AS=avr-as

# Macros
CND_PLATFORM=Arduino-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Tachometer.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=-c -g -Os -Wall -Wextra -std=gnu11 -ffunction-sections -fdata-sections -MMD -fno-fat-lto-objects -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10610 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR

# CC Compiler Flags
CCFLAGS=-Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10610 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR
CXXFLAGS=-Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10610 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../core/dist/Debug ../core/dist/Debug/core.a ../libraries/dist/Debug/libraries.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/telemetry.exe

${CND_DISTDIR}/${CND_CONF}/telemetry.exe: ../core/dist/Debug/core.a

${CND_DISTDIR}/${CND_CONF}/telemetry.exe: ../libraries/dist/Debug/libraries.a

${CND_DISTDIR}/${CND_CONF}/telemetry.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}
	avr-gcc -o ${CND_DISTDIR}/${CND_CONF}/telemetry ${OBJECTFILES} ${LDLIBSOPTIONS} -Wall -Wextra -Os -fuse-linker-plugin -Wl,--gc-sections,--relax -mmcu=atmega2560 -lm

${OBJECTDIR}/Tachometer.o: Tachometer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DUBRR0H -DUBRR1H -DUBRR2H -DUBRR3H -I../core -I../core/core -I../libraries/LiquidCrystal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Tachometer.o Tachometer.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DUBRR0H -DUBRR1H -DUBRR2H -DUBRR3H -I../core -I../core/core -I../libraries/LiquidCrystal -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:
	cd ../core && ${MAKE}  -f Makefile CONF=Debug
	cd ../libraries && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/telemetry.exe

# Subprojects
.clean-subprojects:
	cd ../core && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../libraries && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

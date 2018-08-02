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
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/a4d9402d/SCodec.o \
	${OBJECTDIR}/_ext/a4d9402d/SCodecStamp.o \
	${OBJECTDIR}/_ext/44f86887/SContainer.o \
	${OBJECTDIR}/_ext/44f86887/SHash.o \
	${OBJECTDIR}/Source/main.o


# C Compiler Flags
CFLAGS=-fopenmp

# CC Compiler Flags
CCFLAGS=-fopenmp
CXXFLAGS=-fopenmp

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lpthread

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fileshare

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fileshare: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fileshare ${OBJECTFILES} ${LDLIBSOPTIONS} -fopenmp

${OBJECTDIR}/_ext/a4d9402d/SCodec.o: ../../Share/Skernel/SCodecV1/SCodec.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a4d9402d
	$(COMPILE.cc) -g -I../../Share -I../../Space -IKernel -std=c++11 -o ${OBJECTDIR}/_ext/a4d9402d/SCodec.o ../../Share/Skernel/SCodecV1/SCodec.cpp

${OBJECTDIR}/_ext/a4d9402d/SCodecStamp.o: ../../Share/Skernel/SCodecV1/SCodecStamp.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a4d9402d
	$(COMPILE.cc) -g -I../../Share -I../../Space -IKernel -std=c++11 -o ${OBJECTDIR}/_ext/a4d9402d/SCodecStamp.o ../../Share/Skernel/SCodecV1/SCodecStamp.cpp

${OBJECTDIR}/_ext/44f86887/SContainer.o: ../../Space/Skernel/SContainer.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/44f86887
	$(COMPILE.cc) -g -I../../Share -I../../Space -IKernel -std=c++11 -o ${OBJECTDIR}/_ext/44f86887/SContainer.o ../../Space/Skernel/SContainer.cpp

${OBJECTDIR}/_ext/44f86887/SHash.o: ../../Space/Skernel/SHash.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/44f86887
	$(COMPILE.cc) -g -I../../Share -I../../Space -IKernel -std=c++11 -o ${OBJECTDIR}/_ext/44f86887/SHash.o ../../Space/Skernel/SHash.cpp

${OBJECTDIR}/Source/main.o: Source/main.cpp
	${MKDIR} -p ${OBJECTDIR}/Source
	$(COMPILE.cc) -g -I../../Share -I../../Space -IKernel -std=c++11 -o ${OBJECTDIR}/Source/main.o Source/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

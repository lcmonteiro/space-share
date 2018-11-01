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
	${OBJECTDIR}/_ext/44f86887/SAddress.o \
	${OBJECTDIR}/_ext/44f86887/SBase64.o \
	${OBJECTDIR}/_ext/44f86887/SContainer.o \
	${OBJECTDIR}/_ext/44f86887/SStream.o \
	${OBJECTDIR}/_ext/44f86887/STask.o \
	${OBJECTDIR}/_ext/a7c70a66/SLinuxDir.o \
	${OBJECTDIR}/_ext/a7c70a66/SLinuxFile.o \
	${OBJECTDIR}/_ext/a7c70a66/SLinuxIRC.o \
	${OBJECTDIR}/_ext/a7c70a66/SLinuxResource.o \
	${OBJECTDIR}/_ext/a7c70a66/SLinuxSocket.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lpthread

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testircservers

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testircservers: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testircservers ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/44f86887/SAddress.o: ../../Space/Skernel/SAddress.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/44f86887
	$(COMPILE.cc) -g -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/44f86887/SAddress.o ../../Space/Skernel/SAddress.cpp

${OBJECTDIR}/_ext/44f86887/SBase64.o: ../../Space/Skernel/SBase64.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/44f86887
	$(COMPILE.cc) -g -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/44f86887/SBase64.o ../../Space/Skernel/SBase64.cpp

${OBJECTDIR}/_ext/44f86887/SContainer.o: ../../Space/Skernel/SContainer.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/44f86887
	$(COMPILE.cc) -g -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/44f86887/SContainer.o ../../Space/Skernel/SContainer.cpp

${OBJECTDIR}/_ext/44f86887/SStream.o: ../../Space/Skernel/SStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/44f86887
	$(COMPILE.cc) -g -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/44f86887/SStream.o ../../Space/Skernel/SStream.cpp

${OBJECTDIR}/_ext/44f86887/STask.o: ../../Space/Skernel/STask.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/44f86887
	$(COMPILE.cc) -g -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/44f86887/STask.o ../../Space/Skernel/STask.cpp

${OBJECTDIR}/_ext/a7c70a66/SLinuxDir.o: ../../Space/Sstream/Slinux/SLinuxDir.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a7c70a66
	$(COMPILE.cc) -g -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/a7c70a66/SLinuxDir.o ../../Space/Sstream/Slinux/SLinuxDir.cpp

${OBJECTDIR}/_ext/a7c70a66/SLinuxFile.o: ../../Space/Sstream/Slinux/SLinuxFile.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a7c70a66
	$(COMPILE.cc) -g -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/a7c70a66/SLinuxFile.o ../../Space/Sstream/Slinux/SLinuxFile.cpp

${OBJECTDIR}/_ext/a7c70a66/SLinuxIRC.o: ../../Space/Sstream/Slinux/SLinuxIRC.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a7c70a66
	$(COMPILE.cc) -g -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/a7c70a66/SLinuxIRC.o ../../Space/Sstream/Slinux/SLinuxIRC.cpp

${OBJECTDIR}/_ext/a7c70a66/SLinuxResource.o: ../../Space/Sstream/Slinux/SLinuxResource.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a7c70a66
	$(COMPILE.cc) -g -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/a7c70a66/SLinuxResource.o ../../Space/Sstream/Slinux/SLinuxResource.cpp

${OBJECTDIR}/_ext/a7c70a66/SLinuxSocket.o: ../../Space/Sstream/Slinux/SLinuxSocket.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a7c70a66
	$(COMPILE.cc) -g -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/a7c70a66/SLinuxSocket.o ../../Space/Sstream/Slinux/SLinuxSocket.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -I../../Space -std=c++11 -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

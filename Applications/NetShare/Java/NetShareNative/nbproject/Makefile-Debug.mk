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
	${OBJECTDIR}/_ext/bcfdc1d6/SMachine.o \
	${OBJECTDIR}/_ext/bcfdc1d6/SShare.o \
	${OBJECTDIR}/_ext/b4b3c5cd/SCodec.o \
	${OBJECTDIR}/_ext/b4b3c5cd/SCodecStamp.o \
	${OBJECTDIR}/_ext/f60384c0/SStream.o \
	${OBJECTDIR}/_ext/d18f1f89/SIDirStream.o \
	${OBJECTDIR}/_ext/d18f1f89/SIFileStream.o \
	${OBJECTDIR}/_ext/d18f1f89/SIIrcStream.o \
	${OBJECTDIR}/_ext/d18f1f89/SIOIrcStream.o \
	${OBJECTDIR}/_ext/d18f1f89/SIOTcpStream.o \
	${OBJECTDIR}/_ext/d18f1f89/SITcpStream.o \
	${OBJECTDIR}/_ext/d18f1f89/SODirStream.o \
	${OBJECTDIR}/_ext/d18f1f89/SOFileStream.o \
	${OBJECTDIR}/_ext/d18f1f89/SOIrcStream.o \
	${OBJECTDIR}/_ext/d18f1f89/SOTcpStream.o \
	${OBJECTDIR}/_ext/54945f86/SIFileStream.o \
	${OBJECTDIR}/_ext/54945f86/SIOTcpStream.o \
	${OBJECTDIR}/_ext/54945f86/SITcpStream.o \
	${OBJECTDIR}/_ext/54945f86/SIUdpStream.o \
	${OBJECTDIR}/_ext/54945f86/SOFileStream.o \
	${OBJECTDIR}/_ext/54945f86/SOTcpStream.o \
	${OBJECTDIR}/_ext/54945f86/SOUdpStream.o \
	${OBJECTDIR}/_ext/7fb0f82f/SIDirStream.o \
	${OBJECTDIR}/_ext/7fb0f82f/SIFileStream.o \
	${OBJECTDIR}/_ext/7fb0f82f/SIUdpStream.o \
	${OBJECTDIR}/_ext/7fb0f82f/SODirStream.o \
	${OBJECTDIR}/_ext/7fb0f82f/SOFileStream.o \
	${OBJECTDIR}/_ext/7fb0f82f/SOUdpStream.o \
	${OBJECTDIR}/_ext/e3430ee7/SAddress.o \
	${OBJECTDIR}/_ext/e3430ee7/SBase64.o \
	${OBJECTDIR}/_ext/e3430ee7/SContainer.o \
	${OBJECTDIR}/_ext/e3430ee7/SHash.o \
	${OBJECTDIR}/_ext/e3430ee7/SLog.o \
	${OBJECTDIR}/_ext/d20b1ca9/SLinuxTask.o \
	${OBJECTDIR}/_ext/9a223a38/SLinuxDirectory.o \
	${OBJECTDIR}/_ext/9a223a38/SLinuxEvent.o \
	${OBJECTDIR}/_ext/9a223a38/SLinuxFile.o \
	${OBJECTDIR}/_ext/9a223a38/SLinuxIRC.o \
	${OBJECTDIR}/_ext/9a223a38/SLinuxResource.o \
	${OBJECTDIR}/_ext/9a223a38/SLinuxSocket.o \
	${OBJECTDIR}/_ext/8746b5fd/NetMachine.o \
	${OBJECTDIR}/NetShareJNI.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libNetShareNative.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libNetShareNative.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	g++ -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libNetShareNative.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/_ext/bcfdc1d6/SMachine.o: ../../../../Share/Sinterface/SMachine.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/bcfdc1d6
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bcfdc1d6/SMachine.o ../../../../Share/Sinterface/SMachine.cpp

${OBJECTDIR}/_ext/bcfdc1d6/SShare.o: ../../../../Share/Sinterface/SShare.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/bcfdc1d6
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bcfdc1d6/SShare.o ../../../../Share/Sinterface/SShare.cpp

${OBJECTDIR}/_ext/b4b3c5cd/SCodec.o: ../../../../Share/Skernel/SCodecV1/SCodec.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/b4b3c5cd
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b4b3c5cd/SCodec.o ../../../../Share/Skernel/SCodecV1/SCodec.cpp

${OBJECTDIR}/_ext/b4b3c5cd/SCodecStamp.o: ../../../../Share/Skernel/SCodecV1/SCodecStamp.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/b4b3c5cd
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b4b3c5cd/SCodecStamp.o ../../../../Share/Skernel/SCodecV1/SCodecStamp.cpp

${OBJECTDIR}/_ext/f60384c0/SStream.o: ../../../../Share/Skernel/SStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/f60384c0
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/f60384c0/SStream.o ../../../../Share/Skernel/SStream.cpp

${OBJECTDIR}/_ext/d18f1f89/SIDirStream.o: ../../../../Share/Sstream/Scode/Sbase/SIDirStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d18f1f89
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d18f1f89/SIDirStream.o ../../../../Share/Sstream/Scode/Sbase/SIDirStream.cpp

${OBJECTDIR}/_ext/d18f1f89/SIFileStream.o: ../../../../Share/Sstream/Scode/Sbase/SIFileStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d18f1f89
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d18f1f89/SIFileStream.o ../../../../Share/Sstream/Scode/Sbase/SIFileStream.cpp

${OBJECTDIR}/_ext/d18f1f89/SIIrcStream.o: ../../../../Share/Sstream/Scode/Sbase/SIIrcStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d18f1f89
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d18f1f89/SIIrcStream.o ../../../../Share/Sstream/Scode/Sbase/SIIrcStream.cpp

${OBJECTDIR}/_ext/d18f1f89/SIOIrcStream.o: ../../../../Share/Sstream/Scode/Sbase/SIOIrcStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d18f1f89
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d18f1f89/SIOIrcStream.o ../../../../Share/Sstream/Scode/Sbase/SIOIrcStream.cpp

${OBJECTDIR}/_ext/d18f1f89/SIOTcpStream.o: ../../../../Share/Sstream/Scode/Sbase/SIOTcpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d18f1f89
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d18f1f89/SIOTcpStream.o ../../../../Share/Sstream/Scode/Sbase/SIOTcpStream.cpp

${OBJECTDIR}/_ext/d18f1f89/SITcpStream.o: ../../../../Share/Sstream/Scode/Sbase/SITcpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d18f1f89
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d18f1f89/SITcpStream.o ../../../../Share/Sstream/Scode/Sbase/SITcpStream.cpp

${OBJECTDIR}/_ext/d18f1f89/SODirStream.o: ../../../../Share/Sstream/Scode/Sbase/SODirStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d18f1f89
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d18f1f89/SODirStream.o ../../../../Share/Sstream/Scode/Sbase/SODirStream.cpp

${OBJECTDIR}/_ext/d18f1f89/SOFileStream.o: ../../../../Share/Sstream/Scode/Sbase/SOFileStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d18f1f89
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d18f1f89/SOFileStream.o ../../../../Share/Sstream/Scode/Sbase/SOFileStream.cpp

${OBJECTDIR}/_ext/d18f1f89/SOIrcStream.o: ../../../../Share/Sstream/Scode/Sbase/SOIrcStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d18f1f89
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d18f1f89/SOIrcStream.o ../../../../Share/Sstream/Scode/Sbase/SOIrcStream.cpp

${OBJECTDIR}/_ext/d18f1f89/SOTcpStream.o: ../../../../Share/Sstream/Scode/Sbase/SOTcpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d18f1f89
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d18f1f89/SOTcpStream.o ../../../../Share/Sstream/Scode/Sbase/SOTcpStream.cpp

${OBJECTDIR}/_ext/54945f86/SIFileStream.o: ../../../../Share/Sstream/Sdata/Sbase/SIFileStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/54945f86
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/54945f86/SIFileStream.o ../../../../Share/Sstream/Sdata/Sbase/SIFileStream.cpp

${OBJECTDIR}/_ext/54945f86/SIOTcpStream.o: ../../../../Share/Sstream/Sdata/Sbase/SIOTcpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/54945f86
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/54945f86/SIOTcpStream.o ../../../../Share/Sstream/Sdata/Sbase/SIOTcpStream.cpp

${OBJECTDIR}/_ext/54945f86/SITcpStream.o: ../../../../Share/Sstream/Sdata/Sbase/SITcpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/54945f86
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/54945f86/SITcpStream.o ../../../../Share/Sstream/Sdata/Sbase/SITcpStream.cpp

${OBJECTDIR}/_ext/54945f86/SIUdpStream.o: ../../../../Share/Sstream/Sdata/Sbase/SIUdpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/54945f86
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/54945f86/SIUdpStream.o ../../../../Share/Sstream/Sdata/Sbase/SIUdpStream.cpp

${OBJECTDIR}/_ext/54945f86/SOFileStream.o: ../../../../Share/Sstream/Sdata/Sbase/SOFileStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/54945f86
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/54945f86/SOFileStream.o ../../../../Share/Sstream/Sdata/Sbase/SOFileStream.cpp

${OBJECTDIR}/_ext/54945f86/SOTcpStream.o: ../../../../Share/Sstream/Sdata/Sbase/SOTcpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/54945f86
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/54945f86/SOTcpStream.o ../../../../Share/Sstream/Sdata/Sbase/SOTcpStream.cpp

${OBJECTDIR}/_ext/54945f86/SOUdpStream.o: ../../../../Share/Sstream/Sdata/Sbase/SOUdpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/54945f86
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/54945f86/SOUdpStream.o ../../../../Share/Sstream/Sdata/Sbase/SOUdpStream.cpp

${OBJECTDIR}/_ext/7fb0f82f/SIDirStream.o: ../../../../Share/Sstream/Sitem/Sbase/SIDirStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/7fb0f82f
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7fb0f82f/SIDirStream.o ../../../../Share/Sstream/Sitem/Sbase/SIDirStream.cpp

${OBJECTDIR}/_ext/7fb0f82f/SIFileStream.o: ../../../../Share/Sstream/Sitem/Sbase/SIFileStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/7fb0f82f
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7fb0f82f/SIFileStream.o ../../../../Share/Sstream/Sitem/Sbase/SIFileStream.cpp

${OBJECTDIR}/_ext/7fb0f82f/SIUdpStream.o: ../../../../Share/Sstream/Sitem/Sbase/SIUdpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/7fb0f82f
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7fb0f82f/SIUdpStream.o ../../../../Share/Sstream/Sitem/Sbase/SIUdpStream.cpp

${OBJECTDIR}/_ext/7fb0f82f/SODirStream.o: ../../../../Share/Sstream/Sitem/Sbase/SODirStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/7fb0f82f
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7fb0f82f/SODirStream.o ../../../../Share/Sstream/Sitem/Sbase/SODirStream.cpp

${OBJECTDIR}/_ext/7fb0f82f/SOFileStream.o: ../../../../Share/Sstream/Sitem/Sbase/SOFileStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/7fb0f82f
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7fb0f82f/SOFileStream.o ../../../../Share/Sstream/Sitem/Sbase/SOFileStream.cpp

${OBJECTDIR}/_ext/7fb0f82f/SOUdpStream.o: ../../../../Share/Sstream/Sitem/Sbase/SOUdpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/7fb0f82f
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7fb0f82f/SOUdpStream.o ../../../../Share/Sstream/Sitem/Sbase/SOUdpStream.cpp

${OBJECTDIR}/_ext/e3430ee7/SAddress.o: ../../../../Space/Skernel/SAddress.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/e3430ee7
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e3430ee7/SAddress.o ../../../../Space/Skernel/SAddress.cpp

${OBJECTDIR}/_ext/e3430ee7/SBase64.o: ../../../../Space/Skernel/SBase64.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/e3430ee7
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e3430ee7/SBase64.o ../../../../Space/Skernel/SBase64.cpp

${OBJECTDIR}/_ext/e3430ee7/SContainer.o: ../../../../Space/Skernel/SContainer.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/e3430ee7
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e3430ee7/SContainer.o ../../../../Space/Skernel/SContainer.cpp

${OBJECTDIR}/_ext/e3430ee7/SHash.o: ../../../../Space/Skernel/SHash.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/e3430ee7
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e3430ee7/SHash.o ../../../../Space/Skernel/SHash.cpp

${OBJECTDIR}/_ext/e3430ee7/SLog.o: ../../../../Space/Skernel/SLog.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/e3430ee7
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e3430ee7/SLog.o ../../../../Space/Skernel/SLog.cpp

${OBJECTDIR}/_ext/d20b1ca9/SLinuxTask.o: ../../../../Space/Skernel/Slinux/SLinuxTask.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d20b1ca9
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d20b1ca9/SLinuxTask.o ../../../../Space/Skernel/Slinux/SLinuxTask.cpp

${OBJECTDIR}/_ext/9a223a38/SLinuxDirectory.o: ../../../../Space/Sresource/Slinux/SLinuxDirectory.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/9a223a38
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/9a223a38/SLinuxDirectory.o ../../../../Space/Sresource/Slinux/SLinuxDirectory.cpp

${OBJECTDIR}/_ext/9a223a38/SLinuxEvent.o: ../../../../Space/Sresource/Slinux/SLinuxEvent.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/9a223a38
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/9a223a38/SLinuxEvent.o ../../../../Space/Sresource/Slinux/SLinuxEvent.cpp

${OBJECTDIR}/_ext/9a223a38/SLinuxFile.o: ../../../../Space/Sresource/Slinux/SLinuxFile.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/9a223a38
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/9a223a38/SLinuxFile.o ../../../../Space/Sresource/Slinux/SLinuxFile.cpp

${OBJECTDIR}/_ext/9a223a38/SLinuxIRC.o: ../../../../Space/Sresource/Slinux/SLinuxIRC.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/9a223a38
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/9a223a38/SLinuxIRC.o ../../../../Space/Sresource/Slinux/SLinuxIRC.cpp

${OBJECTDIR}/_ext/9a223a38/SLinuxResource.o: ../../../../Space/Sresource/Slinux/SLinuxResource.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/9a223a38
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/9a223a38/SLinuxResource.o ../../../../Space/Sresource/Slinux/SLinuxResource.cpp

${OBJECTDIR}/_ext/9a223a38/SLinuxSocket.o: ../../../../Space/Sresource/Slinux/SLinuxSocket.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/9a223a38
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/9a223a38/SLinuxSocket.o ../../../../Space/Sresource/Slinux/SLinuxSocket.cpp

${OBJECTDIR}/_ext/8746b5fd/NetMachine.o: ../../Kernel/NetMachine.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/8746b5fd
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/8746b5fd/NetMachine.o ../../Kernel/NetMachine.cpp

${OBJECTDIR}/NetShareJNI.o: NetShareJNI.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../Kernel -I../../../../Share -I../../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/NetShareJNI.o NetShareJNI.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

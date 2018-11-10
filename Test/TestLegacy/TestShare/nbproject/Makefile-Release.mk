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
CND_CONF=Release
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
	${OBJECTDIR}/_ext/44f86887/SHash.o \
	${OBJECTDIR}/_ext/44f86887/SLog.o \
	${OBJECTDIR}/_ext/44f86887/SStream.o \
	${OBJECTDIR}/_ext/44f86887/STask.o \
	${OBJECTDIR}/_ext/a7c70a66/SLinuxDir.o \
	${OBJECTDIR}/_ext/a7c70a66/SLinuxFile.o \
	${OBJECTDIR}/_ext/a7c70a66/SLinuxIRC.o \
	${OBJECTDIR}/_ext/a7c70a66/SLinuxResource.o \
	${OBJECTDIR}/_ext/a7c70a66/SLinuxSocket.o \
	${OBJECTDIR}/_ext/2696bd01/SBufferShare.o \
	${OBJECTDIR}/_ext/2696bd01/SMachine.o \
	${OBJECTDIR}/_ext/2696bd01/SShare.o \
	${OBJECTDIR}/_ext/2b1074b8/SCodec.o \
	${OBJECTDIR}/_ext/2b1074b8/SCodecStamp.o \
	${OBJECTDIR}/_ext/2b1074b9/SCodec.o \
	${OBJECTDIR}/_ext/2b1074b9/SCodecStamp.o \
	${OBJECTDIR}/_ext/ea2a90a7/SIDirStream.o \
	${OBJECTDIR}/_ext/ea2a90a7/SIFileStream.o \
	${OBJECTDIR}/_ext/ea2a90a7/SIIrcStream.o \
	${OBJECTDIR}/_ext/ea2a90a7/SIOIrcStream.o \
	${OBJECTDIR}/_ext/ea2a90a7/SIOTcpStream.o \
	${OBJECTDIR}/_ext/ea2a90a7/SITcpStream.o \
	${OBJECTDIR}/_ext/ea2a90a7/SODirStream.o \
	${OBJECTDIR}/_ext/ea2a90a7/SOFileStream.o \
	${OBJECTDIR}/_ext/ea2a90a7/SOIrcStream.o \
	${OBJECTDIR}/_ext/ea2a90a7/SOTcpStream.o \
	${OBJECTDIR}/_ext/c7cd504a/SIFileStream.o \
	${OBJECTDIR}/_ext/c7cd504a/SIOTcpStream.o \
	${OBJECTDIR}/_ext/c7cd504a/SITcpStream.o \
	${OBJECTDIR}/_ext/c7cd504a/SIUdpStream.o \
	${OBJECTDIR}/_ext/c7cd504a/SOFileStream.o \
	${OBJECTDIR}/_ext/c7cd504a/SOTcpStream.o \
	${OBJECTDIR}/_ext/c7cd504a/SOUdpStream.o \
	${OBJECTDIR}/_ext/43ccc1/SIDirStream.o \
	${OBJECTDIR}/_ext/43ccc1/SIFileStream.o \
	${OBJECTDIR}/_ext/43ccc1/SIUdpStream.o \
	${OBJECTDIR}/_ext/43ccc1/SODirStream.o \
	${OBJECTDIR}/_ext/43ccc1/SOFileStream.o \
	${OBJECTDIR}/_ext/43ccc1/SOUdpStream.o \
	${OBJECTDIR}/Sinterface/STestBasic.o \
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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testshare

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testshare: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testshare ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/44f86887/SAddress.o: ../../Space/Skernel/SAddress.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/44f86887
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/44f86887/SAddress.o ../../Space/Skernel/SAddress.cpp

${OBJECTDIR}/_ext/44f86887/SBase64.o: ../../Space/Skernel/SBase64.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/44f86887
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/44f86887/SBase64.o ../../Space/Skernel/SBase64.cpp

${OBJECTDIR}/_ext/44f86887/SContainer.o: ../../Space/Skernel/SContainer.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/44f86887
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/44f86887/SContainer.o ../../Space/Skernel/SContainer.cpp

${OBJECTDIR}/_ext/44f86887/SHash.o: ../../Space/Skernel/SHash.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/44f86887
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/44f86887/SHash.o ../../Space/Skernel/SHash.cpp

${OBJECTDIR}/_ext/44f86887/SLog.o: ../../Space/Skernel/SLog.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/44f86887
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/44f86887/SLog.o ../../Space/Skernel/SLog.cpp

${OBJECTDIR}/_ext/44f86887/SStream.o: ../../Space/Skernel/SStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/44f86887
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/44f86887/SStream.o ../../Space/Skernel/SStream.cpp

${OBJECTDIR}/_ext/44f86887/STask.o: ../../Space/Skernel/STask.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/44f86887
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/44f86887/STask.o ../../Space/Skernel/STask.cpp

${OBJECTDIR}/_ext/a7c70a66/SLinuxDir.o: ../../Space/Sstream/Slinux/SLinuxDir.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a7c70a66
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a7c70a66/SLinuxDir.o ../../Space/Sstream/Slinux/SLinuxDir.cpp

${OBJECTDIR}/_ext/a7c70a66/SLinuxFile.o: ../../Space/Sstream/Slinux/SLinuxFile.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a7c70a66
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a7c70a66/SLinuxFile.o ../../Space/Sstream/Slinux/SLinuxFile.cpp

${OBJECTDIR}/_ext/a7c70a66/SLinuxIRC.o: ../../Space/Sstream/Slinux/SLinuxIRC.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a7c70a66
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a7c70a66/SLinuxIRC.o ../../Space/Sstream/Slinux/SLinuxIRC.cpp

${OBJECTDIR}/_ext/a7c70a66/SLinuxResource.o: ../../Space/Sstream/Slinux/SLinuxResource.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a7c70a66
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a7c70a66/SLinuxResource.o ../../Space/Sstream/Slinux/SLinuxResource.cpp

${OBJECTDIR}/_ext/a7c70a66/SLinuxSocket.o: ../../Space/Sstream/Slinux/SLinuxSocket.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a7c70a66
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a7c70a66/SLinuxSocket.o ../../Space/Sstream/Slinux/SLinuxSocket.cpp

${OBJECTDIR}/_ext/2696bd01/SBufferShare.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sinterface/SBufferShare.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2696bd01
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2696bd01/SBufferShare.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sinterface/SBufferShare.cpp

${OBJECTDIR}/_ext/2696bd01/SMachine.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sinterface/SMachine.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2696bd01
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2696bd01/SMachine.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sinterface/SMachine.cpp

${OBJECTDIR}/_ext/2696bd01/SShare.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sinterface/SShare.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2696bd01
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2696bd01/SShare.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sinterface/SShare.cpp

${OBJECTDIR}/_ext/2b1074b8/SCodec.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Skernel/SCodecV1/SCodec.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2b1074b8
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2b1074b8/SCodec.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Skernel/SCodecV1/SCodec.cpp

${OBJECTDIR}/_ext/2b1074b8/SCodecStamp.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Skernel/SCodecV1/SCodecStamp.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2b1074b8
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2b1074b8/SCodecStamp.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Skernel/SCodecV1/SCodecStamp.cpp

${OBJECTDIR}/_ext/2b1074b9/SCodec.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Skernel/SCodecV2/SCodec.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2b1074b9
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2b1074b9/SCodec.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Skernel/SCodecV2/SCodec.cpp

${OBJECTDIR}/_ext/2b1074b9/SCodecStamp.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Skernel/SCodecV2/SCodecStamp.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2b1074b9
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2b1074b9/SCodecStamp.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Skernel/SCodecV2/SCodecStamp.cpp

${OBJECTDIR}/_ext/ea2a90a7/SIDirStream.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Scode/Slinux/SIDirStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/ea2a90a7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/ea2a90a7/SIDirStream.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Scode/Slinux/SIDirStream.cpp

${OBJECTDIR}/_ext/ea2a90a7/SIFileStream.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Scode/Slinux/SIFileStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/ea2a90a7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/ea2a90a7/SIFileStream.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Scode/Slinux/SIFileStream.cpp

${OBJECTDIR}/_ext/ea2a90a7/SIIrcStream.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Scode/Slinux/SIIrcStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/ea2a90a7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/ea2a90a7/SIIrcStream.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Scode/Slinux/SIIrcStream.cpp

${OBJECTDIR}/_ext/ea2a90a7/SIOIrcStream.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Scode/Slinux/SIOIrcStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/ea2a90a7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/ea2a90a7/SIOIrcStream.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Scode/Slinux/SIOIrcStream.cpp

${OBJECTDIR}/_ext/ea2a90a7/SIOTcpStream.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Scode/Slinux/SIOTcpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/ea2a90a7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/ea2a90a7/SIOTcpStream.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Scode/Slinux/SIOTcpStream.cpp

${OBJECTDIR}/_ext/ea2a90a7/SITcpStream.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Scode/Slinux/SITcpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/ea2a90a7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/ea2a90a7/SITcpStream.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Scode/Slinux/SITcpStream.cpp

${OBJECTDIR}/_ext/ea2a90a7/SODirStream.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Scode/Slinux/SODirStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/ea2a90a7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/ea2a90a7/SODirStream.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Scode/Slinux/SODirStream.cpp

${OBJECTDIR}/_ext/ea2a90a7/SOFileStream.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Scode/Slinux/SOFileStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/ea2a90a7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/ea2a90a7/SOFileStream.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Scode/Slinux/SOFileStream.cpp

${OBJECTDIR}/_ext/ea2a90a7/SOIrcStream.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Scode/Slinux/SOIrcStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/ea2a90a7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/ea2a90a7/SOIrcStream.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Scode/Slinux/SOIrcStream.cpp

${OBJECTDIR}/_ext/ea2a90a7/SOTcpStream.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Scode/Slinux/SOTcpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/ea2a90a7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/ea2a90a7/SOTcpStream.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Scode/Slinux/SOTcpStream.cpp

${OBJECTDIR}/_ext/c7cd504a/SIFileStream.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Sdata/Slinux/SIFileStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c7cd504a
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c7cd504a/SIFileStream.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Sdata/Slinux/SIFileStream.cpp

${OBJECTDIR}/_ext/c7cd504a/SIOTcpStream.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Sdata/Slinux/SIOTcpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c7cd504a
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c7cd504a/SIOTcpStream.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Sdata/Slinux/SIOTcpStream.cpp

${OBJECTDIR}/_ext/c7cd504a/SITcpStream.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Sdata/Slinux/SITcpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c7cd504a
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c7cd504a/SITcpStream.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Sdata/Slinux/SITcpStream.cpp

${OBJECTDIR}/_ext/c7cd504a/SIUdpStream.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Sdata/Slinux/SIUdpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c7cd504a
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c7cd504a/SIUdpStream.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Sdata/Slinux/SIUdpStream.cpp

${OBJECTDIR}/_ext/c7cd504a/SOFileStream.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Sdata/Slinux/SOFileStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c7cd504a
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c7cd504a/SOFileStream.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Sdata/Slinux/SOFileStream.cpp

${OBJECTDIR}/_ext/c7cd504a/SOTcpStream.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Sdata/Slinux/SOTcpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c7cd504a
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c7cd504a/SOTcpStream.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Sdata/Slinux/SOTcpStream.cpp

${OBJECTDIR}/_ext/c7cd504a/SOUdpStream.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Sdata/Slinux/SOUdpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c7cd504a
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c7cd504a/SOUdpStream.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Sdata/Slinux/SOUdpStream.cpp

${OBJECTDIR}/_ext/43ccc1/SIDirStream.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Sitem/Slinux/SIDirStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/43ccc1
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/43ccc1/SIDirStream.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Sitem/Slinux/SIDirStream.cpp

${OBJECTDIR}/_ext/43ccc1/SIFileStream.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Sitem/Slinux/SIFileStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/43ccc1
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/43ccc1/SIFileStream.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Sitem/Slinux/SIFileStream.cpp

${OBJECTDIR}/_ext/43ccc1/SIUdpStream.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Sitem/Slinux/SIUdpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/43ccc1
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/43ccc1/SIUdpStream.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Sitem/Slinux/SIUdpStream.cpp

${OBJECTDIR}/_ext/43ccc1/SODirStream.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Sitem/Slinux/SODirStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/43ccc1
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/43ccc1/SODirStream.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Sitem/Slinux/SODirStream.cpp

${OBJECTDIR}/_ext/43ccc1/SOFileStream.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Sitem/Slinux/SOFileStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/43ccc1
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/43ccc1/SOFileStream.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Sitem/Slinux/SOFileStream.cpp

${OBJECTDIR}/_ext/43ccc1/SOUdpStream.o: /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Sitem/Slinux/SOUdpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/43ccc1
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/43ccc1/SOUdpStream.o /home/monteiro/workspace/m2bee/C++/ShareSpace/Share/Sstream/Sitem/Slinux/SOUdpStream.cpp

${OBJECTDIR}/Sinterface/STestBasic.o: Sinterface/STestBasic.cpp
	${MKDIR} -p ${OBJECTDIR}/Sinterface
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sinterface/STestBasic.o Sinterface/STestBasic.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

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

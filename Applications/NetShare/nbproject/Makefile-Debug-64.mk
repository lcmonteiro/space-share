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
CND_CONF=Debug-64
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/2be68436/SBufferShare.o \
	${OBJECTDIR}/_ext/2be68436/SMachine.o \
	${OBJECTDIR}/_ext/2be68436/SShare.o \
	${OBJECTDIR}/_ext/a4d9402d/SCodec.o \
	${OBJECTDIR}/_ext/a4d9402d/SCodecStamp.o \
	${OBJECTDIR}/_ext/a4d9402e/SCodec.o \
	${OBJECTDIR}/_ext/a4d9402e/SCodecStamp.o \
	${OBJECTDIR}/_ext/57b8de60/SStream.o \
	${OBJECTDIR}/_ext/eaeb0929/SIDirStream.o \
	${OBJECTDIR}/_ext/eaeb0929/SIFileStream.o \
	${OBJECTDIR}/_ext/eaeb0929/SIIrcStream.o \
	${OBJECTDIR}/_ext/eaeb0929/SIOIrcStream.o \
	${OBJECTDIR}/_ext/eaeb0929/SIOTcpStream.o \
	${OBJECTDIR}/_ext/eaeb0929/SITcpStream.o \
	${OBJECTDIR}/_ext/eaeb0929/SODirStream.o \
	${OBJECTDIR}/_ext/eaeb0929/SOFileStream.o \
	${OBJECTDIR}/_ext/eaeb0929/SOIrcStream.o \
	${OBJECTDIR}/_ext/eaeb0929/SOTcpStream.o \
	${OBJECTDIR}/_ext/6df04926/SIFileStream.o \
	${OBJECTDIR}/_ext/6df04926/SIOTcpStream.o \
	${OBJECTDIR}/_ext/6df04926/SITcpStream.o \
	${OBJECTDIR}/_ext/6df04926/SIUdpStream.o \
	${OBJECTDIR}/_ext/6df04926/SOFileStream.o \
	${OBJECTDIR}/_ext/6df04926/SOTcpStream.o \
	${OBJECTDIR}/_ext/6df04926/SOUdpStream.o \
	${OBJECTDIR}/_ext/990ce1cf/SIDirStream.o \
	${OBJECTDIR}/_ext/990ce1cf/SIFileStream.o \
	${OBJECTDIR}/_ext/990ce1cf/SIUdpStream.o \
	${OBJECTDIR}/_ext/990ce1cf/SODirStream.o \
	${OBJECTDIR}/_ext/990ce1cf/SOFileStream.o \
	${OBJECTDIR}/_ext/990ce1cf/SOUdpStream.o \
	${OBJECTDIR}/_ext/44f86887/SAddress.o \
	${OBJECTDIR}/_ext/44f86887/SBase64.o \
	${OBJECTDIR}/_ext/44f86887/SContainer.o \
	${OBJECTDIR}/_ext/44f86887/SHash.o \
	${OBJECTDIR}/_ext/44f86887/SLog.o \
	${OBJECTDIR}/_ext/400baf09/SLinuxTask.o \
	${OBJECTDIR}/_ext/8a47b498/SLinuxDirectory.o \
	${OBJECTDIR}/_ext/8a47b498/SLinuxEvent.o \
	${OBJECTDIR}/_ext/8a47b498/SLinuxFile.o \
	${OBJECTDIR}/_ext/8a47b498/SLinuxIRC.o \
	${OBJECTDIR}/_ext/8a47b498/SLinuxResource.o \
	${OBJECTDIR}/_ext/8a47b498/SLinuxSocket.o \
	${OBJECTDIR}/Kernel/NetMachine.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-Wall -m64
CXXFLAGS=-Wall -m64

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lpthread

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netshare

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netshare: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netshare ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/2be68436/SBufferShare.o: ../../Share/Sinterface/SBufferShare.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2be68436
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/2be68436/SBufferShare.o ../../Share/Sinterface/SBufferShare.cpp

${OBJECTDIR}/_ext/2be68436/SMachine.o: ../../Share/Sinterface/SMachine.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2be68436
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/2be68436/SMachine.o ../../Share/Sinterface/SMachine.cpp

${OBJECTDIR}/_ext/2be68436/SShare.o: ../../Share/Sinterface/SShare.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2be68436
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/2be68436/SShare.o ../../Share/Sinterface/SShare.cpp

${OBJECTDIR}/_ext/a4d9402d/SCodec.o: ../../Share/Skernel/SCodecV1/SCodec.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a4d9402d
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/a4d9402d/SCodec.o ../../Share/Skernel/SCodecV1/SCodec.cpp

${OBJECTDIR}/_ext/a4d9402d/SCodecStamp.o: ../../Share/Skernel/SCodecV1/SCodecStamp.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a4d9402d
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/a4d9402d/SCodecStamp.o ../../Share/Skernel/SCodecV1/SCodecStamp.cpp

${OBJECTDIR}/_ext/a4d9402e/SCodec.o: ../../Share/Skernel/SCodecV2/SCodec.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a4d9402e
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/a4d9402e/SCodec.o ../../Share/Skernel/SCodecV2/SCodec.cpp

${OBJECTDIR}/_ext/a4d9402e/SCodecStamp.o: ../../Share/Skernel/SCodecV2/SCodecStamp.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a4d9402e
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/a4d9402e/SCodecStamp.o ../../Share/Skernel/SCodecV2/SCodecStamp.cpp

${OBJECTDIR}/_ext/57b8de60/SStream.o: ../../Share/Skernel/SStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/57b8de60
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/57b8de60/SStream.o ../../Share/Skernel/SStream.cpp

${OBJECTDIR}/_ext/eaeb0929/SIDirStream.o: ../../Share/Sstream/Scode/Sbase/SIDirStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/eaeb0929
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/eaeb0929/SIDirStream.o ../../Share/Sstream/Scode/Sbase/SIDirStream.cpp

${OBJECTDIR}/_ext/eaeb0929/SIFileStream.o: ../../Share/Sstream/Scode/Sbase/SIFileStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/eaeb0929
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/eaeb0929/SIFileStream.o ../../Share/Sstream/Scode/Sbase/SIFileStream.cpp

${OBJECTDIR}/_ext/eaeb0929/SIIrcStream.o: ../../Share/Sstream/Scode/Sbase/SIIrcStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/eaeb0929
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/eaeb0929/SIIrcStream.o ../../Share/Sstream/Scode/Sbase/SIIrcStream.cpp

${OBJECTDIR}/_ext/eaeb0929/SIOIrcStream.o: ../../Share/Sstream/Scode/Sbase/SIOIrcStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/eaeb0929
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/eaeb0929/SIOIrcStream.o ../../Share/Sstream/Scode/Sbase/SIOIrcStream.cpp

${OBJECTDIR}/_ext/eaeb0929/SIOTcpStream.o: ../../Share/Sstream/Scode/Sbase/SIOTcpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/eaeb0929
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/eaeb0929/SIOTcpStream.o ../../Share/Sstream/Scode/Sbase/SIOTcpStream.cpp

${OBJECTDIR}/_ext/eaeb0929/SITcpStream.o: ../../Share/Sstream/Scode/Sbase/SITcpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/eaeb0929
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/eaeb0929/SITcpStream.o ../../Share/Sstream/Scode/Sbase/SITcpStream.cpp

${OBJECTDIR}/_ext/eaeb0929/SODirStream.o: ../../Share/Sstream/Scode/Sbase/SODirStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/eaeb0929
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/eaeb0929/SODirStream.o ../../Share/Sstream/Scode/Sbase/SODirStream.cpp

${OBJECTDIR}/_ext/eaeb0929/SOFileStream.o: ../../Share/Sstream/Scode/Sbase/SOFileStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/eaeb0929
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/eaeb0929/SOFileStream.o ../../Share/Sstream/Scode/Sbase/SOFileStream.cpp

${OBJECTDIR}/_ext/eaeb0929/SOIrcStream.o: ../../Share/Sstream/Scode/Sbase/SOIrcStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/eaeb0929
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/eaeb0929/SOIrcStream.o ../../Share/Sstream/Scode/Sbase/SOIrcStream.cpp

${OBJECTDIR}/_ext/eaeb0929/SOTcpStream.o: ../../Share/Sstream/Scode/Sbase/SOTcpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/eaeb0929
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/eaeb0929/SOTcpStream.o ../../Share/Sstream/Scode/Sbase/SOTcpStream.cpp

${OBJECTDIR}/_ext/6df04926/SIFileStream.o: ../../Share/Sstream/Sdata/Sbase/SIFileStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/6df04926
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/6df04926/SIFileStream.o ../../Share/Sstream/Sdata/Sbase/SIFileStream.cpp

${OBJECTDIR}/_ext/6df04926/SIOTcpStream.o: ../../Share/Sstream/Sdata/Sbase/SIOTcpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/6df04926
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/6df04926/SIOTcpStream.o ../../Share/Sstream/Sdata/Sbase/SIOTcpStream.cpp

${OBJECTDIR}/_ext/6df04926/SITcpStream.o: ../../Share/Sstream/Sdata/Sbase/SITcpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/6df04926
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/6df04926/SITcpStream.o ../../Share/Sstream/Sdata/Sbase/SITcpStream.cpp

${OBJECTDIR}/_ext/6df04926/SIUdpStream.o: ../../Share/Sstream/Sdata/Sbase/SIUdpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/6df04926
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/6df04926/SIUdpStream.o ../../Share/Sstream/Sdata/Sbase/SIUdpStream.cpp

${OBJECTDIR}/_ext/6df04926/SOFileStream.o: ../../Share/Sstream/Sdata/Sbase/SOFileStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/6df04926
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/6df04926/SOFileStream.o ../../Share/Sstream/Sdata/Sbase/SOFileStream.cpp

${OBJECTDIR}/_ext/6df04926/SOTcpStream.o: ../../Share/Sstream/Sdata/Sbase/SOTcpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/6df04926
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/6df04926/SOTcpStream.o ../../Share/Sstream/Sdata/Sbase/SOTcpStream.cpp

${OBJECTDIR}/_ext/6df04926/SOUdpStream.o: ../../Share/Sstream/Sdata/Sbase/SOUdpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/6df04926
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/6df04926/SOUdpStream.o ../../Share/Sstream/Sdata/Sbase/SOUdpStream.cpp

${OBJECTDIR}/_ext/990ce1cf/SIDirStream.o: ../../Share/Sstream/Sitem/Sbase/SIDirStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/990ce1cf
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/990ce1cf/SIDirStream.o ../../Share/Sstream/Sitem/Sbase/SIDirStream.cpp

${OBJECTDIR}/_ext/990ce1cf/SIFileStream.o: ../../Share/Sstream/Sitem/Sbase/SIFileStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/990ce1cf
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/990ce1cf/SIFileStream.o ../../Share/Sstream/Sitem/Sbase/SIFileStream.cpp

${OBJECTDIR}/_ext/990ce1cf/SIUdpStream.o: ../../Share/Sstream/Sitem/Sbase/SIUdpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/990ce1cf
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/990ce1cf/SIUdpStream.o ../../Share/Sstream/Sitem/Sbase/SIUdpStream.cpp

${OBJECTDIR}/_ext/990ce1cf/SODirStream.o: ../../Share/Sstream/Sitem/Sbase/SODirStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/990ce1cf
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/990ce1cf/SODirStream.o ../../Share/Sstream/Sitem/Sbase/SODirStream.cpp

${OBJECTDIR}/_ext/990ce1cf/SOFileStream.o: ../../Share/Sstream/Sitem/Sbase/SOFileStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/990ce1cf
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/990ce1cf/SOFileStream.o ../../Share/Sstream/Sitem/Sbase/SOFileStream.cpp

${OBJECTDIR}/_ext/990ce1cf/SOUdpStream.o: ../../Share/Sstream/Sitem/Sbase/SOUdpStream.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/990ce1cf
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/990ce1cf/SOUdpStream.o ../../Share/Sstream/Sitem/Sbase/SOUdpStream.cpp

${OBJECTDIR}/_ext/44f86887/SAddress.o: ../../Space/Skernel/SAddress.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/44f86887
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/44f86887/SAddress.o ../../Space/Skernel/SAddress.cpp

${OBJECTDIR}/_ext/44f86887/SBase64.o: ../../Space/Skernel/SBase64.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/44f86887
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/44f86887/SBase64.o ../../Space/Skernel/SBase64.cpp

${OBJECTDIR}/_ext/44f86887/SContainer.o: ../../Space/Skernel/SContainer.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/44f86887
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/44f86887/SContainer.o ../../Space/Skernel/SContainer.cpp

${OBJECTDIR}/_ext/44f86887/SHash.o: ../../Space/Skernel/SHash.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/44f86887
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/44f86887/SHash.o ../../Space/Skernel/SHash.cpp

${OBJECTDIR}/_ext/44f86887/SLog.o: ../../Space/Skernel/SLog.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/44f86887
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/44f86887/SLog.o ../../Space/Skernel/SLog.cpp

${OBJECTDIR}/_ext/400baf09/SLinuxTask.o: ../../Space/Skernel/Slinux/SLinuxTask.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/400baf09
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/400baf09/SLinuxTask.o ../../Space/Skernel/Slinux/SLinuxTask.cpp

${OBJECTDIR}/_ext/8a47b498/SLinuxDirectory.o: ../../Space/Sresource/Slinux/SLinuxDirectory.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/8a47b498
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/8a47b498/SLinuxDirectory.o ../../Space/Sresource/Slinux/SLinuxDirectory.cpp

${OBJECTDIR}/_ext/8a47b498/SLinuxEvent.o: ../../Space/Sresource/Slinux/SLinuxEvent.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/8a47b498
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/8a47b498/SLinuxEvent.o ../../Space/Sresource/Slinux/SLinuxEvent.cpp

${OBJECTDIR}/_ext/8a47b498/SLinuxFile.o: ../../Space/Sresource/Slinux/SLinuxFile.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/8a47b498
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/8a47b498/SLinuxFile.o ../../Space/Sresource/Slinux/SLinuxFile.cpp

${OBJECTDIR}/_ext/8a47b498/SLinuxIRC.o: ../../Space/Sresource/Slinux/SLinuxIRC.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/8a47b498
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/8a47b498/SLinuxIRC.o ../../Space/Sresource/Slinux/SLinuxIRC.cpp

${OBJECTDIR}/_ext/8a47b498/SLinuxResource.o: ../../Space/Sresource/Slinux/SLinuxResource.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/8a47b498
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/8a47b498/SLinuxResource.o ../../Space/Sresource/Slinux/SLinuxResource.cpp

${OBJECTDIR}/_ext/8a47b498/SLinuxSocket.o: ../../Space/Sresource/Slinux/SLinuxSocket.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/8a47b498
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/_ext/8a47b498/SLinuxSocket.o ../../Space/Sresource/Slinux/SLinuxSocket.cpp

${OBJECTDIR}/Kernel/NetMachine.o: Kernel/NetMachine.cpp
	${MKDIR} -p ${OBJECTDIR}/Kernel
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/Kernel/NetMachine.o Kernel/NetMachine.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -I../../Share -I../../Space -std=c++11 -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

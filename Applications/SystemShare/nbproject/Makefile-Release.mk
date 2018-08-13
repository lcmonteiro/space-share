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
	${OBJECTDIR}/_ext/4b4f2d1c/SIDirConnector.o \
	${OBJECTDIR}/_ext/4b4f2d1c/SIFileConnector.o \
	${OBJECTDIR}/_ext/4b4f2d1c/SODirConnector.o \
	${OBJECTDIR}/_ext/4b4f2d1c/SOFileConnector.o \
	${OBJECTDIR}/_ext/59b61bad/SIFileConnector.o \
	${OBJECTDIR}/_ext/59b61bad/SOFileConnector.o \
	${OBJECTDIR}/_ext/e30f1f44/SIDirConnector.o \
	${OBJECTDIR}/_ext/e30f1f44/SIFileConnector.o \
	${OBJECTDIR}/_ext/e30f1f44/SIIrcConnector.o \
	${OBJECTDIR}/_ext/e30f1f44/SIOIrcConnector.o \
	${OBJECTDIR}/_ext/e30f1f44/SODirConnector.o \
	${OBJECTDIR}/_ext/e30f1f44/SOFileConnector.o \
	${OBJECTDIR}/_ext/e30f1f44/SOIrcConnector.o \
	${OBJECTDIR}/_ext/a358a416/SBufferShare.o \
	${OBJECTDIR}/_ext/a358a416/SMachine.o \
	${OBJECTDIR}/_ext/696bf80d/SCodec.o \
	${OBJECTDIR}/_ext/696bf80d/SCodecStamp.o \
	${OBJECTDIR}/_ext/696bf80e/SCodec.o \
	${OBJECTDIR}/_ext/696bf80e/SCodecStamp.o \
	${OBJECTDIR}/_ext/211dca80/SConnector.o \
	${OBJECTDIR}/_ext/98985010/MProcessTransform.o \
	${OBJECTDIR}/_ext/98985010/MProcessYpsilon.o \
	${OBJECTDIR}/_ext/e5d54a7/SAddress.o \
	${OBJECTDIR}/_ext/e5d54a7/SBase64.o \
	${OBJECTDIR}/_ext/e5d54a7/SContainer.o \
	${OBJECTDIR}/_ext/e5d54a7/SHash.o \
	${OBJECTDIR}/_ext/6de7eec9/SLinuxTask.o \
	${OBJECTDIR}/_ext/e5d54a7/SLog.o \
	${OBJECTDIR}/_ext/4d177c58/SLinuxDirectory.o \
	${OBJECTDIR}/_ext/4d177c58/SLinuxEvent.o \
	${OBJECTDIR}/_ext/4d177c58/SLinuxFile.o \
	${OBJECTDIR}/_ext/4d177c58/SLinuxIRC.o \
	${OBJECTDIR}/_ext/4d177c58/SLinuxPoll.o \
	${OBJECTDIR}/_ext/4d177c58/SLinuxResource.o \
	${OBJECTDIR}/_ext/4d177c58/SLinuxSocket.o \
	${OBJECTDIR}/Source/main.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/systemshare

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/systemshare: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/systemshare ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/4b4f2d1c/SIDirConnector.o: ../../Share/SConnector/SDecoded/SMessage/SKernel/SIDirConnector.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/4b4f2d1c
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/4b4f2d1c/SIDirConnector.o ../../Share/SConnector/SDecoded/SMessage/SKernel/SIDirConnector.cpp

${OBJECTDIR}/_ext/4b4f2d1c/SIFileConnector.o: ../../Share/SConnector/SDecoded/SMessage/SKernel/SIFileConnector.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/4b4f2d1c
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/4b4f2d1c/SIFileConnector.o ../../Share/SConnector/SDecoded/SMessage/SKernel/SIFileConnector.cpp

${OBJECTDIR}/_ext/4b4f2d1c/SODirConnector.o: ../../Share/SConnector/SDecoded/SMessage/SKernel/SODirConnector.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/4b4f2d1c
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/4b4f2d1c/SODirConnector.o ../../Share/SConnector/SDecoded/SMessage/SKernel/SODirConnector.cpp

${OBJECTDIR}/_ext/4b4f2d1c/SOFileConnector.o: ../../Share/SConnector/SDecoded/SMessage/SKernel/SOFileConnector.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/4b4f2d1c
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/4b4f2d1c/SOFileConnector.o ../../Share/SConnector/SDecoded/SMessage/SKernel/SOFileConnector.cpp

${OBJECTDIR}/_ext/59b61bad/SIFileConnector.o: ../../Share/SConnector/SDecoded/SStream/SKernel/SIFileConnector.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/59b61bad
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/59b61bad/SIFileConnector.o ../../Share/SConnector/SDecoded/SStream/SKernel/SIFileConnector.cpp

${OBJECTDIR}/_ext/59b61bad/SOFileConnector.o: ../../Share/SConnector/SDecoded/SStream/SKernel/SOFileConnector.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/59b61bad
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/59b61bad/SOFileConnector.o ../../Share/SConnector/SDecoded/SStream/SKernel/SOFileConnector.cpp

${OBJECTDIR}/_ext/e30f1f44/SIDirConnector.o: ../../Share/SConnector/SEncoded/SMessage/SKernel/SIDirConnector.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/e30f1f44
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/e30f1f44/SIDirConnector.o ../../Share/SConnector/SEncoded/SMessage/SKernel/SIDirConnector.cpp

${OBJECTDIR}/_ext/e30f1f44/SIFileConnector.o: ../../Share/SConnector/SEncoded/SMessage/SKernel/SIFileConnector.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/e30f1f44
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/e30f1f44/SIFileConnector.o ../../Share/SConnector/SEncoded/SMessage/SKernel/SIFileConnector.cpp

${OBJECTDIR}/_ext/e30f1f44/SIIrcConnector.o: ../../Share/SConnector/SEncoded/SMessage/SKernel/SIIrcConnector.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/e30f1f44
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/e30f1f44/SIIrcConnector.o ../../Share/SConnector/SEncoded/SMessage/SKernel/SIIrcConnector.cpp

${OBJECTDIR}/_ext/e30f1f44/SIOIrcConnector.o: ../../Share/SConnector/SEncoded/SMessage/SKernel/SIOIrcConnector.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/e30f1f44
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/e30f1f44/SIOIrcConnector.o ../../Share/SConnector/SEncoded/SMessage/SKernel/SIOIrcConnector.cpp

${OBJECTDIR}/_ext/e30f1f44/SODirConnector.o: ../../Share/SConnector/SEncoded/SMessage/SKernel/SODirConnector.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/e30f1f44
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/e30f1f44/SODirConnector.o ../../Share/SConnector/SEncoded/SMessage/SKernel/SODirConnector.cpp

${OBJECTDIR}/_ext/e30f1f44/SOFileConnector.o: ../../Share/SConnector/SEncoded/SMessage/SKernel/SOFileConnector.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/e30f1f44
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/e30f1f44/SOFileConnector.o ../../Share/SConnector/SEncoded/SMessage/SKernel/SOFileConnector.cpp

${OBJECTDIR}/_ext/e30f1f44/SOIrcConnector.o: ../../Share/SConnector/SEncoded/SMessage/SKernel/SOIrcConnector.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/e30f1f44
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/e30f1f44/SOIrcConnector.o ../../Share/SConnector/SEncoded/SMessage/SKernel/SOIrcConnector.cpp

${OBJECTDIR}/_ext/a358a416/SBufferShare.o: ../../Share/SInterface/SBufferShare.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a358a416
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/a358a416/SBufferShare.o ../../Share/SInterface/SBufferShare.cpp

${OBJECTDIR}/_ext/a358a416/SMachine.o: ../../Share/SInterface/SMachine.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a358a416
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/a358a416/SMachine.o ../../Share/SInterface/SMachine.cpp

${OBJECTDIR}/_ext/696bf80d/SCodec.o: ../../Share/SKernel/SCodecV1/SCodec.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/696bf80d
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/696bf80d/SCodec.o ../../Share/SKernel/SCodecV1/SCodec.cpp

${OBJECTDIR}/_ext/696bf80d/SCodecStamp.o: ../../Share/SKernel/SCodecV1/SCodecStamp.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/696bf80d
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/696bf80d/SCodecStamp.o ../../Share/SKernel/SCodecV1/SCodecStamp.cpp

${OBJECTDIR}/_ext/696bf80e/SCodec.o: ../../Share/SKernel/SCodecV2/SCodec.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/696bf80e
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/696bf80e/SCodec.o ../../Share/SKernel/SCodecV2/SCodec.cpp

${OBJECTDIR}/_ext/696bf80e/SCodecStamp.o: ../../Share/SKernel/SCodecV2/SCodecStamp.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/696bf80e
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/696bf80e/SCodecStamp.o ../../Share/SKernel/SCodecV2/SCodecStamp.cpp

${OBJECTDIR}/_ext/211dca80/SConnector.o: ../../Share/SKernel/SConnector.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/211dca80
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/211dca80/SConnector.o ../../Share/SKernel/SConnector.cpp

${OBJECTDIR}/_ext/98985010/MProcessTransform.o: ../../Share/SKernel/SModule/MProcessTransform.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/98985010
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/98985010/MProcessTransform.o ../../Share/SKernel/SModule/MProcessTransform.cpp

${OBJECTDIR}/_ext/98985010/MProcessYpsilon.o: ../../Share/SKernel/SModule/MProcessYpsilon.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/98985010
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/98985010/MProcessYpsilon.o ../../Share/SKernel/SModule/MProcessYpsilon.cpp

${OBJECTDIR}/_ext/e5d54a7/SAddress.o: ../../Space/SKernel/SAddress.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/e5d54a7
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/e5d54a7/SAddress.o ../../Space/SKernel/SAddress.cpp

${OBJECTDIR}/_ext/e5d54a7/SBase64.o: ../../Space/SKernel/SBase64.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/e5d54a7
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/e5d54a7/SBase64.o ../../Space/SKernel/SBase64.cpp

${OBJECTDIR}/_ext/e5d54a7/SContainer.o: ../../Space/SKernel/SContainer.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/e5d54a7
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/e5d54a7/SContainer.o ../../Space/SKernel/SContainer.cpp

${OBJECTDIR}/_ext/e5d54a7/SHash.o: ../../Space/SKernel/SHash.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/e5d54a7
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/e5d54a7/SHash.o ../../Space/SKernel/SHash.cpp

${OBJECTDIR}/_ext/6de7eec9/SLinuxTask.o: ../../Space/SKernel/SLinux/SLinuxTask.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/6de7eec9
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/6de7eec9/SLinuxTask.o ../../Space/SKernel/SLinux/SLinuxTask.cpp

${OBJECTDIR}/_ext/e5d54a7/SLog.o: ../../Space/SKernel/SLog.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/e5d54a7
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/e5d54a7/SLog.o ../../Space/SKernel/SLog.cpp

${OBJECTDIR}/_ext/4d177c58/SLinuxDirectory.o: ../../Space/SResource/SLinux/SLinuxDirectory.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/4d177c58
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/4d177c58/SLinuxDirectory.o ../../Space/SResource/SLinux/SLinuxDirectory.cpp

${OBJECTDIR}/_ext/4d177c58/SLinuxEvent.o: ../../Space/SResource/SLinux/SLinuxEvent.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/4d177c58
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/4d177c58/SLinuxEvent.o ../../Space/SResource/SLinux/SLinuxEvent.cpp

${OBJECTDIR}/_ext/4d177c58/SLinuxFile.o: ../../Space/SResource/SLinux/SLinuxFile.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/4d177c58
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/4d177c58/SLinuxFile.o ../../Space/SResource/SLinux/SLinuxFile.cpp

${OBJECTDIR}/_ext/4d177c58/SLinuxIRC.o: ../../Space/SResource/SLinux/SLinuxIRC.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/4d177c58
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/4d177c58/SLinuxIRC.o ../../Space/SResource/SLinux/SLinuxIRC.cpp

${OBJECTDIR}/_ext/4d177c58/SLinuxPoll.o: ../../Space/SResource/SLinux/SLinuxPoll.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/4d177c58
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/4d177c58/SLinuxPoll.o ../../Space/SResource/SLinux/SLinuxPoll.cpp

${OBJECTDIR}/_ext/4d177c58/SLinuxResource.o: ../../Space/SResource/SLinux/SLinuxResource.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/4d177c58
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/4d177c58/SLinuxResource.o ../../Space/SResource/SLinux/SLinuxResource.cpp

${OBJECTDIR}/_ext/4d177c58/SLinuxSocket.o: ../../Space/SResource/SLinux/SLinuxSocket.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/4d177c58
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/_ext/4d177c58/SLinuxSocket.o ../../Space/SResource/SLinux/SLinuxSocket.cpp

${OBJECTDIR}/Source/main.o: Source/main.cpp
	${MKDIR} -p ${OBJECTDIR}/Source
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/Source/main.o Source/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

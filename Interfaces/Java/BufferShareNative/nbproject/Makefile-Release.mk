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
	${OBJECTDIR}/_ext/d3f72965/SBufferShare.o \
	${OBJECTDIR}/_ext/1b5f061c/SCodec.o \
	${OBJECTDIR}/_ext/1b5f061c/SCodecStamp.o \
	${OBJECTDIR}/_ext/3b3269b8/SContainer.o \
	${OBJECTDIR}/BufferShareJNI.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libBufferShareNative.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libBufferShareNative.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libBufferShareNative.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -static-libstdc++ -static-libgcc -shared -s -fPIC

${OBJECTDIR}/_ext/d3f72965/SBufferShare.o: ../../../Share/Sinterface/SBufferShare.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/d3f72965
	$(COMPILE.cc) -O2 -s -I../../../Share -I../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -o ${OBJECTDIR}/_ext/d3f72965/SBufferShare.o ../../../Share/Sinterface/SBufferShare.cpp

${OBJECTDIR}/_ext/1b5f061c/SCodec.o: ../../../Share/Skernel/SCodecV1/SCodec.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/1b5f061c
	$(COMPILE.cc) -O2 -s -I../../../Share -I../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -o ${OBJECTDIR}/_ext/1b5f061c/SCodec.o ../../../Share/Skernel/SCodecV1/SCodec.cpp

${OBJECTDIR}/_ext/1b5f061c/SCodecStamp.o: ../../../Share/Skernel/SCodecV1/SCodecStamp.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/1b5f061c
	$(COMPILE.cc) -O2 -s -I../../../Share -I../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -o ${OBJECTDIR}/_ext/1b5f061c/SCodecStamp.o ../../../Share/Skernel/SCodecV1/SCodecStamp.cpp

${OBJECTDIR}/_ext/3b3269b8/SContainer.o: ../../../Space/Skernel/SContainer.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/3b3269b8
	$(COMPILE.cc) -O2 -s -I../../../Share -I../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -o ${OBJECTDIR}/_ext/3b3269b8/SContainer.o ../../../Space/Skernel/SContainer.cpp

${OBJECTDIR}/BufferShareJNI.o: BufferShareJNI.cpp
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -s -I../../../Share -I../../../Space -I/home/monteiro/android-studio/jre/include -I/home/monteiro/android-studio/jre/include/linux -std=c++11 -fPIC  -o ${OBJECTDIR}/BufferShareJNI.o BufferShareJNI.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

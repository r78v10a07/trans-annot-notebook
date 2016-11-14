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
CND_PLATFORM=GNU-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/Blast7Factory.o \
	${OBJECTDIR}/src/UniprotFactory.o \
	${OBJECTDIR}/src/berror.o \
	${OBJECTDIR}/src/bmemory.o \
	${OBJECTDIR}/src/bstring.o \
	${OBJECTDIR}/src/main.o


# C Compiler Flags
CFLAGS=-Wall -g

# CC Compiler Flags
CCFLAGS=-Wall -g
CXXFLAGS=-Wall -g

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/myBlast2GO

${CND_DISTDIR}/${CND_CONF}/myBlast2GO: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/myBlast2GO ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/Blast7Factory.o: src/Blast7Factory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iincludes -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Blast7Factory.o src/Blast7Factory.cpp

${OBJECTDIR}/src/UniprotFactory.o: src/UniprotFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iincludes -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/UniprotFactory.o src/UniprotFactory.cpp

${OBJECTDIR}/src/berror.o: src/berror.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iincludes -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/berror.o src/berror.c

${OBJECTDIR}/src/bmemory.o: src/bmemory.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iincludes -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/bmemory.o src/bmemory.c

${OBJECTDIR}/src/bstring.o: src/bstring.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iincludes -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/bstring.o src/bstring.c

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iincludes -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/myBlast2GO

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

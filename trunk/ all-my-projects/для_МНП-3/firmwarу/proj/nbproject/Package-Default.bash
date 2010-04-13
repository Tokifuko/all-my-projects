#!/bin/bash -x

#
# Generated - do not edit!
#

# Macros
TOP=`pwd`
CND_PLATFORM=MinGW-Windows
CND_CONF=Default
CND_DISTDIR=dist
TMPDIR=build/${CND_CONF}/${CND_PLATFORM}/tmp-packaging
TMPDIRNAME=tmp-packaging
OUTPUT_PATH=C:/Program Files (x86)/Atmel/AVR Tools/AvrDragon/AVRDragon.exe
OUTPUT_BASENAME=AVRDragon.exe
PACKAGE_TOP_DIR=proj/

# Functions
function checkReturnCode
{
    rc=$?
    if [ $rc != 0 ]
    then
        exit $rc
    fi
}
function makeDirectory
# $1 directory path
# $2 permission (optional)
{
    mkdir -p "$1"
    checkReturnCode
    if [ "$2" != "" ]
    then
      chmod $2 "$1"
      checkReturnCode
    fi
}
function copyFileToTmpDir
# $1 from-file path
# $2 to-file path
# $3 permission
{
    cp "$1" "$2"
    checkReturnCode
    if [ "$3" != "" ]
    then
        chmod $3 "$2"
        checkReturnCode
    fi
}

# Setup
cd "${TOP}"
mkdir -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/package
rm -rf ${TMPDIR}
mkdir -p ${TMPDIR}

# Copy files and create directories and links
cd "${TOP}"
makeDirectory ${TMPDIR}/proj/bin
copyFileToTmpDir "${OUTPUT_PATH}" "${TMPDIR}/${PACKAGE_TOP_DIR}bin/${OUTPUT_BASENAME}" 0755


# Generate tar file
cd "${TOP}"
rm -f ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/package/proj.tar
cd ${TMPDIR}
tar -vcf ../../../../${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/package/proj.tar *
checkReturnCode

# Cleanup
cd "${TOP}"
rm -rf ${TMPDIR}

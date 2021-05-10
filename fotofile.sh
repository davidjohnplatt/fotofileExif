#!/bin/bash
#
#  script to drive exiftool and the c++ version of fotofile
#
if [ $# -ne 2 ]
then
    echo "Usage:  $0 sourcedirectory targetdirectory"
    exit 1
fi
SOURCEDIR=$1;export SOURCEDIR
TARGETDIR=$2;export TARGETDIR
#
# loop through files in the source directory
#
for i in `ls -1 $SOURCEDIR`
do
  exiftool $SOURCEDIR/$i >> /tmp/exiftool.txt 
  ./fotofile  $SOURCEDIR $TARGETDIR
done

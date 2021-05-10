# Author:  D.J. Platt
# Date:    May 2021
# Purpose: Copy photos to YYYY/MM/DD directory structure
#
This version of fotofile is written in C++.  Instead of reading the exifdata from the photo
it uses exiftool written by Phil Harvey to extract the data to a temporary file which is 
then parsed for the information needed to create the directory structure.  It is required 
that exiftool be installed. (https://exiftool.org).  Looping over the file list is done  
in the  sh file.  



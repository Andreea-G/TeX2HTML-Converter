#!/bin/bash

TEXFILE=$1
FILE=${TEXFILE%.tex}
INFILE=$FILE.xht
OUTFILE=$FILE.html
CSSFILE=$FILE.css
CSSFILE1=$FILE'_1'.css
INSTALLDIR=${HOME}/Dropbox/Courses/LyxtoHtml/tex2html/

echo $TEXFILE
echo $INFILE
echo $CSSFILE
echo $CSSFILE1

RERUNMK4HT=0
if [ $RERUNMK4HT -eq 1 ]; then
  echo "--- Running mk4ht ---"
  mk4ht mzlatex $TEXFILE "html,mathplayer" #> /dev/null
  cp $CSSFILE $CSSFILE1  #store for backup later
  # Clean up
  \rm $FILE.4ct $FILE.4tc $FILE.dvi $FILE.idv $FILE.lg $FILE.tmp $FILE.xref #Do not delete $FILE.toc, or the contents will not appear!
else
  cp $CSSFILE1 $CSSFILE
fi

echo
echo "--- Running xht2html ---"
./xht2html $INFILE $OUTFILE $CSSFILE $INSTALLDIR


echo Done.


#!/bin/bash

FILE=$1
FOLDER=$2
TEXFILE=$FOLDER/$FILE/$FILE.tex
INFILE=${TEXFILE%.tex}.xht
OUTFILE=${TEXFILE%.tex}.html
CSSFILE=${TEXFILE%.tex}.css
CSSFILE1=${TEXFILE%.tex}_1.css
#echo $TEXFILE

RERUNMK4HT=0
if [ $RERUNMK4HT -eq 1 ]; then
  echo "--- Running mk4ht ---"
  mk4ht mzlatex $TEXFILE "html,mathplayer" #> /dev/null
  cp $CSSFILE $CSSFILE1  #store for backup later
  # Clean up
  cd $FOLDER/$FILE
  \rm $FILE.4ct $FILE.4tc $FILE.dvi $FILE.idv $FILE.lg $FILE.tmp $FILE.xref #Do not delete $FILE.toc, or the contents will not appear!
  cd ..
  cd ..
else
  cp $CSSFILE1 $CSSFILE
fi

echo
echo "--- Running xht2html ---"
./xht2html $INFILE $OUTFILE $CSSFILE


echo Done.


#!/bin/bash

TEXFILE=$1
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
else
  cp $CSSFILE1 $CSSFILE
fi

mv $FILE.* $FOLDER/$FILE/
mv $FILE*x.png $FOLDER/$FILE/

echo
echo "--- Running xht2html ---"
./xht2html $INFILE $OUTFILE $CSSFILE

# Clean up
cd $FOLDER/$FILE
\rm $FILE.4ct $FILE.4tc $FILE.dvi $FILE.idv $FILE.lg $FILE.tmp $FILE.xref   #Do not delete $FILE.toc, or the contents will not appear!
cd ..
cd ..

echo DONE

#kill $(ps -A | grep -m1 firefox | awk '{print $1}')
#/Applications/Firefox.app/Contents/MacOS/firefox $OUTFILE &



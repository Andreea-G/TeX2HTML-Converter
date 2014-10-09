#!/bin/bash

FILE=$1
FOLDER=$2
TEXFILE=$FOLDER/$FILE/$FILE.tex
INFILE=$FOLDER/$FILE/$FILE.xht
OUTFILE=$FOLDER/$FILE/$FILE.html
CSSFILE=$FOLDER/$FILE/$FILE.css
echo $TEXFILE

echo "--- Running mk4ht ---"
#mk4ht mzlatex $TEXFILE "html,mathplayer" #> /dev/null
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



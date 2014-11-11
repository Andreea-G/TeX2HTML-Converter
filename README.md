## TeX and LyX to HTML Converter

### Description 

This program converts entire (La)TeX and LyX documents into HTML. The goal is to produce scientific documents (books, papers, lecture notes) that are interactive (in contrast to pdf files which are entirely static).

The program uses TeX4ht, but with added and improved features. In particular, new commands and environments are defined to allow for:

- Including videos via the `\includevideo` command, similarly to how `\includegraphics` is used for figures

- Toggle content: The reader can decide whether to hide or show a specific section, a detailed proof of a theorem, etc. (that would have otherwise been placed in an appendix)

- Alert boxes: Offering the option to click on a specific part of the text (or equation) in order to see a more detailed explanation

- Multiple columns in the document

- Full justify environment

In addition, several aspects are improved, including:

- The equations are re-aligned, with the equation labels correctly placed at the same level and at the end of the line

- Indentations following equations are corrected

### Installation

#### Option 1: easy install, Linux (Debian) only

Download the script [install.sh](https://raw.githubusercontent.com/Andreea-G/Tex2html-Converter/master/install.sh) anywhere on your computer. Then open a terminal, navigate to the folder where you downloaded the script, and run:

    chmod +x ./install.sh
    sudo ./install.sh
(Yes, you will need sudo!)

Now restart the terminal in order to use the program. 

That's it, if everything worked well then you're done!! :)

As of now, the script has only been tested on Ubuntu. I will extend it to Mac OS in the (very) near future.
No attempts have been made to make this work on Windows, but you're welcome to try following option 2 below.

#### Option 2: build from source

In order to use the program, you will need the following programs and libraries:

 - g++

 - [TeX4ht](http://access2science.com/latex/tutorial_txht.xhtml)

 - [RE2 library](https://code.google.com/p/re2/wiki/Install?tm=4) for regular expressions 

 - LyX (optional, if you prefer to write in LyX rather than directly in LaTeX)

Manually install the programs listed above.

Note! RE2 has two currently known bugs which you will need to fix. In order to install it properly, open a terminal and type the following:

    hg clone https://re2.googlecode.com/hg re2
    cd re2
    sudo make test
    sed -i -e 's/LDFLAGS?=/LDFLAGS?= -pthread/g' Makefile
    sudo make install
    sed -i -e 's/f.FirstMatch/\/\/f.FirstMatch/g' testinstall.cc
    sudo make testinstall

The first "sed" adds -pthread to LDFLAGS in Makefile. The second one comments out a line in testinstall.cc. The explanation for these can be found [here](https://code.google.com/p/re2/issues/detail?id=100).


Now open a terminal and navigate to your home folder where you will download this program. Type

    cd
    git clone https://github.com/Andreea-G/Tex2html-Converter.git
    cd .tex2html
    make

Finally, you need to add the executable to the user's path, so that you can run the program from any folder. For instance, in Linux and Mac you can do this by typing in a terminal

    install_dir=${HOME}/.tex2html
    cat >> ${HOME}/.bashrc << END
    # Allow user to execute tex2html, tex2pdf, lyx2html, lyx2pdf from anywhere 
    # (this block was added by tex2html's install script)
    if [ -d "$install_dir" ] ; then
        PATH="$install_dir:\$PATH"
    fi
    END

Now restart the terminal.


### Usage

There are 4 different options you can choose from. First, you can choose to work either in LyX or in LaTeX. Then, you can convert your .lyx or .tex document to either a .html or a .pdf. This is achieved by opening a terminal and typing either one of the following:

    tex2html <file>.tex
    tex2pdf <file>.tex
    lyx2html <file>.lyx
    lyx2pdf <file>.lyx

If you'll be writing directly in tex, then place 

>\input{preamble.tex}  
\input{html_commands.tex}

(in this order!) after  

>\documentclass[12pt]{article}  

 and before  

>\begin{document}

If you'll be writing in LyX, then place those same commands in the LyX preamble. 

To see what new LaTeX commands and environments you can use (for videos, toggles, alerts etc), have a look at the files preamble.tex, html_commands.tex, and pdf_commands.tex for a full description.


### Licence

GNU GPL version 2 or any later version


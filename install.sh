#!/usr/bin/env bash

install_dir=${HOME}/.tex2html

message_if_failed() {
    #print out message and quit if last command failed
    if [ $? -ne 0 ]; then 
        echo -e >&2 $1
        exit 2
    fi
}

# Test if g++ is installed. 
command -v g++ >/dev/null 2>&1 && has_gpp=true || has_gpp=false
if [ "$has_gpp" = false ]; then
	echo -e "\n"
	read -p "You need g++ to continue, would you like to install it? (y/n)  " user_input
	case $user_input in
		[Yy]* )
			#check for root priveledges here
			if [ "$(whoami)" != "root" ]; then 
				echo "Permission denied.  Please run this script with sudo, or you can't install the programs!"; 
				exit 3
			fi
			apt-get --yes install g++
			message_if_failed "Failed to install g++.  Major bummer! Please try to install it yourself and then rerun this script."
			;;
		[Nn]* )
        		echo "Ok :( ... You can install g++ on your own."
			echo "Exitting..."
			exit 4
			;;
	        * )
			echo "Input not understood.  Please type 'y' or 'n' next time."
			echo "Exitting..."
			exit 5
			;;
	esac
fi

# Test if any of git, tex4ht, Mercurial, and RE2 are missing
command -v git >/dev/null 2>&1 && has_git=true || has_git=false
command -v latex >/dev/null 2>&1 && has_latex=true || has_latex=false
command -v mk4ht >/dev/null 2>&1 && has_mk4ht=true || has_mk4ht=false
command -v hg >/dev/null 2>&1 && has_hg=true || has_hg=false
echo "#include <re2/re2.h>" > delete_this__checking_for_re2_header.h 
if g++ -E delete_this__checking_for_re2_header.h > /dev/null 2>&1; then
	has_re2_header=true
else
	has_re2_header=false
fi
\rm delete_this__checking_for_re2_header.h

# Notify user if there are any missing dependencies
programs_to_install=""
if [ "$has_latex" = false ]; then
	programs_to_install="${programs_to_install} texlive"
fi
if [ "$has_mk4ht" = false ]; then
	programs_to_install="${programs_to_install} tex4ht"
fi
if [ "$has_re2_header" = false ]; then
	if [ "$has_hg" = false ]; then
		programs_to_install="${programs_to_install} mercurial"
	fi
	programs_to_install="${programs_to_install} re2"
fi
if [ "$has_git" = false ]; then
	programs_to_install="${programs_to_install} git"
fi

if [ "$programs_to_install" != "" ]; then
	echo -e "\n\nThe following dependencies are not met: $programs_to_install"
	read -p "Would you like to install them now? (y/n)  " user_input
	case $user_input in
		[Yy]* )
			#check for root priveledges 
			if [ "$(whoami)" != "root" ]; then 
				echo "Please run this script with sudo, or you can't install the programs!"; 
				exit 3
			fi
			echo "Installing programs...  YAYYY!"
			;;
		[Nn]* )
        		echo "Ok :( ...  You can install those programs manually and rerun this script."
			echo "Exitting..."
			exit 4
			;;
	        * )
			echo "Input not understood.  Please type 'y' or 'n' next time."
			echo "Exitting..."
			exit 5
			;;
	esac
fi

if [ "$has_re2_header" = "false" ]; then
	if [ "$has_hg" = "false" ]; then
		apt-get --yes install mercurial #TODO: platform independence
		message_if_failed "Failed to install mercurial!"
	fi
	re2_folder=.re2
	hg clone https://re2.googlecode.com/hg ${HOME}/$re2_folder
	pushd ${HOME}/$re2_folder
	# This is RE2's first bug. We need to add -pthread to LDFLAGS in Makefile. See https://code.google.com/p/re2/issues/detail?id=100
	sed -i -e 's/LDFLAGS?=/LDFLAGS?= -pthread/g' Makefile
	echo -e "\n----- Running make test for re2 -----\n"
	make test
	echo -e "\n----- Running make install for re2 -----\n"
	make install 
	# This is RE2's second bug. This is a workaround until they fix it properly. See https://code.google.com/p/re2/issues/detail?id=100
	sed -i -e 's/f.FirstMatch/\/\/f.FirstMatch/g' testinstall.cc
	echo -e "\n----- Running make testinstall for re2 -----\n"
	make testinstall
	popd
#	\rm $re2_folder
	# update dynamic linker
	ldconfig
fi

if [ "$has_latex" = "false" ]; then
	apt-get --yes install texlive  #TODO: make platform indepedent
	message_if_failed "Failed to install texlive.  Major bummer!  Please install texlive manually and then rerun this script."
fi
if [ "$has_mk4ht" = "false" ]; then
	apt-get --yes install tex4ht  #TODO: make platform indepedent
	message_if_failed "Failed to install tex4ht.  Major bummer!  Please install tex4ht manually following the instructions found at http://access2science.com/latex/tutorial_txht.xhtml#x1-60002 and then rerun this script."
fi
if [ "$has_git" = "false" ]; then
	apt-get --yes install git  #TODO: make platform indepedent
	message_if_failed "Failed to install git.  Major bummer!  Please install tex4ht manually following the instructions found at http://git-scm.com/book/en/v2/Getting-Started-Installing-Git and then rerun this script."
fi

if [ -d  $install_dir ]; then
	echo >&2 "The folder $install_dir already exists!  Please delete it first and try reinstalling."
	exit 6
fi

echo "Downloading tex2html..."
git clone https://bitbucket.org/Andreea_G/tex2html.git $install_dir
message_if_failed "Failed to download tex2html..."
pushd $install_dir
echo "Installing..."
make

popd


# We now add the executable to the user's path
if [ "$(more ${HOME}/.bashrc | grep '.tex2html')" = "" ]; then 
	cat >> ${HOME}/.bashrc << END

# Allow user to execute tex2html, tex2pdf, lyx2html, lyx2pdf from anywhere (this block was added by tex2html's install script)
if [ -d "$install_dir" ] ; then
    PATH="$install_dir:\$PATH"
fi

END
fi

echo -e "\nDone!  Please restart your terminal to begin using the program.\n"


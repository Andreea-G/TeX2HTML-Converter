#!/usr/bin/env bash

install_dir=${HOME}/.tex2html

message_if_failed() {
    #print out message and quit if last command failed
    if [ $? -ne 0 ]; then 
        echo -e >&2 $1
        exit 2
    fi
}

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
if [ "$has_mk4ht" = false ]; then
	programs_to_install="${programs_to_install} tex4ht"
	if [ "$has_hg" = false ]; then
		programs_to_install="${programs_to_install} mercurial"
	fi
fi
if [ "$has_re2_header" = false ]; then
	programs_to_install="${programs_to_install} re2"
fi


if [ "$programs_to_install" != "" ]; then
	echo "The following dependencies are not met: $programs_to_install"
	read -p "Would you like to install them now? (y/n)  " user_input
    case $user_input in
        [Yy]* )
		#TODO: check for root priveledges here
		echo "Installing programs...  YAYYY!"
		;;
        [Nn]* )
        	echo "Ok, fine!  Be that way.  I never liked you anyway.  You can reinstall those programs manually and rerun this script."
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
		apt-get install mercurial #TODO: platform independence
		message_if_failed "Failed to install mercurial!"
	fi
	hg clone https://re2.googlecode.com/hg ${HOME}/.temporary_re2
	pushd ${HOME}/.temporary_re2
	# TODO: explain bug
	sed -i -e 's/LDFLAGS?=/LDFLAGS?= -pthread/g' Makefile
	make test
	make install 
	# re2 has an unresolved bug. This is a workaround until it gets fixed.   #TODO: provide link to the bug
	sed -i -e 's/f.FirstMatch/\/\/f.FirstMatch/g' testinstall.cc
	make testinstall
	popd
#	\rm .temporary_re2
	# update dynamic linker
	ldconfig
fi

if [ "$has_mk4ht" = "false" ]; then
	apt-get install tex4ht  #TODO: make platform indepedent
	message_if_failed "Failed to install tex4ht.  Major bummer, dude!"
fi


if [ -d  $install_dir ]; then
	echo >&2 "The folder $install_dir already exists!  Whhoaaa boy!  Please delete it first and try reinstalling."
	exit 3
fi

echo "Downloading tex2html..."
git clone https://bitbucket.org/Andreea_G/tex2html.git $install_dir
message_if_failed "Failed to download tex2html..."
pushd $install_dir
echo "Installing..."
make

popd


# We now add the executable to the user's path
cat >> ${HOME}/.profile << END

# Allow user to execute tex2html from anywhere (this block was added by tex2html's install script)
if [ -d "$install_dir" ] ; then
    PATH="$install_dir:\$PATH"
fi

END
# source the .profile so we don't have to log out and back in
source ${HOME}/.profile



echo "Done!"


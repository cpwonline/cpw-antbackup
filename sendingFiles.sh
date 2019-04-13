#!/bin/bash

if [ -n "$1" ]; then

	# Variables

		user="jfrc26"
		export SSHPASS="26552160jfrc"
		server="190.205.100.236"
		destiny="/home/jfrc26/"
		options="-P 9122"

	# Connecting to server
		sshpass -e sftp $options -o BatchMode=no -b - $user@$server:$destiny << end
		put test1.tar.gz
		bye
		end

		unset SSHPASS

else

	echo "No parameters found. "

fi

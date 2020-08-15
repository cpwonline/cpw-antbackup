#!/bin/bash

if [ -n "$1" ; -n "$2" ; -n "$3"]; then

	# Variables
		title=$1
		files="$2 $3"
		output=`date +%Y-%m-%d_%H-%M-%S`_${title}.tar

	# Packing files
		tar -cv $files -f $output

	# Compressing
		tar -Jcv $output -f "$output".xz

	# Delete
		rm -rf $output
else

	echo "No parameters found. "

fi

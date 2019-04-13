#!/bin/bash

if [ -n "$1" ]; then

	# Variables
		title=$1
		files=$2
		output=`date +%Y-%m-%d_%H-%M-%S`_${title}.tar

	# Packing files
		tar -cv $files -f $output

	# Compressing
		gzip $output

else

	echo "No parameters found. "

fi

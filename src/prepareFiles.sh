#!/bin/bash

# Variables
    title="title"
    files="file1 file2 file3"
    dirs="dir1 dir2 dir3"
    output=`date +%Y-%m-%d_%H-%M-%S`_${title}.tar

# Packing files and directories
    tar -cv $files $dirs -f $output

# Compressing
    gzip $output
    
# Delete extras
    rm $output

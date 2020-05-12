#!/bin/bash

# Variables
    userDB="jfrc26"
    passwordDB="-2160JfRc*"
    database="jfrc26"
    output=`date +%Y-%m-%d_%H-%M-%S`_$database.sql
    
# Database output
    mysqldump --user=$user --password=$password $database > $output
    
# Compressing
    gzip $output

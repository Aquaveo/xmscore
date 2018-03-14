#!/bin/bash

counter(){
    for file in "$1"/*
    do
    if [ -d "$file" ]
    then
            echo "$file"
            counter "$file"
    fi
    done
}

counter "$1"
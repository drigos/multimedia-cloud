#!/bin/bash

for (( i = 0 ; i < $1 ; i++ ))
do
   ./device &>> /dev/null
done

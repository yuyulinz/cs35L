#!/bin/bash

cmp cmp1 cmp2

if [ $? -eq 0 ]
then
   echo "same"
else
    echo " not same"
fi


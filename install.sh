#!/bin/bash

nameDir="done"
if [ -d $nameDir ]; then
   rm -rvf $nameDir
fi

mkdir $nameDir
cd server
make
mv serverforchat ../$nameDir

cd ../client
make
mv clientforchat ../$nameDir

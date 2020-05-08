#!/bin/bash

cd install
make si_2 2> install_log.txt 1>&2
echo ''

if [ -e si_2 ]
then
  echo "Installation successful."
  echo ''
  echo "Install log:"
  cat install_log.txt
  echo ''
  read -p "Press ENTER to continue..." pause
  resize -s 39 52
  ./si_2

else
  echo "Installation failed. Please check install log."
  echo ''
  echo "Install log:"
  cat install_log.txt
  echo ''
fi

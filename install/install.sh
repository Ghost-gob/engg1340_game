#!/bin/bash

chmod u=rwx install_log.txt
make si_2 2>install_log.txt 1>&2
echo ''

if [ -e si_2 ]
then
  mv si_2 ..
  echo "Installation successful."
  echo ''
else
  echo "Installation failed. Please check install log."
  echo ''
fi

echo "Install log:"
cat install_log.txt
echo ''

read -p "Press any key to continue..." pause

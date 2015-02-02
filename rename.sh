#!/bin/bash

#echo $1
#hostname $1
flag=0
if [ 1$1 == 1 ]; then
	echo "no parameter!"
	exit -1
fi
cat /etc/issue |grep 'CentOS'
if [ $? == "0" ]; then
	flag=0
fi

cat /etc/issue |grep 'Red Hat Enterprise Linux'
if [ $? == "0" ]; then
	flag=0
fi

cat /etc/issue |grep 'Fedora Core'
if [ $? == "0" ]; then
	flag=0
fi

cat /etc/issue |grep 'Ubuntu'
if [ $? == "0" ]; then
	flag=1
fi

cat /etc/issue |grep 'Debian'
if [ $? == "0" ]; then
	flag=1
fi

cat /etc/issue |grep 'SUSE'
if [ $? == "0" ]; then
	flag=2
fi

echo $flag	 
if [ $flag == 0 ]; then
	hostname $1
	sed -i "s/.*HOSTNAME=.*/HOSTNAME=$1/" /etc/sysconfig/network
	exit 0
fi

if [ $flag == 1 ]; then
	hostname $1
	echo "$1" > /etc/hostname
	exit 0
fi

if [ $flag == 2 ]; then
	hostname $1
	sed -i "$1" /etc/HOSTNAME
fi



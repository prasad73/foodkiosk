#!/bin/bash
###################################
#####  EDIT THESE BEFORE USE  #####
###################################
mysqlusername="admin"
mysqlpassword="vs12345"

#############################################################################################################################
################################################### DO NOT EDIT BELOW THIS LINE ##############################################
##############################################################################################################################

#Set  Refresh
#echo "How long do you want the wait time to be?          "
#read waitTime

waitTime=5

#Start Loop
while :
do
#Read MySQL Data
#Status
status1=$(mysql -B --disable-column-names --user=$mysqlusername --password=$mysqlpassword Vendigo_S1 -e "SELECT BoxStatus FROM BoxStatus WHERE BoxNumber='1'";)
status2=$(mysql -B --disable-column-names --user=$mysqlusername --password=$mysqlpassword Vendigo_S1 -e "SELECT BoxStatus FROM BoxStatus WHERE BoxNumber='2'";)
status3=$(mysql -B --disable-column-names --user=$mysqlusername --password=$mysqlpassword Vendigo_S1 -e "SELECT BoxStatus FROM BoxStatus WHERE BoxNumber='3'";)
status4=$(mysql -B --disable-column-names --user=$mysqlusername --password=$mysqlpassword Vendigo_S1 -e "SELECT BoxStatus FROM BoxStatus WHERE BoxNumber='4'";)
status5=$(mysql -B --disable-column-names --user=$mysqlusername --password=$mysqlpassword Vendigo_S1 -e "SELECT BoxStatus FROM BoxStatus WHERE BoxNumber='5'";)
status6=$(mysql -B --disable-column-names --user=$mysqlusername --password=$mysqlpassword Vendigo_S1 -e "SELECT BoxStatus FROM BoxStatus WHERE BoxNumber='6'";)
status7=$(mysql -B --disable-column-names --user=$mysqlusername --password=$mysqlpassword Vendigo_S1 -e "SELECT BoxStatus FROM BoxStatus WHERE BoxNumber='7'";)
status8=$(mysql -B --disable-column-names --user=$mysqlusername --password=$mysqlpassword Vendigo_S1 -e "SELECT BoxStatus FROM BoxStatus WHERE BoxNumber='8'";)
status9=$(mysql -B --disable-column-names --user=$mysqlusername --password=$mysqlpassword Vendigo_S1 -e "SELECT BoxStatus FROM BoxStatus WHERE BoxNumber='9'";)
status10=$(mysql -B --disable-column-names --user=$mysqlusername --password=$mysqlpassword Vendigo_S1 -e "SELECT BoxStatus FROM BoxStatus WHERE BoxNumber='10'";)

#Run Commands
if [ "$status1" == "1" ]; then
	sudo echo "GPIO 1 Turned On"
else
	sudo echo "GPIO 1 Turned Off"
fi


if [ "$status2" == "1" ]; then
        sudo echo "GPIO 2 Turned On"
else
        sudo echo "GPIO 2 Turned Off"
fi


if [ "$status3" == "1" ]; then
        sudo echo "GPIO 3 Turned On"
else
        sudo echo "GPIO 3 Turned Off"
fi


if [ "$status4" == "1" ]; then
        sudo echo "GPIO 4 Turned On"
else
        sudo echo "GPIO 4 Turned Off"
fi

if [ "$status5" == "1" ]; then
        sudo echo "GPIO 5 Turned On"
else
        sudo echo "GPIO 5 Turned Off"
fi

if [ "$status6" == "1" ]; then
        sudo echo "GPIO 6 Turned On"
else
        sudo echo "GPIO 6 Turned Off"
fi

if [ "$status7" == "1" ]; then
        sudo echo "GPIO 7 Turned On"
else
        sudo echo "GPIO 7 Turned Off"
fi

if [ "$status8" == "1" ]; then
        sudo echo "GPIO 8 Turned On"
else
        sudo echo "GPIO 8 Turned Off"
fi

if [ "$status9" == "1" ]; then
        sudo echo "GPIO 9 Turned On"
else
        sudo echo "GPIO 9 Turned Off"
fi

if [ "$status10" == "1" ]; then
        sudo echo "GPIO 10 Turned On"
else
        sudo echo "GPIO 10 Turned Off"
fi
#Complete Loop
sleep $waitTime
done
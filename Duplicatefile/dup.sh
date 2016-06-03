#! /bin/bash

#Group Name :: Juggernaut
#Group ID :: 65
#Problem Statement :: Write a program to list duplicate files from hard drive and give user option to remove them or merge them.
#Assumptions :: In merging duplicate files, all the duplicates are merged into the last(tail) file.   
if [ "$1" = "-h" ]; then
	printf "\n ./dup.sh arg1 arg2\n ./dup.sh -l <path>: for listing of duplicate files \n ./dup.sh -m <path>: for merging of duplicate files \n ./dup.sh -d <path>: for deleting of duplicate files\n Example:\n ./dup.sh -l /home/username/ will list all the duplicate files in /home/username directory \n ./dup.sh -m /home/username/ will merge all the duplicate files in /home/username directory \n ./dup.sh -d /home/username/ will delete all the duplicate files in /home/username directory\n"


elif [ -n "$2" ]; then
answer=$(find "$2" -type f -printf "%f %s\n"|sort -k1,1nr -k2,2n|uniq -d| cut -d" " -f1 )


if [ "$1" = "-l" ]; then
for i in $answer; 
do 
find "$2" -name $i 
printf "\n"
done


elif [ "$1" = "-m" ]; then
for i in $answer; 
do 
z=$(find "$2" -name $i | xargs md5sum | cut -d" " -f1 | uniq -d)
k=$(find "$2" -type f -exec md5sum {} + | grep  $z | cut -d" " -f3 | head -n -1)
for j in $k
do
	printf "\nFile $j is merged"
	rm -rf $k
done
done

printf "\nDone Mering of files\n"


elif [ "$1" = "-d" ]; then
for i in $answer; 
do 
z=$(find "$2" -name $i | xargs md5sum | cut -d" " -f1 | uniq -d)
k=$(find "$2" -type f -exec md5sum {} + | grep  $z | cut -d" " -f3)
for j in $k
do
	printf "\nFile $j is deleted\n"
	rm -rf $k
done
done
printf "\nDone Deleting of files\n"
fi


else
	printf "\nInvild Arguments! Please type './dup.sh -h' for more help. \n"
fi
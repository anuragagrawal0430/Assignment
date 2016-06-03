#! /bin/bash

if [ "$1" = "h" ]; then
	printf "\n ./dup1.sh arg1 arg2 \n ./dup1.sh -m <path>: for merging for files \n ./dup1.sh -d <path> : for deleting of files\n Example:\n ./dup1.sh -m /home/user_name/ will merge all the files in /home/user_name directory \n ./dup1.sh -d /home/user_name/ will delete all the files in /home/user_name directory\n"


elif [ -n "$2" ]; then
answer=$(find "$2" -type f -printf "%f %s\n"|sort -k1,1nr -k2,2n|uniq -d| cut -d" " -f1 )


if [ "$1" = "-m" ]; then
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
	printf "\nInvild Arguments! Please type './dup1.sh h' for more help. \n"
fi
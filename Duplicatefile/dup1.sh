#! /bin/bash
answer=$(find /home/anurag/test  -type f -printf "%f %s\n"|sort -k1,1nr -k2,2n|uniq -d| cut -d" " -f1 )

#var=$(echo $answer | tr ' ' '\n\0')

#echo ${var[1]}
j=0
for i in $answer; 
do 
export z$j=$(find . -name $i | xargs md5sum | cut -d" " -f1 | uniq -d | sort -nr)
let j+=1
done

echo $j
for ((k=0;k<j;k++))
do
	echo (z$k)
done








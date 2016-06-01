 #!/bin/bash 
find /home/anurag/test -printf "\n%f"|sort -k4,4nr -k2,2n -k3,3  | uniq -D


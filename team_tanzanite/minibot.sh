#!/bin/bash

RANDOM=$$
throw=0
MAXTHROWS=600
MAXROTATE=5
MAXCOLUMN=$1
MAXCOLOR=4

bot1="p1_in"
bot2="p2_in"

rotate()
{
	echo "rotate " $1 > $2
}

random_column()
{
	echo "column " $1 $2 > $3
}

while [ "$throw" -lt "$MAXTHROWS" ]
do
	let "rvalue = RANDOM % $MAXCOLUMN - $MAXCOLUMN / 2"
	let "rcolor = 1"
	if [ $rvalue -eq $(( 0 - MAXCOLUMN / 2 )) ] || [ $rvalue -eq $(( 0 + MAXCOLUMN / 2 )) ]
	then
		let "rvalue = RANDOM % $MAXROTATE + 1"
		rotate $rvalue $bot1
	else
		random_column $rvalue $rcolor $bot1
	fi
	let "rvalue = RANDOM % $MAXCOLUMN - $MAXCOLUMN / 2 "
	let "rcolor = 2"
	if [ $rvalue -eq $(( 0 - MAXCOLUMN / 2 )) ] || [ $rvalue -eq $(( 0 + MAXCOLUMN / 2 )) ]
	then
		let "rvalue = RANDOM % $MAXROTATE + 1"
		rotate $rvalue $bot1
	else
		random_column $rvalue $rcolor $bot2
	fi
	let "throw += 1"
done  
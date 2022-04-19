#!/bin/bash

function test () {
	RESULT=`./cub3D map/"${1}" 2>&1`
	#RESULT=`valgrind --leak-check=full ./cub3D map/"${1}" 2>&1`
	STATUS=`echo $?`
	echo "================================================="
	echo "Test file :" "${1}"
	echo ""
	cat map/"${1}" 2>&1
	echo ""
	echo ""
	echo "<<<< RESURT >>>>"
	echo ""
	if [ "$STATUS" == "0" ]; then
		echo "STATUS is GOOD!! ;)"
	else
		echo "STATUS is BAAD!! :("
		echo ""
	fi
	echo "$RESULT"
	echo ""
	echo "================================================="
	echo ""
	echo ""
}

file=(
	'simple.cub'
	'subject.cub'
	'map_no_newline.cub'
)

make
cp /dev/null log/exec_test_result.log
for (( i = 0; i < ${#file[@]}; ++i))
do
	test "${file[$i]}" >> log/exec_test_result.log
done
echo ""
echo '[ TEST FINISHED!! ]'

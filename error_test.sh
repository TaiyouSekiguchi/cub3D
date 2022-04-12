#!/bin/bash

function test () {
	RESULT=`./cub3D error_map/"${error_file[$i]}" 2>&1`
	STATUS=`echo $?`
	echo "================================================="
	echo "Test file :" "${error_file[$i]}"
	echo ""
	echo "$RESULT"
	if [ "$STATUS" != "1" ]; then
		echo "STATUS is DIFFERENT."
		echo "STATUS : $STATUS"
	fi
	echo "================================================="
	echo ""
	echo ""
}

error_file=(
	'texture_bad_path.cub'
	'texture_no_north.cub'
	'color_bad_num.cub'
	'color_no_floor.cub'
)

make
cp /dev/null log/error_test_result.log
for (( i = 0; i < ${#error_file[@]}; ++i))
do
	test "${error_file[$i]}" >> log/error_test_result.log
done

echo 'test finished'

#!/bin/bash

function test () {
	RESULT=`./cub3D error_map/"${1}" 2>&1`
	STATUS=`echo $?`
	echo "================================================="
	echo "Test file :" "${1}"
	echo ""
	cat error_map/"${1}" 2>&1
	echo ""
	echo "<<<< RESURT >>>>"
	echo ""
	if [ "$STATUS" == "1" ]; then
		echo "STATUS is GOOD!! ;)"
		echo ""
	else
		echo "STATUS is BAAD!! :("
	fi
	echo "$RESULT"
	echo ""
	echo "================================================="
	echo ""
	echo ""
}

error_file=(
	'texture_bad_path.cub'
	'texture_no_north.cub'
	'color_bad_num.cub'
	'color_big_num.cub'
	'color_negative_num.cub'
	'color_no_floor.cub'
	'color_num_and_char.cub'
	'color_space_align.cub'
	'color_too_few_num.cub'
	'color_too_many_num.cub'
	'color_too_small_num.cub'
	'map_empty_line.cub'
	'map_no_spawn.cub'
	'map_not_closed.cub'
	'map_not_last.cub'
	'map_space_line.cub'
	'tab_delimiter.cub'
	'bad_extension.cud'
	'directory.cub'
)

make
cp /dev/null log/error_test_result.log
for (( i = 0; i < ${#error_file[@]}; ++i))
do
	test "${error_file[$i]}" >> log/error_test_result.log
done
echo ""
echo '[ TEST FINISHED!! ]'

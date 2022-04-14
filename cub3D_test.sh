#!/bin/bash

function exec_test () {
	#RESULT=`./cub3D map/"${1}" 2>&1`
	#RESULT=`valgrind --leak-check=full ./cub3D map/"${1}" 2>&1`
	#STATUS=`echo $?`
	echo "================================================="
	echo "Test file :" "${1}"
	echo ""
	cat map/"${1}" 2>&1
	echo ""
	echo ""

	RESULT=`./cub3D map/"${1}" 2>&1`
	#RESULT=`valgrind --leak-check=full ./cub3D map/"${1}" 2>&1`
	STATUS=`echo $?`

	echo "<<<< RESULT >>>>"
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

function error_test () {
	RESULT=`./cub3D error_map/"${1}" 2>&1`
	#RESULT=`valgrind --leak-check=full ./cub3D error_map/"${1}" 2>&1`
	STATUS=`echo $?`
	echo "================================================="
	echo "Test file :" "${1}"
	echo ""
	cat error_map/"${1}" 2>&1
	echo ""
	echo "<<<< RESULT >>>>"
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

function exec_loop () {
	echo "<<<<<<<<<<<<<<<<<<< EXEC TEST >>>>>>>>>>>>>>>>>> "
	echo ""
	for (( i = 0; i < ${#file[@]}; ++i))
	do
		exec_test "${file[$i]}"
	done
	echo ""
}

function error_loop () {
	echo "<<<<<<<<<<<<<<<<<<< ERROR TEST >>>>>>>>>>>>>>>>>> "
	echo ""
	for (( i = 0; i < ${#error_file[@]}; ++i))
	do
		error_test "${error_file[$i]}"
	done
	echo ""
}

file=(
	'simple.cub'
	'subject.cub'
	'standard.cub'
	'minimum_1.cub'
	'minimum_2.cub'
	'small.cub'
	'map_no_newline.cub'
)

error_file=(
	'texture_bad_path.cub'
	'texture_multiple_line.cub'
	'texture_multiple_path.cub'
	'texture_no_north.cub'
	'texture_no_path.cub'
	'color_bad_num.cub'
	'color_blue_empty.cub'
	'color_forbidden_char_1.cub'
	'color_forbidden_char_2.cub'
	'color_multiple_line.cub'
	'color_multiple_rgb.cub'
	'color_negative_num.cub'
	'color_no_blue.cub'
	'color_no_ceil.cub'
	'color_no_floor.cub'
	'color_no_num_1.cub'
	'color_no_num_2.cub'
	'color_over_intmax.cub'
	'color_space_align.cub'
	'color_too_many_comma.cub'
	'color_too_many_num.cub'
	'color_under_intmin.cub'
	'map_bad_char.cub'
	'map_bad_spawn_1.cub'
	'map_bad_spawn_2.cub'
	'map_bad_spawn_3.cub'
	'map_bad_spawn_4.cub'
	'map_empty_line.cub'
	'map_no_spawn.cub'
	'map_not_closed.cub'
	'map_not_last.cub'
	'map_space_in_map.cub'
	'map_space_line.cub'
	'bad_extension.bad'
	'tab_delimiter.cub'
	'directory.cub'
)

make
cp /dev/null log/cub3D_test.log
exec_loop
#exec_loop >> log/cub3D_test.log
error_loop >> log/cub3D_test.log
echo ""
echo '[ TEST FINISHED!! ]'
echo ""

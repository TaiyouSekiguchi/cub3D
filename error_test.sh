#!/bin/bash

texture_path_error_file=(
	'texture_path_error.cub'
)

make
for (( i = 0; i < ${#texture_path_error_file[@]}; ++i))
do
	RESULT=`./cub3D error_map/"${texture_path_error_file[$i]}" 2>&1`
	#RESULT=`valgrind --leak-check=full ./cub3D error_map/"${texture_path_error_file[$i]}" 2>&1`
	if [ "$RESULT" == "Error\nmlx: No such file or directory\n" ]; then
		echo "OK"
	else
		echo "NG"
		echo "$RESULT"
	fi
done

echo 'test finished'

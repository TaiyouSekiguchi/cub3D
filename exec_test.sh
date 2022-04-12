#!/bin/bash

files=(
	'simple.cub'
)

make
for (( i = 0; i < ${#files[@]}; ++i))
do
	valgrind --leak-check=full ./cub3D map/"${files[$i]}"
done

echo 'test finished'

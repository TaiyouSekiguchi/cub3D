#!/bin/bash

files=(
	'simple.cub'
	'subject.cub'
)

make
for (( i = 0; i < ${#files[@]}; ++i))
do
	./cub3D map/"${files[$i]}"
done

echo 'test finished'

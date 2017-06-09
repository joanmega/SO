#!/bin/bash

iteraccion=10000000

i=0
x=0

while [ $i -le $iteraccion ]; do 
	printf "%d \n" $i
	x=$(((i+i)*5));
	i=$((i+1));
done
printf "El valor de la variable es %d \n" $iteraccion

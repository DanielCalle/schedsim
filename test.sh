#!/bin/bash

flag=1; 

while [ $flag -eq 1 ] ; do

	echo "¿Que fichero de ejemplo desea simular?: "
	read simulate

	if [ -f $simulate ] ; then
		
		flag=0;
	
	else

		echo "No se encontro el fichero o no era un fichero regular."

	fi

done 

flag=1;

while [ $flag -eq 1 ] ; do

	echo "¿Cuantas CPU's desea utilizar? (1-8): "
	read cores

	if [ $cores -gt 0 ] && [ $cores -lt 9 ] ; then
	
		flag=0;
	
	else

		echo "Las CPU han de estar en el rango (1-8)."

	fi

done 

if [ ! -d "resultados" ] ; then

	mkdir resultados

else

	rm -r resultados
	mkdir resultados

fi

for nameSched in $(./schedsim -L | tail -n +2) ; do

	for(( cpu=1 ; cpu<=cores ; cpu++ ))	
	do

		./schedsim -n $cpu -s $nameSched -i $simulate

		for(( i=0 ; i<cpu ; i++ ))		
		do

			mv CPU_$i.log resultados/$nameSched-CPU-$i.log
			cd ../gantt-gplot
			./generate_gantt_chart ../schedsim/resultados/$nameSched-CPU-$i.log
			cd ../schedsim/		

		done

	done

done

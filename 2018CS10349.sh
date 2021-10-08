if [ "$3" = "-apriori" ] ; then
	./Apriori $1 $2 $4
elif [ "$3" = "-fptree" ] ; then
	./FPTree $1 $2 $4
elif [ "$2" = "-plot" ] ; then
	./plot $1
else
	echo "Invalid argument!"
fi

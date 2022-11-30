for f in *
do
	if [[ $f =~ ^core* ]] || [[ $f =~ ^vgcore* ]]
	then
		echo "Processing $f"
		rm $f
	fi
done

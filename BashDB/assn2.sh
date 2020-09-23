echo -n "% "
read a b c d
while [ "$a" != "quit" ]
do
	#echo $a
	#echo $b
	######################################################################
	if [[ $a == "setdb" ]];then
		if [[ -z "$b" ]]; then
    		echo "Missing Argument."

		elif [[ ! -z "$c" ]]; then
         db=$b
         echo "Database set to $db."
         echo "Extra arguments ignored."
		
		elif [[ -f "$b" ]] && [[ -r "$b" ]]; then
    		db=$b
			echo  "Database set to $db."
		
		elif [[ ! -f "$b" ]]; then
			touch $b
			db=$b
			echo "File $db created. Database set to $db."
		
		elif [[ -f "$b" ]] && [[ ! -r "$b" ]]; then
			echo "File $db is not readable."	
		else db=""
		fi
	######################################################################
	elif [[ $a == "add" ]];then	
		if [[ ! -n "$db" ]]; then
			echo "database not set"
		
		elif [[ -z "$b" ]] || [[ -z "$c" ]] || [[ ! -z "$d" ]]; then
			echo "Incorrect syntax."
		
		elif grep -q "$b" "$db"; then
    		#echo "word exists!!"
			sed -i "s/${b}.*/${b}:${c}/g" $db
			echo "$b has been updated to $c"
		
		else 
			echo "$b:$c" >> $db
			echo "$b:$c has been added to the database."
		fi
	######################################################################
	elif [[ $a == "delete" ]];then
		if [[ ! -n "$db" ]]; then
         echo "database not set"
		
		elif [[ -z "$b" ]] || [[ ! -z "$c" ]]; then
			echo "Incorrect syntax."
		
		elif grep -q "$b" "$db"; then
			sed -i "s/${b}.*//g" $db
			echo "$b has been deleted from $db."
		
		else
			echo "$b does not exist in $db."
		fi
	###################################################################### 
	elif [[ $a == "printdb" ]];then
      if [[ ! -n "$db" ]]; then
         echo "database not set"
		
		else 
			sed -i '/^$/d' $db
			cat $db
		fi
	fi
	echo -n "% "
	read a b c d
done

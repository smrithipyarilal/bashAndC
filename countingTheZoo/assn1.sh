#!/bin/bash


if test "$#" -lt 1; then
    echo "Illegal number of parameters"
	 exit 1
fi

if test "$#" -gt 4; then
    echo "Illegal number of parameters"
	 exit 1
fi

flag=0
final=0
walk_dir () {

   shopt -s nullglob dotglob
	for pathname in "$2"/*; do
        if [ -d "$pathname" ]; then
            walk_dir "$1" "$pathname" "$3"
			fi
			if [[ "$(basename $pathname)" == "$1" ]]; then
				flag=1
			#printf '%s\n' "$pathname"
			#cat "$pathname"
			contents=$(grep "$3 " "$pathname"|tr -s " "|cut -d" " -f2)
			for things in $contents;do
				#echo "$things"
				final=$(( $final + $things ))
			done
        fi
    done
}


if [[ "$#" -eq 4 ]];then
	walk_dir "$2" "$3" "$4"
fi

if [[ "$#" -eq 3 ]];then
	walk_dir "$2" "$PWD" "$3"
fi

if [[ "$#" -eq 2 ]];then
  if [ -d "$1" ];then
	walk_dir ".KS_Dir" "$1" "$2"
else
	echo "no such directory"
	exit 1
  fi
fi

if [[ "$#" -eq 1 ]];then
   walk_dir ".KS_Dir" "$PWD" "$1"
fi
#echo "$flag"

#echo "${BASH_ARGV[0]}"

for w in bear dromedary aardvark genet lemur
do
	if [[ "$w" == "${BASH_ARGV[0]}" ]];
	then
		yes=1
		break
	fi
done;


if [[ "$yes" -lt 1  ]]; then
    echo "Measurement not recoganised."
elif  [[ "$flag" -gt 0 ]];then
	echo "${BASH_ARGV[0]} $final"
elif [[ "$flag" -lt 1 ]];then
	echo "No such file found"
	echo "${BASH_ARGV[0]} 0"
fi





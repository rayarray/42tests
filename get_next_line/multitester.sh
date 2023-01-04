#set -Eeuo pipefail

#trap cleanup SIGINT SIGTERM ERR EXIT

#cleanup() {
#	trap - SIGINT SIGTERM ERR EXIT
#	echo "Error!"
#	# perform script cleanup here
#} ### Just errors errytime, shrug

usage() {
	cat << EOF
Usage: $(basename "${BASH_SOURCE[0]}") file1 file2 [file3..]

Uses multitest and generates a compare file and compares the results. Max 100 files!
EOF
}

if [[ $# -lt 2 ]]; then
usage && exit
fi

let "fn = $#"

if [[ $fn -gt 100 ]]; then 
usage && echo "Too many files!" && exit 
fi
#if [[ $2 -gt 5000 ]]; then echo "Too many lines!" && exit fi
#if [[ $3 -gt 1000000 ]]; then echo "Too many characters per line!" && exit fi

if [[ -f "./diff_gnl" ]]; then
	rm "./diff_gnl";
fi
if [[ -f "./diff_cmp" ]]; then
	rm "./diff_cmp";
fi

#sed -n '$=' tsttxt1 #gets number of lines in file

maxlines=1

for i in "$@"; do
	curlines=$(wc -l $i | awk '{print $1}')
	if [[ $curlines -gt $maxlines ]]; then
		maxlines=$curlines
	fi
done

./multitest $@ > ./diff_gnl

for i in $(eval echo "{1..$maxlines}"); do
	for j in $@; do
###	CAT slow, do not use TAIL ? PERL really slow SED fastest?
#		cat ./tsttxt$j | sed -n $(eval echo "'${i}p'") >> diff_cmp ### SLOW method
#		tail -n $i tsttxt$j | head -n 1 >> ./diff_cmp ### improved but still slow
#		perl -nle 'print && exit if $. == '$i'' ./tsttxt$j >> ./diff_cmp # 5000 lines, slower than sed
		sed -ne $i'{p;q;}' $j >> ./diff_cmp
	done
done

diff -u ./diff_gnl ./diff_cmp
if [ $? -eq 0 ]; then
    echo "Outputs match, success!";
#	rm $FLIST
#	rm ./diff_gnl ./diff_cmp
fi

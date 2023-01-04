#set -Eeuo pipefail

#trap cleanup SIGINT SIGTERM ERR EXIT

#cleanup() {
#	trap - SIGINT SIGTERM ERR EXIT
#	echo "Error!"
#	# perform script cleanup here
#} ### Just errors errytime, shrug

usage() {
	cat << EOF
Usage: $(basename "${BASH_SOURCE[0]}") [-h] n_files n_lines n_col [n_diff]

Generates [n_files] number of files with up to [n_lines] lines of text in them with [n_col] characters per line 
and performs diff on get_next_line output and supposed output as produced by sed. If [n_diff] is specified, diffs
only the first [n_diff] lines.
EOF
}

while :; do
    case "${1-}" in
    -h | --help) usage && exit;;
    -?*) die "Unknown option: $1" ;;
    *) break ;;
	esac
	shift
done

if [[ $# -lt 3 ]]; then
usage && exit
fi

let "fl = $2 * $3"

#if [[ $1 -gt 1000 ]]; then echo "Too many files!" && exit fi
#if [[ $2 -gt 5000 ]]; then echo "Too many lines!" && exit fi
#if [[ $3 -gt 1000000 ]]; then echo "Too many characters per line!" && exit fi

echo "Generating $1 files with $2 lines and $3 max line width, fast method";

if [[ $1 -gt 0 ]] && [[ $2 -gt 0 ]] && [[ $3 -gt 0 ]]; then
for (( i=1; i<=$1; i++ ))
do
	if [[ -f "./tsttxt$i" ]]; then
		rm "./tsttxt$i";
	fi
	touch "./tsttxt$i";
	base64 /dev/urandom | head -c $fl | fold -w $3 >> ./tsttxt$i
done
fi

echo "Generated $1 files with $2 lines and $3 max line width";

if [[ -f "./diff_gnl" ]]; then
	rm "./diff_gnl";
fi
if [[ -f "./diff_cmp" ]]; then
	rm "./diff_cmp";
fi

if [[ $# -gt 3 ]] && [[ $4 -gt 0 ]]; then
	echo "Outputting the first $4 lines";
for i in $(eval echo "{1..$4}")
do
	for j in $(eval echo "{1..$1}")
	do
		cat ./tsttxt$j | sed -n $(eval echo "'${i}p'") >> diff_cmp
	done
done
./gentester $1 $4 > ./diff_gnl
else
FLIST='tsttxt1'
#for i in $(eval echo "{2..$1}") do FLIST="$FLIST tsttxt$i" done ### Old code for multitest
./gentester $1 > ./diff_gnl
for i in $(eval echo "{1..$2}")
do
	for j in $(eval echo "{1..$1}")
	do
		# CAT slow, do not use TAIL ? PERL really slow SED fastest?
#		cat ./tsttxt$j | sed -n $(eval echo "'${i}p'") >> diff_cmp ### SLOW method
#		tail -n $i tsttxt$j | head -n 1 >> ./diff_cmp ### improved but still slow
#		perl -nle 'print && exit if $. == '$i'' ./tsttxt$j >> ./diff_cmp # 5000 lines, slower than sed
		sed -ne $i'{p;q;}' ./tsttxt$j >> ./diff_cmp
	done
done
fi

diff -u ./diff_gnl ./diff_cmp
if [ $? -eq 0 ]; then
    echo "Outputs match, success!";
#	rm $FLIST
#	rm ./diff_gnl ./diff_cmp
fi
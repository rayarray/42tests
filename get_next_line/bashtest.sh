#SVAR='tsttxt1'
#SVAR="$SVAR tsttxt2"
#echo $SVAR
lines=$(wc -l ./tsttxt1 | awk '{print $1}')
#lines=${temp[0]}
echo $lines
if [[ $lines -gt 4444 ]]; then
echo '$lines is over 4444'
fi

#!/bin/bash
AR=('foo' 'bar' 'baz' 'bat')
#for i in "${!AR[@]}"; do
for i in "$@"; do
#  printf '${AR[%s]}=%s\n' "$i" "${AR[i]}"
	printf $i'\n'
done
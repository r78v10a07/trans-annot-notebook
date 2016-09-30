#!/usr/bin/env bash

#!/usr/bin/env bash

usage(){
cmdName=`basename $0`
cat << EOF
usage: $cmdName options

This script preocess the BLast results to be inserted into a relational DB

OPTIONS:
   -h      Show this message
   -t      Transcript folder
   -b      Build line script
EOF
}

t=""
b=""
while getopts "ht:b:" OPTION
do
     case $OPTION in
         h)
             usage
             exit 1
             ;;
         t)
             t="$OPTARG"
             ;;
         b)
             b="$OPTARG"
             ;;
         ?)
             usage
             exit
             ;;
     esac
done

if [[ -z "$t" ]] || [[ -z "$b" ]]
then
    usage
    exit 1
fi

ARG_LIMIT=130000

rm -f blastx_to_load.tsv
for blastx in `find $t -maxdepth 2 -name "*_blastx.tsv"`
do
    dir=`dirname $blastx`
    cat $blastx | grep -v "^#" | cut -c 17-24,28-  >> blastx_to_load.tsv
    cat $blastx | grep -v "^#" | cut -f 2
done | sort -un > proteins.ids

blastdbcmd -db nr -outfmt "%T %g %a %t" -entry_batch proteins.ids > proteins_to_load.txt
cat proteins_to_load.txt | sed 's/ /\t/' | sed 's/ /\t/' | sed 's/ /\t/' > proteins_to_load.tsv
cat proteins_to_load.tsv | cut -f 1 | sort -un > taxonomies.ids

rm -f taxonomies_to_load.tsv
if [ `grep -c "^0" taxonomies.ids` -ne 0 ]
then
    echo -e "0\tUnknown\tUnknown" > taxonomies_to_load.tsv
fi

$b $ARG_LIMIT taxonomies.ids > taxonomies_lines.txt
cat taxonomies_lines.txt | while read line
do
    echo "Retrieving taxonomies, iteration $i"
    esearch -db taxonomy -query "${line}[taxid]" < /dev/null | efetch -format docsum | xtract -pattern DocumentSummary -element "TaxId,ScientificName,GenBankDivision" >> taxonomies_to_load.tsv
done

exit 0

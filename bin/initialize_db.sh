#!/usr/bin/env bash

usage(){
cmdName=`basename $0`
cat << EOF
usage: $cmdName options

This script create and initialize a SQLite db.

OPTIONS:
   -h      Show this message
   -b      Bioproject Id
   -p      Path
   -d      Database name
   -w      Working directory
   -s      Database SQLite3 schema
EOF
}

WDir=""
db=""
b=""
p=""
s=""
while getopts "hp:b:d:w:s:" OPTION
do
     case $OPTION in
         h)
             usage
             exit 1
             ;;
         b)
             b="$OPTARG"
             ;;
         p)
             p="$OPTARG"
             ;;
         d)
             db="$OPTARG"
             ;;
         w)
             WDir="$OPTARG"
             ;;
         s)
             s="$OPTARG"
             ;;
         ?)
             usage
             exit
             ;;
     esac
done

if [[ -z "$p" ]] || [[ -z "$b" ]] || [[ -z "$db" ]] || [[ -z "$WDir" ]] || [[ -z "$s" ]]
then
    usage
    exit 1
fi

cd $WDir || { echo "ERROR: Could not change to the working directory: $WDir" ; exit 1; }

db_name="${db}.sqlite"

if [ ! -e "$db_name" ]
then
	cat $s | sqlite3 $db_name

cat <<EOF | sqlite3 $db_name
INSERT INTO "bioprojects" ("id", "path") VALUES ($b, "$p");
EOF

    esearch -db sra -query "$b[BioProject]" | efetch -format docsum | xtract -pattern DocumentSummary -element "Experiment@acc" -lbl "," -element Title | sed 's/\t//g' |\
    while read line
    do
        acc=`echo $line | awk -F, '{print $1}'`
        title=`echo $line | awk -F, '{print $2}'`

        sqlite3 $db_name "INSERT INTO 'experiments' ('accession', 'title', 'bioproject_id') VALUES ('$acc', '$title', '$b');"
    done

    echo "Experiments inserted: "
    sqlite3 $db_name "select * from experiments where bioproject_id = ${b};"
    echo
    echo

    esearch -db sra -query "${b}[BioProject]" | efetch -format docsum | xtract -pattern DocumentSummary -element 'Experiment@acc' 'Run@acc' > runs

    echo "Runs inserted: "
    sqlite3 $db_name "select id, accession from experiments where bioproject_id = ${b};" | \
    while read line
    do
        id=`echo $line | awk -F\| '{print $1}'`
        acc=`echo $line | awk -F\| '{print $2}'`
        echo "Inserting runs for: $acc"
        for inline in `cat runs | grep "^$acc" | cut -c 11-  | sed 's/ /\n/g'`
        do
            sqlite3 $db_name "INSERT INTO 'runs' ('accession', 'experiment_id') VALUES ('$inline', '$id');"
        done
        sqlite3 $db_name "select * from runs where experiment_id = $id;"
    done

    rm runs
    echo
    echo

fi



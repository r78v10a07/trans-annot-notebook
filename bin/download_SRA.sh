#!/bin/bash

usage(){
cmdName=`basename $0`
cat << EOF
usage: $cmdName options

Download SRR data from SRA database using as input the BioProject ID

OPTIONS:
   -h      Show this message
   -b      Bioproject Id
   -w      Working directory
EOF
}

BIOPROJECT=""
WDir=""
while getopts "hw:b:" OPTION
do
     case $OPTION in
         h)
             usage
             exit 1
             ;;
         b)
             BIOPROJECT="$OPTARG"
             ;;
         w)
             WDir="$OPTARG"
             ;;
         ?)
             usage
             exit
             ;;
     esac
done

if [[ -z "$BIOPROJECT" ]] || [[ -z "$WDir" ]]
then
    usage
    exit 1
fi

cd $WDir || { echo "ERROR: Could not change to the working directory: $WDir" ; exit 1; }

for sra in `esearch -db sra -query "$BIOPROJECT" | efetch -format docsum | \
        xtract -pattern DocumentSummary -element "Run@acc" | \
        xargs `
do
        if [ ! -e "${sra}.fastq.gz" ]
        then
                echo "Downloading sra: $sra"
                fastq-dump $sra || { echo "ERROR: Could not download file: $sra" ; exit 1; }
                gzip -9 ${sra}.fastq
        fi
done

exit 0

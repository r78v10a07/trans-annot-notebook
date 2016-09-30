#!/usr/bin/env bash

usage(){
cmdName=`basename $0`
cat << EOF
usage: $cmdName options

This script runs Bowtie2 and samtools for the transcript

OPTIONS:
   -h      Show this message
   -i      Transcript ID
   -s      SRA data
EOF
}

id=""
s=""
while getopts "hi:w:s:" OPTION
do
     case $OPTION in
         h)
             usage
             exit 1
             ;;
         i)
             id="$OPTARG"
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

if [[ -z "$id" ]] || [[ -z "$s" ]]
then
    usage
    exit 1
fi

# Bowtie2 build
bowtie2-build ${id}.fasta ${id} 3>&1 1>&2 2>&3 > ${id}.buildlog

# Running Bowtie2
rm -rf ${id}.sam
for a in $s/*.fastq.gz
do
    name=`basename $a`
    (zcat $a | bowtie2 -x ${id} -q - -p 16 --fast --no-unal | samtools view -Sb - > ${id}_${name%.fastq.gz}.bam) 3>&1 1>&2 2>&3 | gzip -9 > ${id}_${name%.fastq.gz}.bowtielog.gz
done

# Merging all BAM files
samtools merge ${id}.bam ${id}_*.bam

# Removing unnecessary BAM files
rm ${id}_*.bam

# Sorting the resulting BAM file
samtools sort -o ${id}_sorted.bam ${id}.bam

# Indexing the sorted BAM file
samtools index ${id}_sorted.bam ${id}_sorted.bam.bai

# Running Blast for the transcript
blastx -query ${id}.fasta -db nr -num_threads 16 -outfmt "7 qacc sgi slen qstart qend sstart send evalue bitscore score length pident nident mismatch positive gapopen gaps ppos qcovs qcovhsp" -out ${id}_blastx.tsv 2>&1 > ${id}.blastxlog

tar czf data.tgz `ls -1 | grep -v -e sorted.bam -e sge -e not_aling -e blastx | xargs`
/bin/ls -1 | grep -v -e sorted.bam -e data.tgz -e sge -e not_aling -e blastx | xargs rm -f

exit 0

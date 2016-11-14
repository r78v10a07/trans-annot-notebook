# Workflow and web application for annotation of NCBI BioProject transcriptome data 

Roberto Vera Alvarez$^{1}$, Newton Medeiros Vidal$^{1}$, Gina A Garzón-Martínez$^{2}$, Luz S Barrero$^{2}$, Richa Agarwala$^{3}$, David Landsman$^{1}$ and Leonardo Mariño-Ramírez$^{1,*}$

$^{1}$Computational Biology Branch, National Center for Biotechnology Information, National Library of Medicine, National Institutes of Health, Bethesda, Maryland, USA

$^{2}$Colombian Corporation for Agricultural Research (CORPOICA), Bogota, Colombia

$^{3}$Information Engineering Branch, National Center for Biotechnology Information, National Library of Medicine, National Institutes of Health, Bethesda, Maryland, USA

$^{*}$Corresponding author: Email: marino@ncbi.nlm.nih.gov Address: Building 38A, Room 6S614-M, 8600 Rockville Pike MSC 6075. Bethesda, MD 20894-6075 Tel: 1-301-402-3708

## Abstract

Transcriptome data is growing exponentially due to the latest improvements of experimental devices. In response to that, large central resources, such as those of the National Center for Biotechnology Information (NCBI), are continually adapting their computational infrastructure to accommodate this data influx. New specialized databases have been created like Transcriptome Shotgun Assembly Sequence Database (TSA) and Sequence Read Archive (SRA) aiding the creation of centralized repositories. Although these databases are in a constant development, they do not include automatic pipelines to increase the annotation of the deposited data. Therefore, third party applications are required to achieve that aim. Here we present an automatic workflow and web application for the annotation of transcriptome data. The workflow creates secondary data like sequencing read and BLAST alignments which are available through the web application. It is based on freely available bioinformatics tools and a set of in-house developed scripts. The interactive web application provides a search engine and different browse utilities. Additionally, graphical views of the transcript alignments are available through SeqViewer, a friendly embedded tool developed by NCBI for viewing biological sequence data. The web application is tightly integrated to the other NCBI web applications and tools extending the possibility of data processing and interconnectivity. A case study is presented for the species Physalis peruviana with data generated from the BioProject with ID 67621.

PhysalisDB URL: http://www.ncbi.nlm.nih.gov/projects/physalis/
Workflow Github repository: https://github.com/r78v10a07/trans-annot-notebook
Jupyter Notebook: https://github.com/r78v10a07/trans-annot-notebook/blob/master/docs/Notebook.ipynb 


## Notebook

A Jupyter Notebook https://github.com/r78v10a07/trans-annot-notebook/blob/master/docs/Notebook.ipynb, which illustrate the workflow used for the transcript annotation process is available. This Github project can be clone and executed in a compatible environment.

## Requirements

### Basic programs

1. Python3
2. virtualenv3
3. C++

### Bioinformatics programs

These programs have to be installed and included in the user PATH variable.

1. EDirect (https://www.ncbi.nlm.nih.gov/books/NBK179288/)
2. SRA Toolkit (https://www.ncbi.nlm.nih.gov/books/NBK158900/)
3. Bowtie 2 (http://bowtie-bio.sourceforge.net/bowtie2/manual.shtml)
4. SAMTools (http://www.htslib.org/)
5. BLAST (http://blast.ncbi.nlm.nih.gov/Blast.cgi)

## Instalation of the Notebook

Execute this commands in a BASH terminal just the first time to get the notebook dependencies installed.

```
$ git clone https://github.com/r78v10a07/trans-annot-notebook
$ cd trans-annot-notebook

# Compiling the myBlast2GO C++ tool
$ cd src/myblast2go/
$ make
$ cd ../../

# Creating a virtual environment
$ virtualenv3 venv
$ source venv/bin/activate
$ pip install -r requirements/jupyter.txt
$ chmod a+x ./bin/*
```

Execute this script to start the jupyter server.

```
$ ./bin/runNotebook.sh
```

After this open a web browser with this URL: http://localhost:9096

Click on docs and then, click on Notebook.ipynb to open the notebook

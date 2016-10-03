PRAGMA synchronous = OFF;
PRAGMA journal_mode = MEMORY;
BEGIN TRANSACTION;

CREATE TABLE `bioprojects` (
  `id` INTEGER PRIMARY KEY AUTOINCREMENT,
  `path` varchar(255) NOT NULL
);

CREATE TABLE `blastx` (
  `id`  INTEGER PRIMARY KEY AUTOINCREMENT,
  `slen` int(11) DEFAULT NULL,
  `qstart` int(11) DEFAULT NULL,
  `qend` int(11) DEFAULT NULL,
  `sstart` int(11) DEFAULT NULL,
  `send` int(11) DEFAULT NULL,
  `evalue` double DEFAULT NULL,
  `bitscore` double DEFAULT NULL,
  `score` double DEFAULT NULL,
  `length` int(11) DEFAULT NULL,
  `pident` double DEFAULT NULL,
  `nident` int(11) DEFAULT NULL,
  `mismatch` int(11) DEFAULT NULL,
  `positive` int(11) DEFAULT NULL,
  `gapopen` int(11) DEFAULT NULL,
  `gaps` int(11) DEFAULT NULL,
  `ppos` double DEFAULT NULL,
  `qcovs` double DEFAULT NULL,
  `qcovhsp` double DEFAULT NULL,
  `protein_id` int(11) NOT NULL,
  `nucleotide_id` int(11) NOT NULL
);
CREATE INDEX "blastx_protein_id" ON "blastx" (`protein_id`);
CREATE INDEX "blastx_nucleotide_id" ON "blastx" (`nucleotide_id`);

CREATE TABLE `blastx_temp` (
  `qacc` varchar(45) DEFAULT NULL,
  `sgi` int(11) DEFAULT NULL,
  `slen` int(11) DEFAULT NULL,
  `qstart` int(11) DEFAULT NULL,
  `qend` int(11) DEFAULT NULL,
  `sstart` int(11) DEFAULT NULL,
  `send` int(11) DEFAULT NULL,
  `evalue` double DEFAULT NULL,
  `bitscore` double DEFAULT NULL,
  `score` double DEFAULT NULL,
  `length` int(11) DEFAULT NULL,
  `pident` double DEFAULT NULL,
  `nident` int(11) DEFAULT NULL,
  `mismatch` int(11) DEFAULT NULL,
  `positive` int(11) DEFAULT NULL,
  `gapopen` int(11) DEFAULT NULL,
  `gaps` int(11) DEFAULT NULL,
  `ppos` double DEFAULT NULL,
  `qcovs` double DEFAULT NULL,
  `qcovhsp` double DEFAULT NULL
);
CREATE INDEX "blastx_temp_qacc" ON "blastx_temp" (`qacc`);

CREATE TABLE `enzymes` (
  `id`  INTEGER PRIMARY KEY AUTOINCREMENT,
  `accession` varchar(45) NOT NULL,
  `name` varchar(255)
);
CREATE INDEX "enzymes_accession" ON "enzymes" (`accession`);

CREATE TABLE `experiments` (
  `id`  INTEGER PRIMARY KEY AUTOINCREMENT,
  `accession` varchar(45) NOT NULL,
  `title` text,
  `bioproject_id` int(11) NOT NULL
);
CREATE INDEX "experiments_accession" ON "experiments" (`accession`);
CREATE INDEX "experiments_bioproject_id" ON "experiments" (`bioproject_id`);

CREATE TABLE `gi2go` (
  `gi` int(11) NOT NULL,
  `go` varchar(45) NOT NULL
);
CREATE INDEX "gi2go_go" ON "gi2go" (`go`);
CREATE INDEX "gi2go_gi" ON "gi2go" (`gi`);

CREATE TABLE `ec2go` (
  `ec` varchar(45) NOT NULL,
  `go` varchar(45) NOT NULL
);
CREATE INDEX "ec2go_go" ON "ec2go" (`go`);
CREATE INDEX "ec2go_ec" ON "ec2go" (`ec`);


CREATE TABLE `go` (
  `id`  INTEGER PRIMARY KEY AUTOINCREMENT,
  `accession` varchar(45) NOT NULL,
  `name` varchar(255) NOT NULL,
  `description` text,
  `name_space` varchar(45) NOT NULL DEFAULT 'not_assigned'
);
CREATE INDEX "go_accession" ON "go" (`accession`);
CREATE INDEX "go_name_space" ON "go" (`name_space`);

CREATE TABLE `go_statistics` (
  `id`  INTEGER PRIMARY KEY AUTOINCREMENT,
  `transcripts` int(11) NOT NULL,
  `go_id` int(11) NOT NULL
);
CREATE INDEX "go_statistics_transcripts" ON "go_statistics" (`transcripts`);
CREATE INDEX "go_statistics_go_id" ON "go_statistics" (`go_id`);

CREATE TABLE `go_temp` (
  `accession` varchar(45) NOT NULL,
  `name` varchar(255) NOT NULL,
  `description` text,
  `name_space` varchar(45) NOT NULL DEFAULT 'not_assigned'
);
CREATE INDEX "go_temp_accession" ON "go_temp" (`accession`);
CREATE INDEX "go_temp_name_space" ON "go_temp" (`name_space`);

CREATE TABLE `nucleotides` (
  `id` INTEGER PRIMARY KEY AUTOINCREMENT,
  `accession` varchar(45) NOT NULL,
  `version` int(11) DEFAULT NULL,
  `gi` int(11) DEFAULT NULL,
  `title` text,
  `len` int(11) DEFAULT NULL,
  `path` varchar(255) NOT NULL,
  `moltype` varchar(45) NOT NULL DEFAULT 'mRNA',
  `bioproject_id` int(11) NOT NULL
);
CREATE INDEX "nucleotides_accession" ON "nucleotides" (`accession`);
CREATE INDEX "nucleotides_gi" ON "nucleotides" (`gi`);
CREATE INDEX "nucleotides_bioproject_id" ON "nucleotides" (`bioproject_id`);

CREATE TABLE `nucleotides_enzymes` (
  `nucleotides_id` int(11) NOT NULL,
  `enzymes_id` int(11) NOT NULL,
  PRIMARY KEY (`nucleotides_id`,`enzymes_id`)
);

CREATE TABLE `nucleotides_go` (
  `nucleotides_id` int(11) NOT NULL,
  `go_id` int(11) NOT NULL,
  PRIMARY KEY (`nucleotides_id`,`go_id`)
);

CREATE TABLE `nucleotides_go_temp` (
  `nucleotides` varchar(45) NOT NULL,
  `go_accession` varchar(45) NOT NULL,
  PRIMARY KEY (`nucleotides`,`go_accession`)
);

CREATE TABLE `proteins` (
  `id`  INTEGER PRIMARY KEY AUTOINCREMENT,
  `accession` varchar(45) NOT NULL,
  `title` text,
  `gi` int(11) DEFAULT NULL,
  `taxonomy_id` int(11) NOT NULL
);
CREATE INDEX "proteins_accession" ON "proteins" (`accession`);
CREATE INDEX "proteins_gi" ON "proteins" (`gi`);
CREATE INDEX "proteins_taxonomy_id" ON "proteins" (`taxonomy_id`);

CREATE TABLE `runs` (
  `id` INTEGER PRIMARY KEY AUTOINCREMENT,
  `accession` varchar(45) NOT NULL,
  `experiment_id` int(11) NOT NULL
);
CREATE INDEX "runs_accession" ON "runs" (`accession`);
CREATE INDEX "runs_experiment_id" ON "runs" (`experiment_id`);

CREATE TABLE `taxonomies` (
  `id`  INTEGER PRIMARY KEY AUTOINCREMENT,
  `name` varchar(155) DEFAULT NULL,
  `division` varchar(100) DEFAULT NULL
);
CREATE INDEX "taxonomies_division" ON "taxonomies" (`division`);

END TRANSACTION;

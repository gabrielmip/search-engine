#!/bin/bash

HD="/home/gabriel/Documentos"
DOCS=${HD}/small_collection
RUNS=${HD}/runs
MERGE=${HD}/merge
INDEX=${HD}/index
LOG=${HD}/logs/removendo_log.txt
MEMORY=200

	echo $i
	command="time indexer/indexer ${DOCS} ${RUNS} ${MERGE} ${INDEX} ${MEMORY} ${LOG}"
	eval $command

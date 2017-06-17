#!/bin/bash

HD="/media/gabriel/Dados\\ Massivos"
DOCS=${HD}/small_collection
RUNS=${HD}/runs
MERGE=${HD}/merge
INDEX=${HD}/index
LOG=${HD}/logs/removendo_log.txt
MEMORY=200

for i in 10 9 8 7 6 5; do
	echo $i
	command="time indexer/indexer ${DOCS} ${RUNS} ${MERGE} ${INDEX} ${MEMORY} ${LOG}"
	eval $command
	command="rm ${DOCS}/html_${i}"
	#eval $command
done


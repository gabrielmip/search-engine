#!/bin/bash

HD="/media/gabriel/Dados\\ Massivos"
DOCS=${HD}/collection/
RUNS=${HD}/runs/
MERGE=${HD}/merge/
INDEX=${HD}/index/
LOG=${HD}/logs/completo_log.txt

i=200
command="time indexer/indexer ${DOCS} ${RUNS} ${MERGE} ${INDEX} ${i} ${LOG}"
eval $command



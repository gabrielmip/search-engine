#!/bin/bash

home=/Users/gabriel/Desktop
docs=$home/collection
otherdocs=$home/small_collection
log=indexer/data/logs/tamanho.txt
rm $log

i=5
echo $i
mv $otherdocs/html_$i $docs/
time indexer/indexer $docs indexer/data/runs indexer/data/merge indexer/data/index 200 $log

#!/bin/bash
echo "Analysis started ...."

rm -rf analysis 
mkdir analysis

# Warning : this task takes long time > ~ 20-30 min.
cppcheck --enable=all --inconclusive --xml --xml-version=2 --force . 2> analysis/analysis.xml
cppcheck-htmlreport --file=analysis/analysis.xml --report-dir=analysis --source-dir=.
echo "Analysis finished ...."

cd analysis
python -m SimpleHTTPServer 8081 --bind 0.0.0.0


#!/bin/bash

# This script download files that can be used to test the code

# download file with the URLs
echo "Downloading the file with the paths"
wget https://commoncrawl.s3.amazonaws.com/crawl-data/CC-MAIN-2018-51/warc.paths.gz

# extract file
gunzip --force warc.paths.gz

# get the first data URL
URL=`head -n 1 warc.paths`
echo "Downloading data... $URL"

# download the file
wget https://commoncrawl.s3.amazonaws.com/$URL

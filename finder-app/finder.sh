#!/bin/sh

# finder.sh /tmp/aesd/assignment1 linux

# Check if both parameters are provided
if [ $# -ne 2 ]; then
    echo "Error: Two parameters are required."
    exit 1
fi

filesdir=$1
searchstr=$2

# echo "filesdir: $filesdir"
# echo "searchstr: $searchstr"


if [ ! -d $filesdir ]; then
    echo "$filesdir does not represent a directory on the filesystem"
    exit 1
fi

num_of_files=$(find "$filesdir" -type f | wc -l)
num_of_matches=$(grep -nr "$searchstr" "$filesdir" | wc -l)

echo "The number of files are $num_of_files and the number of matching lines are $num_of_matches"



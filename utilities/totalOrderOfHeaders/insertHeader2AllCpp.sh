#!/bin/bash
# a bash script to find all *.cpp from current and its nested paths
# then prepend #include "total_header.hh" to each of *.cpp files

# Find all .cpp files and process them
find . -type f -name "*.cpp" | while read -r file; do
    # Display a message indicating which file is being modified
    echo "Modifying $file..."

    # Check if file is empty
    if [ ! -s "$file" ]; then
        # File is empty, just add the include line
        echo '#include "total_header.hh"' > "$file"
    else
        # File is not empty, insert include line at the top
        sed -i '1s/^/#include "total_header.hh"\n/' "$file"
    fi
done

echo "Insertion complete."

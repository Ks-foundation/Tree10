#!/bin/bash

# Check if the NASM assembler is installed
if ! command -v nasm &> /dev/null
then
    echo "NASM assembler could not be found. Please install NASM."
    exit
fi

# Check if the input .asm file is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <source.asm>"
    exit 1
fi

# Input file
input_file="$1"
# Output .air file (replace .asm with .air)
output_file="${input_file%.asm}.air"

# Assemble the .asm file into a flat binary (.air)
nasm -f bin "$input_file" -o "$output_file"

# Check if the assembly succeeded
if [ $? -eq 0 ]; then
    echo "Successfully compiled $input_file to $output_file"
else
    echo "Error: Failed to compile $input_file"
fi

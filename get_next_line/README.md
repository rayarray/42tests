simpletest file
		Prints the contents of [file] using get_next_line

stdintest
		Gets content from stdin and prints it using get_next_line

multitest file1 file2 .. fileN
		Prints the contents of file1 to fileN one line from each file and then the next until all files are printed

generatetext.sh x y z [numlines]
		Generates x files with y lines containing z characters, filled with random words. Runs multitest on the generated files and compares it using diff. If [numlines] is given, compares only the first [numlines] lines.

fastgeneratetext.sh x y z [numlines]
		Generates x files with y lines containing z characters, filled with random words. Runs multitest on the generated files and compares it using diff. If [numlines] is given, compares only the first [numlines] lines.
		BUGGED! Compare file has newlines at the end of each file so diff reports as many errors as there are files

removetests.sh
		Deletes the generated test files




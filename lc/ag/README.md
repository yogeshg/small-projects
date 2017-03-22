NOTES
=====

1. Please go into each folder and run the makefile
2. Execute the executables created in each of these folders
3. For a more verbose experience, change #define DEBUG to true in respective cpp

Circular Printer
================

	cd circularprinter/
	make
	# usage: ./main string char_count thread_count loops
	./main ABCDEFGHIJ 3 4 2
	./main ABCDEFGHIFKLMNOPQRSTUVWX_YZ_ 4 7 3
	cd ..

On The Fly Sort
===============

	cd flysort/
	make
	# Run the server at 20301 for 8 exchanges
	./server 20301 8 &
	# Run 8 clients to localhost:20301 using symbols in exch{1,2}.txt
	./client localhost 20301 101 exch1.txt & ./client localhost 20301 202 exch2.txt & ./client localhost 20301 300 exch1.txt & ./client localhost 20301 407 exch2.txt & ./client localhost 20301 502 exch1.txt & ./client localhost 20301 609 exch2.txt & ./client localhost 20301 701 exch1.txt & ./client localhost 20301 846 exch2.txt &
	# Enjoy the sorted symbols list
	cd ..

Version Queue
=============

	cd versionqueue/
	make
	./versionqueue 
	# paste testcase from text*.txt
	cd ..

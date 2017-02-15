CXX=g++ -std=c++11

exe=hw4-sample hw4-sample2 hw4-sample3 hw4-sample4 hw4-sample5
all: ${exe} hw4-yg2482.pdf

hw4-yg2482.pdf: hw4.md
	pandoc hw4.md -o hw4-yg2482.pdf

clean:
	rm ${exe}
 

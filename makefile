main: multiThreadSorter.c
	gcc multiThreadSorter.c -o multiThreadSorter -lpthread 
	
test: test.c
	gcc -lpthread test.c -o test
	

# sorter: sorter.c
# 	gcc -lpthread sorter.c -o sorter
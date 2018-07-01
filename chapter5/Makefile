CPP := g++ 
CPPFLAGS := -Wall -std=c++11

G11 := ${CPP} ${CPPFLAGS} 

PROGS := testGant fcfs fcfs_test

OBJS := testGant.o fcfs.o fcfs_test.o

%.o: %.cpp
	${G11} -c $< -o $@

all: ${PROGS}

testGant: testGant.o
	${G11} -o $@ testGant.o

fcfs: fcfs.o
	${G11} -o $@ $<

fcfs_test: fcfs_test.o
	${G11} -o $@ $<

clean:
	rm -f ${OBJS} ${PROGS}

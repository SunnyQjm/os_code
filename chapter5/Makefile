CPP := g++ 
CPPFLAGS := -Wall -std=c++11 -g

G11 := ${CPP} ${CPPFLAGS} 

PROGS := testGant fcfs fcfs_test sjf_test sjf srtf_test srtf

OBJS := testGant.o fcfs.o fcfs_test.o sjf_test.o sjf.o srtf_test.o srtf.o

%.o: %.cpp
	${G11} -c $< -o $@

all: ${PROGS}

testGant: testGant.o
	${G11} -o $@ testGant.o

fcfs: fcfs.o
	${G11} -o $@ $<

fcfs_test: fcfs_test.o
	${G11} -o $@ $<

sjf_test: sjf_test.o
	${G11} -o $@ $<

sjf: sjf.o
	${G11} -o $@ $<

srtf_test: srtf_test.o
	${G11} -o $@ $<

srtf: srtf.o
	${G11} -o $@ $<

clean:
	rm -f ${OBJS} ${PROGS}

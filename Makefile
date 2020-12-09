B_TARGETS := main.c policy.c workload.c generate.c
T_TARGETS := checker.c policy.c workload.c generate.c
TARGET := page

all:
	gcc -o ${TARGET} ${B_TARGETS} -lm
	./${TARGET}
	python3 plot.py

test:
	gcc -o ${TARGET} ${T_TARGETS} -lm
	./${TARGET}

clean:
	rm -f ${TARGET}
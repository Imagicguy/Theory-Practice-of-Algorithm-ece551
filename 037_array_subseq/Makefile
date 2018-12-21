maxSeq: maxSeq.o test-subseq.o
	gcc -ggdb3 -o maxSeq maxSeq.o test-subseq.o
maxSeq.o:maxSeq.c
	gcc -ggdb3 -c -Wall -Werror -pedantic -std=gnu99 maxSeq.c
test-subseq.o:test-subseq.c
	gcc -ggdb3 -c -Wall -Werror -pedantic -std=gnu99 test-subseq.c

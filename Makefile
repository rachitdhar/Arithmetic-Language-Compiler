comp: cg.c expr.c gen.c interp.c main.c scan.c tree.c
		cc -o comp -g cg.c expr.c gen.c interp.c main.c scan.c tree.c

clean:
		rm -f comp *.o *.s out

test: comp
		./comp input01.txt
		cc -o out out.s
		./out
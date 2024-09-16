cfs   = -Iinclude -O2 -Wall -std=c99 -lm -lraylib
cfl  = $(wildcard *.c)

objf = $(patsubst %.c, obj/%.o, $(cfl))
obj/%.o: %.c
	gcc $(cfs) -c $< -o $@

Build: $(objf)
	gcc $(cfs) $(objf) -o Build/dbg

Clean:
	rm obj/*.o Build/dbg

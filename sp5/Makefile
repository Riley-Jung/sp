SRCS_STATIC = static_main.c open.c close.c set.c get.c
SRCS_DYNAMIC = dynamic_main.c open.c close.c set.c get.c
TARG_STATIC = kvs_static
TARG_DYNAMIC = kvs_dynamic

CC = gcc
OPTS = -Wall -g
LIBS = -L. -lkvs
LIBD = libkvs.so     

OBJS_STATIC = $(SRCS_STATIC:.c=.o)
LOBJS_STATIC = open.o close.o set.o get.o  

LARS = libkvs.a

OBJS_DYNAMIC = $(SRCS_DYNAMIC:.c=.o)
LOBJS_DYNAMIC = open.o close.o set.o get.o  

static: $(TARG_STATIC)

$(TARG_STATIC): $(OBJS_STATIC) $(LARS)
	$(CC) -o $(TARG_STATIC) $(OBJS_STATIC) $(LIBS)

dynamic: $(TARG_DYNAMIC)

$(TARG_DYNAMIC): $(OBJS_DYNAMIC) $(LIBD)
	$(CC) -o $(TARG_DYNAMIC) $(OBJS_DYNAMIC) $(LIBS) -ldl

$(LARS): $(LOBJS_STATIC)
	ar rs $(LARS) $(LOBJS_STATIC)

$(LIBD): $(LOBJS_DYNAMIC)
	$(CC) -shared -fPIC -o $(LIBD) $(LOBJS_DYNAMIC)

%.o: %.c
	$(CC) $(OPTS) -c -fPIC $< -o $@

run_dynamic: dynamic
	LD_LIBRARY_PATH=$(shell pwd) ./$(TARG_DYNAMIC)

clean:
	rm -f $(OBJS_STATIC) $(LARS) $(TARG_STATIC) $(OBJS_DYNAMIC) $(LIBD) $(TARG_DYNAMIC)

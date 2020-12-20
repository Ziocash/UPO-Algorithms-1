#CFLAGS+=-fPIC
bin_objects=$(patsubst %.c, %.o, $(wildcard ../src/*.c))
#bin_objects=$(wildcard ../src/*.c)

#export bin_objects
#
include mk/*.mk


.PHONY: all static shared clean

all: static shared

static: $(bin_objects)
	$(AR) rcs libupoalglib_s.a $^

#shared: CFLAGS := $(CFLAGS) -fPIC
#shared: $(bin_objects)
#	$(CC) -o libupoalglib.so -shared -Wl,-soname,libupoalglib.so $^

clean:
	$(RM) $(bin_objects) *.so *.a

LDFLAGS+=-L../bin
LDLIBS=-lupoalglib_s -lm
#LDLIBS=-lupoalglib -lm
apps_targets=

export LDFLAGS
export LDLIBS
export apps_targets

include mk/*.mk


.PHONY: all clean

all: $(apps_targets)

clean:
	$(RM) $(apps_targets) *.o

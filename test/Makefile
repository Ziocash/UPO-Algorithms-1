LDFLAGS+=-L../bin
LDLIBS=-lupoalglib_s -lm
#LDLIBS=-lupoalglib -lm
test_targets=

export LDFLAGS
export LDLIBS
export test_targets

include mk/*.mk


.PHONY: all clean

all: $(test_targets)

clean:
	$(RM) $(test_targets) *.o

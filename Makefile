TARGET    := dinit
OBJS      := main.o inittab.o

CXXFLAGS  = -std=c++20 -Wall
LDFLAGS   =

ifdef DEBUG
	CXXFLAGS  += -O3
	LDFLAGS   += -Wl,-O2 -Wl,--as-needed -Wl,-s
endif

ifdef STATIC
	LDFLAGS += -static
endif

.PHONY: all clean
all: $(TARGET)
clean:
	rm -f $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

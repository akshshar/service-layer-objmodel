TARGET := quickstart
SRC_FILES := $(wildcard *.cc)
OBJ_FILES := $(patsubst %.cc,%.o,$(SRC_FILES))
LDFLAGS := -L/usr/local/lib -I/usr/local/include -lgrpc++_unsecure -lgrpc -lprotobuf -lpthread -ldl -liosxrsl
CPPFLAGS := -g -std=c++14 -I/usr/local/include -pthread

.PHONY: all
all: $(TARGET)

%.o: %.cc
	g++ $(CPPFLAGS) -c -o $@ $<

$(TARGET): $(OBJ_FILES)
	g++ $^ $(LDFLAGS) -o $@


.PHONY: clean
clean:
	-${RM} ${TARGET} ${OBJ_FILES}

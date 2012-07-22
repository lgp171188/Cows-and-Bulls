SRCS=cows_and_bulls.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

cows-and-bulls: $(OBJS) bin
	$(CXX) -o bin/cows-and-bulls $(LDFLAGS) $(OBJS) $(LDLIBS)

bin:
	mkdir bin

clean:
	rm -f $(OBJS)

dist-clean: clean
	rm -f bin/cows-and-bulls

install: cows-and-bulls
	mv bin/cows-and-bulls $(DESTDIR)/usr/games/

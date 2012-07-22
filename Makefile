OUTDIR = bin
OUTFILE = cows-and-bulls
SOURCE_FILES = cows_and_bulls.cpp

cows-and-bulls: cows_and_bulls.cpp bin
	g++ -o $(OUTDIR)/$(OUTFILE) $(SOURCE_FILES)
bin:
	mkdir $(OUTDIR)

clean:
	rm -rf $(OUTDIR)
install:
	mv $(OUTDIR)/$(OUTFILE) $(DESTDIR)/usr/games/

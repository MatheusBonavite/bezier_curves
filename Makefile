.PHONY: bezier bezier-db clear

bezier:
	$(MAKE) -f Makefile.orig bezier

bezier-db:
	bear -- $(MAKE) -f Makefile.orig bezier

clear:
	rm -rf *.o
	rm -rf bezier
	rm -rf compile_commands.json

all: src examples

src:
	$(MAKE) -C src
	
examples:
	$(MAKE) -C examples

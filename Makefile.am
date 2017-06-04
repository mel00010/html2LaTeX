SUBDIRS=src test docs
docs: 
	cd docs && $(MAKE) docs
doc: docs 
.PHONY: docs

clean-docs:
	cd docs && $(MAKE) clean
clean-doc: clean-docs 
.PHONY: clean-docs

test: 
	cd test && $(MAKE) test && ./test
tests: test
.PHONY: test

clean-test:
	cd test && $(MAKE) clean
clean-tests: clean-test
.PHONY: clean-test
	
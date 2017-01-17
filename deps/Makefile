DEPS			= .
CRITERION_VERSION	= v2.3.0-1
CRITERION_DIR		= criterion-$(CRITERION_VERSION)
CRITERION_TARBALL	= $(CRITERION_DIR).tar.bz2
CRITERION_URL		= https://github.com/Snaipe/Criterion/releases/download/$(CRITERION_VERSION)/$(CRITERION_TARBALL)

all: build-deps

$(DEPS)/$(CRITERION_TARBALL): $(DEPS)
	curl -O -L $(CRITERION_URL)

.SECONDARY: $(DEPS)/$(CRITERION_TARBALL)
$(DEPS)/$(CRITERION_DIR): $(DEPS)/$(CRITERION_TARBALL)
	tar xfvj $(CRITERION_TARBALL)

CRITERION_PACKAGE = $(DEPS)/usr/local/include/criterion

.SECONDARY: $(DEPS)/$(CRITERION_DIR)
$(CRITERION_PACKAGE): $(DEPS)/$(CRITERION_DIR)
	@echo $@
	cd $(CRITERION_DIR); \
		cmake -H. -Bbuild; \
		cd build; \
		cmake --build .; \
		make DESTDIR=../../ install;

.PHONY: build-deps
build-deps: $(CRITERION_PACKAGE)

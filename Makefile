.PHONY: deps
deps:
	$(MAKE) -C $@

.PHONY: clean-all
clean-all:
	git clean -ffxd

.PHONY: docker-build
docker-build:
	docker build . -t damonkelley/tttc

.PHONY: dockerized-build
dockerized-build:
	docker run -it --rm -v $(CURDIR):/build damonkelley/tttc make build

.PHONY: build
build:
	echo "hello world"

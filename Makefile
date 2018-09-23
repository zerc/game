help:
	@echo "build - bild service from sources"
	@echo "install - install dependecies"
	@echo "run - compile and run the service"

build: 
	go build -o bin/game src/game/*.go

install:
	cd src/game && dep ensure

run: build
	rm debug.txt
	./bin/game -s 127.0.0.1

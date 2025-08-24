cflags := -Wall -std=c17 -Iinclude

init:
	mkdir -p build
	mkdir -p install
	mkdir -p build/test
	mkdir -p build/shared
	python3 tools/pec/pec.py .ec include/ec.h _LJW_HSLIB_EC_H_

build: build/libhslib.a build/libhslib.so
tbuild: build/test/hst
test: build/test/hst
	./build/test/hst
install: build/libhslib.a build/libhslib.so
	mkdir -p install/include
	cp -r include/* install/include/
	cp $^ install/
	cp .sym install/
	cd install && zip -r hslib.zip include/ *.a *.so .sym

build/libhslib.a: build/hst.o build/strh.o
	${AR} rcs $@ $^
build/libhslib.so: build/shared/hst.o build/shared/strh.o
	${CC} -shared $^ -o $@

build/test/hst: test/hst.c build/libhslib.a
	${CC} ${cflags} $^ -o $@

build/%.o: src/%.c
	${CC} ${cflags} $< -c -o $@
	nm -g $@ | awk '{print $$3}' >> .sym
build/shared/%.o: src/%.c
	${CC} ${cflags} $< -fPIC -c -o $@

clean:
	rm -rf build
	rm .sym

.PHONY: build tbuild test install clean init
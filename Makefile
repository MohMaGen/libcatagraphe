libs ?=
debug ?= -ggdb
warnings ?= -Wall -Werror -pedantic -pedantic-errors
build-dir ?= build
std ?= -std=c++17

src-dir ?= src
inc-dir ?= include

srcs := $(wildcard $(src-dir)/*.cpp)
incs := $(wildcard $(src-dir)/*.h)
objs := $(patsubst $(src-dir)/%.cpp, $(build-dir)/%.o, $(srcs))

lib: mkdir $(objs)
	gcc -o $(build-dir)/libcatagraphe.so --shared -rdynamic -fPIC \
		$(objs)	$(libs) $(warnings) $(debug) $(std)

$(objs): $(build-dir)/%.o: $(src-dir)/%.cpp $(incs)
	gcc -o $@ -c $< $(warnings) $(debug) -I $(inc-dir) $(std) -fPIC

mkdir:
	bash -c "[[ -d $(build-dir) ]] && mkdir -p $(build-dir) || true"

run-tests:
	#TODO

example-app:
	#TODO


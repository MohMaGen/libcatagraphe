libs ?=
debug ?= -ggdb
warnings ?= -Wall -Werror -pedantic -pedantic-errors
build-dir ?= build
std ?= -std=c++17
clrs ?= -fdiagnostics-color=always

src-dir ?= src
inc-dir ?= include

srcs := $(wildcard $(src-dir)/*.cpp)
incs := $(wildcard $(src-dir)/*.h) $(wildcard $(inc-dir)/catagraphe/*.h)
objs := $(patsubst $(src-dir)/%.cpp, $(build-dir)/%.o, $(srcs))

lib: mkdir $(objs)
	@bash -c "echo -e \"\\t• \\x1b[34mlink shared library:\\x1b[0m\""
	@g++ -o $(build-dir)/libcatagraphe.so --shared -rdynamic -fPIC \
		$(objs)	$(libs) $(warnings) $(debug) $(std) $(clrs)

$(objs): $(build-dir)/%.o: $(src-dir)/%.cpp $(incs)
	@bash -c "echo -e \"\\t• \\x1b[34mcompile object $@ from $<:\\x1b[0m\""
	@g++ -o $@ -c $< $(warnings) $(debug) -I$(inc-dir) $(std) -fPIC $(clrs)

mkdir:
	@bash -c "[[ -d $(build-dir) ]] && mkdir -p $(build-dir) || true"

run-tests: lib
	@bash -c "echo -e \"\\t• \\x1b[34mrun tests:\\x1b[0m\""
	@make -C tests run -s

example-app:
	#TODO


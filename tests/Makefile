src-dir := ./
build-dir := ../build
lib-dir := ../build
inc-dir := ../include/
libcatagraphe := catagraphe
clrs ?= -fdiagnostics-color=always

warnings ?= -Wall -Werror -pedantic -pedantic-errors
debug ?= -ggdb

srcs := $(wildcard $(src-dir)/*.cpp)
objs := $(patsubst $(src-dir)/%.cpp, $(build-dir)/test_%.o, $(srcs))
incs := $(wildcard $(src-dir)/*.h)


build: $(objs)
	@bash -c "echo -e \"\\t• \\x1b[35mbuild tests executable:\\x1b[0m\""
	@g++ -o $(build-dir)/run-tests $(objs) $(debug) $(warnings) \
		-L $(lib-dir) -l$(libcatagraphe) $(clrs)

$(objs): $(build-dir)/test_%.o: $(src-dir)/%.cpp $(incs)
	@bash -c "echo -e \"\\t• \\x1b[35mbuild object $@ from $<:\\x1b[0m\""
	@g++ -o $@ -c $< -ggdb $(warnings) -I $(inc-dir) $(clrs)

run: build
	@bash -c "echo -e \"\\t• \\x1b[35mrun tests\\x1b[0m\""
	@LD_LIBRARY_PATH=$(LD_PATH):$(lib-dir) $(build-dir)/run-tests	

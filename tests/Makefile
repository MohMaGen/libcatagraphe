src-dir := ./
build-dir := ../build
lib-dir := ../build
inc-dir := ../include/
libcatagraphe := catagraphe

warnings ?= -Wall -Werror -pedantic -pedantic-errors
debug ?= -ggdb

srcs := $(wildcard $(src-dir)/*.cpp)
objs := $(patsubst $(src-dir)/%.cpp, $(build-dir)/test_%.o, $(srcs))
incs := $(wildcard $(src-dir)/*.h)


build: $(objs)
	g++ -o $(build-dir)/run-tests $(objs) $(debug) $(warnings) \
		-L $(lib-dir) -l$(libcatagraphe)

$(objs): $(build-dir)/test_%.o: $(src-dir)/%.cpp $(incs)
	g++ -o $@ -c $< -ggdb $(warnings) -I $(inc-dir)

run: build
	LD_LIBRARY_PATH=$(LD_PATH):$(lib-dir) $(build-dir)/run-tests


	

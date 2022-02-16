EXT = c
CC = gcc
CFLAGS = -W -Wall -ansi -pedantic
EXEC=main

ifeq ($(CC),gcc)
	CFLAGS := $(CFLAGS) -std=c99
endif
 
LDFLAGS=



src_dir=src
obj_dir=obj
bin_dir=bin
lib_dir=lib

SRC  = $(wildcard $(src_dir)/*.$(EXT))

ifeq ($(MODE),TEXTE)

EXCLUDE=$(src_dir)/cairo_io.c
SRC:=$(filter-out $(EXCLUDE),$(SRC))

else

EXCLUDE=$(src_dir)/io.c
SRC:=$(filter-out $(EXCLUDE),$(SRC))

CFLAGS += -Iinclude -I/usr/include/cairo -DGRAPHIQUE
LDFLAGS += -lcairo -lm -lX11
 
endif

OBJ = $(SRC:$(src_dir)/%.c=$(obj_dir)/%.o)


all: $(EXEC)
$(EXEC): $(OBJ)
	 [ -d $(bin_dir) ] || mkdir $(bin_dir)
	 $(CC) -o $(bin_dir)/$@ $^ $(LDFLAGS)
	 [ -h $@ ] || ln -s $(bin_dir)/$@ $@
	 [ -d $(lib_dir) ] || mkdir $(lib_dir)
	 ar rcs $(lib_dir)/libjeu.a $(OBJ)
	rm main
	

$(obj_dir)/%.o: $(src_dir)/%.c
	 [ -d $(obj_dir) ] || mkdir $(obj_dir)
	 $(CC) -o $@ -c $< $(CFLAGS)


clean: 
	 rm -rf $(EXEC) $(obj_dir) $(bin_dir) $(lib_dir) Lafdhal_Ahmed-3.0.tar.xz
dist:
	 tar cfJ Lafdhal_Ahmed-3.0.tar.xz doc grilles include src Makefile


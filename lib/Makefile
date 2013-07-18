OUTDIR = build
LIBDIR = $(OUTDIR)/lib

SDL_DIR = SDL2-2.0.0
SDL_IMAGE_DIR = SDL2_image-2.0.0
SDL_MIXER_DIR = SDL2_mixer-2.0.0
SDL_NET_DIR = SDL2_net-2.0.0
SDL_TTF_DIR = SDL2_ttf-2.0.12

LUAJIT_DIR = LuaJIT-2.0.2
LUABRIDGE_DIR = LuaBridge/Source/LuaBridge

SDL_TARGET = $(LIBDIR)/libSDL2.a
SDL_IMAGE_TARGET = $(LIBDIR)/libSDL2_image.a
SDL_MIXER_TARGET = $(LIBDIR)/libSDL2_mixer.a
SDL_NET_TARGET = $(LIBDIR)/libSDL2_net.a
SDL_TTF_TARGET = $(LIBDIR)/libSDL2_ttf.a

LUAJIT_TARGET = $(LIBDIR)/libluajit-5.1.a
LUABRIDGE_TARGET = $(OUTDIR)/include/LuaBridge

all: $(SDL_TARGET) $(SDL_IMAGE_TARGET) $(SDL_MIXER_TARGET) $(SDL_NET_TARGET) $(SDL_TTF_TARGET) $(LUAJIT_TARGET) $(LUABRIDGE_TARGET)

$(SDL_TARGET):
	[ -f $(SDL_DIR)/Makefile ] || (cd $(SDL_DIR) && ./configure --prefix=$(CURDIR)/$(OUTDIR) --disable-shared $(CONFIGURE_OPTS))
	[ -f $(SDL_TARGET) ] || $(MAKE) -C $(SDL_DIR) install

define build-subdir
@echo "Building $< -> $@"
[ -f $</Makefile ] || (cd $< && ./configure --prefix=$(CURDIR)/$(OUTDIR) --with-sdl-prefix=$(CURDIR)/$(OUTDIR) --disable-shared $(CONFIGURE_OPTS))
[ -f $@ ] || $(MAKE) -C $< install
@echo "Delete $@ to force a rebuild of the library"
endef

$(SDL_IMAGE_TARGET): $(SDL_IMAGE_DIR)
	$(build-subdir)

$(SDL_MIXER_TARGET): $(SDL_MIXER_DIR)
	$(build-subdir)

$(SDL_NET_TARGET): $(SDL_NET_DIR)
	$(build-subdir)

# libfreetype2 is installed via Homebrew on OS X
ifeq ($(shell uname -s),Darwin)
$(SDL_TTF_TARGET): CONFIGURE_OPTS += --with-freetype-prefix=/usr/local
endif

$(SDL_TTF_TARGET): $(SDL_TTF_DIR)
	$(build-subdir)

$(LUAJIT_TARGET): $(LUAJIT_DIR)
	[ -f $@ ] || $(MAKE) -C $< install PREFIX=$(CURDIR)/$(OUTDIR)

$(LUABRIDGE_TARGET): $(LUABRIDGE_DIR)
	ln -s $(CURDIR)/$< $@

clean:
	-$(MAKE) -C $(SDL_DIR) distclean
	-$(MAKE) -C $(SDL_IMAGE_DIR) distclean
	-$(MAKE) -C $(SDL_MIXER_DIR) distclean
	-$(MAKE) -C $(SDL_NET_DIR) distclean
	-$(MAKE) -C $(SDL_TTF_DIR) distclean
	-$(MAKE) -C $(LUAJIT_DIR) clean
	$(RM) -r $(OUTDIR)

.PHONY: clean

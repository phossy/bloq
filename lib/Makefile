SDLDIR = SDL2-2.0.0
SUBDIRS = SDL2_image-2.0.0 SDL2_mixer-2.0.0 SDL2_net-2.0.0 SDL2_ttf-2.0.12
OUTDIR = build

all: sdl subdirs

sdl:
	[ -f $(SDLDIR)/Makefile ] || (cd $(SDLDIR) && ./configure --prefix=$(PWD)/$(OUTDIR) --disable-shared)
	$(MAKE) -C $(SDLDIR) install

subdirs: $(SUBDIRS)

$(SUBDIRS):
	[ -f $@/Makefile ] || (cd $@ && ./configure --prefix=$(PWD)/$(OUTDIR) --with-sdl-prefix=$(PWD)/$(OUTDIR) --disable-shared)
	$(MAKE) -C $@ install

clean:
	for DIR in $(SDLDIR) $(SUBDIRS); do	$(MAKE) -C $$DIR distclean; done
	rm -rf $(OUTDIR)

.PHONY: sdl clean subdirs $(SUBDIRS)

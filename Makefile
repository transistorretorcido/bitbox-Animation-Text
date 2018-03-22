NAME = animationText

GAME_C_FILES = main.c level.c simple_bg.c lib/blitter/blitter.c lib/blitter/blitter_tmap.c lib/blitter/blitter_sprites.c lib/sampler/sampler.c
GAME_BINARY_FILES = simple_bg.tmap simple_bg.tset birdy.spr


include $(BITBOX)/kernel/bitbox.mk
main.c: simple_bg.tmap birdy.spr

%.tset %.tmap %.c %.h: %.tmx
	python tmx.py $< > $*.h

birdy.spr : assets/birdy/bird_?.png
	python $(BITBOX)/lib/blitter/scripts/couples_encode.py $@ $(sort $^)

clean::
	rm -f *.tset *.tmap *.spr

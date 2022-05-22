LCC	= /mnt/c/Users/valdi/pvt/gbdk-linux64/bin/lcc
PNG2ASSET = /mnt/c/Users/valdi/pvt/gbdk-linux64/bin/png2asset

CFLAGS	=

# Output name for compiled ROM
BINS	   = game.gb

# Add entries here to have them converted into metasprites
PNGSOURCES   = sprite_tileset.png
PNG_CSOURCES = $(PNGSOURCES:%.png=%.c)
PNG_CHEADERS = $(PNGSOURCES:%.png=%.h)

# List of all C source files except those generated by png2asset
CSOURCES    = $(filter-out $(PNGSOURCES:%.png=%.c), $(wildcard *.c))

all: $(BINS)

compile.bat: Makefile
	@echo "REM Automatically generated from Makefile" > compile.bat
	@make -sn | sed y/\\//\\\\/ | grep -v make >> compile.bat

# Use png2asset to convert the png into C formatted metasprite data
# -sh 48   : Sets sprite height to 48 (width remains automatic)
# -spr8x16 : Use 8x16 hardware sprites
# -c ...   : Set C output file
%.c:	%.png
	$(PNG2ASSET) $< -sh 16 -sw 16 -spr8x8 -c $@ 

# Compile all C sources, including converted png metasprites
$(BINS): $(CSOURCES) $(PNG_CSOURCES)
	$(LCC) $(CFLAGS) -o $(BINS) $(CSOURCES) $(PNG_CSOURCES)


clean:
	rm -f *.o *.lst *.map *.gb *.ihx *.sym *.cdb *.adb *.asm $(PNG_CHEADERS) $(PNG_CSOURCES)

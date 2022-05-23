#include <gb/gb.h>
#include <gb/cgb.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>
#include <stdint.h>
#include "tiles/tileset1_tiles.h"
#include "sprite_tileset.h"

uint16_t PosX, PosY, frames;
uint8_t frame;
joypads_t joypads;
const unsigned char anim[] = {0, 1, 0, 2};
const unsigned char death_anim[] = {0, 1, 0, 1, 0, 1, 2, 3, 4, 5, 6};

const uint16_t bg_palette[] =
{  
0x0000,0x229f,0x00ca,0x01f5,
0x0000,0x3def,0x7fff,0x0000,
0x7df3,0x7ef7,0x7eff,0x0000
};

void main()
{

  PosX = PosY = 32 << 4;

  frames = frame = 0;

  BGP_REG = OBP0_REG = 0x1B;
  OBP1_REG = 0xE0;

  set_bkg_data(0x00, level1_tile_count, level1_tile_data);
  set_bkg_palette(0, 3, bg_palette); 
//   set_bkg_palette(0, 1, sprite_tileset_palettes); 
  set_sprite_palette(0,1,sprite_tileset_palettes);


  set_sprite_data(0, sizeof(sprite_tileset_tiles) >> 4, sprite_tileset_tiles);

  set_sprite_palette(0,1,sprite_tileset_palettes);

  // switch to 2nd video memory bank
  VBK_REG = 1; 
  // set background color palette map, do this first
  set_bkg_tiles(0, 0, level1_tile_map_width, level1_tile_map_height, level1_map_data2); 
  VBK_REG = 0; 

  set_bkg_tiles(0, 0, level1_tile_map_width, level1_tile_map_height, level1_map_data);

  DISPLAY_ON;
  SHOW_BKG;
  SHOW_SPRITES;

  joypad_init(1, &joypads);

  while(1) 
  {
      joypad_ex(&joypads);
        
      // game object
      if (joypads.joy0 & J_UP) {
          PosY -= 16;
      } else if (joypads.joy0 & J_DOWN) {
          PosY += 16;
      }

      if (joypads.joy0 & J_LEFT) {
          PosX -= 16;
      } else if (joypads.joy0 & J_RIGHT) {
          PosX += 16;
      }

      if(!(frames & 15)){
        ++frame;
        if(frame > 10)
          frame= 0;
      }

      move_metasprite(sprite_tileset_metasprites[death_anim[frame] + 25], 0, 0, (PosX >> 4), (PosY >> 4) + 8);
      wait_vbl_done();
      ++frames;
  }
}

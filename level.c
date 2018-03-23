#include <string.h>
#include <stdint.h>

#include "lib/blitter/blitter.h"
#include "lib/sampler/sampler.h"

#include "simple_bg.h"
#define TMAP_SIMPLE_W 40
#define TMAP_SIMPLE_H 30
//#define TILE_SIZE 16

#define Max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define Min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

uint16_t simple_ramtilemap[TMAP_SIMPLE_H][TMAP_SIMPLE_W];
int start_frame;
int birdyAnim_frame;
int fr_BirdyCount = 0;
int birdyLeft = 0;
int birdyRight = 0;
int birdyFlip = 0;
int birdyUp = 0;
int birdyDown = 0;
int birdySpeed = 1;

extern void (*do_frame)(void);
extern  void level_init();
extern char birdy_spr[];
static struct object *birdy;
static struct object *background;
void level_out();

void update_birdy_anim()
{
  if(birdyAnim_frame > 5)
  {
    if(!birdyFlip)
    {
      if(fr_BirdyCount < 2) fr_BirdyCount++;
      else fr_BirdyCount = 0;
      birdy->fr=fr_BirdyCount;
      birdyAnim_frame = 0;
    }else
    {
      if(fr_BirdyCount > 2 && fr_BirdyCount < 5 ) fr_BirdyCount++;
      else fr_BirdyCount = 3;
      birdy->fr=fr_BirdyCount;
      birdyAnim_frame = 0;
    }

  }else birdyAnim_frame++;
}

void update_birdy_position()
{
  if(birdyLeft && birdy->x > 0)
  {
    birdy->x--;
    simple_ramtilemap[27][13]=0x2D;
    simple_ramtilemap[27][14]=0x26;
    simple_ramtilemap[27][15]=0x27;
    simple_ramtilemap[27][16]=0x35;
  }else {
    simple_ramtilemap[27][13]=0x17E;
    simple_ramtilemap[27][14]=0x17E;
    simple_ramtilemap[27][15]=0x17E;
    simple_ramtilemap[27][16]=0x17E;
  }

  if(birdyRight && birdy->x < (640 - birdy->w)) {
    birdy->x++;
    simple_ramtilemap[27][21]=0x33;
    simple_ramtilemap[27][22]=0x2A;
    simple_ramtilemap[27][23]=0x28;
    simple_ramtilemap[27][24]=0x29;
    simple_ramtilemap[27][25]=0x35;
  }else {
    simple_ramtilemap[27][21]=0x17E;
    simple_ramtilemap[27][22]=0x17E;
    simple_ramtilemap[27][23]=0x17E;
    simple_ramtilemap[27][24]=0x17E;
    simple_ramtilemap[27][25]=0x17E;
  }

  if(birdyUp && birdy->y > 0) {
    birdy->y--;
    simple_ramtilemap[26][18]=0x36;
    simple_ramtilemap[26][19]=0x31;
  }else {
    simple_ramtilemap[26][18]=0x17E;
    simple_ramtilemap[26][19]=0x17E;
  }

  if(birdyDown && birdy->y < (480 - birdy->h)) {
    birdy->y++;
    simple_ramtilemap[28][17]=0x25;
    simple_ramtilemap[28][18]=0x30;
    simple_ramtilemap[28][19]=0x38;
    simple_ramtilemap[28][20]=0x2F;
  }else {
    simple_ramtilemap[28][17]=0x17E;
    simple_ramtilemap[28][18]=0x17E;
    simple_ramtilemap[28][19]=0x17E;
    simple_ramtilemap[28][20]=0x17E;
  }
}

void level_frame()
{
  if (GAMEPAD_PRESSED(0,right))
  {
    birdyRight = 1;
    birdyLeft = 0;
    birdyFlip = 0;
	}else if (GAMEPAD_PRESSED(0,left))
  {
    birdyRight = 0;
    birdyLeft = 1;
		birdyFlip = 1;
	}else
  {
    birdyRight = 0;
    birdyLeft = 0;
  }

  if (GAMEPAD_PRESSED(0,up))
  {
    birdyUp = 1;
    birdyDown = 0;
	}else if (GAMEPAD_PRESSED(0,down))
  {
    birdyUp = 0;
    birdyDown = 1;
	}else
  {
    birdyUp = 0;
    birdyDown = 0;
  }

	if (GAMEPAD_PRESSED(0,start)) level_out();
  update_birdy_anim();
  update_birdy_position();
}

void level_init()
{
  birdy = sprite_new(birdy_spr, 300, 140,0);
	birdy->fr=0;

  background = tilemap_new(
  		simple_bg_tset,640,480,
  		TMAP_HEADER(TMAP_SIMPLE_W,TMAP_SIMPLE_H,TSET_16,TMAP_U16),
  		simple_ramtilemap
  		);
  start_frame=vga_frame;

  tmap_blit(background,0,0,simple_bg_header,simple_bg_tmap);

	do_frame = level_frame;
}

void level_out()
{
	// de-allocate objects
	blitter_remove(background);
  blitter_remove(birdy);
  //blitter_remove(sawDisc);
}

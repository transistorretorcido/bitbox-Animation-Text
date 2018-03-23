#include <stdint.h>
// tile ids
// layers
#define simple_bg_intro 0
// max indices :  384
#define simple_bg_header TMAP_HEADER(40,30,TSET_16,TMAP_U16)
extern const uint16_t simple_bg_tset[]; // from assets/tiles3.png
extern const uint16_t simple_bg_tmap[][40*30];

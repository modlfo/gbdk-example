#include "tiles.h"
#include <gb/console.h>
#include <gb/font.h>
#include <gb/gb.h>
#include <stdio.h>

typedef struct Sprite {
  UINT8 x;
  UINT8 y;
  UINT8 index;
  UINT8 sprite;
} Sprite;

typedef struct GlobalState {
  UINT8 sprite_index;
} GlobalState;

void initializeSprite(GlobalState *state, Sprite *s) {
  s->index = state->sprite_index;
  s->sprite = 0U;
  s->x = 0U;
  s->y = 0U;

  state->sprite_index = state->sprite_index + 1;
}

void updateSprite(Sprite *s) {
  set_sprite_tile(s->index, s->sprite);
  move_sprite(s->index, s->x, s->y);
}

void animateSpider(Sprite *s, UINT8 moving) {
  if (moving) {
    s->sprite = s->sprite ? 0U : 1U;
  }
}

void scrollSpider(Sprite *s, INT8 x, INT8 y) {
  s->x += x;
  s->y += y;
  s->x = s->x < 8 ? 8 : (s->x > 160 ? 160 : s->x);
  s->y = s->y < 16 ? 16 : (s->y > 152 ? 152 : s->y);
}

void main() {
  font_init();
  font_t f = font_load(font_min);
  font_set(f);

  GlobalState state;
  Sprite spider;
  set_sprite_data(0, 2, Smiler);
  SHOW_SPRITES;

  initializeSprite(&state, &spider);

  spider.x = 140;
  spider.y = 140;

  while (1) {
    UINT8 key = joypad();
    UINT8 moving = key != 0;
    if (key & J_LEFT) {
      scrollSpider(&spider, -2, 0);
    }
    if (key & J_RIGHT) {
      scrollSpider(&spider, 2, 0);
    }
    if (key & J_UP) {
      scrollSpider(&spider, 0, -2);
    }
    if (key & J_DOWN) {
      scrollSpider(&spider, 0, 2);
    }

    animateSpider(&spider, moving);

    updateSprite(&spider);

    gotoxy(0, 0);
    printf("1016");

    UINT8 counter;
    for (counter = 0; counter < 4; counter++) {
      wait_vbl_done();
    }
  }
}
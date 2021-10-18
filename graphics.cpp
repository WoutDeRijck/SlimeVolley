#include "graphics.h"

#include <stdarg.h>
#include <stdio.h>

#include "constants.h"

void Graphics::LoadFonts()
{
	font = al_load_ttf_font("./assets/fonts/digital.ttf", FONT_SIZE, 0);
	if (!font)
	{
		al->ShowError("Failed to initialize font!");
		al_destroy_display(al->display);
		al_destroy_timer(al->timer);
		exit(-1);
	}
}

void Graphics::LoadSpriteCache()
{
	sprites.resize(SPRITE_LENGTH);
	sprites[SPRITE_NONE] = al_load_bitmap("./assets/images/none.png");
	sprites[SPRITE_ICON] = al_load_bitmap("./assets/images/icon.png");
	sprites[SPRITE_BACKGROUND1] = al_load_bitmap("./assets/images/background1.jpg");
	sprites[SPRITE_BACKGROUND2] = al_load_bitmap("./assets/images/background2.jpg");
	sprites[SPRITE_BACKGROUND3] = al_load_bitmap("./assets/images/background3.jpg");
	sprites[SPRITE_NET] = al_load_bitmap("./assets/images/net.png");
	sprites[SPRITE_PLAYER1] = al_load_bitmap("./assets/images/player1.png");
	sprites[SPRITE_PLAYER2] = al_load_bitmap("./assets/images/player2.png");
	sprites[SPRITE_PUPIL] = al_load_bitmap("./assets/images/pupil.png");
	sprites[SPRITE_OPPONENT1] = al_load_bitmap("./assets/images/opponent1.png");
	sprites[SPRITE_OPPONENT2] = al_load_bitmap("./assets/images/opponent2.png");
	sprites[SPRITE_OPPONENT3] = al_load_bitmap("./assets/images/opponent3.png");
	sprites[SPRITE_POINT] = al_load_bitmap("./assets/images/point.png");
	sprites[SPRITE_POINT_P1] = al_load_bitmap("./assets/images/pointp1.png");
	sprites[SPRITE_POINT_P2] = al_load_bitmap("./assets/images/pointp2.png");
	sprites[SPRITE_POINT_O1] = al_load_bitmap("./assets/images/pointo1.png");
	sprites[SPRITE_POINT_O2] = al_load_bitmap("./assets/images/pointo2.png");
	sprites[SPRITE_POINT_O3] = al_load_bitmap("./assets/images/pointo3.png");
	sprites[SPRITE_BALL] = al_load_bitmap("./assets/images/ball.png");
	al_set_display_icon(al->display, sprites[SPRITE_ICON]);
	al_set_window_title(al->display, "Slime Volley");
}

void Graphics::UnLoadFonts()
{
	al_destroy_font(font);
}

void Graphics::UnLoadSpriteCache()
{
	for (vector<ALLEGRO_BITMAP *>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
	{
		if ((*iter) != NULL)
			al_destroy_bitmap(*iter);
	}
}

void Graphics::ExecuteDraws()
{
	for (auto t : txt_overlay)
	{
		int a;
		switch (t.align)
		{
		case Graphics::ALIGN_LEFT:
			a = ALLEGRO_ALIGN_LEFT;
			break;
		case Graphics::ALIGN_CENTER:
			a = ALLEGRO_ALIGN_CENTRE;
			break;
		case Graphics::ALIGN_RIGHT:
			a = ALLEGRO_ALIGN_RIGHT;
			break;
		}
		al_draw_text(font, al_map_rgb(t.c.r, t.c.g, t.c.b), t.dx, t.dy, a, t.str.c_str());
	}
	al_flip_display();
	ClearScreen();
	txt_overlay.clear();
}

void Graphics::ClearScreen()
{
	al_clear_to_color(al_map_rgb(15, 5, 10));
}

void Graphics::SetBackground(Sprite sprite)
{
	background = sprite;
}

void Graphics::DrawBackground()
{
	DrawBitmap(background, 0, 0);
}

void Graphics::DrawBitmap(Sprite sprite, float dx, float dy, float cx, float cy)
{
	al_draw_rotated_bitmap(sprites[sprite], cx, cy, dx, dy, 0, 0);
}

void Graphics::DrawString(string str, float dx, float dy, Color c, Align align)
{
	Txt txt = { str, dx, dy, c, align };
	txt_overlay.push_back(txt);
}

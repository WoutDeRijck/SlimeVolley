#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <vector>

#include "allegro_lib.h"
#include "color.h"
#include "entity.h"

using namespace std;

class Graphics
{
public:
	static Graphics& Instance()
	{
		static Graphics instance;
		return instance;
	}

	~Graphics()
	{
	};

	enum Sprite
	{
		SPRITE_NONE,
		SPRITE_ICON,
		SPRITE_BACKGROUND1,
		SPRITE_BACKGROUND2,
		SPRITE_BACKGROUND3,
		SPRITE_NET,
		SPRITE_PLAYER1,
		SPRITE_PLAYER2,
		SPRITE_PUPIL,
		SPRITE_OPPONENT1,
		SPRITE_OPPONENT2,
		SPRITE_OPPONENT3,
		SPRITE_POINT,
		SPRITE_POINT_P1,
		SPRITE_POINT_P2,
		SPRITE_POINT_O1,
		SPRITE_POINT_O2,
		SPRITE_POINT_O3,
		SPRITE_BALL,
		SPRITE_LENGTH
	};

	enum Align
	{
		ALIGN_LEFT,
		ALIGN_CENTER,
		ALIGN_RIGHT
	};

	void LoadFonts();
	void LoadSpriteCache();
	void UnLoadFonts();
	void UnLoadSpriteCache();

	void ExecuteDraws();
	void ClearScreen();

	void SetBackground(Sprite sprite);

	void DrawBackground();
	void DrawBitmap(Sprite sprite, float dx, float dy, float cx = 0, float cy = 0);
	void DrawString(std::string str, float dx, float dy, Color c, Align align);

private:
	typedef struct Txt
	{
		std::string str;
		float dx;
		float dy;
		Color c;
		Graphics::Align align;
	} Txt;

	AllegroLib* al;
	ALLEGRO_FONT* font;
	std::vector<Txt> txt_overlay;
	std::vector<ALLEGRO_BITMAP*> sprites;
	Sprite background;

	Graphics() :
		al(&AllegroLib::Instance()),
		background(SPRITE_BACKGROUND1)
	{
	};

	Graphics(Graphics const&)
	{
	};

	void operator=(Graphics const&)
	{
	};
};

#endif
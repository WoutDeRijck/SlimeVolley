#ifndef ALLEGRO_LIB_H
#define ALLEGRO_LIB_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <string>

class Graphics;

class AllegroLib
{
	friend class Graphics;
public:
	static AllegroLib& Instance()
	{
		static AllegroLib instance;
		return instance;
	}

	~AllegroLib()
	{
	};

	enum Sprite
	{
		NONE
	};

	enum Align
	{
		LEFT,
		CENTER,
		RIGHT
	};

	void Init(int _screen_width, int _screen_height, float _fps);
	void StartLoop();
	void StartIteration();
	void Destroy();

	ALLEGRO_EVENT GetCurrentEvent();
	bool IsWindowClosed();
	bool IsTimerEvent();

private:
	AllegroLib()
	{
	};

	AllegroLib(AllegroLib const&)
	{
	};

	void operator=(AllegroLib const&)
	{
	};

	void ShowError(std::string msg);

	ALLEGRO_DISPLAY* display;
	ALLEGRO_TIMER* timer;
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_EVENT event;
	int screen_width;
	int screen_height;
	float fps;
};

#endif
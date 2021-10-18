#include "game.h"

#include <stdio.h>

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <thread>
#include <sstream>
#include <vector>

#include "allegro_lib.h"
#include "context.h"
#include "entity.h"
#include "entity_stream.h"
#include "game_multi.h"
#include "game_replay.h"
#include "game_single.h"
#include "graphics.h"

Game::Game(Context* _context) :
	context(_context)
{
	// Initialize Allegro
	AllegroLib::Instance().Init(context->GetScreenWidth(), context->GetScreenHeight(), context->GetFps());

	// Load sprites and fonts
	Graphics::Instance().LoadSpriteCache();
	Graphics::Instance().LoadFonts();

	// Read highscores and push back to vector
	std::ifstream input("./assets/highscores/highscores.txt");
	int score = 0;
	std::time_t start_time = 0;
	for (int i = 0; i < 5; i++)
	{
		input >> score >> start_time;
		highscores.push_back(score);
		start_times.push_back(start_time);
	}
}

Game::~Game()
{
	// Remove sprites and fonts
	Graphics::Instance().UnLoadSpriteCache();
	Graphics::Instance().UnLoadFonts();

	// Destroy Allegro
	AllegroLib::Instance().Destroy();
}

void Game::Run()
{
	// Initialize game loop
	AllegroLib::Instance().StartLoop();
	bool quit = AllegroLib::Instance().IsWindowClosed();
	int selected_item = 0;

	// Enter game loop
	while (!quit)
	{
		// Start iteration
		AllegroLib::Instance().StartIteration();

		// Process keyboard input
		ALLEGRO_EVENT event = AllegroLib::Instance().GetCurrentEvent();
		if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_UP)
		{
			selected_item--;
			selected_item = (selected_item % 4 + 4) % 4;
		}
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
			selected_item++;
			selected_item %= 4;

		}
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ENTER)
		{
			// Perform action corresponding to selected item
			if (selected_item == 0)
			{
				// Start a singleplayer game
				StartSingleplayer();
			}
			else if (selected_item == 1)
			{
				// Start a multiplayer game
				StartMultiplayer();
			}
			else if (selected_item == 2)
			{
				// Go to the highscores
				ViewHighscores();
			}
			else if (selected_item == 3)
			{
				break;
			}
		}

		// Update screen
		Color red(255, 30, 0);
		Color white(255, 255, 255);
		Graphics::Instance().ClearScreen();
		Graphics::Instance().DrawString("Singleplayer", 375, 100, selected_item == 0 ? red : white, Graphics::ALIGN_CENTER);
		Graphics::Instance().DrawString("Multiplayer", 375, 150, selected_item == 1 ? red : white, Graphics::ALIGN_CENTER);
		Graphics::Instance().DrawString("Highscores", 375, 200, selected_item == 2 ? red : white, Graphics::ALIGN_CENTER);
		Graphics::Instance().DrawString("Quit", 375, 250, selected_item == 3 ? red : white, Graphics::ALIGN_CENTER);
		Graphics::Instance().ExecuteDraws();

		// Check if window is closed
		quit = AllegroLib::Instance().IsWindowClosed();
	}
}

void Game::ViewHighscores()
{
	// Initialize game loop
	bool quit = AllegroLib::Instance().IsWindowClosed();
	int selected_item = 0;

	// Enter game loop
	while (!quit)
	{
		// Start iteration
		AllegroLib::Instance().StartIteration();

		// Process keyboard input
		ALLEGRO_EVENT event = AllegroLib::Instance().GetCurrentEvent();
		if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_UP)
		{
			selected_item--;
			selected_item = (selected_item % 6 + 6) % 6;
		}
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
			selected_item++;
			selected_item %= 6;

		}
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ENTER)
		{
			// Perform action corresponding to selected item
			if (selected_item == 5)
			{
				// Break the game loop to return to first menu
				break;
			}
			else
			{
				if (highscores[selected_item] > 0)
				{
					// Replay the specified game
					StartReplay(selected_item);
				}
			}
		}

		// Update screen
		Color red(255, 30, 0);
		Color white(255, 255, 255);
		Graphics::Instance().ClearScreen();
		int i = 0;
		while (i < 5)
		{
			if (highscores[i] > 0)
			{
				struct tm info;
				char buff[20];
				localtime_r(&start_times[i], &info);
				strftime(buff, 20, "%Y-%m-%d %H:%M:%S", &info);
				stringstream ss;
				ss << setw(5) << std::to_string(highscores[i]);
				Graphics::Instance().DrawString("[" + to_string(i + 1) + "]" + ss.str() + " - " + buff, 375, 60 + 35 * i, selected_item == i ? red : white, Graphics::ALIGN_CENTER);
			}
			else
			{
				Graphics::Instance().DrawString("[" + to_string(i + 1) + "]" + " No highscore set", 375, 60 + 35 * i, selected_item == i ? red : white, Graphics::ALIGN_CENTER);
			}
			
			i++;
		}
		Graphics::Instance().DrawString("Return", 375, 280, selected_item == 5 ? red : white, Graphics::ALIGN_CENTER);
		Graphics::Instance().ExecuteDraws();

		// Check if window is closed
		quit = AllegroLib::Instance().IsWindowClosed();
	}
}

void Game::StartSingleplayer()
{
	// Update start time in context
	context->UpdateStartTime();

	// Indicates whether or not the player wants to restart the game
	bool retry = false;

	// Iterate over all levels
	for (int i = 1; i <= 3; i++)
	{
		// Initialize game
		GameSingle game(context, i);

		// Run the game and get the game state
		int state = game.Run();

		// Determine what happens next
		if (state == 1)
		{
			// Player completed the level, so continue
			printf("Info: Player sucessfully completed level %i\n", i);
		}
		else if (state == 2)
		{
			// Player failed the level and wants to quit
			printf("Info: Player wants to quit\n");
			break;
		}
		else if (state == 3)
		{
			// Player failed the level and wants to retry
			printf("Info: Player wants to retry\n");
			retry = true;
			break;
		}
		else
		{
			// Player closed window
			printf("Info: Player closed window\n");
			break;
		}
	}

	// Get score and game start time
	bool new_highscore = false;
	int score = context->GetScore();
	std::time_t start_time = context->GetStartTime();
	// Determine the score's index compared to highscores
	for (int i = 0; i < 5; i++)
	{
		// Is a new top score achieved?
		if (highscores[i] < score)
		{
			new_highscore = true;
			// Update vectors
			highscores.insert(highscores.begin() + i, score);
			start_times.insert(start_times.begin() + i, start_time);

			// Remove last entry
			highscores.pop_back();
			start_times.pop_back();

			// Update highscores file
			std::ofstream output("./assets/highscores/highscores.txt");
			for (int j = 0; j < 5; j++)
			{
				output << to_string(highscores[j]) + " " + to_string(start_times[j]) + "\n";
			}
			output.close();

			// Change start time of file to remove
			start_time = start_times[4];
			break;
		}
	}

	// Remove unnecessary files
	if (start_time > 0 && !new_highscore)
	{
		// Remove one output file per level
		for (int j = 1; j <= 3; j++)
		{
			std::string file_name = "./assets/highscores/" + std::to_string(start_time) + "_" + std::to_string(j) + ".txt";
			// Determine if the file was removed successfully
			if (remove(file_name.c_str()) == 0)
			{
				printf("Info: File %s successfully deleted\n", file_name.c_str());
			}
			else
			{
				printf("Info: File %s could not be deleted\n", file_name.c_str());
			}
		}
	}

	// Reset score in context
	context->ResetScore();

	// Restart game if necessary
	if (retry)
	{
		// Start a new singleplayer game
		StartSingleplayer();
	}
}

void Game::StartMultiplayer()
{
	// Initialize and run the game
	GameMulti game(context);
	int state = game.Run();
	if(state == 4){
		Run();
	}
}

void Game::StartReplay(int selected_item)
{
	// Iterate over different levels
	for (int i = 1; i <= 3; i++)
	{
		// File name is based on the game's timestamp and level
		std::string file_name = "./assets/highscores/" + to_string(start_times[selected_item]) + "_" + to_string(i) + ".txt";

		// Check if a file for the level exists
		if (std::ifstream(file_name.c_str()))
		{
			// Initialize and run the game
			GameReplay game(context, i, file_name);
			if (game.Run())
			{
				// Player completed the level, so continue
				printf("Info: Player sucessfully completed level %i\n", i);
			}
			else
			{
				// Player failed the level, so break
				printf("Info: Player failed level %i\n", i);
				break;
			}
		}
		else
		{
			printf("Info: File %s does not exist\n", file_name.c_str());
		}
	}

	// Reset score in context
	context->ResetScore();
}

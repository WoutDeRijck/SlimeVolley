#include "context.h"
#include "game.h"

int main(int argc, char** argv)
{
	// Initialize context and game
	Context context(750, 375);
	Game game(&context);

	// Run the game
	game.Run();

	// Quit
	return 0;
}

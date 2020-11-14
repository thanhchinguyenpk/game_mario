#include "UI.h"

void UI::Render(int remainingTime)
{

	text.Render(posX, posY, to_string(remainingTime));
}

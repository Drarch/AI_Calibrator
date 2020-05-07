#include "ArtPainter.h"

void ArtPainter::DrawAI()
{
    ConsoleMarker::DrawTextRectangle(45, 2, 15, 7, Consts::TextColor::LIGHT_YELLOW);
}

void ArtPainter::DrawCell(COORD Position)
{
    ConsoleMarker::DrawTextRectangle({Position.X-1, Position.Y-1}, 3, 3);
    ConsoleMarker::DrawCharacter(Position, 'X');
}

void DrawLine(COORD Start, COORD End, LineDirection Direction, Consts::TextColor Color)
{
    
}
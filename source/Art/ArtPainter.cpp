#include "ArtPainter.h"

const COORD ArtPainter::AIPosition = {60, 3};
const COORD ArtPainter::AISize = {15, 7};
const COORD ArtPainter::AILeftEyeOffset = {4, 1};
const SHORT ArtPainter::AIEyeSeparation = 6;
const COORD ArtPainter::AIMouthOffset = {5, 4};
const SHORT ArtPainter::AIMouthSize = 3;


void ArtPainter::DrawAI()
{
    ConsoleMarker::DrawTextRectangle(AIPosition, AISize.X, AISize.Y, Consts::TextColor::LIGHT_YELLOW);
    DrawAIFace();
}

void ArtPainter::DrawAIFace() /* Make Strategy class structure for diffrent faces */
{
    COORD DrawPosition = {AIPosition.X + AILeftEyeOffset.X, AIPosition.Y + AILeftEyeOffset.Y};
    /* Left eye */
    ConsoleMarker::DrawCharacter(DrawPosition, '_');
    ConsoleMarker::DrawCharacter({DrawPosition.X, DrawPosition.Y+1}, 'O');

    /* Right eye */
    DrawPosition = {DrawPosition.X + AIEyeSeparation, DrawPosition.Y};
    ConsoleMarker::DrawCharacter(DrawPosition, '_');
    ConsoleMarker::DrawCharacter({DrawPosition.X, DrawPosition.Y+1}, 'O');

    /* Mouth */
    DrawPosition = {AIPosition.X + AIMouthOffset.X, AIPosition.Y + AIMouthOffset.Y};;
    ConsoleMarker::DrawTextLine(DrawPosition, AIMouthSize, LineDirection::Horizontal);
    ConsoleMarker::DrawCharacter(DrawPosition, '\\');
}


void ArtPainter::DrawCell(COORD Position)
{
    ConsoleMarker::DrawTextRectangle({Position.X-1, Position.Y-1}, 3, 3);
    ConsoleMarker::DrawCharacter(Position, 'X');
}
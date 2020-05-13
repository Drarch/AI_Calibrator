#pragma once

#include "..\Console\ConsoleMarker.h"

class ArtPainter
{
private:
    static const COORD AIPosition;
    static const COORD AISize;
    static const COORD AILeftEyePosition;
    static const SHORT AIEyeSeparation;
    static const COORD AIMouthPosition;
    static const SHORT AIMouthSize;

public:
    static void DrawAI();
    static void DrawAIFace();
    static void DrawCell(COORD Position);

private:

};

/*
typedef struct _DIM {
    short Width;
    short Height;
} DIM;
*/
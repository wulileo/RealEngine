#pragma once

#include "Core/Collections/Map.h"
#include "KeyCode.h"
#include "Core/Global.h"

class Input {
public:
    static bool IsKeyPress(unsigned short Code);

    static bool IsKeyHold(unsigned short Code);

    static bool IsKeyRelease(unsigned short Code);

    static void RecordKey(unsigned short Code, unsigned char Action);

    static void Update();

    static bool IsMouseButtonPress(unsigned short MouseCode);

    static bool IsMouseButtonHold(unsigned short MouseCode);

    static bool IsMouseButtonRelease(unsigned short MouseCode);

    static void RecordScroll(float RollNum) { MouseRollNum += RollNum; }

public:
    static FVector2 MousePosition;
    static float MouseRollNum;

private:
    static TMap<unsigned short, unsigned char> KeyEventMap;
};

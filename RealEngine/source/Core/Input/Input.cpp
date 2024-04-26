#include "Input.h"
#include "core/collections/Array.h"

TMap<unsigned short, unsigned char> Input::KeyEventMap;
FVector2 Input::MousePosition = {0, 0};
float Input::MouseRollNum = 0;

bool Input::IsKeyPress(unsigned short Code) {
    return KeyEventMap.Contains(Code);
}

bool Input::IsKeyHold(unsigned short Code) {
    if (!KeyEventMap.Contains(Code)) {
        return false;
    }
    return KeyEventMap.Get(Code) != KEY_ACTION_UP;
}

bool Input::IsKeyRelease(unsigned short Code) {
    if (!KeyEventMap.Contains(Code)) {
        return false;
    }
    return KeyEventMap.Get(Code) == KEY_ACTION_UP;
}

void Input::RecordKey(unsigned short Code, unsigned char Action) {
    KeyEventMap.Put(Code, Action);
}

void Input::Update() {
    TArray<unsigned short> Removed;
    for (auto Entry: KeyEventMap) {
        unsigned short Code = Entry.first;
        unsigned char Action = Entry.second;
        if (Action == KEY_ACTION_UP) {
            Removed.Add(Code);
        }
    }
    for (unsigned short Code: Removed) {
        KeyEventMap.Remove(Code);
    }
    MouseRollNum = 0;
}

bool Input::IsMouseButtonPress(unsigned short MouseCode) {
    return IsKeyPress(MouseCode);
}

bool Input::IsMouseButtonHold(unsigned short MouseCode) {
    return IsKeyHold(MouseCode);
}

bool Input::IsMouseButtonRelease(unsigned short MouseCode) {
    return IsKeyRelease(MouseCode);
}

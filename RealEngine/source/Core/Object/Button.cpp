#include "Button.h"

#include "core/input/Input.h"
#include "application/Screen.h"
#include "MeshComponent.h"

void UButton::Tick() {
    UWidget::Tick();

    if (!ImageNormal || !ImagePress) {
        return;
    }

    TArray<AMeshComponent *> MeshComponents = ImageNormal->GetComponents<AMeshComponent>();
    if (MeshComponents.IsEmpty()) {
        return;
    }
    if (Input::IsMouseButtonHold(MOUSE_BUTTON_LEFT)) {
        auto PositionNormal = MeshComponents.Get(0)->Transform.Position;
        auto MousePosition = Input::MousePosition;
        MousePosition.x = MousePosition.x - (float) Screen::get_width() / 2;
        MousePosition.y = (float) Screen::get_height() / 2 - MousePosition.y;
        auto WidthNormal = (float) ImageNormal->Texture2D->width;
        auto HeightNormal = (float) ImageNormal->Texture2D->width;
        if ((MousePosition.x > PositionNormal.x && MousePosition.x < PositionNormal.x + WidthNormal) &&
            (MousePosition.y > PositionNormal.y && MousePosition.y < PositionNormal.y + HeightNormal)) {
            if (bPressed) {
                return;
            }
            bPressed = true;
            if (ClickCallback) {
                ClickCallback();
            }
        } else {
            bPressed = false;
        }
    } else {
        bPressed = false;
    }
}

void UButton::Init() {
    ImageNormal->Init();
    ImagePress->Init();
}

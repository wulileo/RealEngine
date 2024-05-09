#include "Text.h"
#include "MeshComponent.h"

#include <utility>

void UText::SetText(String InText) {
    this->Text = std::move(InText);
    dirty = true;
}

void UText::Tick() {
    UWidget::Tick();

    if (!Font || !Font->font_texture) {
        return;
    }

    if (dirty) {
        dirty = false;
        std::vector<Font::Character *> Characters = Font->load_string(Text);
        std::vector<Vertex> Vertexes;
        std::vector<unsigned short> Indexes(Characters.size() * 6);
        int x = 0;
        std::vector<unsigned short> index = {0, 1, 2, 0, 2, 3};
        for (int i = 0; i < Characters.size(); ++i) {
            auto Character = Characters[i];
            int width = (int) ((Character->right_bottom_x - Character->left_top_x) * (float) Font->font_texture->width);
            int height = (int) ((Character->right_bottom_y - Character->left_top_y) * (float) Font->font_texture->height);
            Vertexes.insert(Vertexes.end(), {
                    {{x,         0.0f,   0.0f}, Color, {Character->left_top_x,     Character->right_bottom_y}},
                    {{x + width, 0.0f,   0.0f}, Color, {Character->right_bottom_x, Character->right_bottom_y}},
                    {{x + width, height, 0.0f}, Color, {Character->right_bottom_x, Character->left_top_y}},
                    {{x,         height, 0.0f}, Color, {Character->left_top_x,     Character->left_top_y}}
            });
            x += width;
            for (int j = 0; j < index.size(); ++j) {
                Indexes[i * index.size() + j] = index[j] + i * 4;
            }
        }
        auto MeshComponent = Cast<AMeshComponent *>(RootComponent);
        if (MeshComponent) {
            MeshComponent->CreateMesh(Vertexes, Indexes);
        }
    }
}

void UText::Init() {
    TArray<AMeshComponent *> MeshComponents = GetComponents<AMeshComponent>();
    if (MeshComponents.IsEmpty()) {
        auto *MeshComponent = AddComponent<AMeshComponent>("Mesh");
        MeshComponent->LoadMaterial(Utils::data_dir + "material/ui_text.mat");
        MeshComponent->MeshRenderer.material->set_texture("u_diffuse_texture", Font->font_texture);
        MeshComponents.Add(MeshComponent);
    }
}

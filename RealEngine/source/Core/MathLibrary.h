#pragma once

#include "vec3.hpp"
#include "detail/type_mat.hpp"

typedef glm::vec3 FVector;
typedef glm::vec4 FVector4;
typedef glm::vec2 FVector2;

typedef glm::mat4 FQuad;

struct FTransform {
    FVector Position{0, 0, 0};
    FVector Rotation{0, 0, 0};
    FVector Scale{1, 1, 1};
};
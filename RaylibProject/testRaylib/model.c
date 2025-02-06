#include "main.h"


JustModel CreateJustModel_Object(char *ModelPath, Vector3 Position, Vector3 Scale) {
    JustModel ThisJustModel = {
        .ModelPath = ModelPath,
        .ThisModel = LoadModel(ModelPath),
        .ThisModelPosition = Position,
        .ThisModelBody     = Scale
    };

    return ThisJustModel;
}

void AddTextureToIndex(JustModel *ThisModel, int ThisIndex, Texture ThisTexture) {
    ThisModel->ThisModel.materials[ThisIndex].maps[MATERIAL_MAP_DIFFUSE].texture = ThisTexture;
    
}

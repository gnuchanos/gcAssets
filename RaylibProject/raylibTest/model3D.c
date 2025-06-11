#include "main.h"

// Normal Model
JustModel CreateJustModel_Object(char *ModelPath, Vector3 Position, Vector3 Scale) {
    JustModel ThisJustModel;
        ThisJustModel.ModelPath         = ModelPath;
        ThisJustModel.ThisModel         = LoadModel(ModelPath);
        ThisJustModel.ThisModelPosition = Position;
        ThisJustModel.ThisModelBody     = Scale;
    return ThisJustModel;
}

void AddTextureToIndex(JustModel *ThisModel, int ThisIndex, Texture ThisTexture) {
    if (ThisIndex < ThisModel->ThisModel.meshCount) {
        ThisModel->ThisModel.materials[ThisIndex].maps[MATERIAL_MAP_DIFFUSE].texture = ThisTexture;
    } else { printf("Index out of range! \n"); }
}

void DrawJustModel(JustModel *ThisModel) {
	DrawModelEx(
		ThisModel->ThisModel,
		ThisModel->ThisModelPosition,
		ThisModel->ThisModelRotation,
		0,
		ThisModel->ThisModelScale,
		WHITE		
	);
}

// Animation Model
ModelAndAnimation CreateAnimationModel(char *ModelPath, Vector3 Position, Vector3 Scale, Vector3 Rotation, int AnimationIndex) {
    ModelAndAnimation ThisAnimationModel;
    if (ModelPath != NULL) {
        ThisAnimationModel.ModelPath        = ModelPath;
        ThisAnimationModel.ThisModel         = LoadModel(ModelPath);
        ThisAnimationModel.ThisModelPosition = Position;
        ThisAnimationModel.ThisModelScale    = Scale;
		ThisAnimationModel.ThisModelRotation = Rotation;
    
        // Load Animations
        ThisAnimationModel.ThisModelAnimIndex         = AnimationIndex;
        ThisAnimationModel.ThisModelAnimsCurrentFrame = 0;
        ThisAnimationModel.ThisModelAnimsCount        = 0;
        ThisAnimationModel.ThisModelAnimations        = LoadModelAnimations(ThisAnimationModel.ModelPath, &ThisAnimationModel.ThisModelAnimsCount);
    } else { printf("Model Path NULL"); }
    return ThisAnimationModel; 
}

void AddTextureToAnimModel(ModelAndAnimation *ThisAnimationModel, int index, Texture texture) {
    if (index < ThisAnimationModel->ThisModel.materialCount) {
        ThisAnimationModel->ThisModel.materials[index].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    } else { printf("Index out of range! \n"); }
    
}

void PlayAnimation(ModelAndAnimation *ThisAnimationModel){
    if (ThisAnimationModel->ThisModelAnimations != NULL) {
        ThisAnimationModel->ThisModelAnimsCurrentFrame++;
        UpdateModelAnimation(ThisAnimationModel->ThisModel, ThisAnimationModel->ThisModelAnimations[ThisAnimationModel->ThisModelAnimIndex], ThisAnimationModel->ThisModelAnimsCurrentFrame);
    } else { printf("Animation Array is NULL"); }
}

void DrawModelAndAnimation(ModelAndAnimation *ThisAnimationModel) {
    DrawModelEx(
        ThisAnimationModel->ThisModel,
        ThisAnimationModel->ThisModelPosition,
        ThisAnimationModel->ThisModelRotation,
        0,
        ThisAnimationModel->ThisModelScale,
        WHITE
    );
}

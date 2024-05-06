#include "Include/main.h"

Object3D BetaNewVegas() {
    Object3D BetaVegas;
    strcpy(BetaVegas.FilePath, "./Assets/3D/new_vegas_securitron.m3d");
    BetaVegas.Obj = LoadModel(BetaVegas.FilePath);
    BetaVegas.Position = (Vector3){0.0f, 0.0f, -3.0f};
    BetaVegas.Scale = (Vector3){3.5f, 3.5f, 3.5f};
    BetaVegas.Rotation = (Vector3){0.0f, 0.0f, 0.0f};
    BetaVegas.Texture[0] = LoadTexture("./Assets/Texture/color_atlas.png");
    BetaVegas.Texture[1] = LoadTexture("./Assets/Texture/face.png");
    BetaVegas.Obj.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture = BetaVegas.Texture[0];
    BetaVegas.Obj.materials[2].maps[MATERIAL_MAP_DIFFUSE].texture = BetaVegas.Texture[1]; // Face
    BetaVegas.Obj.materials[3].maps[MATERIAL_MAP_EMISSION].color = Purple8;
    BetaVegas.Obj.materials[4].maps[MATERIAL_MAP_DIFFUSE].color = PURPLE;
    BetaVegas.Obj.materials[5].maps[MATERIAL_MAP_DIFFUSE].color = PurpleTrans;
    return BetaVegas; }

Object3D TardisBody() {
    Object3D tBody;
    strcpy(tBody.FilePath, "./Assets/3D/tardis_v1.m3d");
    tBody.Obj = LoadModel(tBody.FilePath);
    tBody.Position = (Vector3){0.0f, 0.0f, -10.0f};
    tBody.Scale = (Vector3){6.5f, 6.5f, 6.5f};
    tBody.Rotation = (Vector3){0.0f, 90.0f, 0.0f};
    tBody.Texture[0] = LoadTexture("./Assets/Texture/color_atlas.png");
    tBody.Texture[1] = LoadTexture("./Assets/Texture/tardisInside.png");
    tBody.Obj.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture = tBody.Texture[0];
    tBody.Obj.materials[2].maps[MATERIAL_MAP_DIFFUSE].texture = tBody.Texture[1];
    tBody.Obj.materials[4].maps[MATERIAL_MAP_DIFFUSE].texture = tBody.Texture[1];
    tBody.Obj.transform = MatrixRotateY(tBody.Rotation.y * DEG2RAD);
    return tBody; }


// level design no animation
Object3D TardisInside() {
    Object3D tardis;
    strcpy(tardis.FilePath, "./Assets/3D/studio.m3d");
    tardis.Obj = LoadModel(tardis.FilePath);
    tardis.Position = (Vector3){0.0f, 0.0f, 0.0f};
    tardis.Rotation = (Vector3){0.0f, 0.0f, 0.0f};
    tardis.Scale = (Vector3){20.0f, 20.0f, 20.0f};
    tardis.Texture[0] = BetaNewVegas().Texture[0];
    tardis.Obj.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture = tardis.Texture[0];
    tardis.Obj.materials[2].maps[MATERIAL_MAP_ALBEDO].color = Purple2;
    tardis.Obj.materials[3].maps[MATERIAL_MAP_ALBEDO].color = Purple2;
    tardis.Obj.materials[4].maps[MATERIAL_MAP_DIFFUSE].texture = tardis.Texture[0];
    return tardis;
}

Object3D RedRoom() {
    Object3D rRoom;
    strcpy(rRoom.FilePath, "./Assets/3D/redRoom.gltf");
    rRoom.Obj = LoadModel(rRoom.FilePath);
    rRoom.Position = (Vector3){0.0f, 0.0f, 0.0f};
    rRoom.Rotation = (Vector3){0.0f, 0.0f, 0.0f};
    rRoom.Scale = (Vector3){20.0f, 20.0f, 20.0f};
    rRoom.Texture[0] = BetaNewVegas().Texture[0];
    rRoom.Obj.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture = rRoom.Texture[0];
    return rRoom;
}
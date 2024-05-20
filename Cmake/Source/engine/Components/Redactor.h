#pragma once
#include "Engine.h"

inline glm::vec2 AqueredCameraScale = glm::vec2(1.0f);

inline glm::vec2 PrevMousePosition = { 0.0f,0.0f };
inline Scene Map;

inline int SceneWindowID;
inline Scene* GameScene;

inline std::vector<std::string> AssetNames;
inline std::vector<std::string> NodeNames;

inline std::string MapFileName =  "./Scenes/Map.sav";

void PreReady();
void Ready();
void Process(float dt);
void Rescale(int NewWidth,int NewHeight);
void Destroy();



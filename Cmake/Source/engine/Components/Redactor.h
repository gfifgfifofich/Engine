#pragma once
#include "Engine.h"

inline glm::vec2 AqueredCameraScale = glm::vec2(1.0f);
inline int SceneWindowID;
inline int InspectorWindowID;
inline int ProjectWindowID;
inline int ConsoleWindowID;

inline glm::vec2 PrevMousePosition = { 0.0f,0.0f };
inline Scene Map;

inline Scene* GameScene;

inline std::vector<std::string> AssetNames;
inline std::vector<std::string> NodeNames;

inline std::string MapFileName =  "./Scenes/Map.sav";

void Ready();
void PreReady();
void Process(float dt);
void Destroy();



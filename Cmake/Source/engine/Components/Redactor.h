#pragma once
#include "Engine.h"

inline glm::vec2 AqueredCameraScale = glm::vec2(1.0f);

inline glm::vec2 PrevMousePosition = { 0.0f,0.0f };
inline Scene Map;

inline int SceneWindowID;
inline Scene* GameScene;

inline std::vector<std::string> AssetNames;
inline std::vector<std::string> NodeNames;

inline glm::vec2 s_Resolution = { 1920,1080 };
inline bool s_Fullscreen = true;

inline int substeps = 10;

inline std::string MapFileName =  "./Scenes/Sun.sav";

void PreReady();
void Ready();
void SubSteppedProcess(float dt, int SubStep);
void Process(float dt);
void SceneEnd();
void Rescale(int NewWidth,int NewHeight);
void Destroy();



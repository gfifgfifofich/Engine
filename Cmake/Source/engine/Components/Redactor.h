#pragma once
#include "Engine.h"

inline Scene* GameScene;

inline std::vector<std::string> AssetNames;
inline std::vector<std::string> NodeNames;


void Ready();
void PreReady();
void Process(float dt);
void Destroy();



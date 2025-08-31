#pragma once
#include "pch-il2cpp.h"


namespace PlayTAB {
    void Render();
    
    // Play相关功能开关
    extern bool speed_hack_enabled;
    extern bool no_clip_enabled;
    extern bool infinite_stamina_enabled;
    extern bool auto_play_enabled;
    
    // Play相关参数
    extern float speed_multiplier;
    extern float jump_height_multiplier;
    
    // Hook管理
    // void InitializePlayHooks();
    // void CleanupPlayHooks();
    
    // // Hook函数声明
    // app::Vector3 hPlayerManager_GetMainPlayerPosition_Speed(app::MethodInfo* method);
    // app::Vector3 hBaseData_GetPosition_NoClip(app::BaseData* __this, app::MethodInfo* method);
    
    // // 功能函数
    // void UpdateSpeedHack();
    // void UpdateNoClip();
    // void UpdateInfiniteStamina();
}
// Generated C++ file by Il2CppInspectorPro - http://www.djkaty.com - https://github.com/djkaty
// Modified by Jadis0x - https://github.com/jadis0x
// Target Unity version: 2021.3.0 - 2023.1.99

// ******************************************************************************
// * IL2CPP application-specific method definition addresses and signatures
// ******************************************************************************

using namespace app;
DO_APP_FUNC(0x020F4C50, AzurWorld*, AzurWorld_get_Instance, (MethodInfo* method));
DO_APP_FUNC_METHODINFO(0x08302EB8, AzurWorld_get_Instance__MethodInfo);

DO_APP_FUNC(0x020F58F0, bool, AzurWorld_get_inGame, (AzurWorld* __this, MethodInfo* method));
DO_APP_FUNC_METHODINFO(0x08307AA8, AzurWorld_get_inGame__MethodInfo);

DO_APP_FUNC(0x0153E320, void, AzurPlay_WorldUpdate, (AzurPlay* __this, float deltaTime, MethodInfo* method));
DO_APP_FUNC_METHODINFO(0x082E22C8, AzurPlay_WorldUpdate__MethodInfo);

DO_APP_FUNC(0x020F3830, void, AzurWorld_OnUpdate, (AzurWorld* __this, MethodInfo* method));
DO_APP_FUNC_METHODINFO(0x082FEA60, AzurWorld_OnUpdate__MethodInfo);


DO_APP_FUNC(0x02500D20, List_1_Lens_Gameplay_Modules_BigWorld_Entity_*, EntityManager_GetAllEntities, (MethodInfo* method));
DO_APP_FUNC_METHODINFO(0x082CED50, EntityManager_GetAllEntities__MethodInfo);


DO_APP_FUNC(0x021B8830, int32_t, BaseData_get_configId, (BaseData * __this, MethodInfo * method));//
DO_APP_FUNC_METHODINFO(0x08373D68, BaseData_get_configId__MethodInfo);//
DO_APP_FUNC(0x021BA430, void, BaseData_set_configId, (BaseData * __this, int32_t value, MethodInfo * method));
DO_APP_FUNC_METHODINFO(0x0837D4F0, BaseData_set_configId__MethodInfo);
DO_APP_FUNC(0x021B88D0, String *, BaseData_get_configName, (BaseData * __this, MethodInfo * method));
DO_APP_FUNC_METHODINFO(0x08374260, BaseData_get_configName__MethodInfo); 
DO_APP_FUNC(0x021B8F40, EEntityType__Enum, BaseData_get_entityType, (BaseData* __this, MethodInfo* method));
DO_APP_FUNC_METHODINFO(0x083762A8, BaseData_get_entityType__MethodInfo);
DO_APP_FUNC(0x021B8EF0, int32_t, BaseData_get_entityId, (BaseData* __this, MethodInfo* method));
DO_APP_FUNC_METHODINFO(0x08376030, BaseData_get_entityId__MethodInfo);

DO_APP_FUNC(0x021B3F40, Vector3, BaseData_GetPosition, (BaseData* __this, MethodInfo* method));
DO_APP_FUNC_METHODINFO(0x08368A88, BaseData_GetPosition__MethodInfo);
DO_APP_FUNC(0x021B4710, Quaternion, BaseData_GetRotation, (BaseData* __this, MethodInfo* method));
DO_APP_FUNC_METHODINFO(0x08369478, BaseData_GetRotation__MethodInfo);
DO_APP_FUNC(0x021B9A30, float, BaseData_get_selfTimeScale, (BaseData* __this, MethodInfo* method));
DO_APP_FUNC_METHODINFO(0x0837A5C0, BaseData_get_selfTimeScale__MethodInfo);

DO_APP_FUNC(0x02517820, PlayerEntity*, EntityManager_get_MainPlayer, (MethodInfo* method));
DO_APP_FUNC_METHODINFO(0x082EA820, EntityManager_get_MainPlayer__MethodInfo);

DO_APP_FUNC(0x013ABD50, Vector3, PlayerManager_GetMainPlayerPosition, (PlayerManager* __this, MethodInfo* method));
DO_APP_FUNC_METHODINFO(0x08289AF0, PlayerManager_GetMainPlayerPosition__MethodInfo);
DO_APP_FUNC(0x020F5A60, PlayerManager*, AzurWorld_get_playerMgr, (MethodInfo* method));
DO_APP_FUNC_METHODINFO(0x083084C8, AzurWorld_get_playerMgr__MethodInfo);



//musthave
DO_APP_FUNC(0x062A4EF0, bool, Screen_get_fullScreen, (MethodInfo* method));
DO_APP_FUNC(0x062A50C0, int32_t, Screen_get_width, (MethodInfo* method));
DO_APP_FUNC(0x062A4F20, int32_t, Screen_get_height, (MethodInfo* method));

DO_APP_FUNC(0x0625FF70, Camera*, Camera_get_main, (MethodInfo* method));
DO_APP_FUNC(0x0625F230, Vector3, Camera_WorldToScreenPoint_1, (Camera* __this, Vector3 position, MethodInfo* method));
DO_APP_FUNC(0x062C34D0, float, Vector3_Distance, (Vector3 a, Vector3 b, MethodInfo* method));
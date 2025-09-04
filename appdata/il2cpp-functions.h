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


DO_APP_FUNC(0x01EB0230, void, AntiCheatManager_Initialize, (MethodInfo * method));
DO_APP_FUNC_METHODINFO(0x0822EAB8, AntiCheatManager_Initialize__MethodInfo);
DO_APP_FUNC(0x01C76510, void *, AceSdkClient_LoadLibrary, (String * lpLibFileName, MethodInfo * method));
DO_APP_FUNC_METHODINFO(0x083C7840, AceSdkClient_LoadLibrary__MethodInfo);
DO_APP_FUNC(0x01C76AA0, AceSdkResult__Enum, AceSdkClient_ace_sdk_client_init, (AceSdkClient * * ace_client, MethodInfo * method));
DO_APP_FUNC_METHODINFO(0x083C8230, AceSdkClient_ace_sdk_client_init__MethodInfo);


DO_APP_FUNC(0x02500D20, List_1_Lens_Gameplay_Modules_BigWorld_Entity_*, EntityManager_GetAllEntities, (MethodInfo* method));
DO_APP_FUNC_METHODINFO(0x082CED50, EntityManager_GetAllEntities__MethodInfo);
DO_APP_FUNC(0x02500E70, List_1_Lens_Gameplay_Modules_BigWorld_MonsterEntity_ *, EntityManager_GetAllMonsters, (MethodInfo * method));
DO_APP_FUNC_METHODINFO(0x082CF770, EntityManager_GetAllMonsters__MethodInfo);

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
DO_APP_FUNC(0x0625FD10, float, Camera_get_fieldOfView, (Camera* __this, MethodInfo* method));
DO_APP_FUNC(0x062612D0, void, Camera_set_fieldOfView, (Camera* __this, float value, MethodInfo* method));
DO_APP_FUNC(0x0625D0B0, void, Camera_CopyFrom, (Camera* __this, Camera* other, MethodInfo* method));


DO_APP_FUNC(0x062F32F0, float, Time_1_get_timeScale, (MethodInfo* method));
DO_APP_FUNC(0x062F35A0, void, Time_1_set_timeScale, (float value, MethodInfo* method));





//unity object
DO_APP_FUNC(0x062D0A80, Object_1*, Object_1_Instantiate, (Object_1* original, Vector3 position, Quaternion rotation, MethodInfo* method));
DO_APP_FUNC_METHODINFO(0x0833FA18, Object_1_Instantiate__MethodInfo);
DO_APP_FUNC(0x062CF6F0, void, Object_1_DestroyImmediate_1, (Object_1* obj, MethodInfo* method));
DO_APP_FUNC(0x062D0520, String*, Object_1_GetName, (Object_1* obj, MethodInfo* method));
DO_APP_FUNC(0x062CB8C0, Transform*, GameObject_get_transform, (GameObject* __this, MethodInfo* method));

//game object
DO_APP_FUNC(0x062CB010, void, GameObject_SetActive, (GameObject* __this, bool value, MethodInfo* method));
DO_APP_FUNC(0x062CB6A0, bool, GameObject_get_active, (GameObject* __this, MethodInfo* method));
DO_APP_FUNC(0x062CA280, Component*, GameObject_GetComponentByName, (GameObject* __this, String* type, MethodInfo* method));

DO_APP_FUNC(0x062CA110, GameObject*, GameObject_Find, (String* name, MethodInfo* method));
DO_APP_FUNC(0x062CA800, Component__Array *, GameObject_GetComponents, (GameObject * __this, Type * type, MethodInfo * method));
DO_APP_FUNC(0x051F6A70, Type*, Type_GetType_3, (String* typeName, MethodInfo* method));


DO_APP_FUNC(0x062C7A20, GameObject*, Component_get_gameObject, (Component* __this, MethodInfo* method));

//transform
DO_APP_FUNC(0x062F97C0, Vector3, Transform_get_right, (Transform* __this, MethodInfo* method));
DO_APP_FUNC(0x062FA010, void, Transform_set_right, (Transform* __this, Vector3 value, MethodInfo* method));
DO_APP_FUNC(0x062F9930, Vector3, Transform_get_up, (Transform* __this, MethodInfo* method));
DO_APP_FUNC(0x062FA160, void, Transform_set_up, (Transform* __this, Vector3 value, MethodInfo* method));
DO_APP_FUNC(0x062F9190, Vector3, Transform_get_forward, (Transform* __this, MethodInfo* method));
DO_APP_FUNC(0x062F9B80, void, Transform_set_forward, (Transform* __this, Vector3 value, MethodInfo* method));
DO_APP_FUNC(0x062F98E0, Quaternion, Transform_get_rotation, (Transform* __this, MethodInfo* method));
DO_APP_FUNC(0x062FA110, void, Transform_set_rotation, (Transform* __this, Quaternion value, MethodInfo* method));
DO_APP_FUNC(0x062F9770, Vector3, Transform_get_position, (Transform* __this, MethodInfo* method));
DO_APP_FUNC(0x062F9FC0, void, Transform_set_position, (Transform* __this, Vector3 value, MethodInfo* method));
DO_APP_FUNC(0x062F90C0, Vector3, Transform_get_eulerAngles, (Transform* __this, MethodInfo* method));
DO_APP_FUNC(0x062F9AF0, void, Transform_set_eulerAngles, (Transform* __this, Vector3 value, MethodInfo* method));
DO_APP_FUNC(0x062F9080, int32_t, Transform_get_childCount, (Transform* __this, MethodInfo* method));
DO_APP_FUNC(0x062F5640, Transform*, Transform_GetChild, (Transform* __this, int32_t index, MethodInfo* method));
DO_APP_FUNC(0x062F9440, Vector3, Transform_get_localPosition, (Transform* __this, MethodInfo* method));
DO_APP_FUNC(0x062F9D20, void, Transform_set_localPosition, (Transform* __this, Vector3 value, MethodInfo* method));
DO_APP_FUNC(0x062F9580, Vector3, Transform_get_localScale, (Transform* __this, MethodInfo* method));
DO_APP_FUNC(0x062F9E60, void, Transform_set_localScale, (Transform* __this, Vector3 value, MethodInfo* method));



DO_APP_FUNC(0x063757F0, float, Input_GetAxis, (String* axisName, MethodInfo* method));
DO_APP_FUNC_METHODINFO(0x08399E28, Input_GetAxis__MethodInfo);

DO_APP_FUNC(0x062CCCC0, float, Mathf_Lerp, (float a, float b, float t, MethodInfo* method));
DO_APP_FUNC(0x062C3870, Vector3, Vector3_Lerp, (Vector3 a, Vector3 b, float t, MethodInfo* method));
DO_APP_FUNC(0x062C34D0, float, Vector3_Distance, (Vector3 a, Vector3 b, MethodInfo* method));

//unity explorer
DO_APP_FUNC(0x062ED7F0, GameObject__Array*, Scene_GetRootGameObjects, (Scene* __this, MethodInfo* method));
DO_APP_FUNC(0x062EB180, Scene__Array*, SceneManager_GetAllScenes, (MethodInfo* method));
DO_APP_FUNC(0x062EDC60, String*, Scene_get_name, (Scene* __this, MethodInfo* method));

DO_APP_FUNC(0x06259AF0, int32_t, Application_get_targetFrameRate, (MethodInfo* method));
DO_APP_FUNC(0x0625A670, void, Application_set_targetFrameRate, (int32_t value, MethodInfo* method));
DO_APP_FUNC(0x06259650, bool, Application_get_isFocused, (MethodInfo* method));




DO_APP_FUNC(0x062B05C0, bool, Cursor_1_get_visible, (MethodInfo* method));
DO_APP_FUNC(0x062B0630, void, Cursor_1_set_visible, (bool value, MethodInfo* method));
DO_APP_FUNC(0x062B0590, CursorLockMode__Enum, Cursor_1_get_lockState, (MethodInfo* method));
DO_APP_FUNC(0x062B05F0, void, Cursor_1_set_lockState, (CursorLockMode__Enum value, MethodInfo* method));


DO_APP_FUNC(0x062A19A0, bool, RenderSettings_get_fog, (MethodInfo* method));
DO_APP_FUNC(0x062A2100, void, RenderSettings_set_fog, (bool value, MethodInfo* method));


DO_APP_FUNC(0x00FECEC0, String*, LTextMeshProUGUI_get_text, (LTextMeshProUGUI* __this, MethodInfo* method));
DO_APP_FUNC_METHODINFO(0x08324BA0, LTextMeshProUGUI_get_text__MethodInfo);
DO_APP_FUNC(0x00FED110, void, LTextMeshProUGUI_set_text, (LTextMeshProUGUI* __this, String* value, MethodInfo* method));
DO_APP_FUNC_METHODINFO(0x083255C0, LTextMeshProUGUI_set_text__MethodInfo);




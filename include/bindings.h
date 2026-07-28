#ifndef _RAYLIB_PULSAR_BINDINGS_H
#define _RAYLIB_PULSAR_BINDINGS_H

#include <cpulsar/runtime.h>

typedef struct {
    uint64_t SoundTypeId;
} Raylib_Binding_Args;

CPulsar_RuntimeState Raylib_InitWindow(CPulsar_ExecutionContext* eContext, void* args);
CPulsar_RuntimeState Raylib_SetTargetFPS(CPulsar_ExecutionContext* eContext, void* args);
CPulsar_RuntimeState Raylib_GetFrameTime(CPulsar_ExecutionContext* eContext, void* args);
CPulsar_RuntimeState Raylib_WindowShouldClose(CPulsar_ExecutionContext* eContext, void* args);
CPulsar_RuntimeState Raylib_CloseWindow(CPulsar_ExecutionContext* eContext, void* args);

CPulsar_RuntimeState Raylib_BeginDrawing(CPulsar_ExecutionContext* eContext, void* args);
CPulsar_RuntimeState Raylib_GetScreenWidth(CPulsar_ExecutionContext* eContext, void* args);
CPulsar_RuntimeState Raylib_GetScreenHeight(CPulsar_ExecutionContext* eContext, void* args);
CPulsar_RuntimeState Raylib_ClearBackground(CPulsar_ExecutionContext* eContext, void* args);
CPulsar_RuntimeState Raylib_DrawRectangle(CPulsar_ExecutionContext* eContext, void* args);
CPulsar_RuntimeState Raylib_DrawText(CPulsar_ExecutionContext* eContext, void* args);
CPulsar_RuntimeState Raylib_MeasureText(CPulsar_ExecutionContext* eContext, void* args);
CPulsar_RuntimeState Raylib_EndDrawing(CPulsar_ExecutionContext* eContext, void* args);

CPulsar_RuntimeState Raylib_IsKeyPressed(CPulsar_ExecutionContext* eContext, void* args);

CPulsar_RuntimeState Raylib_GetDirectoryPath(CPulsar_ExecutionContext* eContext, void* args);
CPulsar_RuntimeState Raylib_ChangeDirectory(CPulsar_ExecutionContext* eContext, void* args);

CPulsar_RuntimeState Raylib_InitAudioDevice(CPulsar_ExecutionContext* eContext, void* args);
CPulsar_RuntimeState Raylib_CloseAudioDevice(CPulsar_ExecutionContext* eContext, void* args);

typedef struct Raylib_Sound Raylib_Sound;
CPulsar_RuntimeState Raylib_LoadSound(CPulsar_ExecutionContext* eContext, Raylib_Binding_Args* args);
CPulsar_RuntimeState Raylib_UnloadSound(CPulsar_ExecutionContext* eContext, Raylib_Binding_Args* args);
CPulsar_RuntimeState Raylib_SetSoundVolume(CPulsar_ExecutionContext* eContext, Raylib_Binding_Args* args);
CPulsar_RuntimeState Raylib_PlaySound(CPulsar_ExecutionContext* eContext, Raylib_Binding_Args* args);

typedef struct {
    const char* Name;
} Raylib_CustomType;

typedef struct {
    const Raylib_CustomType* Items;
    size_t Count;
} Raylib_CustomTypes;

typedef struct {
    CPulsar_FunctionSignature Signature;
    CPulsar_NativeFunction Function;
} Raylib_Binding;

typedef struct {
    const Raylib_Binding* Items;
    size_t Count;
} Raylib_Bindings;

Raylib_Binding_Args Raylib_GetBindingArgs(const CPulsar_Module* module);
CPulsar_CBuffer Raylib_BindingArgs_ToCBuffer(Raylib_Binding_Args args);

Raylib_CustomTypes Raylib_GetCustomTypes(void);
Raylib_Bindings Raylib_GetBindings(void);

#endif // _RAYLIB_PULSAR_BINDINGS_H

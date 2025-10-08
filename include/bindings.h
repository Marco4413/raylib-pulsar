#ifndef _RAYLIB_PULSAR_BINDINGS_H
#define _RAYLIB_PULSAR_BINDINGS_H

#include <cpulsar/runtime.h>

CPulsar_RuntimeState Raylib_InitWindow(CPulsar_ExecutionContext eContext, void* args);
CPulsar_RuntimeState Raylib_SetTargetFPS(CPulsar_ExecutionContext eContext, void* args);
CPulsar_RuntimeState Raylib_GetFrameTime(CPulsar_ExecutionContext eContext, void* args);
CPulsar_RuntimeState Raylib_WindowShouldClose(CPulsar_ExecutionContext eContext, void* args);
CPulsar_RuntimeState Raylib_CloseWindow(CPulsar_ExecutionContext eContext, void* args);

CPulsar_RuntimeState Raylib_BeginDrawing(CPulsar_ExecutionContext eContext, void* args);
CPulsar_RuntimeState Raylib_GetScreenWidth(CPulsar_ExecutionContext eContext, void* args);
CPulsar_RuntimeState Raylib_GetScreenHeight(CPulsar_ExecutionContext eContext, void* args);
CPulsar_RuntimeState Raylib_ClearBackground(CPulsar_ExecutionContext eContext, void* args);
CPulsar_RuntimeState Raylib_DrawRectangle(CPulsar_ExecutionContext eContext, void* args);
CPulsar_RuntimeState Raylib_DrawText(CPulsar_ExecutionContext eContext, void* args);
CPulsar_RuntimeState Raylib_MeasureText(CPulsar_ExecutionContext eContext, void* args);
CPulsar_RuntimeState Raylib_EndDrawing(CPulsar_ExecutionContext eContext, void* args);

CPulsar_RuntimeState Raylib_IsKeyPressed(CPulsar_ExecutionContext eContext, void* args);

typedef struct {
    CPulsar_FunctionSignature Signature;
    CPulsar_NativeFunction Function;
} Raylib_Binding;

typedef struct {
    const Raylib_Binding* Items;
    size_t Count;
} Raylib_Bindings;

Raylib_Bindings Raylib_GetBindings();

#endif // _RAYLIB_PULSAR_BINDINGS_H

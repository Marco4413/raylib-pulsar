#include "bindings.h"

#include <raylib.h>

#define GET_ARG(typeCheckMethod, unwrapMethod, outVar, argIdx)                \
    do {                                                                      \
        const CPulsar_Value* value = CPulsar_Locals_Get(locals, (argIdx));    \
        if (!(typeCheckMethod)(value)) return CPulsar_RuntimeState_TypeError; \
        (outVar) = (unwrapMethod)(value);                                     \
    } while (0)

#define GET_STRING_ARG(outVar, argIdx)  GET_ARG(CPulsar_Value_IsString, CPulsar_Value_AsString, (outVar), (argIdx))
#define GET_INTEGER_ARG(outVar, argIdx) GET_ARG(CPulsar_Value_IsInteger, CPulsar_Value_AsInteger, (outVar), (argIdx))
#define GET_INTEGER_NUMBER_ARG(outVar, argIdx) GET_ARG(CPulsar_Value_IsNumber, CPulsar_Value_AsIntegerNumber, (outVar), (argIdx))

int   _CPulsar_Value_IsColor(const CPulsar_Value* self);
Color _CPulsar_Value_AsColor(const CPulsar_Value* self);
#define GET_COLOR_ARG(outVar, argIdx) GET_ARG(_CPulsar_Value_IsColor, _CPulsar_Value_AsColor, (outVar), (argIdx))

Raylib_Bindings Raylib_GetBindings()
{
    static const Raylib_Binding BINDINGS[] = {
        { { .Name = "raylib/init-window!",         .Arity = 3, .Returns = 0 },
            Raylib_InitWindow },
        { { .Name = "raylib/set-target-fps!",      .Arity = 1, .Returns = 0 },
            Raylib_SetTargetFPS },
        { { .Name = "raylib/get-frame-time",       .Arity = 0, .Returns = 1 },
            Raylib_GetFrameTime },
        { { .Name = "raylib/window-should-close?", .Arity = 0, .Returns = 1 },
            Raylib_WindowShouldClose },
        { { .Name = "raylib/close-window!",        .Arity = 0, .Returns = 0 },
            Raylib_CloseWindow },
        { { .Name = "raylib/begin-drawing!",       .Arity = 0, .Returns = 0 },
            Raylib_BeginDrawing },
        { { .Name = "raylib/get-screen-width",     .Arity = 0, .Returns = 1 },
            Raylib_GetScreenWidth },
        { { .Name = "raylib/get-screen-height",    .Arity = 0, .Returns = 1 },
            Raylib_GetScreenHeight },
        { { .Name = "raylib/clear-background!",    .Arity = 1, .Returns = 0 },
            Raylib_ClearBackground },
        { { .Name = "raylib/draw-rectangle!",      .Arity = 5, .Returns = 0 },
            Raylib_DrawRectangle },
        { { .Name = "raylib/draw-text!",           .Arity = 5, .Returns = 0 },
            Raylib_DrawText },
        { { .Name = "raylib/measure-text",         .Arity = 2, .Returns = 1 },
            Raylib_MeasureText },
        { { .Name = "raylib/end-drawing!",         .Arity = 0, .Returns = 0 },
            Raylib_EndDrawing },
        { { .Name = "raylib/is-key-pressed?",      .Arity = 1, .Returns = 1 },
            Raylib_IsKeyPressed },
    };

    return (Raylib_Bindings){
        .Items = BINDINGS,
        .Count = sizeof(BINDINGS) / sizeof(*BINDINGS),
    };
}

CPulsar_RuntimeState Raylib_InitWindow(CPulsar_ExecutionContext* eContext, void* args)
{
    (void)args;
    CPulsar_Frame*  frame  = CPulsar_ExecutionContext_CurrentFrame(eContext);
    CPulsar_Locals* locals = CPulsar_Frame_GetLocals(frame);

    const char* title = NULL;
    int64_t width, height;

    size_t argIdx = 0;
    GET_INTEGER_ARG(width, argIdx++);
    GET_INTEGER_ARG(height, argIdx++);
    GET_STRING_ARG(title, argIdx++);

    InitWindow((int)width, (int)height, title);

    return CPulsar_RuntimeState_OK;
}

CPulsar_RuntimeState Raylib_SetTargetFPS(CPulsar_ExecutionContext* eContext, void* args)
{
    (void)args;
    CPulsar_Frame*  frame  = CPulsar_ExecutionContext_CurrentFrame(eContext);
    CPulsar_Locals* locals = CPulsar_Frame_GetLocals(frame);

    int64_t targetFPS;
    GET_INTEGER_ARG(targetFPS, 0);

    SetTargetFPS((int)targetFPS);

    return CPulsar_RuntimeState_OK;
}

CPulsar_RuntimeState Raylib_GetFrameTime(CPulsar_ExecutionContext* eContext, void* args)
{
    (void)args;
    CPulsar_Frame* frame = CPulsar_ExecutionContext_CurrentFrame(eContext);
    CPulsar_Stack* stack = CPulsar_Frame_GetStack(frame);

    CPulsar_Value_SetDouble(
            CPulsar_Stack_Emplace(stack),
            (double)GetFrameTime());

    return CPulsar_RuntimeState_OK;
}

CPulsar_RuntimeState Raylib_WindowShouldClose(CPulsar_ExecutionContext* eContext, void* args)
{
    (void)args;
    CPulsar_Frame* frame = CPulsar_ExecutionContext_CurrentFrame(eContext);
    CPulsar_Stack* stack = CPulsar_Frame_GetStack(frame);

    CPulsar_Value_SetInteger(
            CPulsar_Stack_Emplace(stack),
            WindowShouldClose() ? 1 : 0);

    return CPulsar_RuntimeState_OK;
}

CPulsar_RuntimeState Raylib_CloseWindow(CPulsar_ExecutionContext* eContext, void* args)
{
    (void)args, (void)eContext;
    CloseWindow();
    return CPulsar_RuntimeState_OK;
}

CPulsar_RuntimeState Raylib_BeginDrawing(CPulsar_ExecutionContext* eContext, void* args)
{
    (void)args, (void)eContext;
    BeginDrawing();
    return CPulsar_RuntimeState_OK;
}

CPulsar_RuntimeState Raylib_GetScreenWidth(CPulsar_ExecutionContext* eContext, void* args)
{
    (void)args;
    CPulsar_Frame* frame = CPulsar_ExecutionContext_CurrentFrame(eContext);
    CPulsar_Stack* stack = CPulsar_Frame_GetStack(frame);

    CPulsar_Value_SetInteger(
            CPulsar_Stack_Emplace(stack),
            (int64_t)GetScreenWidth());

    return CPulsar_RuntimeState_OK;
}

CPulsar_RuntimeState Raylib_GetScreenHeight(CPulsar_ExecutionContext* eContext, void* args)
{
    (void)args;
    CPulsar_Frame* frame = CPulsar_ExecutionContext_CurrentFrame(eContext);
    CPulsar_Stack* stack = CPulsar_Frame_GetStack(frame);

    CPulsar_Value_SetInteger(
            CPulsar_Stack_Emplace(stack),
            (int64_t)GetScreenHeight());

    return CPulsar_RuntimeState_OK;
}

CPulsar_RuntimeState Raylib_ClearBackground(CPulsar_ExecutionContext* eContext, void* args)
{
    (void)args;
    CPulsar_Frame*  frame  = CPulsar_ExecutionContext_CurrentFrame(eContext);
    CPulsar_Locals* locals = CPulsar_Frame_GetLocals(frame);

    Color color;
    GET_COLOR_ARG(color, 0);

    ClearBackground(color);

    return CPulsar_RuntimeState_OK;
}

CPulsar_RuntimeState Raylib_DrawRectangle(CPulsar_ExecutionContext* eContext, void* args)
{
    (void)args;
    CPulsar_Frame*  frame  = CPulsar_ExecutionContext_CurrentFrame(eContext);
    CPulsar_Locals* locals = CPulsar_Frame_GetLocals(frame);

    int64_t x, y, w, h;
    Color color;

    size_t argIdx = 0;
    GET_INTEGER_NUMBER_ARG(x, argIdx++);
    GET_INTEGER_NUMBER_ARG(y, argIdx++);
    GET_INTEGER_NUMBER_ARG(w, argIdx++);
    GET_INTEGER_NUMBER_ARG(h, argIdx++);
    GET_COLOR_ARG(color, argIdx++);

    DrawRectangle((int)x, (int)y, (int)w, (int)h, color);

    return CPulsar_RuntimeState_OK;
}

CPulsar_RuntimeState Raylib_DrawText(CPulsar_ExecutionContext* eContext, void* args)
{
    (void)args;
    CPulsar_Frame*  frame  = CPulsar_ExecutionContext_CurrentFrame(eContext);
    CPulsar_Locals* locals = CPulsar_Frame_GetLocals(frame);

    const char* text = NULL;
    int64_t x, y, fontSize;
    Color color;

    size_t argIdx = 0;
    GET_STRING_ARG(text, argIdx++);
    GET_INTEGER_NUMBER_ARG(x, argIdx++);
    GET_INTEGER_NUMBER_ARG(y, argIdx++);
    GET_INTEGER_NUMBER_ARG(fontSize, argIdx++);
    GET_COLOR_ARG(color, argIdx++);

    DrawText(text, (int)x, (int)y, (int)fontSize, color);

    return CPulsar_RuntimeState_OK;
}

CPulsar_RuntimeState Raylib_MeasureText(CPulsar_ExecutionContext* eContext, void* args)
{
    (void)args;
    CPulsar_Frame*  frame  = CPulsar_ExecutionContext_CurrentFrame(eContext);
    CPulsar_Locals* locals = CPulsar_Frame_GetLocals(frame);
    CPulsar_Stack*  stack  = CPulsar_Frame_GetStack(frame);

    const char* text = NULL;
    int64_t fontSize;

    size_t argIdx = 0;
    GET_STRING_ARG(text, argIdx++);
    GET_INTEGER_NUMBER_ARG(fontSize, argIdx++);

    CPulsar_Value_SetInteger(
            CPulsar_Stack_Emplace(stack),
            MeasureText(text, fontSize));

    return CPulsar_RuntimeState_OK;
}

CPulsar_RuntimeState Raylib_EndDrawing(CPulsar_ExecutionContext* eContext, void* args)
{
    (void)args, (void)eContext;
    EndDrawing();
    return CPulsar_RuntimeState_OK;
}

CPulsar_RuntimeState Raylib_IsKeyPressed(CPulsar_ExecutionContext* eContext, void* args)
{
    (void)args;
    CPulsar_Frame*  frame  = CPulsar_ExecutionContext_CurrentFrame(eContext);
    CPulsar_Locals* locals = CPulsar_Frame_GetLocals(frame);
    CPulsar_Stack*  stack  = CPulsar_Frame_GetStack(frame);

    int64_t key;
    GET_INTEGER_ARG(key, 0);

    CPulsar_Value_SetInteger(
            CPulsar_Stack_Emplace(stack),
            IsKeyPressed((int)key) ? 1 : 0);

    return CPulsar_RuntimeState_OK;
}

int   _CPulsar_Value_IsColor(const CPulsar_Value* self) { return CPulsar_Value_IsInteger(self); }
Color _CPulsar_Value_AsColor(const CPulsar_Value* self) { return GetColor((unsigned int)CPulsar_Value_AsInteger(self)); }

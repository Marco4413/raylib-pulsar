#include "bindings.h"

#include <raylib.h>

#define GET_ARG(typeCheckMethod, unwrapMethod, outVar, argIdx)                \
    do {                                                                      \
        CPulsar_Value* value = CPulsar_Locals_Get(locals, (argIdx));          \
        if (!(typeCheckMethod)(value)) return CPulsar_RuntimeState_TypeError; \
        (outVar) = (unwrapMethod)(value);                                     \
    } while (0)

#define GET_ARG_EX(typeCheckMethod, unwrapMethod, outVar, argIdx, ...)                     \
    do {                                                                                   \
        CPulsar_Value* value = CPulsar_Locals_Get(locals, (argIdx));                       \
        if (!(typeCheckMethod)(value, __VA_ARGS__)) return CPulsar_RuntimeState_TypeError; \
        (outVar) = (unwrapMethod)(value, __VA_ARGS__);                                     \
    } while (0)

#define GET_STRING_ARG(outVar, argIdx)  GET_ARG(CPulsar_Value_IsString, CPulsar_Value_AsString, (outVar), (argIdx))
#define GET_INTEGER_ARG(outVar, argIdx) GET_ARG(CPulsar_Value_IsInteger, CPulsar_Value_AsInteger, (outVar), (argIdx))
#define GET_INTEGER_NUMBER_ARG(outVar, argIdx) GET_ARG(CPulsar_Value_IsNumber, CPulsar_Value_AsIntegerNumber, (outVar), (argIdx))

#define GET_DOUBLE_NUMBER_ARG(outVar, argIdx) GET_ARG(CPulsar_Value_IsNumber, CPulsar_Value_AsDoubleNumber, (outVar), (argIdx))

static bool  _CPulsar_Value_IsColor(const CPulsar_Value* self);
static Color _CPulsar_Value_AsColor(const CPulsar_Value* self);
#define GET_COLOR_ARG(outVar, argIdx) GET_ARG(_CPulsar_Value_IsColor, _CPulsar_Value_AsColor, (outVar), (argIdx))

static bool          _CPulsar_Value_IsSound(CPulsar_Value* self, const Raylib_Binding_Args* args);
static Raylib_Sound* _CPulsar_Value_AsSound(CPulsar_Value* self, const Raylib_Binding_Args* args);
#define GET_SOUND_ARG(outVar, argIdx, args) GET_ARG_EX(_CPulsar_Value_IsSound, _CPulsar_Value_AsSound, (outVar), (argIdx), (args))

Raylib_Binding_Args Raylib_GetBindingArgs(const CPulsar_Module* module)
{
    Raylib_Binding_Args args = {0};
    args.SoundTypeId = CPulsar_Module_FindCustomType(module, "Raylib/Sound");
    return args;
}

CPulsar_CBuffer Raylib_BindingArgs_ToCBuffer(Raylib_Binding_Args args)
{
    // TODO: Add an option to pass Pulsar::Ref to CPulsar_Module_BindNativeFunction
    //       we don't need to copy this for each binding.

    CPulsar_CBuffer buffer = CPULSAR_CBUFFER_NULL;
    Raylib_Binding_Args* myArgs = CPulsar_Malloc(sizeof(Raylib_Binding_Args));
    *myArgs = args;

    buffer.Data = myArgs;
    buffer.Free = CPulsar_Free;

    return buffer;
}

Raylib_CustomTypes Raylib_GetCustomTypes()
{
    static Raylib_CustomType TYPES[] = {
        { "Raylib/Sound" },
    };

    return (Raylib_CustomTypes){
        .Items = TYPES,
        .Count = sizeof(TYPES) / sizeof(*TYPES),
    };
}

Raylib_Bindings Raylib_GetBindings()
{
    static const Raylib_Binding BINDINGS[] = {
        { .Signature = { .Name = "raylib/init-window!",         .Arity = 3, .Returns = 0 },
          .Function  = Raylib_InitWindow,
          },
        { .Signature = { .Name = "raylib/set-target-fps!",      .Arity = 1, .Returns = 0 },
          .Function  = Raylib_SetTargetFPS,
          },
        { .Signature = { .Name = "raylib/get-frame-time",       .Arity = 0, .Returns = 1 },
          .Function  = Raylib_GetFrameTime,
          },
        { .Signature = { .Name = "raylib/window-should-close?", .Arity = 0, .Returns = 1 },
          .Function  = Raylib_WindowShouldClose,
          },
        { .Signature = { .Name = "raylib/close-window!",        .Arity = 0, .Returns = 0 },
          .Function  = Raylib_CloseWindow,
          },
        { .Signature = { .Name = "raylib/begin-drawing!",       .Arity = 0, .Returns = 0 },
          .Function  = Raylib_BeginDrawing,
          },
        { .Signature = { .Name = "raylib/get-screen-width",     .Arity = 0, .Returns = 1 },
          .Function  = Raylib_GetScreenWidth,
          },
        { .Signature = { .Name = "raylib/get-screen-height",    .Arity = 0, .Returns = 1 },
          .Function  = Raylib_GetScreenHeight,
          },
        { .Signature = { .Name = "raylib/clear-background!",    .Arity = 1, .Returns = 0 },
          .Function  = Raylib_ClearBackground,
          },
        { .Signature = { .Name = "raylib/draw-rectangle!",      .Arity = 5, .Returns = 0 },
          .Function  = Raylib_DrawRectangle,
          },
        { .Signature = { .Name = "raylib/draw-text!",           .Arity = 5, .Returns = 0 },
          .Function  = Raylib_DrawText,
          },
        { .Signature = { .Name = "raylib/measure-text",         .Arity = 2, .Returns = 1 },
          .Function  = Raylib_MeasureText,
          },
        { .Signature = { .Name = "raylib/end-drawing!",         .Arity = 0, .Returns = 0 },
          .Function  = Raylib_EndDrawing,
          },
        { .Signature = { .Name = "raylib/is-key-pressed?",      .Arity = 1, .Returns = 1 },
          .Function  = Raylib_IsKeyPressed,
          },
        { .Signature = { .Name = "raylib/get-directory-path",   .Arity = 1, .Returns = 1 },
          .Function  = Raylib_GetDirectoryPath,
          },
        { .Signature = { .Name = "raylib/change-directory",     .Arity = 1, .Returns = 1 },
          .Function  = Raylib_ChangeDirectory,
          },
        { .Signature = { .Name = "raylib/init-audio-device!",   .Arity = 0, .Returns = 0 },
          .Function  = Raylib_InitAudioDevice,
          },
        { .Signature = { .Name = "raylib/close-audio-device!",  .Arity = 0, .Returns = 0 },
          .Function  = Raylib_CloseAudioDevice,
          },
        { .Signature = { .Name = "raylib/load-sound",           .Arity = 1, .Returns = 1 },
          .Function  = (CPulsar_NativeFunction)Raylib_LoadSound,
          },
        { .Signature = { .Name = "raylib/unload-sound!",        .Arity = 1, .Returns = 0 },
          .Function  = (CPulsar_NativeFunction)Raylib_UnloadSound,
          },
        { .Signature = { .Name = "raylib/set-sound-volume!",    .Arity = 2, .Returns = 0 },
          .Function  = (CPulsar_NativeFunction)Raylib_SetSoundVolume,
          },
        { .Signature = { .Name = "raylib/play-sound!",          .Arity = 1, .Returns = 0 },
          .Function  = (CPulsar_NativeFunction)Raylib_PlaySound,
          },
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

CPulsar_RuntimeState Raylib_GetDirectoryPath(CPulsar_ExecutionContext* eContext, void* args)
{
    (void)args;
    CPulsar_Frame*  frame  = CPulsar_ExecutionContext_CurrentFrame(eContext);
    CPulsar_Locals* locals = CPulsar_Frame_GetLocals(frame);
    CPulsar_Stack*  stack  = CPulsar_Frame_GetStack(frame);

    const char* filePath = NULL;
    GET_STRING_ARG(filePath, 0);

    CPulsar_Value_SetString(CPulsar_Stack_Emplace(stack), GetDirectoryPath(filePath));

    return CPulsar_RuntimeState_OK;
}

CPulsar_RuntimeState Raylib_ChangeDirectory(CPulsar_ExecutionContext* eContext, void* args)
{
    (void)args;
    CPulsar_Frame*  frame  = CPulsar_ExecutionContext_CurrentFrame(eContext);
    CPulsar_Locals* locals = CPulsar_Frame_GetLocals(frame);
    CPulsar_Stack*  stack  = CPulsar_Frame_GetStack(frame);

    const char* directory = NULL;
    GET_STRING_ARG(directory, 0);

    ChangeDirectory(directory);
    CPulsar_Value_SetInteger(CPulsar_Stack_Emplace(stack), 1);

    return CPulsar_RuntimeState_OK;
}

CPulsar_RuntimeState Raylib_InitAudioDevice(CPulsar_ExecutionContext* eContext, void* args)
{
    (void)args, (void)eContext;
    InitAudioDevice();
    return CPulsar_RuntimeState_OK;
}

CPulsar_RuntimeState Raylib_CloseAudioDevice(CPulsar_ExecutionContext* eContext, void* args)
{
    (void)args, (void)eContext;
    CloseAudioDevice();
    return CPulsar_RuntimeState_OK;
}

struct Raylib_Sound
{
    Sound S;
    bool Unloaded;
};

static Raylib_Sound* _AllocSound(Sound s)
{
    Raylib_Sound* sound = CPulsar_Malloc(sizeof(Raylib_Sound));
    sound->S = s;
    sound->Unloaded = false;
    return sound;
}

static void _UnloadSound(Raylib_Sound* sound)
{
    if (!sound->Unloaded) {
        UnloadSound(sound->S);
        sound->Unloaded = true;
    }
}

static void _FreeSound(void* sound)
{
    _UnloadSound((Raylib_Sound*)sound);
    CPulsar_Free(sound);
}

CPulsar_RuntimeState Raylib_LoadSound(CPulsar_ExecutionContext* eContext, Raylib_Binding_Args* args)
{
    CPulsar_Frame*  frame  = CPulsar_ExecutionContext_CurrentFrame(eContext);
    CPulsar_Locals* locals = CPulsar_Frame_GetLocals(frame);
    CPulsar_Stack*  stack  = CPulsar_Frame_GetStack(frame);

    const char* soundPath;
    GET_STRING_ARG(soundPath, 0);

    CPulsar_Value* soundVal = CPulsar_Stack_Emplace(stack);
    CPulsar_Value_SetCustomBuffer(soundVal, args->SoundTypeId, (CPulsar_CBuffer){
        .Data = _AllocSound(LoadSound(soundPath)),
        .Free = _FreeSound,
        .Copy = NULL,
    });

    return CPulsar_RuntimeState_OK;
}

CPulsar_RuntimeState Raylib_UnloadSound(CPulsar_ExecutionContext* eContext, Raylib_Binding_Args* args)
{
    CPulsar_Frame*  frame  = CPulsar_ExecutionContext_CurrentFrame(eContext);
    CPulsar_Locals* locals = CPulsar_Frame_GetLocals(frame);

    Raylib_Sound* sound = NULL;
    GET_SOUND_ARG(sound, 0, args);
    _UnloadSound(sound);

    return CPulsar_RuntimeState_OK;
}

CPulsar_RuntimeState Raylib_SetSoundVolume(CPulsar_ExecutionContext* eContext, Raylib_Binding_Args* args)
{
    CPulsar_Frame*  frame  = CPulsar_ExecutionContext_CurrentFrame(eContext);
    CPulsar_Locals* locals = CPulsar_Frame_GetLocals(frame);

    Raylib_Sound* sound = NULL;
    double volume = 1.0;
    GET_SOUND_ARG(sound, 0, args);
    GET_DOUBLE_NUMBER_ARG(volume, 1);
    SetSoundVolume(sound->S, (float)volume);

    return CPulsar_RuntimeState_OK;
}

CPulsar_RuntimeState Raylib_PlaySound(CPulsar_ExecutionContext* eContext, Raylib_Binding_Args* args)
{
    CPulsar_Frame*  frame  = CPulsar_ExecutionContext_CurrentFrame(eContext);
    CPulsar_Locals* locals = CPulsar_Frame_GetLocals(frame);

    Raylib_Sound* sound = NULL;
    GET_SOUND_ARG(sound, 0, args);
    PlaySound(sound->S);

    return CPulsar_RuntimeState_OK;
}

static bool  _CPulsar_Value_IsColor(const CPulsar_Value* self) { return CPulsar_Value_IsInteger(self); }
static Color _CPulsar_Value_AsColor(const CPulsar_Value* self) { return GetColor((unsigned int)CPulsar_Value_AsInteger(self)); }

static bool _CPulsar_Value_IsSound(CPulsar_Value* self, const Raylib_Binding_Args* args)
{
    if (!CPulsar_Value_IsCustom(self)) return false;
    CPulsar_CBuffer* soundData = CPulsar_Value_AsCustomBuffer(self, args->SoundTypeId);
    return soundData != NULL && soundData->Data != NULL;
}

static Raylib_Sound* _CPulsar_Value_AsSound(CPulsar_Value* self, const Raylib_Binding_Args* args)
{
    CPulsar_CBuffer* soundData = CPulsar_Value_AsCustomBuffer(self, args->SoundTypeId);
    return (Raylib_Sound*)soundData->Data;
}

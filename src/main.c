#include <cpulsar/runtime.h>
#include <cpulsar/version.h>

#include "bindings.h"

// Returns the version of CPulsar this binding was made for.
CPULSAR_EXPORT uint64_t CPULSAR_CALL PulsarExt_GetCPulsarVersion(void)
{
    // Return the version of the CPulsar header files used at compile-time.
    return CPULSAR_VERSION_NUMBER_CURRENT();
}

// Both PulsarExt_BindTypes and PulsarExt_BindFunctions are optional.

CPULSAR_EXPORT void CPULSAR_CALL PulsarExt_BindTypes(CPulsar_Module* module)
{
    Raylib_CustomTypes types = Raylib_GetCustomTypes();
    for (size_t i = 0; i < types.Count; ++i) {
        CPulsar_Module_BindCustomType(module, types.Items[i].Name, NULL);
    }
}

CPULSAR_EXPORT void CPULSAR_CALL PulsarExt_BindFunctions(CPulsar_Module* module)
{
    CPulsar_CBuffer_Ref* args = CPulsar_CBuffer_Ref_Create(
        Raylib_BindingArgs_ToCBuffer(Raylib_GetBindingArgs(module)));
    Raylib_Bindings bindings = Raylib_GetBindings();
    for (size_t i = 0; i < bindings.Count; ++i) {
        Raylib_Binding binding = bindings.Items[i];
        CPulsar_Module_BindNativeFunction(
            module,
            binding.Signature,
            binding.Function,
            args
        );
    }
    CPulsar_CBuffer_Ref_Delete(args);
}

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

CPULSAR_EXPORT void CPULSAR_CALL PulsarExt_BindFunctions(CPulsar_Module* module, bool declareAndBind)
{
    Raylib_Binding_Args args = Raylib_GetBindingArgs(module);
    Raylib_Bindings bindings = Raylib_GetBindings();
    for (size_t i = 0; i < bindings.Count; ++i) {
        Raylib_Binding binding = bindings.Items[i];
        CPulsar_Module_BindNativeFunctionEx(
            module,
            binding.Signature,
            binding.Function,
            binding.UsesArgs
                ? Raylib_BindingArgs_ToCBuffer(args)
                : CPULSAR_CBUFFER_NULL,
            declareAndBind
        );
    }
}

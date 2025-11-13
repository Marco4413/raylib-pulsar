#include <cpulsar/runtime.h>
#include <cpulsar/version.h>

#include "bindings.h"

// Returns the version of Pulsar this binding was made for
CPULSAR_EXPORT uint64_t CPULSAR_CALL GetPulsarVersion(void)
{
    // It is safe to return the CPulsar version we linked with since
    //  these bindings don't depend on anything advanced.
    return CPulsar_SemVer_ToNumber(CPulsar_GetLanguageVersion());
}

// No need to define this function if it's not used.
// CPULSAR_EXPORT void CPULSAR_CALL BindTypes(CPulsar_Module* module)
// {
//     (void)module;
// }

CPULSAR_EXPORT void CPULSAR_CALL BindFunctions(CPulsar_Module* module, int declareAndBind)
{
    Raylib_Bindings bindings = Raylib_GetBindings(); 
    for (size_t i = 0; i < bindings.Count; ++i) {
        CPulsar_Module_BindNativeFunctionEx(
            module,
            bindings.Items[i].Signature,
            bindings.Items[i].Function,
            CPULSAR_CBUFFER_NULL,
            declareAndBind
        );
    }
}

#include <cpulsar/runtime.h>
#include <cpulsar/version.h>

#include "bindings.h"

// Returns the version of CPulsar this binding was made for.
CPULSAR_EXPORT uint64_t CPULSAR_CALL PulsarExt_GetCPulsarVersion(void)
{
    // Return the version of the CPulsar header files used at compile-time.
    return CPULSAR_VERSION_NUMBER_CURRENT();
}

// No need to define this function if it's not used.
// CPULSAR_EXPORT void CPULSAR_CALL PulsarExt_BindTypes(CPulsar_Module* module)
// {
//     (void)module;
// }

CPULSAR_EXPORT void CPULSAR_CALL PulsarExt_BindFunctions(CPulsar_Module* module, int declareAndBind)
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

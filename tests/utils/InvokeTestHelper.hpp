#ifndef CUKEBINS_INVOKETESTHELPER_HPP_
#define CUKEBINS_INVOKETESTHELPER_HPP_

#include <cukebins/internal/CukeCommands.hpp>
#include <cukebins/internal/drivers/FakeDriver.hpp>

namespace cukebins {
namespace internal {

class InvokeTestHelper {
public:
    virtual command_args_type *buildInvokeArgs() = 0;
    virtual void testBeforeInvoke() = 0;
    virtual void testOnInvoke() = 0;
    virtual void testAfterInvoke() = 0;
};

template<class T>
class CukeCommandsTestInjector : public CukeCommands {
private:
    T testMethods;
    shared_ptr<command_args_type> args;
public:
    CukeCommandsTestInjector() :
        args(testMethods.buildInvokeArgs()) {
    }
    InvokeResult buildArgsAndInvoke() {
        testMethods.testBeforeInvoke();
        InvokeResult result = CukeCommands::invoke(0, args);
        testMethods.testAfterInvoke();
        return result;
    }
    const InvokeResult invokeNoArgs(step_id_type id) {
        testMethods.testOnInvoke();
        return CukeCommands::invokeNoArgs(id);
    }
};

}
}

#endif /* CUKEBINS_INVOKETESTHELPER_HPP_ */

#include <iostream>

#include "icemu/emu/types.h"
#include "icemu/hooks/HookCode.h"
#include "icemu/hooks/HookManager.h"
#include "icemu/hooks/RegisterHook.h"

using namespace std;

class MyHookCodePlugin : public HookCode {
 public:
  // Hook name, start address and end address
  MyHookCodePlugin() : HookCode("Hook Code Pluging Example", 50, 50) {
    cout << "Constructor my DLL code hook" << endl;
  }

  // One address specifies a single address of interest
  //MyHookCodePlugin() : HookCode("Hook Code Pluging Example", 50) {
  //  cout << "Constructor my DLL code hook" << endl;
  //}

  // No address range would always execute
  //MyHookCodePlugin() : HookCode("Hook Code Pluging Example") {
  //  cout << "Constructor my DLL code hook" << endl;
  //}

  // Hook run
  void run(hook_arg_t *arg) {
    cout << name << ": run() at address: " << arg->address << endl;
  }
};

// Function that registers the hook
static void registerMyCodeHook(HookManager &HM) {
  HM.add(new MyHookCodePlugin());
}

// Class that is used by ICEmu to finf the register function
// NB.  * MUST BE NAMED "RegisterMyHook"
//      * MUST BE global
RegisterHook RegisterMyHook(registerMyCodeHook);

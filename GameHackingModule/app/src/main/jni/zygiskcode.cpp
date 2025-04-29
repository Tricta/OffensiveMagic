#include <android/log.h>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dlfcn.h>
#include <thread>

#include "zygisk.hpp"
#include "dobby/dobby.h"

using zygisk::Api;
using zygisk::AppSpecializeArgs;

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "gameHacking", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_INFO, "gameHacking", __VA_ARGS__)

#define OFFSET_MONEY 0xD9FF40
#define GAME_NAME "ccom.yourpackage.example"

typedef uint32_t (*MoneyFunc)(void* arg1, int32_t arg2, void* arg3);
static MoneyFunc orig_MoneyFunc = nullptr;

static int (*orig_dladdr)(const void*, Dl_info*) = nullptr;
static void* sym_dladdr = nullptr;

class gameHacking : public zygisk::ModuleBase {
public:
    void onLoad(Api *api, JNIEnv *env) override {
        this->api = api;
        this->env = env;
    }

    void postAppSpecialize(const AppSpecializeArgs *args) override {
        const char *process = env->GetStringUTFChars(args->nice_name, nullptr);

        if (strcmp(process, GAME_NAME) == 0) {
            LOGI("find game process: %s", GAME_NAME);

            std::thread([] {
                void* sym = DobbySymbolResolver("linker", "__dl__Z9do_dladdrPKvP7Dl_info");
                if (sym) {
                    sym_dladdr = sym;
                    if (DobbyHook(sym, (void*)hooked_dladdr, (void**)&orig_dladdr) == 0) {
                        LOGI("Hooked dladdr");
                    } else {
                        LOGE("Failed hooking dladdr");
                    }
                } else {
                    LOGE("Failed to resolve dladdr symbol");
                }
            }).detach();
        }

        env->ReleaseStringUTFChars(args->nice_name, process);
    }

private:
    Api *api;
    JNIEnv *env;

    static uint32_t hooked_MoneyFunc(void* arg1, int32_t arg2, void* arg3) {
        LOGI("Hooked MoneyFunc called!");

        arg2 = 0x410000;
        uint32_t result = orig_MoneyFunc(arg1, arg2, arg3);

        LOGI("Money added!");
        return result;
    }

    static int hooked_dladdr(const void *addr, Dl_info *info) {
        int handle = orig_dladdr(addr, info);

        if (info->dli_fname && strstr(info->dli_fname, "libil2cpp.so")) {
            LOGI("Loaded: %s -> %p", info->dli_fname, info->dli_fbase);

            void* target = (void*)((uintptr_t)info->dli_fbase + OFFSET_MONEY);
            LOGI("Target address: %p", target);

            if (DobbyHook(target, (void*)hooked_MoneyFunc, (void**)&orig_MoneyFunc) == 0) {
                LOGI("MoneyFunc hook successful!");

                if (sym_dladdr) {
                    if (DobbyDestroy(sym_dladdr) == 0) {
                        LOGI("Unhooked dladdr");
                        sym_dladdr = nullptr;
                    } else {
                        LOGE("Failed to unhook dladdr.");
                    }
                }
            } else {
                LOGE("MoneyFunc hook failed.");
            }
        }

        return handle;
    }
};

REGISTER_ZYGISK_MODULE(gameHacking)
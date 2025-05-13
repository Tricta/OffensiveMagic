#include <android/log.h>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <android/dlext.h>
#include <dlfcn.h>
#include <thread>

#include "zygisk.hpp"
#include "dobby/dobby.h"

using zygisk::Api;
using zygisk::AppSpecializeArgs;

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "bypassProtections", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_INFO, "bypassProtections", __VA_ARGS__)

#define APK_NAME "com.example.demoprotections"

void *(*orig_android_dlopen_ext)(const char *_Nullable __filename, int __flags, const android_dlextinfo *_Nullable __info);

typedef int (*DebuggerFunc)(void);
static DebuggerFunc orig_debuggerFunc = nullptr;

typedef const char* (*CoolFunc)(const char* arg1);
static CoolFunc orig_coolFunc = nullptr;

class bypass : public zygisk::ModuleBase {
public:
    void onLoad(Api *api, JNIEnv *env) override {
        this->api = api;
        this->env = env;
    }

    void postAppSpecialize(const AppSpecializeArgs *args) override {
        const char *process = env->GetStringUTFChars(args->nice_name, nullptr);

        if (strcmp(process, APK_NAME) == 0) {
            LOGI("find process: %s", APK_NAME);

            void* sym = DobbySymbolResolver(nullptr, "android_dlopen_ext");
            if (sym) {
                if (DobbyHook(sym, (void*)android_dlopen_ext, (void**)&orig_android_dlopen_ext) == 0) {
                    LOGI("Hooked dlopen_ext");
                } else {
                    LOGE("Failed hooking dlopen_ext");
                }
            } else {
                LOGE("Failed to resolve dlopen_ext symbol");
            }
        }

        env->ReleaseStringUTFChars(args->nice_name, process);
    }

private:
    Api *api;
    JNIEnv *env;

    static bool hooked_debuggerFunc(void) {
        LOGI("Hooked debuggerFunc called!");
        return 0;
    }

    static const char* hooked_coolFunc(const char* arg1) {
        LOGI("Hooked coolFunc called!");
        return "Hacked";
    }

    static void *android_dlopen_ext(const char *_Nullable __filename, int __flags, const android_dlextinfo *_Nullable __info)
    {
        if (strstr(__filename, "libdemoprotections.so")) {
            LOGI("android_dlopen_ext: %s flags: %08x", __filename, __flags);

            void* res = orig_android_dlopen_ext(__filename, __flags, __info);

            void* sym = DobbySymbolResolver("libdemoprotections.so", "_Z14JDWPDetectionsv");
            if (sym) {
                if (DobbyHook(sym, (void*)hooked_debuggerFunc, (void**)&orig_debuggerFunc) == 0) {
                    LOGI("Hooked debuggerDetection");
                } else {
                    LOGE("Failed hooking debuggerDetection");
                }
            } else {
                LOGE("Failed to resolve debuggerDetection symbol");
            }

            void* sym2 = DobbySymbolResolver("libdemoprotections.so", "_Z13CoolParameterPKc");
            if (sym2) {
                if (DobbyHook(sym2, (void*)hooked_coolFunc, (void**)&orig_coolFunc) == 0) {
                    LOGI("Hooked coolFunc");
                } else {
                    LOGE("Failed hooking coolFunc");
                }
            } else {
                LOGE("Failed to resolve coolFunc symbol");
            }

            return res;
        }

        return orig_android_dlopen_ext(__filename, __flags, __info);
    }
};

REGISTER_ZYGISK_MODULE(bypass)
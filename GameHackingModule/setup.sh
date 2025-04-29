#!/bin/bash

cd ./app/src/main && ndk-build && cd ../../.. && rm -rf ./magiskModule/game.zip

rm -rf ./magiskModule/zygisk/armeabi-v7a.so
rm -rf ./magiskModule/zygisk/arm64-v8a.so

cp ./app/src/main/libs/armeabi-v7a/libgameLib.so ./magiskModule/zygisk/armeabi-v7a.so
cp ./app/src/main/libs/arm64-v8a/libgameLib.so ./magiskModule/zygisk/arm64-v8a.so

cd ./magiskModule && zip -r game.zip *
adb push game.zip /sdcard/Download
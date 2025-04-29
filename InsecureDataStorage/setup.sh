#!/bin/bash

rm -rf ./magiskModule/insecureStorage.zip

cd ./magiskModule && zip -r insecureStorage.zip *
adb push insecureStorage.zip /sdcard/Download
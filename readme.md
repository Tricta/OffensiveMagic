<h1 align="center">Offensive Magic</h1>
<img align="right" height="260" width="260" src="https://media.tenor.com/nkEfyODuk1oAAAAM/istorik-dancing-cat.gif"/>

This repo is a collection of PoCs to demonstrate how Magisk can be used by an attacker to perform malicious activity. Reconstructing the idea that mobile attacks typically happen locally...

There are 3 projects for you to check out:
- **Decoy** (Learn how mobile threats can grab your attention)
- **Insecure Data Local Storage** (See how an attacker can steal your credentials and sessions remotely)
- **Game Hacking** (Understand how an attacker can hook into your application code remotely or without a computer)

## Build

Clone the project:

~~~bash
  git clone https://github.com/Tricta/OffensiveMagic.git
~~~

Navigate to the PoC directory and edit it for your goals:

~~~bash
  cd OffensiveMagic/<choose your poc>
~~~

Give execute permissions to `setup.sh`:

~~~bash
  chmod +x ./setup.sh
~~~

Run `setup.sh` to generate the Magisk module `.zip` and push it to your device:

~~~bash
  ./setup.sh
~~~

Now install it via Magisk and have fun :)

## Warning

**Preferable to set up on Linux!** Zipping Magisk modules on Windows or macOS may result in incompatibility with Magisk's unzip format. If you create the module on one of these systems, you will need to install it via the command line.

Connect through ADB:
~~~bash
  adb shell
~~~

Give `su` privileges:
~~~bash
  su
~~~

Enter the modules folder, create a directory, and navigate into it:
~~~bash
  cd /data/adb/modules && mkdir moduleName && cd moduleName
~~~

Move the generated zip file and unzip it:
~~~bash
  mv /sdcard/Download/module.zip . && unzip module.zip && rm -rf module.zip
~~~

Reboot to apply the changes:
~~~bash
  reboot
~~~

Now you can really have fun ;)
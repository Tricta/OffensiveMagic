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

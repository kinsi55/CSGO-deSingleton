# CSGO-deSingleton

This Counter-Strike: Global Offensive plugin releases the Singleton Mutex created by all Source engine games to prevent it from being launched multiple times thus allowing you to run multiple instances at once. This is useful for testing things that require multiple players.

# ❗❗❗❗❗ WARNING ❗❗❗❗❗

Eventho addons can only loaded when you've explicitly disabled VAC by using the `-insecure` launch option, this addon will **NOT** prevent you from removing the flag and starting another instance alongside without it. I have no idea if you risk being banned by doing that, accidently or on purpose, no matter what: **I am not responsible if you somehow get banned by using this**

## Installation

1. Download the latest release of the plugin from GitHub (Or compile it yourself): https://github.com/kinsi55/CSGO-deSingleton/releases
2. Extract the contents of the ZIP to `$STEAM\steamapps\common\Counter-Strike Global Offensive\csgo` (Make sure both the files end up in an addons folder, so within `Counter-Strike Global Offensive\csgo\addons`).
3. Create a Shortcut to your csgo.exe located in `$STEAM\steamapps\common\Counter-Strike Global Offensive`
4. Add `-insecure` to the launch options of Counter-Strike: Global Offensive. If you do not know how to do this, take a look this [Steam Community guide](https://steamcommunity.com/sharedfiles/filedetails/?id=379782151).
5. Launch CS:GO as many times as you want, wait for it to launch so that the plugin is loaded and does its job

#### To then join a server:

1. Make sure `sv_lan` is set to 1 as otherwise you will encounter issues (Being unable to join multiple times with the same account
2. Launch a local game on a map / mode of your choice in one of the instances
3. Connect using *your local ip* (NOT 127.0.0.1 as that is not what the server binds to)

Thanks to the amazing [csgo-cvar-unhide](https://github.com/saul/csgo-cvar-unhide) addon which I've butchered up for creating this :P

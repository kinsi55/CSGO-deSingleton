# CSGO-deSingleton

This Counter-Strike: Global Offensive plugin will release the Singleton mutex that all Source engine games create to prevent multiple instances of running at the same time. I've found this an annoying limitation when developing server mods as I've always needed to use a second machine for debugging purposes whenever I needed to test something with multiple clients. This solves that.

# ❗ ❗ ❗ ❗ WARNING ❗ ❗ ❗ ❗

While addons can only be loaded when the game is launched with `-insecure` (And thus with disabled VAC) this addon will **NOT** prevent you from launching the game again with the insecure flag removed. I have no idea what was to happen if you play on a VAC secured server while having other instances running so always make sure to close all instances of the game before trying to remove the `-insecure` flag / playing on secured servers. **I AM NOT RESPONSIBLE IF YOU IN ANY WAY SOMEHOW END UP BANNED BY USING THIS**

## Installation

1. Download the latest release of the plugin or compile it yourself: https://github.com/kinsi55/CSGO-deSingleton/releases/latest
2. Extract the contents of the ZIP to `$STEAM\steamapps\common\Counter-Strike Global Offensive\csgo`
3. Add `-insecure` to the Counter-Strike: Global Offensive launch options. If you do not know how to do this, take a look this [Steam Community guide](https://steamcommunity.com/sharedfiles/filedetails/?id=379782151).
3. Create a Shortcut to your CS:GO executeable (`$STEAM\steamapps\common\Counter-Strike Global Offensive\csgo.exe`) and launch it as many times as you want (Waiting for it to launch so that the plugin is loaded)
4. Make sure the `sv_lan` ConVar is set to 1 as otherwise your locally launched server is not going to allow your account to join multiple times and start a local game with bots on a map / mode of your choice
5. In the other instances use the `connect` console command **with your local ip** (Not 127.0.0.1) to connect to the server ran in your first instance.

## Caveats

- Panorama UI changed the scoreboard in a way where players are grouped by their Steamid, this means you will only see one of your clients on the scoreboard (The host)

Thanks to the amazing [csgo-cvar-unhide](https://github.com/saul/csgo-cvar-unhide) addon which I've butchered up for creating this.
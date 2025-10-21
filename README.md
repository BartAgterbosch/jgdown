This is essentially my very first little program written in C, so, don't take this as an example of what to do.. And please don't run this in a production environment.
Yes I know this code is very repetitive for no reason, and I also know it is ripe for a buffer overflow, unfortunately I'm still just learning C so I don't know how to do it properly yet or use dynamic allocation sizes.
But, for now, it works.
This specific code also makes an effort to skip any NordVPN tunnels if present, since that uses a variation of Wireguard, other VPN providers might also do the same but since NordVPN is all I have to test it against right now, that's what it's limited to.

The point of this program is essentially to do what Jellyguard can't, which is disconnect the Wireguard tunnel used to connect to the Jellyfin Server, which, can result in no internet connectivity if that wg server doesn't allow access outwards.

---
title: UserGametypeStat
parent: Types
layout: default
nav_order: 21
permalink: "/Types/UserGametypeStat"
---

### Type: struct

### Definition:
```cpp
struct UserGametypeStat {
	struct baseCasual {
		int death;
		int kills;
		int matchlost;
		int matchplayed;
		int matchwon;
		long timeplayed;
	} Casual;
	struct baseRanked {
		int death;
		int kills;
		int matchlost;
		int matchplayed;
		int matchwon;
		long timeplayed;
	} Ranked;
};
```
### Note(s)
OUTDATED
{: .label .label-yellow } 
Changing individual gametype structs to share the same structure
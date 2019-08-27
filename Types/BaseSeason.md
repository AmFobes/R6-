---
title: BaseSeason
parent: Types
layout: default
nav_order: 18
permalink: "/Types/BaseSeason"
---

### Type: struct

### Definition:
```cpp
struct BaseSeason {
	int SeasonID;
	std::string SeasonName;
	inline BaseSeason(int seasonID, std::string seasonName) {
		this->SeasonID = SeasonID;
		this->SeasonName = SeasonName;
	}
	inline BaseSeason() {}
};
```

### Note(s)
Creating an instance of this struct should only be done by R6pp **UNLESS** R6pp is not updated and a new season comes out

Instances of BaseSeason is provided in the namespace [R6pp, here](https://github.com/AmFobes/R6pp/blob/master/R6pp/Types.h#L60)
```cpp
static BaseSeason
	Current(-1, ""), PhantomSight(14, "Phantom Sight"), BurntHorizon(13, "Burnt Horizon"),
	WindBastion(12, "Wind Bastion"), GrimSky(11, "Grim Sky"), ParaBellum(10, "Para Bellum"),
	Chimera(9, "Chimera"), WhiteNoise(8, "White Noise"), BloodOrchid(7, "Blood Orchid"),
	Health(6, "Health"), VelvetShell(5, "Velvet Shell"), RedCrow(4, "Red Crow"),
	SkullRain(3, "Skull Rain"), DustLine(2, "Dust Line"), BlackIce(1, "Black Ice");
```

A vector of all known seasons is provided aswell in the namespace [R6pp, here](https://github.com/AmFobes/R6pp/blob/master/R6pp/Types.h#L251)

```cpp
static std::vector<BaseSeason> Seasons{
	Current,PhantomSight,BurntHorizon,
	WindBastion,GrimSky,ParaBellum,
	Chimera,WhiteNoise,BloodOrchid,
	Health,VelvetShell,RedCrow,
	SkullRain,DustLine,BlackIce
};
```
	
OUTDATED
{: .label .label-yellow } 
BaseSeason "Current" is being removed from the Seasons array, it's redundant
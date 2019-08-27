---
title: BaseWeapon
parent: Types
layout: default
nav_order: 13
permalink: "/Types/BaseWeapon"
---

### Type: struct

### Definition:
```cpp
struct BaseWeapon {
	int number;
	std::string name;
	inline BaseWeapon(int number, std::string name) {
		this->number = number;
		this->name = name;
	}
	inline BaseWeapon() {};
};
```

### Note(s)
Creating an instance of this struct should only be done by R6pp **UNLESS** R6pp is not updated and a new weapon type gets released (I highly doubt it'll happen)

Instances of BaseWeapon is provided in the namespace [R6pp, here](https://github.com/AmFobes/R6pp/blob/master/R6pp/Types.h#L184)
```cpp
static BaseWeapon
	AR(1, "Assault Rifle"),
	MR(2, "Marksman Rifle"),
	SMG(3, "Submachine Gun"),
	Handgun(4, "Handgun"),
	Shotgun(5, "Shotgun"),
	LMG(6, "Light Machine Gun"),
	MachinePistol(7, "Machine Pistol");
```

A vector of all known weapon types is provided aswell in the namespace [R6pp, here](https://github.com/AmFobes/R6pp/blob/master/R6pp/Types.h#L193)

```cpp
static std::vector<BaseWeapon> Weapons{
	AR,MR,SMG,
	Handgun,Shotgun,
	LMG,MachinePistol,
};
```
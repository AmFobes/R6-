---
title: GetUserWeaponStat
parent: R6Connection
layout: default
nav_order: 9
permalink: "/R6Connection/GetUserWeaponStat"
---

### Return Type: [UserWeaponStat](/Types/UserWeaponStat)

### Arguments 
```cpp 
UserWeaponStat GetUserWeaponStat(SearchedUser user, BaseWeapon weapon);
```
* [SearchedUser](/Types/SearchedUser) user
 * Ubisoft user account to fetch UserSeasonStat from
* [BaseWeapon](Types/BaseWeapon) weapon
	*  The weapon to get stats for

```cpp
UserWeaponStat GetUserWeaponStat(std::string username, BaseWeapon weapon, PlatformType platform = PlatformType::Uplay);
```
* `std::string` username
	* Name of user account to fetch UserGametypeStat from
* [BaseWeapon](Types/BaseWeapon) weapon
	* The weapon to get stats for 
* [PlatformType](Types/PlatformType) platform
	* Rainbow six platform of user
		* Default: Uplay

```cpp
UserWeaponStat GetUserWeaponStatByID(std::string profileID, BaseWeapon weapon);
```
* `std::string` profileID
	* Ubisoft profile ID of user to fetch UserGametypeStat from
* [BaseWeapon](Types/BaseWeapon) weapon
	*  The weapon to get stats for
---
title: GetUserWeaponStats
parent: R6Connection
layout: default
nav_order: 8
permalink: "/R6Connection/GetUserWeaponStats"
---

### Return Type: [UserWeaponStats](/R6pp/Types/UserWeaponStats)

### Arguments 
```cpp 
UserWeaponStats GetUserWeaponStats(SearchedUser user);
```
* [SearchedUser](/Types/SearchedUser) user
 * Ubisoft user account to fetch UserSeasonStat from

```cpp
UserWeaponStats GetUserWeaponStats(std::string username, R6pp::PlatformType platform = PlatformType::Uplay);
```
* `std::string` username
	* Name of user account to fetch UserGametypeStats from
* [PlatformType](Types/PlatformType) platform
	* Rainbow six platform of user
		* Default: Uplay

```cpp
UserWeaponStats GetUserWeaponStatsByID(std::string profileID);
```
* `std::string` profileID
	* Ubisoft profile ID of user to fetch UserGametypeStats from
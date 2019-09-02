---
title: GetUserGametypeStat
parent: R6Connection
layout: default
nav_order: 11
permalink: "/R6Connection/GetUserGametypeStat"
---

### Return Type: [UserGametypeStat](/R6pp/Types/UserGametypeStat)

### Arguments 
```cpp 
UserGametypeStat GetUserGametypeStat(SearchedUser user);
```
* [SearchedUser](/Types/SearchedUser) user
 * Ubisoft user account to fetch UserGametypeStat from
* 
 
```cpp
UserGametypeStat GetUserGametypeStat(std::string username, PlatformType platform = PlatformType::Uplay);
```
* `std::string` username
	* Name of user account to fetch UserGametypeStat from
* [PlatformType](/Types/PlatformType) platform
	* Rainbow six platform of user
		* Default: Uplay

```cpp
UserGametypeStat GetUserGametypeStatByID(std::string profileID);
```
* `std::string` profileID
	* Ubisoft profile ID of user to fetch UserGametypeStat from
---
title: GetPlayerProfile
parent: R6Connection
layout: default
nav_order: 13
permalink: "/R6Connection/GetPlayerProfile"
---

### Return Type: [PlayerProfile](/Types/PlayerProfile)

### Arguments 
```cpp 
PlayerProfile GetPlayerProfile(SearchedUser user); 
```
* [SearchedUser](/Types/SearchedUser) user
 * Ubisoft user account to fetch PlayerProfile from
 
```cpp
PlayerProfile GetPlayerProfile(std::string username, PlatformType platform = PlatformType::Uplay);
```
* `std::string` username
	* Name of user account to fetch PlayerProfile from
* [PlatformType](/Types/PlatformType) platform
	* Rainbow six platform of user
		* Default: Uplay

```cpp
PlayerProfile GetPlayerProfileByID(std::string profileID);
```
* `std::string` profileID
	* Ubisoft profile ID of user to fetch PlayerProfile from
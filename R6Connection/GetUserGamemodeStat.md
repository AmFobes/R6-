---
title: GetUserGamemodeStat
parent: R6Connection
layout: default
nav_order: 12
permalink: "/R6Connection/GetUserGamemodeStat"
---

### Return Type: [UserGamemodeStat](/Types/UserGamemodeStat)

### Arguments 
```cpp 
UserGamemodeStat GetUserGamemodeStat(SearchedUser user);
```
* [SearchedUser](/Types/SearchedUser) user
 * Ubisoft user account to fetch UserGamemodeStat from
 
```cpp
UserGamemodeStat GetUserGamemodeStat(std::string username, PlatformType platform = PlatformType::Uplay);
```
* `std::string` username
	* Name of user account to fetch UserGamemodeStat from
* [PlatformType](/Types/PlatformType) platform
	* Rainbow six platform of user
		* Default: Uplay

```cpp
UserGamemodeStat GetUserGamemodeStatByID(std::string profileID);
```
* `std::string` profileID
	* Ubisoft profile ID of user to fetch UserApplications from
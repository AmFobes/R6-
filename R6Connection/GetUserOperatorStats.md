---
title: GetUserOperatorStats
parent: R6Connection
layout: default
nav_order: 6
permalink: "/R6Connection/GetUserOperatorStats"
---

### Return Type: [UserOperatorStats](/Types/UserOperatorStats)

### Arguments 
```cpp 
UserOperatorStats GetUserOperatorStats(SearchedUser user);
```
* [SearchedUser](/Types/SearchedUser) user
 * Ubisoft user account to fetch UserOperatorStats from

```cpp
UserOperatorStats GetUserOperatorStats(std::string username, PlatformType platform = PlatformType::Uplay);
```
* `std::string` username
	* Name of user account to fetch UserOperatorStats from
* [PlatformType](/Types/PlatformType) platform
	* Rainbow six platform of user
		* Default: Uplay

```cpp
UserOperatorStats GetUserOperatorStatsByID(std::string profileID);
```
* `std::string` profileID
	* Ubisoft profile ID of user to fetch UserOperatorStats from
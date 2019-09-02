---
title: GetUserSeasonStat
parent: R6Connection
layout: default
nav_order: 10
permalink: "/R6Connection/GetUserSeasonStat"
---

### Return Type: [UserSeasonStat](/R6pp/Types/UserSeasonStat)

### Arguments 
```cpp 
UserSeasonStat GetUserSeasonStat(SearchedUser user, BaseSeason season, Region region);
```
* [SearchedUser](/Types/SearchedUser) user
 * Ubisoft user account to fetch UserSeasonStat from
* [BaseSeason](Types/Season) season
	*  The season to get stats for 
* [Region](Types/Season) region
	*  The region to get stats for

```cpp
UserSeasonStat GetUserSeasonStat(std::string username, BaseSeason season, Region region, PlatformType platform = PlatformType::Uplay);
```
* `std::string` username
	* Name of user account to fetch UserGametypeStat from
* [BaseSeason](Types/Season) season
	*  The season to get stats for 
* [Region](Types/Season) region
	*  The region to get stats for
* [PlatformType](/Types/PlatformType) platform
	* Rainbow six platform of user
		* Default: Uplay

```cpp
UserSeasonStat GetUserSeasonStatByID(std::string profileID, BaseSeason season, Region region);
```
* `std::string` profileID
	* Ubisoft profile ID of user to fetch UserGametypeStat from
* [BaseSeason](Types/Season) season
	*  The season to get stats for 
* [Region](Types/Season) region
	*  The region to get stats for
---
title: GetUserActions
parent: R6Connection
layout: default
nav_order: 5
permalink: "/R6Connection/GetUserActions"
---

### Return Type: [UserActions](/R6pp/Types/UserActions)

### Arguments 
```cpp 
UserActions GetUserActions(SearchedUser user);
 
```
* [SearchedUser](/Types/SearchedUser) user
 * Ubisoft user account to fetch UserActions from
 
```cpp
UserActions GetUserActions(std::string username, PlatformType platform = PlatformType::Uplay);
```
* `std::string` username
	* Name of user account to fetch UserActions from
* [PlatformType](/Types/PlatformType) platform
	* Rainbow six platform of user
		* Default: Uplay

```cpp
UserActions GetUserActionsByID(std::string profileID);
```
* `std::string` profileID
	* Ubisoft profile ID of user to fetch UserActions from
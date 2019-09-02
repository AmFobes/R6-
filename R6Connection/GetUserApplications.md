---
title: GetUserApplications
parent: R6Connection
layout: default
nav_order: 4
permalink: "/R6Connection/GetUserApplications"
---

### Return Type: [UserApplications](/R6pp/Types/UserApplications)

### Arguments 
```cpp 
UserApplications GetUserApplications(SearchedUser user, std::vector<std::string> applications = {});
```
* [SearchedUser](/Types/SearchedUser) user
 * Ubisoft user account to fetch UserApplications from
* 
 
```cpp
UserApplications GetUserApplications(std::string username, PlatformType platform = PlatformType::Uplay, std::vector<std::string> applications = {});
```
* `std::string` username
	* Name of user account to fetch UserApplications from
* [PlatformType](/Types/PlatformType) platform
	* Rainbow six platform of user
		* Default: Uplay

```cpp
UserApplications GetUserApplicationsByID(std::string profileID, std::vector<std::string> applications = {});
```
* `std::string` profileID
	* Ubisoft profile ID of user to fetch UserApplications from

### Note(s)
* The function will fill the applications field if it is left blank, leaving it blank is recommended
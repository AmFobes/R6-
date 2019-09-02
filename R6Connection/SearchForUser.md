---
title: SearchForUser
parent: R6Connection
layout: default
nav_order: 2
permalink: "/R6Connection/SearchForUser"
---

### Return Type: [SearchedUser](/R6pp/Types/SearchedUser)

### Arguments 
```cpp 
SearchedUsers SearchForUser(std::string name,PlatformType platform = PlatformType::Uplay);
```
* `std::string` user
 * Username to search for
* [PlatformType](Types/Platform)
	* Platform the user is on
		* Default: Uplay
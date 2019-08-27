---
title: SearchedUser
parent: Types
layout: default
nav_order: 3
permalink: "/Types/SearchedUser"
---

### Type: struct

### Definition:
```cpp
struct SearchedUser {
	std::string profileId;
	std::string userId;
	PlatformType platformType;
	std::string idOnPlatform;
	std::string nameOnPlatform;
};
```
### Note(s)
Search for a user using [R6Connection.SearchForUser(string,PlatformType)](/R6Connection/SearchForUser)
---
title: AuthenticationHeader
parent: Types
layout: default
nav_order: 1
permalink: "/Types/AuthenticationHeader"
---

### Type: struct

### Definition:
```cpp
struct AuthenticationHeader {
	std::string clientIp;
	std::string clientIpCountry;
	std::string environment;
	std::string expiration;
	std::string nameOnPlatform;
	std::string platformType;
	std::string profileId;
	std::string serverTime;
	std::string sessionId;
	std::string sessionKey;
	std::string spaceId;
	std::string ticket;
	std::string userId;
};
```

### Note(s)
Get the read-only constructor initialized auth header by calling
[R6Connection.GetAuthHeader()](/R6Connection/GetAuthHeader)
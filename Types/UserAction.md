---
title: UserAction
parent: Types
layout: default
nav_order: 9
permalink: "/Types/UserAction"
---

### Type: struct

### Definition:
```cpp
struct UserAction {
	std::string activationDate;
	bool available;
	std::string availableDateEnd;
	std::string availableDateStart;
	std::string completionDate;
	std::string description;
	std::vector<Group> groups;
	std::string id;
	std::vector<Image> images;
	bool isBadge;
	bool isCompleted;
	std::string name;
	std::string obj;
	std::string profileId;
	std::string spaceId;
	std::string statCompletionThreshold;
	std::string statName;
	int value;
	unsigned int xp;
};
```
### Note(s)
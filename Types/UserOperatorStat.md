---
title: UserOperatorStat
parent: Types
layout: default
nav_order: 11
permalink: "/Types/UserOperatorStat"
---

### Type: struct

### Definition:
```cpp
struct UserOperatorStat {
	R6pp::Operators::BaseOperator baseOperator;
	int kills;
	int deaths;
	int unique;
	int roundlost;
	int roundwon;
	int timeplayed;
};
```
### Note(s)
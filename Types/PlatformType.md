---
title: PlatformType
parent: Types
layout: default
nav_order: 2
permalink: "/Types/PlatformType"
---

### Type: enum class

### Definition:
```cpp
enum class PlatformType {
	Uplay,
	PSN,
	Xbox,
};
```
### Note(s)
Two functions are used to have string --> PlatformType and PlatformType --> string abilities

[PlatformTypeToString(PlatformType)](https://github.com/AmFobes/R6pp/blob/master/R6pp/Types.h#L88)
and
[StringToPlatformType(string)](https://github.com/AmFobes/R6pp/blob/master/R6pp/Types.h#L99)

```cpp
inline std::string PlatformTypeToString(PlatformType type) {
switch (type) {
	case PlatformType::Uplay:
		return "uplay";
	case PlatformType::PSN:
		return "psn";
	case PlatformType::Xbox:
		return "xbl";
	}
}
	
inline std::string PlatformTypeToString(PlatformType type) {
 switch (type) {
	case PlatformType::Uplay:
		return "uplay";
	case PlatformType::PSN:
		return "psn";
	case PlatformType::Xbox:
		return "xbl";
	}
}
```
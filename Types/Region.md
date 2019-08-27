---
title: Region
parent: Types
layout: default
nav_order: 17
permalink: "/Types/Region"
---

### Type: enum class

### Definition:
```cpp
enum class Region {
	America,
	Europe,
	Asia,
};
```
### Note(s)
Two functions are used to have string --> Region and Region --> string abilities

[RegionToString(Region)](https://github.com/AmFobes/R6pp/blob/master/R6pp/Types.h#L215)
and
[StringToRegion(string)](https://github.com/AmFobes/R6pp/blob/master/R6pp/Types.h#L224)

```cpp
inline std::string RegionToString(Region region) {
	if (region == Region::America)
		return "ncsa";
	if (region == Region::Europe)
		return "emea";
	if (region == Region::Asia)
		return "apac";
}
	
inline Region StringToRegion(std::string region) {
	std::transform(region.begin(), region.end(),region.begin(), [](unsigned char c) 
	{ return std::tolower(c); });
	if (region == "ncsa")
		return Region::America;
	if (region == "emea")
		return Region::Europe;
	if (region == "apac")
		return Region::Asia;
}
```
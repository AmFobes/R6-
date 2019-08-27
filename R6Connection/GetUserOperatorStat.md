---
title: GetUserOperatorStat
parent: R6Connection
layout: default
nav_order: 7
permalink: "/R6Connection/GetUserOperatorStat"
---

### Return Type: [UserOperatorStat](/Types/UserOperatorStat)

### Arguments 
```cpp 
UserOperatorStat GetUserOperatorStat(SearchedUser user, R6pp::Operators::BaseOperator operator);
```
* [SearchedUser](/Types/SearchedUser) user
 * Ubisoft user account to fetch UserOperatorStat from
* [BaseOperator](Types/BaseOperator) operator
	*  The operator to pull stats from
 
```cpp
UserOperatorStat GetUserOperatorStat(std::string username, R6pp::Operators::BaseOperator operator, PlatformType platform = PlatformType::Uplay);
```
* `std::string` username
	* Name of user account to fetch UserOperatorStat from
* [BaseOperator](Types/BaseOperator) operator
	*  The operator to pull stats from
* [PlatformType](/Types/PlatformType) platform
	* Rainbow six platform of user
		* Default: Uplay

```cpp
UserOperatorStat GetUserOperatorStatByID(std::string profileID, R6pp::Operators::BaseOperator operator);
```
* `std::string` profileID
	* Ubisoft profile ID of user to fetch UserOperatorStat from
* [BaseOperator](Types/BaseOperator) operator
	*  The operator to pull stats from
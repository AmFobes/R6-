---
title: R6Connection
layout: default
New field 3: R6Connection
nav_order: 2
has_children: true
permalink: "/R6Connection"
---

# R6Connection
## This is the main class containing all the methods you'll use

|  Function                           | Return Type            | Arguments                                                                                                      | Comment                                                    |
|:------------------------- -|:----------------------|:---------------------------------------------------------------------- |:-----------------------------------------|
| [Constructor](/R6pp/R6Connection/R6connection) | R6Connection        | `String` email & `String` password                                                   | Fetches the auth header data from ubi  |
| [SearchForUser](/R6pp/R6Connection/SearchForUser) | SearchedUsers      | `String` name & `PlatformType` platform                                    | Searches for a user                                |
| [GetAuthHeader](/R6pp/R6Connection/GetAuthHeader) | AuthenticationHeader| | See the AuthenticationHeader page for info
| [GetUserApplications](/R6pp/R6Connection/GetUserApplications) | UserApplications | `SearchedUser` user & `String[]` applications                          | See the `application` page for information|
| [GetUserApplications](/R6pp/R6Connection/GetUserApplications) | UserApplications | `String` name & `PlatformType` platform & `String[]` applications | See the `application` page for information|
| [GetUserApplicationsByID](/R6pp/R6Connection/GetUserApplications) | UserApplications | `String` profileID & `String[]` applications                     |Se the `application` page for information |
| [GetUserActions](/R6pp/R6Connection/GetUserActions) | UserActions | `SearchedUser` user |  |
| [GetUserActions](/R6pp/R6Connection/GetUserActions) | UserActions | `String` name & `PlatformType` platform | |
| [GetUserActionsByID](/R6pp/R6Connection/GetUserActions) | UserActions | `String` profileID | |
| [GetUserOperatorStats](/R6pp/R6Connection/GetUserOperatorStats) | UserOperatorStats | `SearchedUser` user | Returns every r6 operator stat |
| [GetUserOperatorStats](/R6pp/R6Connection/GetUserOperatorStats) | UserOperatorStats | `String` name & `PlatformType` platform |Returns every r6 operator stat| 
| [GetUserOperatorStatsByID](/R6pp/R6Connection/GetUserOperatorStats) | UserOperatorStats | `String` profileID | Returns every r6 operator stat |
| [GetUserOperatorStat](/R6pp/R6Connection/GetUserOperatorStat) | UserOperatorStat | `SearchedUser` user & `BaseOperator` operator | |
| [GetUserOperatorStat](/R6pp/R6Connection/GetUserOperatorStat) | UserOperatorStat| `String` name & `PlatformType` platform & `BaseOperator` operator | |
| [GetUserOperatorStatByID](/R6pp/R6Connection/GetUserOperatorStat) | UserOperatorStat | `String` profileID & `BaseOperator` operator | |
| [GetUserWeaponStats](/R6pp/R6Connection/GetUserWeaponStats) | UserWeaponStats | `SearchedUser` user | |
| [GetUserWeaponStats](/R6pp/R6Connection/GetUserWeaponStats) | UserWeaponStats | `String` name & `PlatformType` platform | |
| [GetUserWeaponStatsByID](/R6pp/R6Connection/GetUserWeaponStats) | UserWeaponStats | `String` profileID | |
| [GetUserWeaponStat](/R6pp/R6Connection/GetUserWeaponStat) | UserWeaponStat | `SearchedUser` user &  `BaseWeapon` weapon | |
| [GetUserWeaponStat](/R6pp/R6Connection/GetUserWeaponStat) | UserWeaponStat | `String` name & `PlatformType` platform & `BaseWeapon` weapon | |
| [GetUserWeaponStatByID](/R6pp/R6Connection/GetUserWeaponStat) | UserWeaponStat | `String` profileID & `BaseWeapon` weapon | |
| [GetUserSeasonStat](/R6pp/R6Connection/GetUserSeasonStat) | UserSeasonStat | `SearchedUser` user & `BaseSeason` season & `Region` region | |
| [GetUserSeasonStat](/R6pp/R6Connection/GetUserSeasonStat) | UserSeasonStat | `String` name & `PlatformType` platform &`BaseSeason` season & `Region` region | | 
| [GetUserSeasonStatByID](/R6pp/R6Connection/GetUserSeasonStat) | UserSeasonStat | `String` profileID | |
| [GetUserGametypeStat](/R6pp/R6Connection/GetUserGametypeStat) | UserGametypeStat | `SearchedUser` user | |
| [GetUserGametypeStat](/R6pp/R6Connection/GetUserGametypeStat) | UserGametypeStat | `String` name & `PlatformType` platform | |
| [GetUserGametypeStatByID](/R6Connection/GetUserGametypeStat) | UserGametypeStat | `String` profileID | |
| [GetUserGamemodeStat](/R6pp/R6Connection/GetUserGamemodeStat) | UserGamemodeStat | `SearchedUser` user | |
| [GetUserGamemodeStat](/R6pp/R6Connection/GetUserGamemodeStat) | UserGamemodeStat | `String` name & `PlatformType` platform | |
| [GetUserGamemodeStatByID](/R6pp/R6Connection/GetUserGamemodeStat) | UserGamemodeStat | `String` profileID | |
| [GetPlayerProfile](/R6pp/R6Connection/GetUserPlayerProfile) | PlayerProfile | `SearchedUser` user | |
| [GetPlayerProfile](/R6pp/R6Connection/GetUserPlayerProfile) | PlayerProfile | `String` name & `PlatformType` platform | |
| [GetPlayerProfileByID](/R6pp/R6Connection/GetUserPlayerProfile)| PlayerProfile | `String` profileID | |
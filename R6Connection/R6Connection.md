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
| [Constructor](/R6Connection/R6connection) | R6Connection        | `String` email & `String` password                                                   | Fetches the auth header data from ubi  |
| [SearchForUser](SearchForUser) | SearchedUsers      | `String` name & `PlatformType` platform                                    | Searches for a user                                |
| [GetAuthHeader](GetAuthHeader) | AuthenticationHeader| | See the AuthenticationHeader page for info
| [GetUserApplications](GetUserApplications) | UserApplications | `SearchedUser` user & `String[]` applications                          | See the `application` page for information|
| [GetUserApplications](GetUserApplications) | UserApplications | `String` name & `PlatformType` platform & `String[]` applications | See the `application` page for information|
| [GetUserApplicationsByID](GetUserApplications) | UserApplications | `String` profileID & `String[]` applications                     |Se the `application` page for information |
| [GetUserActions](GetUserActions) | UserActions | `SearchedUser` user |  |
| [GetUserActions](GetUserActions) | UserActions | `String` name & `PlatformType` platform | |
| [GetUserActionsByID](GetUserActions) | UserActions | `String` profileID | |
| [GetUserOperatorStats](GetUserOperatorStats) | UserOperatorStats | `SearchedUser` user | Returns every r6 operator stat |
| [GetUserOperatorStats](GetUserOperatorStats) | UserOperatorStats | `String` name & `PlatformType` platform |Returns every r6 operator stat| 
| [GetUserOperatorStatsByID](GetUserOperatorStats) | UserOperatorStats | `String` profileID | Returns every r6 operator stat |
| [GetUserOperatorStat](GetUserOperatorStat) | UserOperatorStat | `SearchedUser` user & `BaseOperator` operator | |
| [GetUserOperatorStat](GetUserOperatorStat) | UserOperatorStat| `String` name & `PlatformType` platform & `BaseOperator` operator | |
| [GetUserOperatorStatByID](GetUserOperatorStat) | UserOperatorStat | `String` profileID & `BaseOperator` operator | |
| [GetUserWeaponStats](GetUserWeaponStats) | UserWeaponStats | `SearchedUser` user | |
| [GetUserWeaponStats](GetUserWeaponStats) | UserWeaponStats | `String` name & `PlatformType` platform | |
| [GetUserWeaponStatsByID](GetUserWeaponStats) | UserWeaponStats | `String` profileID | |
| [GetUserWeaponStat](GetUserWeaponStat) | UserWeaponStat | `SearchedUser` user &  `BaseWeapon` weapon | |
| [GetUserWeaponStat](GetUserWeaponStat) | UserWeaponStat | `String` name & `PlatformType` platform & `BaseWeapon` weapon | |
| [GetUserWeaponStatByID](GetUserWeaponStat) | UserWeaponStat | `String` profileID & `BaseWeapon` weapon | |
| [GetUserSeasonStat](GetUserSeasonStat) | UserSeasonStat | `SearchedUser` user & `BaseSeason` season & `Region` region | |
| [GetUserSeasonStat](GetUserSeasonStat) | UserSeasonStat | `String` name & `PlatformType` platform &`BaseSeason` season & `Region` region | | 
| [GetUserSeasonStatByID](GetUserSeasonStat) | UserSeasonStat | `String` profileID | |
| [GetUserGametypeStat](GetUserGametypeStat) | UserGametypeStat | `SearchedUser` user | |
| [GetUserGametypeStat](GetUserGametypeStat) | UserGametypeStat | `String` name & `PlatformType` platform | |
| [GetUserGametypeStatByID](GetUserGametypeStat) | UserGametypeStat | `String` profileID | |
| [GetUserGamemodeStat](GetUserGamemodeStat) | UserGamemodeStat | `SearchedUser` user | |
| [GetUserGamemodeStat](GetUserGamemodeStat) | UserGamemodeStat | `String` name & `PlatformType` platform | |
| [GetUserGamemodeStatByID](GetUserGamemodeStat) | UserGamemodeStat | `String` profileID | |
| [GetPlayerProfile](GetUserPlayerProfile) | PlayerProfile | `SearchedUser` user | |
| [GetPlayerProfile](GetUserPlayerProfile) | PlayerProfile | `String` name & `PlatformType` platform | |
| [GetPlayerProfileByID](GetUserPlayerProfile)| PlayerProfile | `String` profileID | |
---
title: UserSeasonStat
parent: Types
layout: default
nav_order: 20
permalink: "/Types/UserSeasonStat"
---

### Type: struct

### Definition:
```cpp
struct UserSeasonStat {
	BaseSeason Season;
	int abandons;
	std::string board_id;
	int deaths;
	int kills;
	int last_match_mmr_change;
	int last_match_result;
	int last_match_skill_mean_change;
	int last_match_skill_stdev_change;
	int losses;
	int max_mmr;	
	int max_rank;
	int mmr;
	int next_rank_mmr;
	int previous_rank_mmr;
	std::string profile_id;
	int rank;
	Region typeRegion;
	std::string region;
	int season;
	int skill_mean;
	int skill_stdev;
	std::string update_time;
	int wins;
};
```

### Note(s)
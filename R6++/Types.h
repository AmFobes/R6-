#pragma once
#include "Operators.h"
#include <vector>
#include <exception>
#include <string>
#include <algorithm>
/*

	Exceptions

*/
namespace Exceptions {
	class InputArgumentsInvalid : public std::runtime_error {
	public:
		std::string ermsg;

		InputArgumentsInvalid(std::string msg) : runtime_error(msg) {
			this->ermsg = msg;
		};
		InputArgumentsInvalid() : runtime_error("Input arguments that were expected were not present") {
			this->ermsg = "Input arguments that were expected were not present";
		}
		const char* what() throw() {
			return ermsg.c_str();
		}
	};

	class FatalConnectionError : public std::runtime_error {
	public:
		std::string ermsg;

		FatalConnectionError(std::string msg) : runtime_error(msg) {
			this->ermsg = msg;
		};
		FatalConnectionError(int code) : runtime_error("Error: " + std::to_string(code)) {
			this->ermsg = "Error: " + std::to_string(code);
		};
		const char* what() throw() {
			return ermsg.c_str();
		}
	};

	class
		JsonParseError : public std::runtime_error {
	public:
		std::string ermsg;

		JsonParseError(std::string msg) : runtime_error(msg) {
			this->ermsg = msg;
		};

		const char* what() throw() {
			return ermsg.c_str();
		}
	};
}

namespace R6pp {
	struct AuthenticationHeader {
		std::string clientIp;
		std::string clientIpCountry;
		std::string environment;
		std::string expiration;
		std::string nameOnPlatform;
		std::string platformType;
		std::string profileId;
		// std::string rememberMeTicket;
		std::string serverTime;
		std::string sessionId;
		std::string sessionKey;
		std::string spaceId;
		std::string ticket;
		// std::string twoFactorAuthentication
		std::string userId;

		std::string email;
		std::string password;
	};

	enum class PlatformType {
		Uplay,
		PSN,
		Xbox,
	};

	std::string PlatformTypeToString(PlatformType type) {
		switch (type) {
		case PlatformType::Uplay:
			return "uplay";
		case PlatformType::PSN:
			return "psn";
		case PlatformType::Xbox:
			return "xbl";
		}
	}

	PlatformType StringToPlatformType(std::string type) {
		std::transform(type.begin(), type.end(), type.begin(),
			[](unsigned char c) { return std::tolower(c); });
		if (type == "uplay")
			return PlatformType::Uplay;
		if (type == "psn")
			return PlatformType::PSN;
		if (type == "xbl")
			return PlatformType::Xbox;
	}

	struct SearchedUser {
		std::string profileId;
		std::string userId;
		PlatformType platformType;
		std::string idOnPlatform;
		std::string nameOnPlatform;
	};

	typedef std::vector<SearchedUser> SearchedUsers;

	struct UserApplication {
		std::string profileId;
		std::string applicationId;
		std::string firstSessionDate;
		std::string lastSessionDate;
		// May change to uint32_t ?
		unsigned int sessionsCount;
	};

	typedef std::vector<UserApplication> UserApplications;

	struct Group {
		std::string id;
		std::string name;
	};
	struct Image {
		std::string type;
		std::string url;
	};
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

	typedef std::vector<UserAction> UserActions;

	struct UserOperatorStat {
		R6pp::Operators::BaseOperator baseOperator;
		int kills;
		int deaths;
		int unique;
		int roundlost;
		int roundwon;
		int timeplayed;
	};

	typedef std::vector<UserOperatorStat> UserOperatorStats;

	struct BaseWeapon {
		int number;
		std::string name;
		BaseWeapon(int number, std::string name) {
			this->number = number;
			this->name = name;
		}
		BaseWeapon() {};
	}AR(1, "Assault Rifle"), MR(2, "Marksman Rifle"),
		SMG(3, "Submachine Gun"), Handgun(4, "Handgun"),
		Shotgun(5, "Shotgun"), LMG(6, "Light Machine Gun"),
		MachinePistol(7, "Machine Pistol");

	std::vector<BaseWeapon> Weapons{
		AR,MR,SMG,
		Handgun,Shotgun,
		LMG,MachinePistol,
	};

	struct UserWeaponStat {
		BaseWeapon weapon;
		int bulletfired;
		int bullethit;
		int headshot;
		int kills;
	};

	typedef std::vector<UserWeaponStat> UserWeaponStats;

	enum class Region {
		America,
		Europe,
		Asia,
	};

	std::string RegionToString(Region region) {
		if (region == Region::America)
			return "ncsa";
		if (region == Region::Europe)
			return "emea";
		if (region == Region::Asia)
			return "apac";
	}

	Region StringToRegion(std::string region) {
		std::transform(region.begin(), region.end(), region.begin(),
			[](unsigned char c) { return std::tolower(c); });
		if (region == "ncsa")
			return Region::America;
		if (region == "emea")
			return Region::Europe;
		if (region == "apac")
			return Region::Asia;
	}

	struct BaseSeason {
		int SeasonID;
		std::string SeasonName;
		BaseSeason(int SeasonID, std::string SeasonName) {
			this->SeasonID = SeasonID;
			this->SeasonName = SeasonName;
		}
		BaseSeason() {}
	}Current(-1,""),PhantomSight(14,"Phantom Sight"),BurntHorizon(13,"Burnt Horizon"),
		WindBastion(12,"Wind Bastion"),GrimSky(11,"Grim Sky"),ParaBellum(10,"Para Bellum"),
		Chimera(9,"Chimera"),WhiteNoise(8,"White Noise"),BloodOrchid(7,"Blood Orchid"),
		Health(6,"Health"),VelvetShell(5,"Velvet Shell"),RedCrow(4,"Red Crow"),
			SkullRain(3,"Skull Rain"), DustLine(2,"Dust Line"),BlackIce(1,"Black Ice");

	std::vector<BaseSeason> Seasons{
		Current,PhantomSight,BurntHorizon,
		WindBastion,GrimSky,ParaBellum,
		Chimera,WhiteNoise,BloodOrchid,
		Health,VelvetShell,RedCrow,
		SkullRain,DustLine,BlackIce
	};

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
	
	struct UserGametypeStat {
		struct baseCasual {
			int death;
			int kills;
			int matchlost;
			int matchplayed;
			int matchwon;
			long timeplayed;
		} Casual;
		struct baseRanked {
			int death;
			int kills;
			int matchlost;
			int matchplayed;
			int matchwon;
			long timeplayed;
		} Ranked;
	};

	struct UserGeneralStat {
		int bulletfired;
		int bullethit;
		int death;
		int headshot;
		int killassists;
		int kills;
		int matchlost;
		int matchplayed;
		int matchwon;
		int meleekills;
		int penetrationkills;
		int revive;
		long timeplayed;
	};

	struct UserGamemodeStat {
		struct BaseGamemode {
			int bestscore;
			int matchlost;
			int matchplayed;
			int matchwon;
		}PlantBomb,RescueHostage,SecureArea;
	};

	struct PlayerProfile{
		int level;
		int lootbox_probability;
		std::string profile_id;
		int xp;
	};
}
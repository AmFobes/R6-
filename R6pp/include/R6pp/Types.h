#pragma once
#include "Operators.h"
#include <vector>
#include <exception>
#include <string>
#include <cctype>
#include <algorithm>

/*

	Exceptions

*/
namespace Exceptions {
	class InputArgumentsInvalid : public std::runtime_error {
	public:
		std::string ermsg;

		InputArgumentsInvalid(const std::string& msg) : runtime_error(msg), ermsg(msg) { };
		InputArgumentsInvalid() : runtime_error("Input arguments that were expected were not present"), ermsg("Input arguments that were expected were not present") {}
		const char* what() throw() {
			return ermsg.c_str();
		}
	};

	class FatalConnectionError : public std::runtime_error {
	public:
		std::string ermsg;

		FatalConnectionError(const std::string &msg) : runtime_error(msg), ermsg(msg) { };
		FatalConnectionError(int code) : runtime_error("Error: " + std::to_string(code)), ermsg("Error: " + std::to_string(code)) {	};
		const char* what() throw() {
			return ermsg.c_str();
		}
	};

	class
		JsonParseError : public std::runtime_error {
	public:
		std::string ermsg;

		JsonParseError(const std::string &msg) : runtime_error(msg), ermsg(msg) { };

		const char* what() throw() {
			return ermsg.c_str();
		}
	};
}

namespace R6pp {
	
	struct ServiceStatus {
		struct platformStatus {
			
			std::string AppID;
			std::string Category;
			std::string Maintenance;
			std::string Name;
			std::string Platform;
			std::string Status;
		}PC,PS4,XBOXONE;
	};

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

	inline std::string PlatformTypeToString(PlatformType type) {
		switch (type) {
		case PlatformType::Uplay:
			return "uplay";
		case PlatformType::PSN:
			return "psn";
		case PlatformType::Xbox:
			return "xbl";
		default:
			return "uplay";
		}
	}

	inline PlatformType StringToPlatformType(std::string type) {
		std::transform(type.begin(), type.end(), type.begin(),
			[](unsigned char c) { return std::tolower(c); });
		if (type == "uplay")
			return PlatformType::Uplay;
		if (type == "psn")
			return PlatformType::PSN;
		if (type == "xbl")
			return PlatformType::Xbox;
		return PlatformType::Uplay;
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
		bool operator < (UserOperatorStat cmpOperatorStat) {
			return this->kills < cmpOperatorStat.timeplayed;
		}
		bool operator > (UserOperatorStat cmpOperatorStat) {
			return this->kills > cmpOperatorStat.timeplayed;
		}
	};

	typedef std::vector<UserOperatorStat> UserOperatorStats;

	struct BaseWeapon {
		int number;
		std::string name;
		inline BaseWeapon(int number, const std::string &name) {
			this->number = number;
			this->name = name;
		}
		inline BaseWeapon() : number(0), name(""){};
	};
	static BaseWeapon
		AR(1, "Assault Rifle"),
		MR(2, "Marksman Rifle"),
		SMG(3, "Submachine Gun"),
		Handgun(4, "Handgun"),
		Shotgun(5, "Shotgun"),
		LMG(6, "Light Machine Gun"),
		MachinePistol(7, "Machine Pistol");

	static std::vector<BaseWeapon> Weapons{
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
		bool operator<(UserWeaponStat cmpWeaponStat) {
			return this->kills < cmpWeaponStat.kills;
		}
		bool operator>(UserWeaponStat cmpWeaponStat) {
			return this->kills > cmpWeaponStat.kills;
		}
	};

	typedef std::vector<UserWeaponStat> UserWeaponStats;

	enum class Region {
		America,
		Europe,
		Asia,
	};

	inline std::string RegionToString(Region region) {
		if (region == Region::America)
			return "ncsa";
		if (region == Region::Europe)
			return "emea";
		if (region == Region::Asia)
			return "apac";
		return "ncsa";
	}

	inline Region StringToRegion(std::string region) {
		std::transform(region.begin(), region.end(), region.begin(),
			[](unsigned char c) { return std::tolower(c); });
		if (region == "ncsa")
			return Region::America;
		if (region == "emea")
			return Region::Europe;
		if (region == "apac")
			return Region::Asia;
		return Region::America;
	}

	struct BaseSeason {
		int SeasonID;
		std::string SeasonName;
		inline BaseSeason(int SeasonID, std::string SeasonName) {
			this->SeasonID = SeasonID;
			this->SeasonName = SeasonName;
		}
		inline BaseSeason() : SeasonID(0), SeasonName(""){}
	};
	static BaseSeason
		Current(-1, ""), EmberRise(15,"Ember Rise"), PhantomSight(14, "Phantom Sight"), BurntHorizon(13, "Burnt Horizon"),
		WindBastion(12, "Wind Bastion"), GrimSky(11, "Grim Sky"), ParaBellum(10, "Para Bellum"),
		Chimera(9, "Chimera"), WhiteNoise(8, "White Noise"), BloodOrchid(7, "Blood Orchid"),
		Health(6, "Health"), VelvetShell(5, "Velvet Shell"), RedCrow(4, "Red Crow"),
		SkullRain(3, "Skull Rain"), DustLine(2, "Dust Line"), BlackIce(1, "Black Ice");

	static std::vector<BaseSeason> Seasons{
		EmberRise,PhantomSight,BurntHorizon,
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
		double last_match_mmr_change;
		int last_match_result;
		double last_match_skill_mean_change;
		double last_match_skill_stdev_change;
		int losses;
		double max_mmr;
		double max_rank;
		double mmr;
		double next_rank_mmr;
		double previous_rank_mmr;
		std::string profile_id;
		int rank;
		Region typeRegion;
		std::string region;
		int season;
		double skill_mean;
		double skill_stdev;
		std::string update_time;
		int wins;
		bool operator<(UserSeasonStat cmpSeasonStat) {
			return this->rank < cmpSeasonStat.rank;
		}
		bool operator>(UserSeasonStat cmpSeasonStat) {
			return this->rank > cmpSeasonStat.rank;
		}
	};
	   
	struct UserGametypeStat {
		struct baseGametype {
			int death;
			int kills;
			int matchlost;
			int matchplayed;
			int matchwon;
			int64_t timeplayed;
		} Casual, Ranked;		
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
		int64_t timeplayed;
	};

	struct UserGamemodeStat {
		struct BaseGamemode {
			int bestscore;
			int matchlost;
			int matchplayed;
			int matchwon;
		}PlantBomb, RescueHostage, SecureArea;
	};

	struct PlayerProfile {
		int level;
		int lootbox_probability;
		std::string profile_id;
		int xp;
	};
}
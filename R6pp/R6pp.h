#pragma once
// For whatever reason cpr is unable to successfully verify ssl on my machine using openssl
// this define allows ssl verifying to not be used
#define VERIFYSSL true

#pragma once
#include <string>
#include <iostream>
#include "Types.h"
#include <cpr/cpr.h>
#include <rapidjson/document.h>

namespace R6pp{
	
	

	class R6Connection {
	private:
		AuthenticationHeader _authHeader;
		rapidjson::Document _sendCPRRequest(std::string url);
	public:
		R6Connection(std::string email, std::string password);

		AuthenticationHeader GetAuthHeader() {return this->_authHeader;}

		SearchedUsers SearchForUser(std::string name,PlatformType platform = PlatformType::Uplay);
		
		UserApplications GetUserApplications(const SearchedUser &user, std::vector<std::string> applications = {});
		UserApplications GetUserApplications(std::string username, PlatformType platform = PlatformType::Uplay, std::vector<std::string> applications = {});
		UserApplications GetUserApplicationsByID(std::string profileID, std::vector<std::string> applications = {});

		UserActions GetUserActions(const SearchedUser &user);
		UserActions GetUserActions(std::string username, PlatformType platform = PlatformType::Uplay);
		UserActions GetUserActionsByID(std::string profileID);

		UserOperatorStats GetUserOperatorStats(const SearchedUser &user);
		UserOperatorStats GetUserOperatorStats(std::string username, PlatformType platform = PlatformType::Uplay);
		UserOperatorStats GetUserOperatorStatsByID(std::string profileID);

		UserOperatorStat GetUserOperatorStat(const SearchedUser &user, const R6pp::Operators::BaseOperator &Operator);
		UserOperatorStat GetUserOperatorStat(std::string username, const R6pp::Operators::BaseOperator &Operator, PlatformType platform = PlatformType::Uplay);
		UserOperatorStat GetUserOperatorStatByID(std::string profileID, const R6pp::Operators::BaseOperator &Operator);
	
		UserWeaponStats GetUserWeaponStats(const SearchedUser &user);
		UserWeaponStats GetUserWeaponStats(std::string username, R6pp::PlatformType platform = PlatformType::Uplay);
		UserWeaponStats GetUserWeaponStatsByID(std::string profileID);

		UserWeaponStat GetUserWeaponStat(const SearchedUser &user, const BaseWeapon &Weapon);
		UserWeaponStat GetUserWeaponStat(std::string username, const BaseWeapon &Weapon, PlatformType platform = PlatformType::Uplay);
		UserWeaponStat GetUserWeaponStatByID(std::string profileID, const BaseWeapon &Weapon);

		UserSeasonStat GetUserSeasonStat(const SearchedUser &user, const BaseSeason &Season, const Region &region);
		UserSeasonStat GetUserSeasonStat(std::string username, const BaseSeason &Season, const Region &region, PlatformType platform = PlatformType::Uplay);
		UserSeasonStat GetUserSeasonStatByID(std::string profileID, const BaseSeason &Season, const Region &region);

		UserGametypeStat GetUserGametypeStat(const SearchedUser &user);
		UserGametypeStat GetUserGametypeStat(std::string username, PlatformType platform = PlatformType::Uplay);
		UserGametypeStat GetUserGametypeStatByID(std::string profileID);

		UserGeneralStat GetUserGeneralStat(const SearchedUser &user);
		UserGeneralStat GetUserGeneralStat(std::string username, PlatformType platform = PlatformType::Uplay);
		UserGeneralStat GetUserGeneralStatByID(std::string profileID);

		UserGamemodeStat GetUserGamemodeStat(const SearchedUser &user);
		UserGamemodeStat GetUserGamemodeStat(std::string username, PlatformType platform = PlatformType::Uplay);
		UserGamemodeStat GetUserGamemodeStatByID(std::string profileID);

		PlayerProfile GetPlayerProfile(const SearchedUser &user);
		PlayerProfile GetPlayerProfile(std::string username, PlatformType platform = PlatformType::Uplay);
		PlayerProfile GetPlayerProfileByID(std::string profileID);
	};

	ServiceStatus GetServiceStatus();

};


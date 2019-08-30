// R6++.cpp : Defines the entry point for the application.
//

#include "R6pp.h"


#include <string>
R6pp::R6Connection::R6Connection(std::string email, std::string password) {
	if (email.empty() || password.empty())
		throw Exceptions::InputArgumentsInvalid("The email or password field is empty");

	auto resp =
		cpr::Post(cpr::Url{ "https://public-ubiservices.ubi.com/v3/profiles/sessions" },
			cpr::Authentication(email, password),
			cpr::Header{ {"Content-Type", "application/json"},
						 {"Content-Length", "0"}, // Required
						 {"Ubi-AppId","39baebad-39e5-4552-8c25-2c9b919064e2"} },
			cpr::VerifySsl(VERIFYSSL));

	if (resp.error || resp.status_code != 200)
		throw Exceptions::FatalConnectionError("Request error when trying to authenticate with rainbow six. \"" + resp.error.message + "\" HTTP status code " + std::to_string(resp.status_code));

	AuthenticationHeader header;

	rapidjson::Document doc;
	doc.Parse(resp.text.c_str());
	
	if (doc.HasParseError())
		throw Exceptions::JsonParseError("Error when parsing json. Raw response: " + resp.text);

	_authHeader.clientIp = doc["clientIp"].GetString();
	_authHeader.clientIpCountry = doc["clientIpCountry"].GetString();
	_authHeader.environment = doc["environment"].GetString();
	_authHeader.expiration = doc["expiration"].GetString();
	_authHeader.nameOnPlatform = doc["nameOnPlatform"].GetString();
	_authHeader.platformType = doc["platformType"].GetString();
	_authHeader.profileId = doc["profileId"].GetString();
	_authHeader.sessionId = doc["sessionId"].GetString();
	_authHeader.sessionKey = doc["sessionKey"].GetString();
	_authHeader.spaceId = doc["spaceId"].GetString();
	_authHeader.ticket = doc["ticket"].GetString();
	_authHeader.userId = doc["userId"].GetString();
	
}

R6pp::SearchedUsers R6pp::R6Connection::SearchForUser(std::string name,R6pp::PlatformType platformType) {
	if (name.empty())
		throw Exceptions::InputArgumentsInvalid("The name field is empty");

	auto resp =
		cpr::Get(cpr::Url{ "https://public-ubiservices.ubi.com/v2/profiles?nameOnPlatform=" + name + "&platformType=" + PlatformTypeToString(platformType) },
			cpr::Header{ {"Authorization", "Ubi_v1 t=" + this->_authHeader.ticket},
						 {"Accept","application/json"},
						 {"Ubi-AppId", "39baebad-39e5-4552-8c25-2c9b919064e2"}},
			cpr::VerifySsl(VERIFYSSL));

	if(resp.error || resp.status_code != 200)
		throw Exceptions::FatalConnectionError("Request error when trying to search for a user.\"" + resp.error.message + "\" HTTP status code " + std::to_string(resp.status_code));

	SearchedUsers su;
	
	rapidjson::Document doc;
	doc.Parse(resp.text.c_str());

	if (doc.HasParseError())
		throw Exceptions::JsonParseError("Error when parsing json. Raw response: " + resp.text);

	for (auto& user : doc["profiles"].GetArray()) {
		SearchedUser sUser;
		sUser.idOnPlatform = user["idOnPlatform"].GetString();
		sUser.nameOnPlatform = user["nameOnPlatform"].GetString();
		sUser.platformType = StringToPlatformType(user["platformType"].GetString());
		sUser.profileId = user["profileId"].GetString();
		sUser.userId = user["userId"].GetString();
		su.emplace_back(sUser);
	}
	return su;
}

R6pp::UserApplications R6pp::R6Connection::GetUserApplicationsByID(std::string profileID,  std::vector<std::string> applications) {
	if (applications.size() == 0)
		// Default
		applications = {
		"e3d5ea9e-50bd-43b7-88bf-39794f4e3d40",
		"fb4cc4c9-2063-461d-a1e8-84a7d36525fc",
		"4008612d-3baf-49e4-957a-33066726a7bc"
	};

	if (profileID.empty())
		throw Exceptions::InputArgumentsInvalid("Missing user profileID");

	std::stringstream applicationIds;
	std::copy(applications.begin(), applications.end(), std::ostream_iterator<std::string>(applicationIds, ","));

	auto resp =
		cpr::Get(cpr::Url{ "https://public-ubiservices.ubi.com/v3/profiles/applications?applicationIds=" + applicationIds.str() + "&profileIds=" + profileID },
			cpr::Header{ {"Authorization","Ubi_v1 t=" + this->_authHeader.ticket},
						 {"Accept","application/json"},
						 {"Ubi-AppId","39baebad-39e5-4552-8c25-2c9b919064e2" } },
			cpr::VerifySsl(VERIFYSSL));

	if (resp.error || resp.status_code != 200)
		throw Exceptions::FatalConnectionError("Request error when retrieving user applications. \"" + resp.error.message + "\" HTTP status code " + std::to_string(resp.status_code));

	UserApplications ua;

	rapidjson::Document doc;
	doc.Parse(resp.text.c_str());

	if (doc.HasParseError())
		throw Exceptions::JsonParseError("Error when parsing json. Raw response: " + resp.text);

	for (auto& application : doc["applications"].GetArray()) {
		UserApplication uapplication;
		uapplication.applicationId = application["applicationId"].GetString();
		uapplication.firstSessionDate = application["firstSessionDate"].GetString();
		uapplication.lastSessionDate = application["lastSessionDate"].GetString();
		uapplication.profileId = application["profileId"].GetString();
		uapplication.sessionsCount = application["sessionsCount"].GetInt();
		ua.emplace_back(uapplication);
	}
	return ua;
}


R6pp::UserApplications R6pp::R6Connection::GetUserApplications(const R6pp::SearchedUser &user, std::vector<std::string> applications) {
	if (user.profileId.empty())
		throw Exceptions::InputArgumentsInvalid("Missing user profileID");

		return this->GetUserApplicationsByID(user.profileId);
}

R6pp::UserApplications R6pp::R6Connection::GetUserApplications(std::string username,R6pp::PlatformType platform, std::vector<std::string> applications) {
	if (username.empty())
		throw Exceptions::InputArgumentsInvalid("Missing username");

		auto user = this->SearchForUser(username, platform);
		return this->GetUserApplicationsByID(user[0].profileId);
}

R6pp::UserActions R6pp::R6Connection::GetUserActionsByID(std::string profileID) {
	if (profileID.empty())
		throw Exceptions::InputArgumentsInvalid("Missing user profileID");

	auto resp =
	cpr::Get(cpr::Url{ "https://public-ubiservices.ubi.com/v1/profiles/" + profileID + "/uplay/actions?locale=en-us&spaceId=5172a557-50b5-4665-b7db-e3f2e8c5041d" },
		cpr::Header{ {"Authorization","Ubi_v1 t=" + this->_authHeader.ticket},
					 {"Accept","application/json"},
					 {"Ubi-AppId","39baebad-39e5-4552-8c25-2c9b919064e2" } },
		cpr::VerifySsl(VERIFYSSL));

	if (resp.error || resp.status_code != 200)
		throw Exceptions::FatalConnectionError("Request error when retrieving user applications. \"" + resp.error.message + "\" HTTP status code " + std::to_string(resp.status_code));

	UserActions ua;

	rapidjson::Document doc;
	doc.Parse(resp.text.c_str());

	if (doc.HasParseError())
		throw Exceptions::JsonParseError("Error when parsing json. Raw response: " + resp.text);

	for (auto& userAction : doc["actions"].GetArray()) {
		UserAction uaction;
		uaction.activationDate = userAction["activationDate"].GetString();
		uaction.available = userAction["available"].GetBool();
		bool e = userAction["availableDateEnd"].IsNull();
		uaction.availableDateEnd = !userAction["availableDateEnd"].IsNull() ? userAction["availableDateEnd"].GetString() : "";
		uaction.availableDateStart = !userAction["availableDateStart"].IsNull() ? userAction["availableDateStart"].GetString() : "";
		uaction.completionDate = !userAction["completionDate"].IsNull() ? userAction["completionDate"].GetString() : "";
		uaction.description = userAction["description"].GetString();
		for (auto &actionGroup : userAction["groups"].GetArray()) {
			Group agroup;
			agroup.id = actionGroup["id"].GetString();
			agroup.name = actionGroup["name"].GetString();
			uaction.groups.emplace_back(agroup);
		}
		uaction.id = userAction["id"].GetString();
		for (auto& actionImage : userAction["images"].GetArray()) {
			Image aimage;
			aimage.type = actionImage["type"].GetString();
			aimage.url = actionImage["url"].GetString();
			uaction.images.emplace_back(aimage);
		}
		uaction.isBadge = userAction["isBadge"].GetBool();
		uaction.isCompleted = userAction["isCompleted"].GetBool();
		uaction.name = userAction["name"].GetString();
		uaction.obj = !userAction["obj"].IsNull() ? userAction["obj"].GetString() : "";
		uaction.profileId = userAction["profileId"].GetString();
		uaction.spaceId = userAction["spaceId"].GetString();
		uaction.statCompletionThreshold = !userAction["statCompletionThreshold"].IsNull() ? userAction["statCompletionThreshold"].GetString() : "";
		uaction.statName = !userAction["statName"].IsNull() ? userAction["statName"].GetString() : "";
		uaction.value = userAction["value"].GetInt();
		uaction.xp = userAction["xp"].GetInt();
		ua.emplace_back(uaction);
	}
	return ua;

}
R6pp::UserActions R6pp::R6Connection::GetUserActions(const SearchedUser &user) {
	if (user.profileId.empty())
		throw Exceptions::InputArgumentsInvalid("Missing user profileID");

		return this->GetUserActionsByID(user.profileId);
}

R6pp::UserActions R6pp::R6Connection::GetUserActions(std::string username, R6pp::PlatformType platform){
	if (username.empty())
		throw Exceptions::InputArgumentsInvalid("Missing username");

		auto user = this->SearchForUser(username, platform);
		return this->GetUserActionsByID(user[0].profileId);
	
}

R6pp::UserOperatorStats R6pp::R6Connection::GetUserOperatorStatsByID(std::string profileID) {
	if (profileID.empty())
		throw Exceptions::InputArgumentsInvalid("Missing user profileID");

	auto resp =
		cpr::Get(cpr::Url{ "https://public-ubiservices.ubi.com/v1/spaces/5172a557-50b5-4665-b7db-e3f2e8c5041d/sandboxes/OSBOR_PC_LNCH_A/playerstats2/statistics?populations=" + profileID + "&statistics=" +	// Such a beauty
			"operatorpvp_smoke_poisongaskill,operatorpvp_timeplayed,operatorpvp_roundwon,operatorpvp_roundlost,operatorpvp_kills,operatorpvp_death,operatorpvp_mute_gadgetjammed" +
			",operatorpvp_sledge_hammerhole,operatorpvp_thatcher_gadgetdestroywithemp,operatorpvp_castle_kevlarbarricadedeployed,operatorpvp_ash_bonfirewallbreached,operatorpvp_pulse_heartbeatspot" +
			",operatorpvp_thermite_reinforcementbreached,operatorpvp_doc_teammaterevive,operatorpvp_rook_armortakenteammate,operatorpvp_twitch_gadgetdestroybyshockdrone,operatorpvp_montagne_shieldblockdamage" +
			",operatorpvp_glaz_sniperkill,operatorpvp_fuze_clusterchargekill,operatorpvp_kapkan_boobytrapkill,operatorpvp_tachanka_turretkill,operatorpvp_blitz_flashedenemy,operatorpvp_iq_gadgetspotbyef" +
			",operatorpvp_jager_gadgetdestroybycatcher,operatorpvp_bandit_batterykill,operatorpvp_buck_kill,operatorpvp_frost_dbno,operatorpvp_blackbeard_gunshieldblockdamage,operatorpvp_valkyrie_camdeployed" +
			",operatorpvp_capitao_lethaldartkills,operatorpvp_caveira_interrogations,operatorpvp_hibana_detonate_projectile,operatorpvp_echo_enemy_sonicburst_affected,operatorpvp_cazador_assist_kill" +
			",operatorpvp_black_mirror_gadget_deployed,operatorpvp_dazzler_gadget_detonate,operatorpvp_caltrop_enemy_affected,operatorpvp_concussionmine_detonate,operatorpvp_concussiongrenade_detonate" +
			",operatorpvp_phoneshacked,operatorpvp_attackerdrone_diminishedrealitymode,operatorpvp_tagger_tagdevice_spot,operatorpvp_rush_adrenalinerush,operatorpvp_barrage_killswithturret" +
			",operatorpvp_deceiver_revealedattackers,operatorpvp_maverick_wallbreached,operatorpvp_clash_sloweddown,operatorpvp_mozzie_droneshacked,operatorpvp_gridlock_traxdeployed,operatorpvp_nokk_cameras_deceived" +
			",operatorpvp_warden_kills_during_ability" },
			cpr::Header{ {"Authorization","Ubi_v1 t=" + this->_authHeader.ticket},
						 {"Accept","application/json"},
						 {"Ubi-AppId","39baebad-39e5-4552-8c25-2c9b919064e2" } },
			cpr::VerifySsl(VERIFYSSL));

	if (resp.error || resp.status_code != 200)
		throw Exceptions::FatalConnectionError("Request error when retrieving user operator stats. \"" + resp.error.message + "\" HTTP status code " + std::to_string(resp.status_code));

	R6pp::UserOperatorStats uos;
	rapidjson::Document doc;
	doc.Parse(resp.text.c_str());


	if (doc.HasParseError())
		throw Exceptions::JsonParseError("Error when parsing json. Raw response: " + resp.text);

	auto stats = doc["results"][profileID.c_str()].GetObject();

	for (auto& op : Operators::Operators) {
		UserOperatorStat uoStat;
		uoStat.baseOperator = op;
		std::string deathString = "operatorpvp_death:" + op.firstNum + ":" + op.secondNum + ":infinite";
		if (stats.HasMember(deathString.c_str())) 
			uoStat.deaths = stats[deathString.c_str()].GetInt();		
		else
			uoStat.deaths = 0;
		

		std::string killString = "operatorpvp_kills:" + op.firstNum + ":" + op.secondNum + ":infinite";
		if (stats.HasMember(killString.c_str()))
			uoStat.kills = stats[killString.c_str()].GetInt();
		else
			uoStat.kills = 0;

		std::string roundLostString = "operatorpvp_roundlost:" + op.firstNum + ":" + op.secondNum + ":infinite";
		if (stats.HasMember(roundLostString.c_str()))
			uoStat.roundlost = stats[roundLostString.c_str()].GetInt();
		else
			uoStat.roundlost = 0;

		std::string roundWonString = "operatorpvp_roundwon:" + op.firstNum + ":" + op.secondNum + ":infinite";
		if (stats.HasMember(roundWonString.c_str()))
			uoStat.roundwon = stats[roundWonString.c_str()].GetInt();
		else
			uoStat.roundwon = 0;
			
		std::string timeplayedString = "operatorpvp_timeplayed:" + op.firstNum + ":" + op.secondNum + ":infinite";
		if (stats.HasMember(timeplayedString.c_str()))
			uoStat.timeplayed = stats[timeplayedString.c_str()].GetInt();
		else
			uoStat.timeplayed = 0;

		std::string specialString = "operatorpvp_"+ op.unique + ":" + op.firstNum + ":" + op.secondNum + ":infinite";
		if (stats.HasMember(specialString.c_str()))
			uoStat.unique = stats[specialString.c_str()].GetInt();
		else
			uoStat.unique = 0;
		uos.emplace_back(uoStat);
	}
	return uos;
}

R6pp::UserOperatorStats R6pp::R6Connection::GetUserOperatorStats(std::string username, R6pp::PlatformType platform) {
	if (username.empty())
		throw Exceptions::InputArgumentsInvalid("Missing username");

	auto user = this->SearchForUser(username, platform)[0];
	return this->GetUserOperatorStatsByID(user.profileId);
}

R6pp::UserOperatorStats  R6pp::R6Connection::GetUserOperatorStats(const SearchedUser &user) {
	if (user.profileId.empty())
		throw Exceptions::InputArgumentsInvalid("Missing profileID");

	return this->GetUserOperatorStatsByID(user.profileId);
}

R6pp::UserOperatorStat R6pp::R6Connection::GetUserOperatorStatByID(std::string profileID, const R6pp::Operators::BaseOperator &userOperator) {
	if (profileID.empty())
		throw Exceptions::InputArgumentsInvalid("Missing user profileID");
	
	auto resp =
		cpr::Get(cpr::Url{ "https://public-ubiservices.ubi.com/v1/spaces/5172a557-50b5-4665-b7db-e3f2e8c5041d/sandboxes/OSBOR_PC_LNCH_A/playerstats2/statistics?populations=" + profileID + "&statistics=operatorpvp_" + userOperator.unique + 
			",operatorpvp_roundlost,operatorpvp_roundwon,operatorpvp_kills,operatorpvp_deaths,operatorpvp_timeplayed"},
			cpr::Header{ {"Authorization","Ubi_v1 t=" + this->_authHeader.ticket},
						 {"Accept","application/json"},
						 {"Ubi-AppId","39baebad-39e5-4552-8c25-2c9b919064e2" } },
			cpr::VerifySsl(VERIFYSSL));

	if (resp.error || resp.status_code != 200)
		throw Exceptions::FatalConnectionError("Request error when retrieving user operator stat. \"" + resp.error.message + "\" HTTP status code " + std::to_string(resp.status_code));

	
	rapidjson::Document doc;
	doc.Parse(resp.text.c_str());


	if (doc.HasParseError())
		throw Exceptions::JsonParseError("Error when parsing json. Raw response: " + resp.text);

	auto stats = doc["results"][profileID.c_str()].GetObject();

	
		UserOperatorStat uoStat;
		uoStat.baseOperator = userOperator;
		
		std::string deathString = "operatorpvp_death:" + userOperator.firstNum + ":" + userOperator.secondNum + ":infinite";
		if (stats.HasMember(deathString.c_str()))
			uoStat.deaths = stats[deathString.c_str()].GetInt();
		else
			uoStat.deaths = 0;


		std::string killString = "operatorpvp_kills:" + userOperator.firstNum + ":" + userOperator.secondNum + ":infinite";
		if (stats.HasMember(killString.c_str()))
			uoStat.kills = stats[killString.c_str()].GetInt();
		else
			uoStat.kills = 0;

		std::string roundLostString = "operatorpvp_roundlost:" + userOperator.firstNum + ":" + userOperator.secondNum + ":infinite";
		if (stats.HasMember(roundLostString.c_str()))
			uoStat.roundlost = stats[roundLostString.c_str()].GetInt();
		else
			uoStat.roundlost = 0;

		std::string roundWonString = "operatorpvp_roundwon:" + userOperator.firstNum + ":" + userOperator.secondNum + ":infinite";
		if (stats.HasMember(roundWonString.c_str()))
			uoStat.roundwon = stats[roundWonString.c_str()].GetInt();
		else
			uoStat.roundwon = 0;

		std::string timeplayedString = "operatorpvp_timeplayed:" + userOperator.firstNum + ":" + userOperator.secondNum + ":infinite";
		if (stats.HasMember(timeplayedString.c_str()))
			uoStat.timeplayed = stats[timeplayedString.c_str()].GetInt();
		else
			uoStat.timeplayed = 0;

		std::string specialString = "operatorpvp_" + userOperator.unique + ":" + userOperator.firstNum + ":" + userOperator.secondNum + ":infinite";
		if (stats.HasMember(specialString.c_str()))
			uoStat.unique = stats[specialString.c_str()].GetInt();
		else
			uoStat.unique = 0;
		
		return uoStat;
}

R6pp::UserOperatorStat R6pp::R6Connection::GetUserOperatorStat(const R6pp::SearchedUser &user, const R6pp::Operators::BaseOperator &userOperator) {
	if (user.profileId.empty())
		throw Exceptions::InputArgumentsInvalid("Missing profileID");

	return this->GetUserOperatorStatByID(user.profileId, userOperator);
}

R6pp::UserOperatorStat R6pp::R6Connection::GetUserOperatorStat(std::string username, const R6pp::Operators::BaseOperator &userOperator, R6pp::PlatformType platformType) {
	if (username.empty())
		throw Exceptions::InputArgumentsInvalid("Missing profileID");

	auto user = this->SearchForUser(username, platformType)[0];
	return this->GetUserOperatorStatByID(user.profileId, userOperator);
}

R6pp::UserWeaponStats R6pp::R6Connection::GetUserWeaponStatsByID(std::string profileID) {
	if (profileID.empty())
		throw Exceptions::InputArgumentsInvalid("Missing profileID");

	auto resp =
		cpr::Get(cpr::Url{ "https://public-ubiservices.ubi.com/v1/spaces/5172a557-50b5-4665-b7db-e3f2e8c5041d/sandboxes/OSBOR_PC_LNCH_A/playerstats2/statistics?populations=" + profileID + "&statistics=weapontypepvp_kills,weapontypepvp_headshot,weapontypepvp_bulletfired,weapontypepvp_bullethit" },
			cpr::Header{ {"Authorization","Ubi_v1 t=" + this->_authHeader.ticket},
						 {"Accept","application/json"},
						 {"Ubi-AppId","39baebad-39e5-4552-8c25-2c9b919064e2" } },
			cpr::VerifySsl(VERIFYSSL));

	if (resp.error || resp.status_code != 200)
		throw Exceptions::FatalConnectionError("Request error when retrieving user weapon stats. \"" + resp.error.message + "\" HTTP status code " + std::to_string(resp.status_code));

	UserWeaponStats uws;

	rapidjson::Document doc;
	doc.Parse(resp.text.c_str());


	if (doc.HasParseError())
		throw Exceptions::JsonParseError("Error when parsing json. Raw response: " + resp.text);

	auto stats = doc["results"][profileID.c_str()].GetObject();

	for (auto& weapon : Weapons) {
		UserWeaponStat uwstat;
		uwstat.weapon = weapon;

		std::string bulletfiredstring = "weapontypepvp_bulletfired:" + std::to_string(weapon.number) + ":infinite";
		if (stats.HasMember(bulletfiredstring.c_str()))
			uwstat.bulletfired = stats[bulletfiredstring.c_str()].GetInt();
		else
			uwstat.bulletfired = 0;

		std::string bullethitstring = "weapontypepvp_bullethit:" + std::to_string(weapon.number) + ":infinite";
		if (stats.HasMember(bullethitstring.c_str()))
			uwstat.bullethit = stats[bullethitstring.c_str()].GetInt();
		else
			uwstat.bullethit = 0;

		std::string headshotstring = "weapontypepvp_headshot:" + std::to_string(weapon.number) + ":infinite";
		if (stats.HasMember(headshotstring.c_str()))
			uwstat.headshot = stats[headshotstring.c_str()].GetInt();
		else
			uwstat.headshot = 0;

		std::string killsstring = "weapontypepvp_kills:" + std::to_string(weapon.number) + ":infinite";
		if (stats.HasMember(killsstring.c_str()))
			uwstat.kills = stats[killsstring.c_str()].GetInt();
		else
			uwstat.kills = 0;
		uws.emplace_back(uwstat);
	}
	return uws;
}

R6pp::UserWeaponStats R6pp::R6Connection::GetUserWeaponStats(const SearchedUser &user) {
	if (user.profileId.empty())
		throw Exceptions::InputArgumentsInvalid("Missing profileID");

	return this->GetUserWeaponStatsByID(user.profileId);
}

R6pp::UserWeaponStats R6pp::R6Connection::GetUserWeaponStats(std::string username, R6pp::PlatformType platformType) {
	if (username.empty())
		throw Exceptions::InputArgumentsInvalid("Missing username");

	auto user = this->SearchForUser(username, platformType)[0];
	return this->GetUserWeaponStatsByID(user.profileId);
}

R6pp::UserWeaponStat R6pp::R6Connection::GetUserWeaponStatByID(std::string profileID, const BaseWeapon &userWeapon) {
		if (profileID.empty())
			throw Exceptions::InputArgumentsInvalid("Missing profileID");

		auto resp =
			cpr::Get(cpr::Url{ "https://public-ubiservices.ubi.com/v1/spaces/5172a557-50b5-4665-b7db-e3f2e8c5041d/sandboxes/OSBOR_PC_LNCH_A/playerstats2/statistics?populations=" + profileID + "&statistics=weapontypepvp_kills,weapontypepvp_headshot,weapontypepvp_bulletfired,weapontypepvp_bullethit" },
				cpr::Header{ {"Authorization","Ubi_v1 t=" + this->_authHeader.ticket},
							 {"Accept","application/json"},
							 {"Ubi-AppId","39baebad-39e5-4552-8c25-2c9b919064e2" } },
				cpr::VerifySsl(VERIFYSSL));

		if (resp.error || resp.status_code != 200)
			throw Exceptions::FatalConnectionError("Request error when retrieving user weapon stat. \"" + resp.error.message + "\" HTTP status code " + std::to_string(resp.status_code));

		

		rapidjson::Document doc;
		doc.Parse(resp.text.c_str());


		if (doc.HasParseError())
			throw Exceptions::JsonParseError("Error when parsing json. Raw response: " + resp.text);

		auto stats = doc["results"][profileID.c_str()].GetObject();

			UserWeaponStat uwstat;
			uwstat.weapon = userWeapon;

			std::string bulletfiredstring = "weapontypepvp_bulletfired:" + std::to_string(userWeapon.number) + ":infinite";
			if (stats.HasMember(bulletfiredstring.c_str()))
				uwstat.bulletfired = stats[bulletfiredstring.c_str()].GetInt();
			else
				uwstat.bulletfired = 0;

			std::string bullethitstring = "weapontypepvp_bullethit:" + std::to_string(userWeapon.number) + ":infinite";
			if (stats.HasMember(bullethitstring.c_str()))
				uwstat.bullethit = stats[bullethitstring.c_str()].GetInt();
			else
				uwstat.bullethit = 0;

			std::string headshotstring = "weapontypepvp_headshot:" + std::to_string(userWeapon.number) + ":infinite";
			if (stats.HasMember(headshotstring.c_str()))
				uwstat.headshot = stats[headshotstring.c_str()].GetInt();
			else
				uwstat.headshot = 0;

			std::string killsstring = "weapontypepvp_kills:" + std::to_string(userWeapon.number) + ":infinite";
			if (stats.HasMember(killsstring.c_str()))
				uwstat.kills = stats[killsstring.c_str()].GetInt();
			else
				uwstat.kills = 0;
			
		
		return uwstat;
}

R6pp::UserWeaponStat R6pp::R6Connection::GetUserWeaponStat(const SearchedUser &user, const BaseWeapon &userWeapon) {
	if (user.profileId.empty())
		throw Exceptions::InputArgumentsInvalid("Missing profileID");

	return this->GetUserWeaponStatByID(user.profileId, userWeapon);
}

R6pp::UserWeaponStat R6pp::R6Connection::GetUserWeaponStat(std::string username, const BaseWeapon &userWeapon, R6pp::PlatformType platformType) {
	if (username.empty())
		throw Exceptions::InputArgumentsInvalid("Missing profileID");

	auto user = this->SearchForUser(username, platformType)[0];
	return this->GetUserWeaponStatByID(user.profileId, userWeapon);
}

R6pp::UserSeasonStat R6pp::R6Connection::GetUserSeasonStatByID(std::string profileID, const BaseSeason &Season, const Region &region) {
	if (profileID.empty())
		throw Exceptions::InputArgumentsInvalid("Missing profileID");

	auto resp =
		cpr::Get(cpr::Url{ "https://public-ubiservices.ubi.com/v1/spaces/5172a557-50b5-4665-b7db-e3f2e8c5041d/sandboxes/OSBOR_PC_LNCH_A/r6karma/players?board_id=pvp_ranked&profile_ids=" + profileID + "&region_id=" + RegionToString(region) + "&season_id=" + std::to_string(Season.SeasonID) },
			cpr::Header{ {"Authorization","Ubi_v1 t=" + this->_authHeader.ticket},
							 {"Accept","application/json"},
							 {"Ubi-AppId","39baebad-39e5-4552-8c25-2c9b919064e2" } },
			cpr::VerifySsl(VERIFYSSL));


	if (resp.error || resp.status_code != 200)
		throw Exceptions::FatalConnectionError("Request error when retrieving user season stat. \"" + resp.error.message + "\" HTTP status code " + std::to_string(resp.status_code));


	UserSeasonStat uss;
	rapidjson::Document doc;
	doc.Parse(resp.text.c_str());


	if (doc.HasParseError())
		throw Exceptions::JsonParseError("Error when parsing json. Raw response: " + resp.text);

	auto stat = doc["players"][profileID.c_str()].GetObject();
	
	uss.abandons = stat["abandons"].GetInt();
	uss.board_id = stat["board_id"].GetString();
	uss.deaths = stat["deaths"].GetInt();
	uss.kills = stat["kills"].GetInt();
	uss.last_match_mmr_change = stat["last_match_mmr_change"].GetDouble();
	uss.last_match_result = stat["last_match_result"].GetInt();
	uss.last_match_skill_mean_change = stat["last_match_skill_mean_change"].GetDouble();
	uss.last_match_skill_stdev_change = stat["last_match_skill_stdev_change"].GetDouble();
	uss.losses = stat["losses"].GetInt();
	uss.max_mmr = stat["max_mmr"].GetDouble();
	uss.max_rank = stat["max_rank"].GetInt();
	uss.mmr = stat["mmr"].GetDouble();
	uss.next_rank_mmr = stat["next_rank_mmr"].GetDouble();
	uss.previous_rank_mmr = stat["previous_rank_mmr"].GetDouble();
	uss.profile_id = stat["profile_id"].GetString();
	uss.rank = stat["rank"].GetInt();
	uss.region = stat["region"].GetString();
	uss.typeRegion = StringToRegion(uss.region.c_str());
	uss.season = stat["season"].GetInt();
	uss.skill_mean = stat["skill_mean"].GetDouble();
	uss.skill_stdev = stat["skill_stdev"].GetDouble();
	uss.update_time = stat["update_time"].GetString();
	uss.wins = stat["wins"].GetInt();
	return uss;
}

R6pp::UserSeasonStat R6pp::R6Connection::GetUserSeasonStat(const SearchedUser &user, const BaseSeason &season,const Region &region) {
	if (user.profileId.empty())
		throw Exceptions::InputArgumentsInvalid("Missing profileID");

	return this->GetUserSeasonStatByID(user.profileId,season,region);
}

R6pp::UserSeasonStat R6pp::R6Connection::GetUserSeasonStat(std::string username, const BaseSeason &season, const Region &region, R6pp::PlatformType type) {
	if (username.empty())
		throw Exceptions::InputArgumentsInvalid("Missing username");

	auto user = this->SearchForUser(username, type)[0];
	return this->GetUserSeasonStatByID(user.profileId, season, region);
}

R6pp::UserGametypeStat R6pp::R6Connection::GetUserGametypeStatByID(std::string profileID) {
	if (profileID.empty())
		throw Exceptions::InputArgumentsInvalid("Missing profileID");

	auto resp =
		cpr::Get(cpr::Url{ "https://public-ubiservices.ubi.com/v1/spaces/5172a557-50b5-4665-b7db-e3f2e8c5041d/sandboxes/OSBOR_PC_LNCH_A/playerstats2/statistics?populations=" + profileID + "&statistics=casualpvp_timeplayed,"
			 + "casualpvp_matchwon,casualpvp_matchlost,casualpvp_matchplayed,casualpvp_kills,casualpvp_death,rankedpvp_matchwon,rankedpvp_matchlost,rankedpvp_timeplayed,rankedpvp_matchplayed,rankedpvp_kills,rankedpvp_death" },
			cpr::Header{ {"Authorization","Ubi_v1 t=" + this->_authHeader.ticket},
							 {"Accept","application/json"},
							 {"Ubi-AppId","39baebad-39e5-4552-8c25-2c9b919064e2" } },
			cpr::VerifySsl(VERIFYSSL));

	if (resp.error || resp.status_code != 200)
		throw Exceptions::FatalConnectionError("Request error when retrieving user operator gamemode stats. \"" + resp.error.message + "\" HTTP status code " + std::to_string(resp.status_code));

	R6pp::UserGametypeStat ugs;
	rapidjson::Document doc;
	doc.Parse(resp.text.c_str());

	
	if (doc.HasParseError())
		throw Exceptions::JsonParseError("Error when parsing json. Raw response: " + resp.text);

	auto stat = doc["results"][profileID.c_str()].GetObject();

	ugs.Casual.death = stat["casualpvp_death:infinite"].GetInt();
	ugs.Casual.kills = stat["casualpvp_kills:infinite"].GetInt();
	ugs.Casual.matchlost = stat["casualpvp_matchlost:infinite"].GetInt();
	ugs.Casual.matchplayed = stat["casualpvp_matchplayed:infinite"].GetInt();
	ugs.Casual.matchwon = stat["casualpvp_matchwon:infinite"].GetInt();
	ugs.Casual.timeplayed = stat["casualpvp_timeplayed:infinite"].GetInt64();

	ugs.Ranked.death = stat["rankedpvp_death:infinite"].GetInt();
	ugs.Ranked.kills = stat["rankedpvp_kills:infinite"].GetInt();
	ugs.Ranked.matchlost = stat["rankedpvp_matchlost:infinite"].GetInt();
	ugs.Ranked.matchplayed = stat["rankedpvp_matchplayed:infinite"].GetInt();
	ugs.Ranked.matchwon = stat["rankedpvp_matchwon:infinite"].GetInt();
	ugs.Ranked.timeplayed = stat["rankedpvp_timeplayed:infinite"].GetInt64();

	return ugs;
}

R6pp::UserGametypeStat R6pp::R6Connection::GetUserGametypeStat(const SearchedUser &user) {
	if (user.profileId.empty())
		throw Exceptions::InputArgumentsInvalid("Missing profileID");

	return this->GetUserGametypeStatByID(user.profileId);
}

R6pp::UserGametypeStat R6pp::R6Connection::GetUserGametypeStat(std::string username, PlatformType platform) {
	if (username.empty())
		throw Exceptions::InputArgumentsInvalid("Missing username");

	auto user = this->SearchForUser(username, platform)[0];
	return this->GetUserGametypeStatByID(user.profileId);
}

R6pp::UserGeneralStat R6pp::R6Connection::GetUserGeneralStatByID(std::string profileID) {
	if (profileID.empty())
		throw Exceptions::InputArgumentsInvalid("Missing profileID");

	auto resp =
		cpr::Get(cpr::Url{"https://public-ubiservices.ubi.com/v1/spaces/5172a557-50b5-4665-b7db-e3f2e8c5041d/sandboxes/OSBOR_PC_LNCH_A/playerstats2/statistics?populations=" + profileID
			 +"&statistics=generalpvp_timeplayed,generalpvp_matchplayed,generalpvp_killassists,generalpvp_revive,generalpvp_headshot,generalpvp_penetrationkills,generalpvp_meleekills,"
			+ "generalpvp_matchwon,generalpvp_matchlost,generalpvp_kills,generalpvp_death,generalpvp_bullethit,generalpvp_bulletfired"},
			cpr::Header{ {"Authorization","Ubi_v1 t=" + this->_authHeader.ticket},
							 {"Accept","application/json"},
							 {"Ubi-AppId","39baebad-39e5-4552-8c25-2c9b919064e2" } },
			cpr::VerifySsl(VERIFYSSL));

	if (resp.error || resp.status_code != 200)
		throw Exceptions::FatalConnectionError("Request error when retrieving user operator general stat. \"" + resp.error.message + "\" HTTP status code " + std::to_string(resp.status_code));

	R6pp::UserGeneralStat ugs;
	rapidjson::Document doc;
	doc.Parse(resp.text.c_str());


	if (doc.HasParseError())
		throw Exceptions::JsonParseError("Error when parsing json. Raw response: " + resp.text);

	auto stat = doc["results"][profileID.c_str()].GetObject();

	ugs.bulletfired = stat["generalpvp_bulletfired:infinite"].GetInt();
	ugs.bullethit = stat["generalpvp_bullethit:infinite"].GetInt();
	ugs.death = stat["generalpvp_death:infinite"].GetInt();
	ugs.headshot = stat["generalpvp_headshot:infinite"].GetInt();
	ugs.killassists = stat["generalpvp_killassists:infinite"].GetInt();
	ugs.kills = stat["generalpvp_kills:infinite"].GetInt();
	ugs.matchlost = stat["generalpvp_matchlost:infinite"].GetInt();
	ugs.matchplayed = stat["generalpvp_matchplayed:infinite"].GetInt();
	ugs.matchwon = stat["generalpvp_matchwon:infinite"].GetInt();
	ugs.meleekills = stat["generalpvp_meleekills:infinite"].GetInt();
	ugs.penetrationkills = stat["generalpvp_penetrationkills:infinite"].GetInt();
	ugs.revive = stat["generalpvp_revive:infinite"].GetInt();
	ugs.timeplayed = stat["generalpvp_timeplayed:infinite"].GetInt64();

	return ugs;

}

R6pp::UserGeneralStat R6pp::R6Connection::GetUserGeneralStat(const SearchedUser &user) {
	if (user.profileId.empty())
		throw Exceptions::InputArgumentsInvalid("Missing profileID");

	return this->GetUserGeneralStatByID(user.profileId);
}

R6pp::UserGeneralStat R6pp::R6Connection::GetUserGeneralStat(std::string username, PlatformType platform) {
	if (username.empty())
		throw Exceptions::InputArgumentsInvalid("Missing username");

	auto user = this->SearchForUser(username, platform)[0];
	return this->GetUserGeneralStatByID(user.profileId);
}

R6pp::UserGamemodeStat R6pp::R6Connection::GetUserGamemodeStatByID(std::string profileID) {
	if (profileID.empty())
		throw Exceptions::InputArgumentsInvalid("Missing profileID");

	auto resp=
		cpr::Get(cpr::Url{"https://public-ubiservices.ubi.com/v1/spaces/5172a557-50b5-4665-b7db-e3f2e8c5041d/sandboxes/OSBOR_PC_LNCH_A/playerstats2/statistics?populations="+profileID+
			"&statistics=secureareapvp_matchwon,secureareapvp_matchlost,secureareapvp_matchplayed,secureareapvp_bestscore,rescuehostagepvp_matchwon,rescuehostagepvp_matchlost"+
			",rescuehostagepvp_matchplayed,rescuehostagepvp_bestscore,plantbombpvp_matchwon,plantbombpvp_matchlost,plantbombpvp_matchplayed,plantbombpvp_bestscore"},
			cpr::Header{ {"Authorization","Ubi_v1 t=" + this->_authHeader.ticket},
							 {"Accept","application/json"},
							 {"Ubi-AppId","39baebad-39e5-4552-8c25-2c9b919064e2" } },
			cpr::VerifySsl(VERIFYSSL));

	if (resp.error || resp.status_code != 200)
		throw Exceptions::FatalConnectionError("Request error when retrieving user operator gamemode stat. \"" + resp.error.message + "\" HTTP status code " + std::to_string(resp.status_code));

	R6pp::UserGamemodeStat ugs;
	rapidjson::Document doc;
	doc.Parse(resp.text.c_str());


	if (doc.HasParseError())
		throw Exceptions::JsonParseError("Error when parsing json. Raw response: " + resp.text);

	auto stat = doc["results"][profileID.c_str()].GetObject();

	ugs.PlantBomb.bestscore = stat["plantbombpvp_bestscore:infinite"].GetInt();
	ugs.PlantBomb.matchlost = stat["plantbombpvp_matchlost:infinite"].GetInt();
	ugs.PlantBomb.matchplayed = stat["plantbombpvp_matchplayed:infinite"].GetInt();
	ugs.PlantBomb.matchwon = stat["plantbombpvp_matchwon:infinite"].GetInt();

	ugs.RescueHostage.bestscore = stat["rescuehostagepvp_bestscore:infinite"].GetInt();
	ugs.RescueHostage.matchlost = stat["rescuehostagepvp_matchlost:infinite"].GetInt();
	ugs.RescueHostage.matchplayed = stat["rescuehostagepvp_matchplayed:infinite"].GetInt();
	ugs.RescueHostage.matchwon = stat["rescuehostagepvp_matchwon:infinite"].GetInt();

	ugs.SecureArea.bestscore = stat["secureareapvp_bestscore:infinite"].GetInt();
	ugs.SecureArea.matchlost = stat["secureareapvp_matchlost:infinite"].GetInt();
	ugs.SecureArea.matchplayed = stat["secureareapvp_matchplayed:infinite"].GetInt();
	ugs.SecureArea.matchwon = stat["secureareapvp_matchwon:infinite"].GetInt();

	return ugs;
}
R6pp::UserGamemodeStat R6pp::R6Connection::GetUserGamemodeStat(const SearchedUser &user) {
	if (user.profileId.empty())
		throw Exceptions::InputArgumentsInvalid("Missing profileID");

	return this->GetUserGamemodeStatByID(user.profileId);
}
R6pp::UserGamemodeStat R6pp::R6Connection::GetUserGamemodeStat(std::string username, PlatformType platform) {
	if (username.empty())
		throw Exceptions::InputArgumentsInvalid("Missing username");

	auto user = this->SearchForUser(username, platform)[0];
	return this->GetUserGamemodeStatByID(user.profileId);
}

R6pp::PlayerProfile R6pp::R6Connection::GetPlayerProfileByID(std::string profileID) {
	if (profileID.empty())
		throw Exceptions::InputArgumentsInvalid("Missing profileID");

	auto resp = 
		cpr::Get(cpr::Url{"https://public-ubiservices.ubi.com/v1/spaces/5172a557-50b5-4665-b7db-e3f2e8c5041d/sandboxes/OSBOR_PC_LNCH_A/r6playerprofile/playerprofile/progressions?profile_ids=" + profileID},
			cpr::Header{ {"Authorization","Ubi_v1 t=" + this->_authHeader.ticket},
							 {"Accept","application/json"},
							 {"Ubi-AppId","39baebad-39e5-4552-8c25-2c9b919064e2" } },
			cpr::VerifySsl(VERIFYSSL));

	if (resp.error || resp.status_code != 200)
		throw Exceptions::FatalConnectionError("Request error when retrieving user operator gamemode stat. \"" + resp.error.message + "\" HTTP status code " + std::to_string(resp.status_code));

	R6pp::PlayerProfile pp;
	rapidjson::Document doc;
	doc.Parse(resp.text.c_str());


	if (doc.HasParseError())
		throw Exceptions::JsonParseError("Error when parsing json. Raw response: " + resp.text);

	auto stat = doc["player_profiles"].GetArray()[0].GetObject();

	pp.level = stat["level"].GetInt();
	pp.lootbox_probability = stat["lootbox_probability"].GetInt();
	pp.profile_id = stat["profile_id"].GetString();
	pp.xp = stat["xp"].GetInt();

	return pp;
}

R6pp::PlayerProfile R6pp::R6Connection::GetPlayerProfile(const SearchedUser &user) {
	if (user.profileId.empty())
		throw Exceptions::InputArgumentsInvalid("Missing profileID");

	return this->GetPlayerProfileByID(user.profileId);
}

R6pp::PlayerProfile R6pp::R6Connection::GetPlayerProfile(std::string username, PlatformType platform) {
	if (username.empty())
		throw Exceptions::InputArgumentsInvalid("Missing username");

	auto user = this->SearchForUser(username, platform)[0];
	return this->GetPlayerProfileByID(user.profileId);
}




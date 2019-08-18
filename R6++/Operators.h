#pragma once
#include <string>
#include <vector>

/*

https://docs.google.com/spreadsheets/d/1wxuBDPzSdapV4kg4tTh6eaXyhSvxAksO52WC4TVM-0U/

*/

namespace R6pp {
	namespace Operators {
		struct BaseOperator {
			std::string firstNum;
			std::string secondNum;
			std::string name; // Possibly unused
			std::string unique;
			BaseOperator(std::string first, std::string second, std::string name, std::string unique) {
				this->firstNum = first;
				this->secondNum = second;
				this->name = name;
				this->unique = unique;
			}
			BaseOperator() {};
			BaseOperator(std::string first, std::string second, std::string unique) {
				this->firstNum = first;
				this->secondNum = second;
				this->unique = unique;
			}
		};

			BaseOperator SAS(		"1","1", "SAS RECRUIT",	"");
			BaseOperator FBI(		"1","2", "FBI RECRUIT",	"");
			BaseOperator GIGN(		"1","3", "GIGN RECRUIT","");
			BaseOperator GSG9(		"1","5", "GSG9 RECRUIT","");

			BaseOperator Smoke(		"2","1", "SMOKE",		"smoke_poisongaskill");
			BaseOperator Castle(	"2","2", "CASTLE",		"castle_kevlarbarricaded eployed");		
			BaseOperator Doc(		"2","3", "DOC",			"doc_teammaterevive");
			BaseOperator Glaz(		"2","4", "GLAZ",		"glaz_sniperkill");
			BaseOperator Blitz(		"2","5", "BLITZ",		"blitz_flashedenemy");
			BaseOperator Buck(		"2","6", "BUCK",		"buck_kill");
			BaseOperator Blackbeard("2","7", "BLACKBEARD",	"blackbeard_gunshieldblockdamage");
			BaseOperator Capitao(	"2","8", "CAPITAO",		"capitao_lethaldartkills");
			BaseOperator Hibana(	"2","9", "HIBANA",		"hibana_detonate_projectile");
			BaseOperator Maverik(	"2","10","MAVERIK",		"maverick_wallbreached");
			BaseOperator Nomad(		"2","11","NOMAD",		""); // NOT IMPLEMENTED
			BaseOperator Mozzie(	"2","12","MOZZIE",		"mozzie_droneshacked");
			BaseOperator Nokk(		"2","13","NOKK",		"nokk_cameras_deceived"); // NOT IMPLEMENTED
			BaseOperator Warden(	"2","14","WARDEN",		"warden_kills_during_ability"); // NOT IMPLEMENTED
			BaseOperator Jackal(	"2","A", "JACKAL",		"cazador_assist_kill");
			BaseOperator Ying(		"2","B", "YING",		"dazzler_gadget_detonate");
			BaseOperator Ela(		"2","C", "ELA",			"concussionmine_detibate");
			BaseOperator Dokkaebi(	"2","D", "DOKKAEBI",	"phoneshacked");
			BaseOperator Maestro(	"2","F", "MAESTRO",		"barrage_killswithturret"); // NOT IMPLEMENTED

			BaseOperator Mute(		"3","1", "MUTE",		"mute_gadgetjammed");
			BaseOperator Ash(		"3","2", "ASH",			"ash_bonfirewallbreached");
			BaseOperator Rook(		"3","3", "ROOK",		"rook_armortakenteammate");
			BaseOperator Fuze(		"3","4", "FUZE",		"fuze_clusterchargekill");
			BaseOperator IQ(		"3","5", "IQ",			"iq_gadgetspotbyef");
			BaseOperator Frost(		"3","6", "FROST",		"frost_dbno");
			BaseOperator Valkyrie(	"3","7", "VALKYRIE",	"valkyrie_camdeployed");
			BaseOperator Caveira(	"3","8", "CAVEIRA",		"caveira_interrogations");
			BaseOperator Echo(		"3","9", "ECHO",		"echo_enemy_sonicburst_affected");
			BaseOperator Clash(		"3","10","CLASH",		"clash_slowddown");
			BaseOperator Kaid(		"3","11","KAID",		""); // NOT IMPLEMENTED
			BaseOperator Gridlock(	"3","12","GRIDLOCK",	"gridlock_traxdeployed");
			BaseOperator Mira(		"3","A", "MIRA",		"black_mirror_gadget_deployed");
			BaseOperator Lesion(	"3","B", "LESION",		"caltrop_enemy_affected");
			BaseOperator Zofia(		"3","C", "ZOFIA",		"concussiogrenade_detonate");
			BaseOperator Vigil(		"3","D", "VIGIL",		"attackerdrone_diminishedrealitymode");
			BaseOperator Lion(		"3","E", "LION",		"tagger_tagdevice_spot");
			BaseOperator Alibi(		"3","F", "ALIBI",		"deceiver_revealedattackers");

			BaseOperator Sledge(	"4","1", "SLEDGE",		"sledge_hammerhole");
			BaseOperator Pulse(		"4","2", "PULSE",		"pulse_heartbeatspot");
			BaseOperator Twitch(	"4","3", "TWITCH",		"twitch_gadgetdestroybyshockdrone");
			BaseOperator Kapkan(	"4","4", "KAPKAN",		"kapkan_boobytrapkill");
			BaseOperator Jager(		"4","5", "JAGER",		"jager_gadgetdestroybycatcher");
			BaseOperator Finka(		"4","E", "FINKA",		"rush_adrenalinerush");

			BaseOperator Thatcher(	"5","1", "THACTHER",	"thatcher_gadgetdestroywithemp");
			BaseOperator Thermite(	"5","2", "THERMITE",	"thermite_reinforcementbreached");
			BaseOperator Montagne(	"5","3", "MONTAGNE",	"montagne_shieldblockdamage");
			BaseOperator Tachanka(	"5","4", "TACHANKA",	"tachanka_turretkill");
			BaseOperator Bandit(	"5","5", "BANDIT ",		"bandit_batterykill");


			std::vector<BaseOperator> Operators{
				SAS,
				FBI,
				GIGN,
				GSG9,

				Smoke,
				Castle,
				Doc,
				Glaz,
				Blitz,
				Buck,
				Blackbeard,
				Capitao,
				Hibana,
				Maverik,
				Nomad,
				Mozzie,
				Nokk,
				Warden,
				Jackal,
				Ying,
				Ela,
				Dokkaebi,
				Maestro,

				Mute,
				Ash,
				Rook,
				Fuze,
				IQ,
				Frost,
				Valkyrie,
				Caveira,
				Echo,
				Clash,
				Kaid,
				Gridlock,
				Mira,
				Lesion,
				Zofia,
				Vigil,
				Lion,
				Alibi,

				Sledge,
				Pulse,
				Twitch,
				Kapkan,
				Jager,
				Finka,

				Thatcher,
				Thermite,
				Montagne,
				Tachanka,
				Bandit
			};
	}
}
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
			inline BaseOperator(const std::string &first, const std::string &second, const std::string &name, const std::string &unique) : firstNum(first), secondNum(second), name(name), unique(unique) { }
			inline BaseOperator() {};
			inline BaseOperator(const std::string &first, const std::string &second, const std::string &unique) : firstNum(first), secondNum(second),unique(unique){ }
		};

		static	BaseOperator  SAS("1", "1", "SAS RECRUIT", "");
		static	BaseOperator FBI("1", "2", "FBI RECRUIT", "");
		static	BaseOperator GIGN("1", "3", "GIGN RECRUIT", "");
		static	BaseOperator GSG9("1", "5", "GSG9 RECRUIT", "");

		static	BaseOperator Smoke("2", "1", "SMOKE", "smoke_poisongaskill");
		static	BaseOperator Castle("2", "2", "CASTLE", "castle_kevlarbarricaded eployed");
		static	BaseOperator Doc("2", "3", "DOC", "doc_teammaterevive");
		static	BaseOperator Glaz("2", "4", "GLAZ", "glaz_sniperkill");
		static	BaseOperator Blitz("2", "5", "BLITZ", "blitz_flashedenemy");
		static	BaseOperator Buck("2", "6", "BUCK", "buck_kill");
		static	BaseOperator Blackbeard("2", "7", "BLACKBEARD", "blackbeard_gunshieldblockdamage");
		static	BaseOperator Capitao("2", "8", "CAPITAO", "capitao_lethaldartkills");
		static	BaseOperator Hibana("2", "9", "HIBANA", "hibana_detonate_projectile");
		static	BaseOperator Maverik("2", "10", "MAVERIK", "maverick_wallbreached");
		static	BaseOperator Nomad("2", "11", "NOMAD", ""); // NOT IMPLEMENTED
		static	BaseOperator Mozzie("2", "12", "MOZZIE", "mozzie_droneshacked");
		static	BaseOperator Nokk("2", "13", "NOKK", "nokk_cameras_deceived"); // NOT IMPLEMENTED
		static	BaseOperator Warden("2", "14", "WARDEN", "warden_kills_during_ability"); // NOT IMPLEMENTED
		static	BaseOperator Jackal("2", "A", "JACKAL", "cazador_assist_kill");
		static	BaseOperator Ying("2", "B", "YING", "dazzler_gadget_detonate");
		static	BaseOperator Ela("2", "C", "ELA", "concussionmine_detibate");
		static	BaseOperator Dokkaebi("2", "D", "DOKKAEBI", "phoneshacked");
		static	BaseOperator Maestro("2", "F", "MAESTRO", "barrage_killswithturret"); // NOT IMPLEMENTED

		static	BaseOperator Mute("3", "1", "MUTE", "mute_gadgetjammed");
		static	BaseOperator Ash("3", "2", "ASH", "ash_bonfirewallbreached");
		static	BaseOperator Rook("3", "3", "ROOK", "rook_armortakenteammate");
		static	BaseOperator Fuze("3", "4", "FUZE", "fuze_clusterchargekill");
		static	BaseOperator IQ("3", "5", "IQ", "iq_gadgetspotbyef");
		static	BaseOperator Frost("3", "6", "FROST", "frost_dbno");
		static	BaseOperator Valkyrie("3", "7", "VALKYRIE", "valkyrie_camdeployed");
		static	BaseOperator Caveira("3", "8", "CAVEIRA", "caveira_interrogations");
		static	BaseOperator Echo("3", "9", "ECHO", "echo_enemy_sonicburst_affected");
		static	BaseOperator Clash("3", "10", "CLASH", "clash_slowddown");
		static	BaseOperator Kaid("3", "11", "KAID", ""); // NOT IMPLEMENTED
		static	BaseOperator Gridlock("3", "12", "GRIDLOCK", "gridlock_traxdeployed");
		static	BaseOperator Mira("3", "A", "MIRA", "black_mirror_gadget_deployed");
		static	BaseOperator Lesion("3", "B", "LESION", "caltrop_enemy_affected");
		static	BaseOperator Zofia("3", "C", "ZOFIA", "concussiogrenade_detonate");
		static	BaseOperator Vigil("3", "D", "VIGIL", "attackerdrone_diminishedrealitymode");
		static	BaseOperator Lion("3", "E", "LION", "tagger_tagdevice_spot");
		static	BaseOperator Alibi("3", "F", "ALIBI", "deceiver_revealedattackers");

		static	BaseOperator Sledge("4", "1", "SLEDGE", "sledge_hammerhole");
		static	BaseOperator Pulse("4", "2", "PULSE", "pulse_heartbeatspot");
		static	BaseOperator Twitch("4", "3", "TWITCH", "twitch_gadgetdestroybyshockdrone");
		static	BaseOperator Kapkan("4", "4", "KAPKAN", "kapkan_boobytrapkill");
		static	BaseOperator Jager("4", "5", "JAGER", "jager_gadgetdestroybycatcher");
		static	BaseOperator Finka("4", "E", "FINKA", "rush_adrenalinerush");

		static	BaseOperator Thatcher("5", "1", "THACTHER", "thatcher_gadgetdestroywithemp");
		static	BaseOperator Thermite("5", "2", "THERMITE", "thermite_reinforcementbreached");
		static	BaseOperator Montagne("5", "3", "MONTAGNE", "montagne_shieldblockdamage");
		static	BaseOperator Tachanka("5", "4", "TACHANKA", "tachanka_turretkill");
		static	BaseOperator Bandit("5", "5", "BANDIT ", "bandit_batterykill");


		static std::vector<BaseOperator> Operators{
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
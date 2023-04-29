//
// Created by PinkySmile on 29/04/23.
//

#include "ActionName.hpp"

std::map<SokuLib::Action, std::string> actionNames{
	{ SokuLib::ACTION_IDLE,                              "Idle" },
	{ SokuLib::ACTION_CROUCHING,                         "Crouching" },
	{ SokuLib::ACTION_CROUCHED,                          "Crouched" },
	{ SokuLib::ACTION_STANDING_UP,                       "Standing Up" },
	{ SokuLib::ACTION_WALK_FORWARD,                      "Walk Forward" },
	{ SokuLib::ACTION_WALK_BACKWARD,                     "Walk Backward" },
	{ SokuLib::ACTION_NEUTRAL_JUMP,                      "Neutral Jump" },
	{ SokuLib::ACTION_FORWARD_JUMP,                      "Forward Jump" },
	{ SokuLib::ACTION_BACKWARD_JUMP,                     "Backward Jump" },
	{ SokuLib::ACTION_FALLING,                           "Falling" },
	{ SokuLib::ACTION_LANDING,                           "Landing" },
	{ SokuLib::ACTION_STAND_GROUND_HIT_SMALL_HITSTUN,    "Stand Ground Hit Small Hitstun" },
	{ SokuLib::ACTION_STAND_GROUND_HIT_MEDIUM_HITSTUN,   "Stand Ground Hit Medium Hitstun" },
	{ SokuLib::ACTION_STAND_GROUND_HIT_BIG_HITSTUN,      "Stand Ground Hit Big Hitstun" },
	{ SokuLib::ACTION_STAND_GROUND_HIT_HUGE_HITSTUN,     "Stand Ground Hit Huge Hitstun" },
	{ SokuLib::ACTION_STAND_GROUND_HIT_SMALL_HITSTUN_2,  "Stand Ground Hit Small Hitstun 2" },
	{ SokuLib::ACTION_STAND_GROUND_HIT_MEDIUM_HITSTUN_2, "Stand Ground Hit Medium Hitstun 2" },
	{ SokuLib::ACTION_STAND_GROUND_HIT_BIG_HITSTUN_2,    "Stand Ground Hit Big Hitstun 2" },
	{ SokuLib::ACTION_CROUCH_GROUND_HIT_SMALL_HITSTUN,   "Crouch Ground Hit Small Hitstun" },
	{ SokuLib::ACTION_CROUCH_GROUND_HIT_MEDIUM_HITSTUN,  "Crouch Ground Hit Medium Hitstun" },
	{ SokuLib::ACTION_CROUCH_GROUND_HIT_BIG_HITSTUN,     "Crouch Ground Hit Big Hitstun" },
	{ SokuLib::ACTION_AIR_HIT_SMALL_HITSTUN,             "Air Hit Small Hitstun" },
	{ SokuLib::ACTION_AIR_HIT_MEDIUM_HITSTUN,            "Air Hit Medium Hitstun" },
	{ SokuLib::ACTION_AIR_HIT_BIG_HITSTUN,               "Air Hit Big Hitstun" },
	{ SokuLib::ACTION_AIR_HIT_DIRECT_KNOCKDOWN,          "Air Hit Direct Knockdown" },
	{ SokuLib::ACTION_AIR_HIT_CAN_WALL_SLAM,             "Air Hit Can Wall Slam" },
	{ SokuLib::ACTION_AIR_HIT_BIG_HITSTUN4,              "Air Hit Big Hitstun4" },
	{ SokuLib::ACTION_AIR_HIT_WALL_SLAMMED,              "Air Hit Wall Slammed" },
	{ SokuLib::ACTION_AIR_HIT_HUGE_HITSTUN,              "Air Hit Huge Hitstun" },
	{ SokuLib::ACTION_AIR_HIT_WALL_SLAMMED2,             "Air Hit Wall Slammed2" },
	{ SokuLib::ACTION_AIR_HIT_WILL_GROUND_SLAM,          "Air Hit Will Ground Slam" },
	{ SokuLib::ACTION_AIR_HIT_GROUND_SLAMMED,            "Air Hit Ground Slammed" },
	{ SokuLib::ACTION_KNOCKED_DOWN,                      "Knocked Down" },
	{ SokuLib::ACTION_KNOCKED_DOWN_STATIC,               "Knocked Down Static" },
	{ SokuLib::ACTION_GRABBED,                           "Grabbed" },
	{ SokuLib::ACTION_GROUND_CRUSHED,                    "Ground Crushed" },
	{ SokuLib::ACTION_AIR_CRUSHED,                       "Air Crushed" },
	{ SokuLib::ACTION_RIGHTBLOCK_HIGH_SMALL_BLOCKSTUN,   "Rightblock High Small Blockstun" },
	{ SokuLib::ACTION_RIGHTBLOCK_HIGH_MEDIUM_BLOCKSTUN,  "Rightblock High Medium Blockstun" },
	{ SokuLib::ACTION_RIGHTBLOCK_HIGH_BIG_BLOCKSTUN,     "Rightblock High Big Blockstun" },
	{ SokuLib::ACTION_RIGHTBLOCK_HIGH_HUGE_BLOCKSTUN,    "Rightblock High Huge Blockstun" },
	{ SokuLib::ACTION_RIGHTBLOCK_LOW_SMALL_BLOCKSTUN,    "Rightblock Low Small Blockstun" },
	{ SokuLib::ACTION_RIGHTBLOCK_LOW_MEDIUM_BLOCKSTUN,   "Rightblock Low Medium Blockstun" },
	{ SokuLib::ACTION_RIGHTBLOCK_LOW_BIG_BLOCKSTUN,      "Rightblock Low Big Blockstun" },
	{ SokuLib::ACTION_RIGHTBLOCK_LOW_HUGE_BLOCKSTUN,     "Rightblock Low Huge Blockstun" },
	{ SokuLib::ACTION_AIR_GUARD,                         "Air Guard" },
	{ SokuLib::ACTION_WRONGBLOCK_HIGH_SMALL_BLOCKSTUN,   "Wrongblock High Small Blockstun" },
	{ SokuLib::ACTION_WRONGBLOCK_HIGH_MEDIUM_BLOCKSTUN,  "Wrongblock High Medium Blockstun" },
	{ SokuLib::ACTION_WRONGBLOCK_HIGH_BIG_BLOCKSTUN,     "Wrongblock High Big Blockstun" },
	{ SokuLib::ACTION_WRONGBLOCK_HIGH_HUGE_BLOCKSTUN,    "Wrongblock High Huge Blockstun" },
	{ SokuLib::ACTION_WRONGBLOCK_LOW_SMALL_BLOCKSTUN,    "Wrongblock Low Small Blockstun" },
	{ SokuLib::ACTION_WRONGBLOCK_LOW_MEDIUM_BLOCKSTUN,   "Wrongblock Low Medium Blockstun" },
	{ SokuLib::ACTION_WRONGBLOCK_LOW_BIG_BLOCKSTUN,      "Wrongblock Low Big Blockstun" },
	{ SokuLib::ACTION_WRONGBLOCK_LOW_HUGE_BLOCKSTUN,     "Wrongblock Low Huge Blockstun" },
	{ SokuLib::ACTION_FORWARD_AIRTECH,                   "Forward Airtech" },
	{ SokuLib::ACTION_BACKWARD_AIRTECH,                  "Backward Airtech" },
	{ SokuLib::ACTION_FORWARD_TECH,                      "Forward Tech" },
	{ SokuLib::ACTION_BACKWARD_TECH,                     "Backward Tech" },
	{ SokuLib::ACTION_NEUTRAL_TECH,                      "Neutral Tech" },
	{ SokuLib::ACTION_FORWARD_DASH,                      "Forward Dash" },
	{ SokuLib::ACTION_BACKDASH,                          "Backdash" },
	{ SokuLib::ACTION_FORWARD_AIRDASH,                   "Forward Airdash" },
	{ SokuLib::ACTION_BACKWARD_AIRDASH,                  "Backward Airdash" },
	{ SokuLib::ACTION_GROUNDDASH_RECOVERY,               "Grounddash Recovery" },
	{ SokuLib::ACTION_LILYPAD_FORWARD_DASH,              "Lilypad Forward Dash" },
	{ SokuLib::ACTION_LILYPAD_BACKDASH,                  "Lilypad Backdash" },
	{ SokuLib::ACTION_NEUTRAL_HIGH_JUMP,                 "Neutral High Jump" },
	{ SokuLib::ACTION_FORWARD_HIGH_JUMP,                 "Forward High Jump" },
	{ SokuLib::ACTION_BACKWARD_HIGH_JUMP,                "Backward High Jump" },
	{ SokuLib::ACTION_NEUTRAL_HIGH_JUMP_FROM_GROUND_DASH, "Neutral High Jump From Ground Dash" },
	{ SokuLib::ACTION_FORWARD_HIGH_JUMP_FROM_GROUND_DASH, "Forward High Jump From Ground Dash" },
	{ SokuLib::ACTION_FLY,                                "Fly" },
	{ SokuLib::ACTION_HARDLAND,                           "Hardland" },
	{ SokuLib::ACTION_SUWAKO_j2D,                         "Suwako j2d" },
	{ SokuLib::ACTION_SUWAKO_j1D_j3D,                     "Suwako j1d/j3d" },
	{ SokuLib::ACTION_BE2,                                "Be2" },
	{ SokuLib::ACTION_BE1,                                "Be1" },
	{ SokuLib::ACTION_BE6,                                "Be6" },
	{ SokuLib::ACTION_BE4,                                "Be4" },
	{ SokuLib::ACTION_jBE4,                               "Jbe4" },
	{ SokuLib::ACTION_jBE6,                               "Jbe6" },
	{ SokuLib::ACTION_5A,                                 "5a" },
	{ SokuLib::ACTION_f5A,                                "F5a" },
	{ SokuLib::ACTION_6A,                                 "6a" },
	{ SokuLib::ACTION_2A,                                 "2a" },
	{ SokuLib::ACTION_3A,                                 "3a" },
	{ SokuLib::ACTION_66A,                                "66a" },
	{ SokuLib::ACTION_j5A,                                "J5a" },
	{ SokuLib::ACTION_j6A,                                "J6a" },
	{ SokuLib::ACTION_j2A,                                "J2a" },
	{ SokuLib::ACTION_j8A,                                "J8a" },
	{ SokuLib::ACTION_f2A,                                "F2a" },
	{ SokuLib::ACTION_5AA,                                "5aa" },
	{ SokuLib::ACTION_5AAA,                               "5aaa" },
	{ SokuLib::ACTION_5AAAA,                              "5aaaa" },
	{ SokuLib::ACTION_5AAAAA,                             "5aaaaa" },
	{ SokuLib::ACTION_5AAA3A,                             "5aaa3a" },
	{ SokuLib::ACTION_j5AA,                               "J5aa" },
	{ SokuLib::ACTION_4A,                                 "4a" },
	{ SokuLib::ACTION_SUWAKO_3A,                          "Suwako 3a" },
	{ SokuLib::ACTION_SUWAKO_LILYPAD_6A,                  "Suwako Lilypad 6a" },
	{ SokuLib::ACTION_5B,                                 "5b" },
	{ SokuLib::ACTION_6B,                                 "6b" },
	{ SokuLib::ACTION_2B,                                 "2b" },
	{ SokuLib::ACTION_3B,                                 "3b" },
	{ SokuLib::ACTION_j5B,                                "J5b" },
	{ SokuLib::ACTION_j6B,                                "J6b" },
	{ SokuLib::ACTION_j2B,                                "J2b" },
	{ SokuLib::ACTION_4B,                                 "4b" },
	{ SokuLib::ACTION_66B,                                "66b" },
	{ SokuLib::ACTION_j4B,                                "J4b" },
	{ SokuLib::ACTION_5C,                                 "5c" },
	{ SokuLib::ACTION_6C,                                 "6c" },
	{ SokuLib::ACTION_2C,                                 "2c" },
	{ SokuLib::ACTION_4C,                                 "4c" },
	{ SokuLib::ACTION_j5C,                                "J5c" },
	{ SokuLib::ACTION_j6C,                                "J6c" },
	{ SokuLib::ACTION_j2C,                                "J2c" },
	{ SokuLib::ACTION_j1C,                                "J1c" },
	{ SokuLib::ACTION_66C,                                "66c" },
	{ SokuLib::ACTION_ALICE_4C,                           "Alice 4c" },
	{ SokuLib::ACTION_ORRERIES_B,                         "Orreries B" },
	{ SokuLib::ACTION_AIR_ORRERIES_B,                     "Air Orreries B" },
	{ SokuLib::ACTION_ORRERIES_C,                         "Orreries C" },
	{ SokuLib::ACTION_AIR_ORRERIES_C,                     "Air Orreries C" },
	{ SokuLib::ACTION_DEFAULT_SKILL1_B,                   "Default Skill1 B" },
	{ SokuLib::ACTION_DEFAULT_SKILL1_C,                   "Default Skill1 C" },
	{ SokuLib::ACTION_DEFAULT_SKILL1_AIR_B,               "Default Skill1 Air B" },
	{ SokuLib::ACTION_DEFAULT_SKILL1_AIR_C,               "Default Skill1 Air C" },
	{ SokuLib::ACTION_ALT1_SKILL1_B,                      "Alt1 Skill1 B" },
	{ SokuLib::ACTION_ALT1_SKILL1_C,                      "Alt1 Skill1 C" },
	{ SokuLib::ACTION_ALT1_SKILL1_AIR_B,                  "Alt1 Skill1 Air B" },
	{ SokuLib::ACTION_ALT1_SKILL1_AIR_C,                  "Alt1 Skill1 Air C" },
	{ SokuLib::ACTION_ALT2_SKILL1_B,                      "Alt2 Skill1 B" },
	{ SokuLib::ACTION_ALT2_SKILL1_C,                      "Alt2 Skill1 C" },
	{ SokuLib::ACTION_ALT2_SKILL1_AIR_B,                  "Alt2 Skill1 Air B" },
	{ SokuLib::ACTION_ALT2_SKILL1_AIR_C,                  "Alt2 Skill1 Air C" },
	{ SokuLib::ACTION_DEFAULT_SKILL2_B,                   "Default Skill2 B" },
	{ SokuLib::ACTION_DEFAULT_SKILL2_C,                   "Default Skill2 C" },
	{ SokuLib::ACTION_DEFAULT_SKILL2_AIR_B,               "Default Skill2 Air B" },
	{ SokuLib::ACTION_DEFAULT_SKILL2_AIR_C,               "Default Skill2 Air C" },
	{ SokuLib::ACTION_ALT1_SKILL2_B,                      "Alt1 Skill2 B" },
	{ SokuLib::ACTION_ALT1_SKILL2_C,                      "Alt1 Skill2 C" },
	{ SokuLib::ACTION_ALT1_SKILL2_AIR_B,                  "Alt1 Skill2 Air B" },
	{ SokuLib::ACTION_ALT1_SKILL2_AIR_C,                  "Alt1 Skill2 Air C" },
	{ SokuLib::ACTION_ALT2_SKILL2_B,                      "Alt2 Skill2 B" },
	{ SokuLib::ACTION_ALT2_SKILL2_C,                      "Alt2 Skill2 C" },
	{ SokuLib::ACTION_ALT2_SKILL2_AIR_B,                  "Alt2 Skill2 Air B" },
	{ SokuLib::ACTION_ALT2_SKILL2_AIR_C,                  "Alt2 Skill2 Air C" },
	{ SokuLib::ACTION_DEFAULT_SKILL3_B,                   "Default Skill3 B" },
	{ SokuLib::ACTION_DEFAULT_SKILL3_C,                   "Default Skill3 C" },
	{ SokuLib::ACTION_DEFAULT_SKILL3_AIR_B,               "Default Skill3 Air B" },
	{ SokuLib::ACTION_DEFAULT_SKILL3_AIR_C,               "Default Skill3 Air C" },
	{ SokuLib::ACTION_ALT1_SKILL3_B,                      "Alt1 Skill3 B" },
	{ SokuLib::ACTION_ALT1_SKILL3_C,                      "Alt1 Skill3 C" },
	{ SokuLib::ACTION_ALT1_SKILL3_AIR_B,                  "Alt1 Skill3 Air B" },
	{ SokuLib::ACTION_ALT1_SKILL3_AIR_C,                  "Alt1 Skill3 Air C" },
	{ SokuLib::ACTION_ALT2_SKILL3_B,                      "Alt2 Skill3 B" },
	{ SokuLib::ACTION_ALT2_SKILL3_C,                      "Alt2 Skill3 C" },
	{ SokuLib::ACTION_ALT2_SKILL3_AIR_B,                  "Alt2 Skill3 Air B" },
	{ SokuLib::ACTION_ALT2_SKILL3_AIR_C,                  "Alt2 Skill3 Air C" },
	{ SokuLib::ACTION_DEFAULT_SKILL4_B,                   "Default Skill4 B" },
	{ SokuLib::ACTION_DEFAULT_SKILL4_C,                   "Default Skill4 C" },
	{ SokuLib::ACTION_DEFAULT_SKILL4_AIR_B,               "Default Skill4 Air B" },
	{ SokuLib::ACTION_DEFAULT_SKILL4_AIR_C,               "Default Skill4 Air C" },
	{ SokuLib::ACTION_ALT1_SKILL4_B,                      "Alt1 Skill4 B" },
	{ SokuLib::ACTION_ALT1_SKILL4_C,                      "Alt1 Skill4 C" },
	{ SokuLib::ACTION_ALT1_SKILL4_AIR_B,                  "Alt1 Skill4 Air B" },
	{ SokuLib::ACTION_ALT1_SKILL4_AIR_C,                  "Alt1 Skill4 Air C" },
	{ SokuLib::ACTION_ALT2_SKILL4_B,                      "Alt2 Skill4 B" },
	{ SokuLib::ACTION_ALT2_SKILL4_C,                      "Alt2 Skill4 C" },
	{ SokuLib::ACTION_ALT2_SKILL4_AIR_B,                  "Alt2 Skill4 Air B" },
	{ SokuLib::ACTION_ALT2_SKILL4_AIR_C,                  "Alt2 Skill4 Air C" },
	{ SokuLib::ACTION_DEFAULT_SKILL5_B,                   "Default Skill5 B" },
	{ SokuLib::ACTION_DEFAULT_SKILL5_C,                   "Default Skill5 C" },
	{ SokuLib::ACTION_DEFAULT_SKILL5_AIR_B,               "Default Skill5 Air B" },
	{ SokuLib::ACTION_DEFAULT_SKILL5_AIR_C,               "Default Skill5 Air C" },
	{ SokuLib::ACTION_ALT1_SKILL5_B,                      "Alt1 Skill5 B" },
	{ SokuLib::ACTION_ALT1_SKILL5_C,                      "Alt1 Skill5 C" },
	{ SokuLib::ACTION_ALT1_SKILL5_AIR_B,                  "Alt1 Skill5 Air B" },
	{ SokuLib::ACTION_ALT1_SKILL5_AIR_C,                  "Alt1 Skill5 Air C" },
	{ SokuLib::ACTION_ALT2_SKILL5_B,                      "Alt2 Skill5 B" },
	{ SokuLib::ACTION_ALT2_SKILL5_C,                      "Alt2 Skill5 C" },
	{ SokuLib::ACTION_ALT2_SKILL5_AIR_B,                  "Alt2 Skill5 Air B" },
	{ SokuLib::ACTION_ALT2_SKILL5_AIR_C,                  "Alt2 Skill5 Air C" },
	{ SokuLib::ACTION_USING_SC_ID_200,                    "Using SC Id 200" },
	{ SokuLib::ACTION_USING_SC_ID_201,                    "Using SC Id 201" },
	{ SokuLib::ACTION_USING_SC_ID_202,                    "Using SC Id 202" },
	{ SokuLib::ACTION_USING_SC_ID_203,                    "Using SC Id 203" },
	{ SokuLib::ACTION_USING_SC_ID_204,                    "Using SC Id 204" },
	{ SokuLib::ACTION_USING_SC_ID_205,                    "Using SC Id 205" },
	{ SokuLib::ACTION_USING_SC_ID_206,                    "Using SC Id 206" },
	{ SokuLib::ACTION_USING_SC_ID_207,                    "Using SC Id 207" },
	{ SokuLib::ACTION_USING_SC_ID_208,                    "Using SC Id 208" },
	{ SokuLib::ACTION_USING_SC_ID_209,                    "Using SC Id 209" },
	{ SokuLib::ACTION_USING_SC_ID_210,                    "Using SC Id 210" },
	{ SokuLib::ACTION_USING_SC_ID_211,                    "Using SC Id 211" },
	{ SokuLib::ACTION_USING_SC_ID_212,                    "Using SC Id 212" },
	{ SokuLib::ACTION_USING_SC_ID_213,                    "Using SC Id 213" },
	{ SokuLib::ACTION_USING_SC_ID_214,                    "Using SC Id 214" },
	{ SokuLib::ACTION_USING_SC_ID_215,                    "Using SC Id 215" },
	{ SokuLib::ACTION_USING_SC_ID_216,                    "Using SC Id 216" },
	{ SokuLib::ACTION_USING_SC_ID_217,                    "Using SC Id 217" },
	{ SokuLib::ACTION_USING_SC_ID_218,                    "Using SC Id 218" },
	{ SokuLib::ACTION_USING_SC_ID_219,                    "Using SC Id 219" },
	{ SokuLib::ACTION_SC_ID_200_ALT_EFFECT,               "SC Id 200 Alt Effect" },
	{ SokuLib::ACTION_SC_ID_201_ALT_EFFECT,               "SC Id 201 Alt Effect" },
	{ SokuLib::ACTION_SC_ID_202_ALT_EFFECT,               "SC Id 202 Alt Effect" },
	{ SokuLib::ACTION_SC_ID_203_ALT_EFFECT,               "SC Id 203 Alt Effect" },
	{ SokuLib::ACTION_SC_ID_204_ALT_EFFECT,               "SC Id 204 Alt Effect" },
	{ SokuLib::ACTION_SC_ID_205_ALT_EFFECT,               "SC Id 205 Alt Effect" },
	{ SokuLib::ACTION_SC_ID_206_ALT_EFFECT,               "SC Id 206 Alt Effect" },
	{ SokuLib::ACTION_SC_ID_207_ALT_EFFECT,               "SC Id 207 Alt Effect" },
	{ SokuLib::ACTION_SC_ID_208_ALT_EFFECT,               "SC Id 208 Alt Effect" },
	{ SokuLib::ACTION_SC_ID_209_ALT_EFFECT,               "SC Id 209 Alt Effect" },
	{ SokuLib::ACTION_SC_ID_210_ALT_EFFECT,               "SC Id 210 Alt Effect" },
	{ SokuLib::ACTION_SC_ID_211_ALT_EFFECT,               "SC Id 211 Alt Effect" },
	{ SokuLib::ACTION_SC_ID_212_ALT_EFFECT,               "SC Id 212 Alt Effect" },
	{ SokuLib::ACTION_SC_ID_213_ALT_EFFECT,               "SC Id 213 Alt Effect" },
	{ SokuLib::ACTION_SC_ID_214_ALT_EFFECT,               "SC Id 214 Alt Effect" },
	{ SokuLib::ACTION_SC_ID_215_ALT_EFFECT,               "SC Id 215 Alt Effect" },
	{ SokuLib::ACTION_SC_ID_216_ALT_EFFECT,               "SC Id 216 Alt Effect" },
	{ SokuLib::ACTION_SC_ID_217_ALT_EFFECT,               "SC Id 217 Alt Effect" },
	{ SokuLib::ACTION_SC_ID_218_ALT_EFFECT,               "SC Id 218 Alt Effect" },
	{ SokuLib::ACTION_SC_ID_219_ALT_EFFECT,               "SC Id 219 Alt Effect" },
	{ SokuLib::ACTION_SKILL_CARD,                         "Skill Card" },
	{ SokuLib::ACTION_SYSTEM_CARD,                        "System Card" },
	{ SokuLib::ACTION_IBUKI_GOURD,                        "Ibuki Gourd" },
	{ SokuLib::ACTION_RECOVERY_CHARM,                     "Recovery Charm" },
	{ SokuLib::ACTION_MAGIC_POTION,                       "Magic Potion" },
	{ SokuLib::ACTION_TALISMAN,                           "Talisman" },
	{ SokuLib::ACTION_BOMB,                               "Bomb" },
	{ SokuLib::ACTION_HANGEKI,                            "Hangeki" },
	{ SokuLib::ACTION_LEFT_HANDED_FOLDING_FAN,            "Left Handed Folding Fan" },
	{ SokuLib::ACTION_SPELL_BREAKING_DRUG,                "Spell Breaking Drug" },
};
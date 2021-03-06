#include <iostream>
#include <memory>
#include <TGUI/TGUI.hpp>
#include <SoFGV.hpp>
#include "EditableObject.hpp"
#include <package.hpp>
#include <Action.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#include <dbghelp.h>
#include <crtdbg.h>
#endif

using namespace SpiralOfFate;

void	displayPalEditor(std::unique_ptr<EditableObject> &object, tgui::Gui &gui, bool force = false);

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

auto c = std::make_shared<bool>(false);
float updateTimer = 0;
float timer = 0;
std::string loadedPath;
bool canDrag = false;
bool dragStart = false;
bool dragUp = false;
bool dragDown = false;
bool dragLeft = false;
bool dragRight = false;
bool updateAnyway = false;
bool spriteSelected = false;
bool quitRequest = false;
tgui::Color normalColor;
tgui::Button::Ptr boxButton;
Vector2i mouseStart;
Vector2i lastMouse;
static bool displayHitboxes = true;
static int selectedColor = 0;
ShadyCore::Schema::Sequence::BBox *selectedBox;
std::array<tgui::Button::Ptr, 8> resizeButtons;
std::string swr;
std::string soku;
std::string soku2;
sf::Color bgColor = sf::Color::Black;
ShadyCore::Schema tempSchema;

struct {
	ShadyCore::Schema *schema = nullptr;
	ShadyCore::Palette *palette = nullptr;
	std::string palName;
	std::string chr;
} editSession;

void	arrangeButtons(EditableObject *object)
{
	auto *data = object ? &object->_moves.at(object->_action)[object->_actionBlock][object->_animation] : nullptr;
	Box box = spriteSelected ? Box{
		{
			static_cast<int>(-data->offsetX),
			static_cast<int>(-data->offsetY)
		}, {
			static_cast<unsigned int>(data->texWidth * (data->blendOptions.scaleX ? data->blendOptions.scaleX : 200) / 100.f),
			static_cast<unsigned int>(data->texHeight * (data->blendOptions.scaleY ? data->blendOptions.scaleY : 200) / 100.f)
		}
	} : Box{
		{selectedBox->left, selectedBox->up},
		{
			static_cast<unsigned int>(selectedBox->right - selectedBox->left),
			static_cast<unsigned int>(selectedBox->down - selectedBox->up)
		}
	};

	for (int i = 0; i < 8; i++) {
		Vector2i pos;
		auto resizeButton = resizeButtons[i];

		if (i == 0 || i == 3 || i == 5)
			pos.x = box.pos.x - resizeButton->getSize().x;
		else if (i == 2 || i == 4 || i == 7)
			pos.x = box.pos.x + box.size.x;
		else
			pos.x = box.pos.x - resizeButton->getSize().x / 2 + box.size.x / 2;

		if (i < 3)
			pos.y = box.pos.y - resizeButton->getSize().x;
		else if (i > 4)
			pos.y = box.pos.y + box.size.y;
		else
			pos.y = box.pos.y - resizeButton->getSize().x / 2 + box.size.y / 2;
		resizeButton->setPosition("boxes.w / 2 + " + std::to_string(pos.x), "boxes.h / 2 + " + std::to_string(pos.y + 300));
	}
}

void	selectBox(tgui::Button::Ptr button, ShadyCore::Schema::Sequence::BBox *box)
{
	spriteSelected = false;
	selectedBox = box;
	if (boxButton)
		boxButton->getRenderer()->setBackgroundColor(normalColor);
	if (button) {
		normalColor = button->getRenderer()->getBackgroundColor();
		button->getRenderer()->setBackgroundColor(button->getRenderer()->getBackgroundColorFocused());
	}
	boxButton = button;
	for (auto &b : resizeButtons)
		b->setVisible(box != nullptr);
	if (box)
		arrangeButtons(nullptr);
}

void	selectSprite(tgui::Button::Ptr button, std::unique_ptr<EditableObject> &object)
{
	boxButton = button;
	normalColor = button->getRenderer()->getBackgroundColor();
	button->getRenderer()->setBackgroundColor(button->getRenderer()->getBackgroundColorFocused());
	spriteSelected = true;
	for (auto &b : resizeButtons)
		b->setVisible(true);
	arrangeButtons(&*object);
}

bool	exists(const std::string &path)
{
	struct stat s;

	return stat(path.c_str(), &s) == 0;
}

void	verifySettings()
{
	if (!soku.empty())
		try {
			if (!exists((std::filesystem::path(soku) / "th123a.dat").string()))
				throw std::runtime_error("th123a.dat was not found in " + soku);
			if (!exists((std::filesystem::path(soku) / "th123b.dat").string()))
				throw std::runtime_error("th123b.dat was not found in " + soku);
			if (!exists((std::filesystem::path(soku) / "th123c.dat").string()))
				throw std::runtime_error("th123c.dat was not found in " + soku);
		} catch (const std::exception &e) {
			soku.clear();
			Utils::dispMsg("Settings loading error", "Loaded soku directory is invalid: " + std::string(e.what()) + ".\nPlease select a valid Soku directory", MB_ICONERROR);
		}

	if (!swr.empty())
		try {
			if (!exists((std::filesystem::path(swr) / "th105a.dat").string()))
				throw std::runtime_error("th105a.dat was not found in " + swr);
			if (!exists((std::filesystem::path(swr) / "th105b.dat").string()))
				throw std::runtime_error("th105b.dat was not found in " + swr);
		} catch (const std::exception &e) {
			swr.clear();
			Utils::dispMsg("Settings loading error", "Loaded SWT directory is invalid: " + std::string(e.what()) + ".\nPlease select a valid SWR directory", MB_ICONERROR);
		}

	if (soku.empty()) {
		soku = Utils::openFileDialog("Select Soku dat", ".", {{"th123.\\.dat", "Touhou 12.3 dat file"}});
		if (soku.empty())
			throw std::runtime_error("No Soku dat file selected");
		soku = std::filesystem::path(soku).parent_path().string();
	}
	if (!exists((std::filesystem::path(soku) / "th123a.dat").string()))
		throw std::runtime_error("th123a.dat was not found in " + soku);
	if (!exists((std::filesystem::path(soku) / "th123b.dat").string()))
		throw std::runtime_error("th123b.dat was not found in " + soku);
	if (!exists((std::filesystem::path(soku) / "th123c.dat").string()))
		throw std::runtime_error("th123c.dat was not found in " + soku);

	if (
		exists((std::filesystem::path(soku) / "th105a.dat").string()) &&
		exists((std::filesystem::path(soku) / "th105b.dat").string())
	) {
		game->logger.info("Autodetected SWR dats in " + soku);
		swr = soku;
	}

	if (swr.empty()) {
		swr = Utils::openFileDialog("Select SWR dat", ".", {{"th105.\\.dat", "Touhou 10.5 dat file"}});
		if (swr.empty())
			throw std::runtime_error("No SWR dat file selected");
		swr = std::filesystem::path(swr).parent_path().string();
	}
	if (!exists((std::filesystem::path(swr) / "th105a.dat").string()))
		throw std::runtime_error("th105a.dat was not found in " + swr);
	if (!exists((std::filesystem::path(swr) / "th105b.dat").string()))
		throw std::runtime_error("th105b.dat was not found in " + swr);
}

void loadPackages()
{
	std::vector<std::filesystem::path> paths = {
		std::filesystem::path(soku) / "th123a.dat",
		std::filesystem::path(soku) / "th123b.dat",
		std::filesystem::path(soku) / "th123c.dat",
		std::filesystem::path(swr)  / "th105a.dat",
		std::filesystem::path(swr)  / "th105b.dat",
	};

	try {
		for (auto &path: std::filesystem::directory_iterator(soku2))
			paths.push_back(soku2 / path.path().filename() / (path.path().filename().string() + ".dat"));
	} catch (const std::exception &e) {
		game->logger.error("Error loading soku2: " + std::string(e.what()));
	}

	game->package.clear();
	game->characterPaths.clear();
	for (auto &path : paths)
		game->package.merge(new ShadyCore::Package(path));
	for (auto &entry : game->package) {
		if (entry.first.name.substr(0, strlen("data_character_")) != "data_character_")
			continue;
		if (entry.first.name.substr(0, strlen("data_character_common_")) == "data_character_common_")
			continue;

		std::string name = std::string(entry.first.name.substr(strlen("data_character_")));
		std::string filename = name.substr(name.find_last_of('_') + 1);

		name = name.substr(0, name.find('_'));
		if (entry.first.fileType == ShadyCore::FileType::TYPE_SCHEMA) {
			game->logger.debug("Found schema " + std::string(entry.first.name));
			//ShadyCore::getResourceReader({ShadyCore::FileType::TYPE_SCHEMA, ShadyCore::FileType::SCHEMA_GAME_ANIM})(&game->characterPaths[name].framedata, entry.second->open());
		} else if (entry.first.fileType == ShadyCore::FileType::TYPE_PALETTE) {
			auto &pal = game->characterPaths[name].palettes["data/character/" + name + "/" + filename + ".pal"];

			game->logger.debug("Found palette " + std::string(entry.first.name));
			ShadyCore::getResourceReader(entry.first.fileType)(&pal, entry.second->open());
			if (pal.bitsPerPixel > 16)
				pal.pack();
		}
	}
}

void	refreshBoxes(tgui::Panel::Ptr panel, FrameData &data, std::unique_ptr<EditableObject> &object)
{
	int i = 0;
	auto button = tgui::Button::create();
	auto renderer = button->getRenderer();

	panel->removeAllWidgets();
	renderer->setBackgroundColor({0xFF, 0xFF, 0xFF, 0x00});
	renderer->setBackgroundColorDown({0xFF, 0xFF, 0xFF, 0xA0});
	renderer->setBackgroundColorHover({0xFF, 0xFF, 0xFF, 0x80});
	renderer->setBackgroundColorDisabled({0xFF, 0xFF, 0xFF, 0x4C});
	renderer->setBackgroundColorFocused({0xFF, 0xFF, 0xFF, 0xA0});
	renderer->setBorderColor({0xFF, 0xFF, 0xFF});
	renderer->setBorderColorDown({0xFF, 0xFF, 0xFF});
	renderer->setBorderColorHover({0xFF, 0xFF, 0xFF});
	renderer->setBorderColorDisabled({0xFF, 0xFF, 0xFF});
	renderer->setBorderColorFocused({0xFF, 0xFF, 0xFF});
	renderer->setBorders(1);
	button->setSize(data.texWidth * (data.blendOptions.scaleX ? data.blendOptions.scaleX : 200) / 100.f, data.texHeight * (data.blendOptions.scaleY ? data.blendOptions.scaleY : 200) / 100.f);
	button->setPosition(
		"&.w / 2 + " + std::to_string(-data.offsetX),
		"&.h / 2 + " + std::to_string(-data.offsetY + 300)
	);
	button->connect("MousePressed", [&object](std::weak_ptr<tgui::Button> self){
		selectSprite(self.lock(), object);
		canDrag = true;
	}, std::weak_ptr<tgui::Button>(button));
	panel->add(button, "SpriteBox");

	for (auto &box : data.hBoxes) {
		button = tgui::Button::create();
		renderer = button->getRenderer();
		renderer->setBackgroundColor({0x00, 0xFF, 0x00, 0x4C});
		renderer->setBackgroundColorDown({0x00, 0xFF, 0x00, 0xA0});
		renderer->setBackgroundColorHover({0x00, 0xFF, 0x00, 0x80});
		renderer->setBackgroundColorDisabled({0x00, 0xFF, 0x00, 0x4C});
		renderer->setBackgroundColorFocused({0x00, 0xFF, 0x00, 0xA0});
		renderer->setBorderColor({0x00, 0xFF, 0x00});
		renderer->setBorderColorDown({0x00, 0xFF, 0x00});
		renderer->setBorderColorHover({0x00, 0xFF, 0x00});
		renderer->setBorderColorDisabled({0x00, 0xFF, 0x00});
		renderer->setBorderColorFocused({0x00, 0xFF, 0x00});
		renderer->setBorders(1);
		button->setSize(box.right - box.left, box.down - box.up);
		button->setPosition("&.w / 2 + " + std::to_string(box.left), "&.h / 2 + " + std::to_string(box.up + 300));
		button->connect("MousePressed", [&box](std::weak_ptr<tgui::Button> self){
			selectBox(self.lock(), &box);
			canDrag = true;
		}, std::weak_ptr<tgui::Button>(button));
		panel->add(button, "HurtBox" + std::to_string(i));
		i++;
	}
	i = 0;
	for (auto &box : data.aBoxes) {
		button = tgui::Button::create();
		renderer = button->getRenderer();
		renderer->setBackgroundColor({0xFF, 0x00, 0x00, 0x4C});
		renderer->setBackgroundColorDown({0xFF, 0x00, 0x00, 0xA0});
		renderer->setBackgroundColorHover({0xFF, 0x00, 0x00, 0x80});
		renderer->setBackgroundColorDisabled({0xFF, 0x00, 0x00, 0x4C});
		renderer->setBackgroundColorFocused({0xFF, 0x00, 0x00, 0xA0});
		renderer->setBorderColor({0xFF, 0x00, 0x00});
		renderer->setBorderColorDown({0xFF, 0x00, 0x00});
		renderer->setBorderColorHover({0xFF, 0x00, 0x00});
		renderer->setBorderColorDisabled({0xFF, 0x00, 0x00});
		renderer->setBorderColorFocused({0xFF, 0x00, 0x00});
		renderer->setBorders(1);
		button->setSize(box.right - box.left, box.down - box.up);
		button->setPosition("&.w / 2 + " + std::to_string(box.left), "&.h / 2 + " + std::to_string(box.up + 300));
		button->connect("MousePressed", [&box](std::weak_ptr<tgui::Button> self){
			selectBox(self.lock(), &box);
			canDrag = true;
		}, std::weak_ptr<tgui::Button>(button));
		panel->add(button, "HitBox" + std::to_string(i));
		i++;
	}
	if (!data.cBoxes.empty()) {
		auto &box = data.cBoxes.front();

		button = tgui::Button::create();
		renderer = button->getRenderer();
		renderer->setBackgroundColor({0xFF, 0xFF, 0x00, 0x4C});
		renderer->setBackgroundColorDown({0xFF, 0xFF, 0x00, 0xA0});
		renderer->setBackgroundColorHover({0xFF, 0xFF, 0x00, 0x80});
		renderer->setBackgroundColorDisabled({0xFF, 0xFF, 0x00, 0x4C});
		renderer->setBackgroundColorFocused({0xFF, 0xFF, 0x00, 0xA0});
		renderer->setBorderColor({0xFF, 0xFF, 0x00});
		renderer->setBorderColorDown({0xFF, 0xFF, 0x00});
		renderer->setBorderColorHover({0xFF, 0xFF, 0x00});
		renderer->setBorderColorDisabled({0xFF, 0xFF, 0x00});
		renderer->setBorderColorFocused({0xFF, 0xFF, 0x00});
		renderer->setBorders(1);
		button->setSize(box.right - box.left, box.down - box.up);
		button->setPosition("&.w / 2 + " + std::to_string(box.left), "&.h / 2 + " + std::to_string(box.up + 300));
		button->connect("MousePressed", [&data, &box](std::weak_ptr<tgui::Button> self){
			selectBox(self.lock(), &box);
			canDrag = true;
		}, std::weak_ptr<tgui::Button>(button));
		panel->add(button, "CollisionBox");
	}
}

void	refreshFrameDataPanel(tgui::Panel::Ptr panel, tgui::Panel::Ptr boxes, std::unique_ptr<EditableObject> &object)
{
	auto progress = panel->get<tgui::Slider>("Progress");
	auto limit = panel->get<tgui::EditBox>("Limit");
	auto sprite = panel->get<tgui::EditBox>("Sprite");
	auto hitSound = panel->get<tgui::EditBox>("HitSFX");
	auto offset = panel->get<tgui::EditBox>("Offset");
	auto bounds = panel->get<tgui::EditBox>("Bounds");
	auto scale = panel->get<tgui::EditBox>("Scale");
	auto collisionBox = panel->get<tgui::CheckBox>("Collision");
	auto duration = panel->get<tgui::EditBox>("Duration");
	auto pushBack = panel->get<tgui::EditBox>("PushBack");
	auto pushBlock = panel->get<tgui::EditBox>("PushBlock");
	auto pBlockStun = panel->get<tgui::EditBox>("PBlockStun");
	auto eBlockStun = panel->get<tgui::EditBox>("EBlockStun");
	auto pHitStun = panel->get<tgui::EditBox>("PHitStun");
	auto eHitStun = panel->get<tgui::EditBox>("EHitStun");
	auto hitStun = panel->get<tgui::EditBox>("HitStun");
	auto hitSpeed = panel->get<tgui::EditBox>("HitSpeed");
	auto counterHitSpeed = panel->get<tgui::EditBox>("CHSpeed");
	auto prorate = panel->get<tgui::EditBox>("Rate");
	auto damage = panel->get<tgui::EditBox>("Damage");
	auto speed = panel->get<tgui::EditBox>("MoveSpeed");
	auto fFlags = panel->get<tgui::EditBox>("fFlags");
	auto aFlags = panel->get<tgui::EditBox>("aFlags");
	auto chip = panel->get<tgui::EditBox>("ChipDmg");
	auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];
	auto actionName = panel->get<tgui::Button>("ActionName");
	auto name = actionNames.find(static_cast<SokuLib::Action>(object->_action));

	game->logger.debug("Soft refresh");
	*c = true;
	actionName->setText(name == actionNames.end() ? "Action #" + std::to_string(object->_action) : name->second);
	fFlags->setText(std::to_string(data.traits.frameFlags));
	aFlags->setText(std::to_string(data.traits.attackFlags));
	chip->setText(std::to_string(data.traits.chipDamage));
	progress->setMinimum(0);
	progress->setMaximum(object->_moves.at(object->_action)[object->_actionBlock].size() - 1);
	progress->setValue(object->_animation);
	sprite->setText(data._schema.images[data.imageIndex].name);
	hitSound->setText(std::to_string(data.traits.onHitSfx));
	damage->setText(std::to_string(data.traits.damage));
	duration->setText(std::to_string(data.duration));
	pBlockStun->setText(std::to_string(data.traits.onBlockPlayerStun));
	eBlockStun->setText(std::to_string(data.traits.onBlockEnemyStun));
	pHitStun->setText(std::to_string(data.traits.onHitPlayerStun));
	eHitStun->setText(std::to_string(data.traits.onHitEnemyStun));
	hitStun->setText(std::to_string(data.traits.onHitEnemyStun));
	prorate->setText(std::to_string(data.traits.proration / 10) + "." + std::to_string(data.traits.proration % 10) + "%");
	limit->setText(std::to_string(data.traits.limit));

	auto newBounds = "(" + std::to_string(data.texOffsetX) + "," + std::to_string(data.texOffsetY) + "," + std::to_string(data.texWidth) + "," + std::to_string(data.texHeight) + ")";
	auto newScale = "(" +
		std::to_string(data.blendOptions.scaleX / 100) + "." + (data.blendOptions.scaleX % 100 < 10 ? "0" : "") + std::to_string(data.blendOptions.scaleX % 100) + "," +
		std::to_string(data.blendOptions.scaleY / 100) + "." + (data.blendOptions.scaleY % 100 < 10 ? "0" : "") + std::to_string(data.blendOptions.scaleY % 100) +
	")";
	auto newOffset = "(" + std::to_string(data.offsetX) + "," + std::to_string(data.offsetY) + ")";
	auto newSpeed = "(" +
		std::to_string(data.effect.speedX / 100) + "." + (data.effect.speedX % 100 < 10 ? "0" : "") + std::to_string(data.effect.speedX % 100) + "," +
		std::to_string(data.effect.speedY / 100) + "." + (data.effect.speedY % 100 < 10 ? "0" : "") + std::to_string(data.effect.speedY % 100) +
	")";
	auto newHitSpeed = "(" +
		std::to_string(data.traits.speedX / 100) + "." + (data.traits.speedX % 100 < 10 ? "0" : "") + std::to_string(data.traits.speedX % 100) + "," +
		std::to_string(data.traits.speedY / 100) + "." + (data.traits.speedY % 100 < 10 ? "0" : "") + std::to_string(data.traits.speedY % 100) +
	")";

	hitSpeed->setText(newHitSpeed);
	speed->setText(newSpeed);
	offset->setText(newOffset);
	bounds->setText(newBounds);
	scale->setText(newScale);
	collisionBox->setChecked(!data.cBoxes.empty());
	selectBox(nullptr, nullptr);
	refreshBoxes(boxes, data, object);
	*c = false;
}

void	refreshRightPanel(tgui::Gui &gui, std::unique_ptr<EditableObject> &object, bool resetAction = true)
{
	auto panel = gui.get<tgui::Panel>("Panel1");
	auto animPanel = panel->get<tgui::Panel>("AnimPanel");
	auto action = panel->get<tgui::EditBox>("Action");
	auto block = panel->get<tgui::SpinButton>("Block");
	auto play = panel->get<tgui::Button>("Play");
	auto step = panel->get<tgui::Button>("Step");
	auto speedCtrl = panel->get<tgui::SpinButton>("Speed");
	auto speedLabel = panel->get<tgui::Label>("SpeedLabel");
	auto frame = panel->get<tgui::SpinButton>("Frame");

	game->logger.debug("Hard refresh");
	panel->setEnabled(static_cast<bool>(object));
	if (!object)
		return gui.get<tgui::Panel>("Boxes")->removeAllWidgets();
	step->onPress.emit(&*step, "Step");
	if (resetAction) {
		action->setText("0");
		action->onReturnKeyPress.emit(&*action, "0");
	}
	if (speedCtrl->getValue() == 0)
		speedCtrl->onValueChange.emit(&*speedCtrl, 0);
	else
		speedCtrl->setValue(0);
	if (object->_moves[0].empty()) {
		object->_moves[0].emplace_back();

		auto newElem = new ShadyCore::Schema::Sequence::MoveFrame();

		tempSchema.objects.push_back(reinterpret_cast<ShadyCore::Schema::Object *const>(newElem));
		object->_moves[0][0].emplace_back(editSession.chr, tempSchema, *newElem, *editSession.palette, editSession.palName);
	}
	refreshFrameDataPanel(panel, gui.get<tgui::Panel>("Boxes"), object);
}

void	placeAnimPanelHooks(tgui::Gui &gui, tgui::Panel::Ptr panel, tgui::Panel::Ptr boxes, std::unique_ptr<EditableObject> &object)
{
	// Ctrl UI
	auto panWeak = std::weak_ptr<tgui::Panel>(panel);
	auto animPanel = panel->get<tgui::Panel>("AnimPanel");
	auto action = panel->get<tgui::EditBox>("Action");
	auto actionName = panel->get<tgui::Button>("ActionName");
	auto block = panel->get<tgui::SpinButton>("Block");
	auto blockLabel = panel->get<tgui::Label>("Label1");
	auto frameLabel = panel->get<tgui::Label>("Label2");
	auto progress = panel->get<tgui::Slider>("Progress");
	auto play = panel->get<tgui::Button>("Play");
	auto step = panel->get<tgui::Button>("Step");
	auto speedCtrl = panel->get<tgui::SpinButton>("Speed");
	auto speedLabel = panel->get<tgui::Label>("SpeedLabel");

	auto sprite = panel->get<tgui::EditBox>("Sprite");
	auto hitSound = panel->get<tgui::EditBox>("HitSFX");
	auto offset = panel->get<tgui::EditBox>("Offset");
	auto bounds = panel->get<tgui::EditBox>("Bounds");
	auto scale = panel->get<tgui::EditBox>("Scale");
	auto collisionBox = panel->get<tgui::CheckBox>("Collision");
	auto duration = panel->get<tgui::EditBox>("Duration");
	auto pBlockStun = panel->get<tgui::EditBox>("PBlockStun");
	auto eBlockStun = panel->get<tgui::EditBox>("EBlockStun");
	auto pHitStun = panel->get<tgui::EditBox>("PHitStun");
	auto eHitStun = panel->get<tgui::EditBox>("EHitStun");
	auto prorate = panel->get<tgui::EditBox>("Rate");
	auto damage = panel->get<tgui::EditBox>("Damage");
	auto hitSpeed = panel->get<tgui::EditBox>("HitSpeed");
	auto limit = panel->get<tgui::EditBox>("Limit");
	auto gravity = panel->get<tgui::EditBox>("Gravity");
	auto speed = panel->get<tgui::EditBox>("MoveSpeed");
	auto aFlags = panel->get<tgui::EditBox>("aFlags");
	auto fFlags = panel->get<tgui::EditBox>("fFlags");
	auto chip = panel->get<tgui::EditBox>("ChipDmg");
	std::vector<tgui::CheckBox::Ptr> fFlagsCheckboxes;
	std::vector<tgui::CheckBox::Ptr> aFlagsCheckboxes;

	actionName->connect("Clicked", [&gui, &object, block, action]{
		auto window = Utils::openWindowWithFocus(gui, 500, "&.h - 100");
		auto pan = tgui::ScrollablePanel::create({"&.w", "&.h"});
		unsigned i = 0;
		std::vector<unsigned> toDisplay;

		for (auto &a : actionNames)
			toDisplay.push_back(a.first);
		for (auto &a : object->_moves) {
			if (std::find(toDisplay.begin(), toDisplay.end(), a.first) == toDisplay.end())
				toDisplay.push_back(a.first);
		}
		std::sort(toDisplay.begin(), toDisplay.end());
		Utils::setRenderer(pan);
		window->setTitle("Default character moves");
		window->add(pan);
		for (auto &moveId : toDisplay) {
			auto it = actionNames.find(static_cast<SokuLib::Action>(moveId));
			auto label = tgui::Label::create(std::to_string(moveId));
			auto button = tgui::Button::create(it == actionNames.end() ? "Unnamed move #" + std::to_string(moveId) : it->second);

			label->setPosition(10, i * 25 + 12);
			button->setPosition(50, i * 25 + 10);
			button->setSize(430, 20);
			Utils::setRenderer(button);
			Utils::setRenderer(label);
			if (object->_moves.find(moveId) == object->_moves.end()) {
				button->getRenderer()->setTextColor(tgui::Color::Red);
				button->getRenderer()->setTextColorHover(tgui::Color{0xFF, 0x40, 0x40});
				button->getRenderer()->setTextColorDisabled(tgui::Color{0xA0, 0, 0});
				button->getRenderer()->setTextColorDown(tgui::Color{0x80, 0x00, 0x00});
				button->getRenderer()->setTextColorFocused(tgui::Color{0x80, 0x20, 0x20});
			} else if (it == actionNames.end()) {
				button->getRenderer()->setTextColor(tgui::Color{0xFF, 0x80, 0x00});
				button->getRenderer()->setTextColorHover(tgui::Color{0xFF, 0xA0, 0x40});
				button->getRenderer()->setTextColorDisabled(tgui::Color{0xA0, 0x50, 0});
				button->getRenderer()->setTextColorDown(tgui::Color{0x80, 0x40, 0x00});
				button->getRenderer()->setTextColorFocused(tgui::Color{0x80, 0x60, 0x20});
			}

			button->connect("Clicked", [moveId, action](std::weak_ptr<tgui::ChildWindow> win){
				win.lock()->close();
				action->setText(std::to_string(moveId));
				action->onReturnKeyPress.emit(&*action, action->getText());
			}, std::weak_ptr<tgui::ChildWindow>(window));

			pan->add(label);
			pan->add(button);
			i++;
		}

		auto label = tgui::Label::create("");

		label->setPosition(10, i * 25 + 10);
		label->setSize(10, 5);
		pan->add(label);
	});
	boxes->connect("Clicked", []{
		if (!dragStart && !canDrag)
			selectBox(nullptr, nullptr);
	});
	action->connect("ReturnKeyPressed", [&object, block](const std::string &t){
		if (t.empty())
			return;
		auto newAction = std::stoul(t);
		if (object->_moves.find(newAction) == object->_moves.end())
			object->_moves.emplace(newAction, object->_moves[object->_action]);
		object->_action = newAction;
		block->setMaximum(object->_moves[object->_action].size() - 1);
		block->setMinimum(0);
		if (block->getValue() == 0)
			block->onValueChange.emit(&*block, 0);
		else
			block->setValue(0);
	});
	block->connect("ValueChanged", [&object, blockLabel, progress](float f){
		int i = f;

		blockLabel->setText("Block " + std::to_string(i));
		object->_actionBlock = i;
		if (object->_moves[object->_action][i].empty()) {
			auto old = reinterpret_cast<ShadyCore::Schema::Sequence::MoveFrame *>(tempSchema.objects.back());
			auto newElem = new ShadyCore::Schema::Sequence::MoveFrame();

			//TODO: Properly init a default one
			tempSchema.objects.push_back(reinterpret_cast<ShadyCore::Schema::Object *const>(newElem));
			object->_moves[object->_action][i].emplace_back(editSession.chr, tempSchema, *newElem, *editSession.palette, editSession.palName);
		}
		progress->setMaximum(object->_moves[object->_action][i].size() - 1);
		progress->setMinimum(0);
		if (progress->getValue() == 0)
			progress->onValueChange.emit(&*progress, 0);
		else
			progress->setValue(0);
	});
	progress->connect("ValueChanged", [boxes, &object, frameLabel, panWeak](float f){
		int i = f;

		frameLabel->setText("Frame " + std::to_string(i));
		object->_animation = i;
		object->_animationCtr = 0;
		refreshFrameDataPanel(panWeak.lock(), boxes, object);
	});
	play->connect("Clicked", [speedLabel, speedCtrl]{
		speedCtrl->setValue(1);
	});
	step->connect("Clicked", [speedLabel, speedCtrl]{
		updateAnyway = true;
		speedCtrl->setValue(0);
	});
	speedCtrl->connect("ValueChanged", [speedLabel, animPanel](float f){
		speedLabel->setText(f == 0 ? "Paused" : "x" + std::to_string(f));
		updateTimer = 1 / f;
		timer = 0;
		animPanel->setEnabled(f == 0);
	});
	chip->connect("TextChanged", [&object](std::string t){
		if (*c)
			return;
		if (t.empty())
			return;

		auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];

		data.traits.chipDamage = std::stoul(t);
	});
	sprite->connect("TextChanged", [&object](std::string t){
		if (*c)
			return;

		auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];

		//TODO: Actually change the sprite
		//data.spritePath = t;
		//data.reloadTexture();
	});
	hitSound->connect("TextChanged", [&object](std::string t){
		if (*c)
			return;

		auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];

		data.traits.onHitSfx = std::stoul(t);
		data.reloadSound();
	});
	speed->connect("TextChanged", [boxes, &object](std::string t){
		if (*c)
			return;
		if (t.empty())
			return;

		auto pos = t.find(',');
		auto x = t.substr(1, pos - 1);
		auto y = t.substr(pos + 1, t.size() - pos - 1);
		auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];

		try {
			std::stol(y);
			data.effect.speedX = std::stof(x) * 100;
			data.effect.speedY = std::stof(y) * 100;
			refreshBoxes(boxes, data, object);
			if (spriteSelected)
				arrangeButtons(&*object);
		} catch (std::exception &) {}
	});
	offset->connect("TextChanged", [boxes, &object](std::string t){
		if (*c)
			return;
		if (t.empty())
			return;

		auto pos = t.find(',');
		auto x = t.substr(1, pos - 1);
		auto y = t.substr(pos + 1, t.size() - pos - 1);
		auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];

		try {
			std::stol(y);
			data.offsetX = std::stol(x);
			data.offsetY = std::stol(y);
			refreshBoxes(boxes, data, object);
			if (spriteSelected)
				arrangeButtons(&*object);
		} catch (std::exception &) {}
	});
	hitSpeed->connect("TextChanged", [boxes, &object](std::string t){
		if (*c)
			return;
		if (t.empty())
			return;

		auto pos = t.find(',');
		auto x = t.substr(1, pos - 1);
		auto y = t.substr(pos + 1, t.size() - pos - 1);
		auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];

		try {
			data.traits.speedX = std::stof(x) * 100;
			data.traits.speedY = std::stof(y) * 100;
		} catch (...) {}
		refreshBoxes(boxes, data, object);
		if (spriteSelected)
			arrangeButtons(&*object);
	});
	scale->connect("TextChanged", [&object, boxes](std::string t){
		if (*c)
			return;
		if (t.empty())
			return;

		auto pos = t.find(',');
		auto x = t.substr(1, pos - 1);
		auto y = t.substr(pos + 1, t.size() - pos - 1);
		auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];

		try {
			std::stoul(y);
			data.blendOptions.scaleX = std::stof(x) * 100;
			data.blendOptions.scaleY = std::stof(y) * 100;
		} catch (...) {}
		refreshBoxes(boxes, data, object);
		if (spriteSelected)
			arrangeButtons(&*object);
	});
	bounds->connect("TextChanged", [&object](std::string t){
		if (*c)
			return;
		if (t.empty())
			return;

		auto pos = t.find(',');
		auto x = t.substr(1, pos - 1);

		auto remainder = t.substr(pos + 1);
		auto pos2 = remainder.find(',');
		auto y = remainder.substr(0, pos2 + 1);

		auto remainder2 = remainder.substr(pos2 + 1);
		auto pos3 = remainder2.find(',');
		auto w = remainder2.substr(0, pos3 + 1);
		auto h = remainder2.substr(pos3 + 1, remainder2.size() - pos3 - 1);;

		auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];

		try {
			std::stoul(x);
			std::stoul(y);
			std::stoul(w);
			data.texOffsetX = std::stoul(x);
			data.texOffsetY = std::stoul(y);
			data.texWidth   = std::stoul(w);
			data.texHeight  = std::stoul(h);
		} catch (...) {}
	});
	duration->connect("TextChanged", [&object](std::string t){
		if (*c)
			return;
		if (t.empty())
			return;

		auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];

		data.duration = std::stoul(t);
	});
	damage->connect("TextChanged", [&object](std::string t){
		if (*c)
			return;
		if (t.empty())
			return;

		auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];

		data.traits.damage = std::stoul(t);
	});
	pBlockStun->connect("TextChanged", [&object](std::string t){
		if (*c)
			return;
		if (t.empty())
			return;

		auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];

		data.traits.onBlockPlayerStun = std::stoul(t);
	});
	eBlockStun->connect("TextChanged", [&object](std::string t){
		if (*c)
			return;
		if (t.empty())
			return;

		auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];

		data.traits.onBlockEnemyStun = std::stoul(t);
	});
	pHitStun->connect("TextChanged", [&object](std::string t){
		if (*c)
			return;
		if (t.empty())
			return;

		auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];

		data.traits.onHitPlayerStun = std::stoul(t);
	});
	eHitStun->connect("TextChanged", [&object](std::string t){
		if (*c)
			return;
		if (t.empty())
			return;

		auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];

		data.traits.onHitEnemyStun = std::stoul(t);
	});
	limit->connect("TextChanged", [&object](std::string t){
		if (*c)
			return;
		if (t.empty())
			return;

		auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];

		data.traits.limit = std::stoul(t);
	});
	prorate->connect("TextChanged", [&object](std::string t){
		if (*c)
			return;
		if (t.empty())
			return;

		auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];

		data.traits.proration = std::stof(t) * 10;
	});
	collisionBox->connect("Checked", [&object, boxes]{
		if (*c)
			return;

		auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];

		if (data.cBoxes.empty())
			data.cBoxes.push_back({
				static_cast<int>(-data.offsetX),
				static_cast<int>(-data.offsetY),
				static_cast<int>(data.texWidth  * (data.blendOptions.scaleX ? data.blendOptions.scaleX : 200) / 100.f - data.offsetX),
				static_cast<int>(data.texHeight * (data.blendOptions.scaleY ? data.blendOptions.scaleY : 200) / 100.f -data.offsetY),
			});
		refreshBoxes(boxes, data, object);
	});
	collisionBox->connect("Unchecked", [&object, boxes]{
		if (*c)
			return;

		auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];

		if (selectedBox && selectedBox == &data.cBoxes.front())
			selectBox(nullptr, nullptr);
		data.cBoxes.clear();
		refreshBoxes(boxes, data, object);
	});

	for (int i = 0; i < 32; i++) {
		auto checkbox = panel->get<tgui::CheckBox>("fFlag" + std::to_string(i));

		fFlagsCheckboxes.push_back(checkbox);
		if (!checkbox)
			continue;
		checkbox->connect("Changed", [i, fFlags, &object](bool b){
			if (*c)
				return;

			auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];

			*c = true;
			data.traits.frameFlags = (data.traits.frameFlags & ~(1 << i)) | b << i;
			fFlags->setText(std::to_string(data.traits.frameFlags));
			*c = false;
		});
	}
	fFlags->connect("TextChanged", [&object, fFlagsCheckboxes](std::string t){
		if (t.empty())
			return;

		auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];
		auto g = *c;

		if (!*c) {
			*c = true;
			data.traits.frameFlags = std::stoul(t);
		}
		for (int i = 0; i < 32; i++)
			if (fFlagsCheckboxes[i])
				fFlagsCheckboxes[i]->setChecked((data.traits.frameFlags & (1 << i)) != 0);
		if (!g)
			*c = false;
	});

	for (int i = 0; i < 32; i++) {
		auto checkbox = panel->get<tgui::CheckBox>("aFlag" + std::to_string(i));

		aFlagsCheckboxes.push_back(checkbox);
		if (!checkbox)
			continue;
		checkbox->connect("Changed", [i, aFlags, &object](bool b){
			if (*c)
				return;

			auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];

			*c = true;
			data.traits.attackFlags = (data.traits.attackFlags & ~(1 << i)) | b << i;
			aFlags->setText(std::to_string(data.traits.attackFlags));
			*c = false;
		});
	}
	aFlags->connect("TextChanged", [&object, aFlagsCheckboxes](std::string t){
		if (t.empty())
			return;

		auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];
		auto g = *c;

		if (!*c) {
			*c = true;
			data.traits.attackFlags = std::stoul(t);
		}
		for (int i = 0; i < 32; i++)
			if (aFlagsCheckboxes[i])
				aFlagsCheckboxes[i]->setChecked((data.traits.attackFlags & (1 << i)) != 0);
		if (!g)
			*c = false;
	});
}

void	removeBoxCallback(tgui::Panel::Ptr boxes, std::unique_ptr<EditableObject> &object, tgui::Panel::Ptr panel)
{
	if (!selectedBox)
		return;

	auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];

	if (selectedBox == &data.cBoxes.front()) {
		auto block = panel->get<tgui::CheckBox>("Collision");

		block->setChecked(false);
		selectBox(nullptr, nullptr);
		return;
	}
	for (auto it = data.aBoxes.begin(); it < data.aBoxes.end(); it++) {
		if (&*it == selectedBox) {
			data.aBoxes.erase(it);
			refreshBoxes(boxes, data, object);
			selectBox(nullptr, nullptr);
			return;
		}
	}
	for (auto it = data.hBoxes.begin(); it < data.hBoxes.end(); it++) {
		if (&*it == selectedBox) {
			data.hBoxes.erase(it);
			refreshBoxes(boxes, data, object);
			selectBox(nullptr, nullptr);
			return;
		}
	}
	my_assert(false);
}

void	quitCallback()
{
	quitRequest = true;
}

void	newFileCallback(std::unique_ptr<EditableObject> &object, tgui::MenuBar::Ptr bar, tgui::Gui &gui)
{
	Utils::dispMsg("Error", "Not implemented yet", MB_ICONERROR);
	return;
	object = std::make_unique<EditableObject>();
	loadedPath.clear();
	object->_moves[0].emplace_back();
	refreshRightPanel(gui, object);
	bar->setMenuEnabled({"New"}, true);
	bar->setMenuEnabled({"Remove"}, true);
	bar->setMenuEnabled({"Misc"}, true);
	bar->setMenuItemEnabled({"File", "Export..."}, true);
	bar->setMenuItemEnabled({"File", "Import...", "palette..."}, true);
}

void openFramedataFromPackage(std::unique_ptr<EditableObject> &object, tgui::MenuBar::Ptr bar, tgui::Gui &gui)
{
	auto window = Utils::openWindowWithFocus(gui, 300, 300);
	std::vector<std::string> chrs;
	tgui::ListBox::Ptr list = tgui::ListBox::create();

	for (auto &chr : game->characterPaths)
		chrs.push_back(chr.first);

	window->setTitle("Select character's framedata to load");
	std::sort(chrs.begin(), chrs.end());
	list->connect("DoubleClicked", [&object, bar, &gui, window](std::string character){
		editSession.palName = "data/character/" + character + "/palette000.pal";

		//auto path = Utils::openFileDialog("Open framedata", "assets", {{".*\\.json", "Frame data file"}});
		std::string path = "data/character/" + character + "/" + character + ".pat";
		auto pal = game->characterPaths[character].palettes.find(editSession.palName);
		auto entry = game->package.find(path, ShadyCore::FileType::TYPE_SCHEMA);

		game->logger.info("Loading framedata from package: " + path);
		if (entry == game->package.end()) {
			Utils::dispMsg("Loading error", "Could not find file " + path, MB_ICONERROR);
			return;
		}
		if (pal == game->characterPaths[character].palettes.end()) {
			Utils::dispMsg("Loading error", "Could not find palette " + editSession.palName, MB_ICONERROR);
			return;
		}

		editSession.chr = character;
		editSession.palName = pal->first;
		editSession.palette = &pal->second;
		tempSchema.destroy();
		ShadyCore::getResourceReader({ShadyCore::FileType::TYPE_SCHEMA, ShadyCore::FileType::SCHEMA_GAME_PATTERN})(&tempSchema, entry.open());
		entry.close();
		try {
			object.reset();
			object = std::make_unique<EditableObject>(editSession.chr, tempSchema, *editSession.palette, editSession.palName);
			loadedPath = path;
			refreshRightPanel(gui, object);
			bar->setMenuEnabled({"New"}, true);
			bar->setMenuEnabled({"Remove"}, true);
			bar->setMenuEnabled({"Misc"}, true);
			bar->setMenuItemEnabled({"File", "Export..."}, true);
			bar->setMenuItemEnabled({"File", "Import...", "palette..."}, true);
		} catch (std::exception &e) {
			Utils::dispMsg("Error", e.what(), MB_ICONERROR);
			loadedPath = path;
			refreshRightPanel(gui, object);
			bar->setMenuEnabled({"New"}, false);
			bar->setMenuEnabled({"Remove"}, false);
			bar->setMenuEnabled({"Misc"}, false);
			bar->setMenuItemEnabled({"File", "Export..."}, false);
			bar->setMenuItemEnabled({"File", "Import...", "palette..."}, false);
		}
		displayPalEditor(object, gui);
		window->close();
	});
	for (auto &character : chrs)
		list->addItem(character);
	list->setSize("&.w", "&.h");
	list->setScrollbarValue(0);
	window->add(list);
}

void openFramedataFromFile(std::unique_ptr<EditableObject> &object, tgui::MenuBar::Ptr bar, tgui::Gui &gui)
{
	auto path = Utils::openFileDialog("Open framedata file", ".",{{".*\\.pat", "Pattern file"}, {".*\\.xml", "XML file"}});

	if (path.empty())
		return;

	auto win = Utils::openWindowWithFocus(gui, 250, 70);

	win->loadWidgetsFromFile("assets/gui/edit.gui");

	auto edit = win->get<tgui::EditBox>("EditBox");
	auto cancel = win->get<tgui::Button>("Cancel");
	auto ok = win->get<tgui::Button>("OK");
	size_t pos;

	try {
		while ((pos = path.find_last_of('\\')) != std::string::npos)
			path[pos] = '/';
		edit->setText(path.substr(path.find_last_of('/') + 1, path.find_last_of('.') - path.find_last_of('/') - 1));
	} catch (...) {}
	win->setTitle("Enter character name");
	ok->connect("Clicked", [win, edit, &object, bar, &gui, path]{
		std::string character = edit->getText();

		editSession.palName = "data/character/" + character + "/palette000.pal";

		//auto path = Utils::openFileDialog("Open framedata", "assets", {{".*\\.json", "Frame data file"}});
		auto pal = game->characterPaths[character].palettes.find(editSession.palName);
		std::ifstream stream{path, std::fstream::binary};
		std::string ext = path.substr(path.find_last_of('.') + 1);

		game->logger.info("Loading framedata from file: " + path);
		if (stream.fail()) {
			Utils::dispMsg("Loading error", "Could not find file " + path + ": " + strerror(errno), MB_ICONERROR);
			return;
		}
		if (pal == game->characterPaths[character].palettes.end()) {
			Utils::dispMsg("Loading error", "Could not find palette " + editSession.palName, MB_ICONERROR);
			return;
		}

		editSession.chr = character;
		editSession.palName = pal->first;
		editSession.palette = &pal->second;
		tempSchema.destroy();
		ShadyCore::getResourceReader({ShadyCore::FileType::TYPE_SCHEMA, ext == "xml" ? ShadyCore::FileType::SCHEMA_XML : ShadyCore::FileType::SCHEMA_GAME_PATTERN})(&tempSchema, stream);
		try {
			object.reset();
			object = std::make_unique<EditableObject>(editSession.chr, tempSchema, *editSession.palette, editSession.palName);
			loadedPath = path;
			refreshRightPanel(gui, object);
			bar->setMenuEnabled({"New"}, true);
			bar->setMenuEnabled({"Remove"}, true);
			bar->setMenuEnabled({"Misc"}, true);
			bar->setMenuItemEnabled({"File", "Export..."}, true);
			bar->setMenuItemEnabled({"File", "Import...", "palette..."}, true);
		} catch (std::exception &e) {
			Utils::dispMsg("Error", e.what(), MB_ICONERROR);
			loadedPath = path;
			refreshRightPanel(gui, object);
			bar->setMenuEnabled({"New"}, false);
			bar->setMenuEnabled({"Remove"}, false);
			bar->setMenuEnabled({"Misc"}, false);
			bar->setMenuItemEnabled({"File", "Export..."}, false);
			bar->setMenuItemEnabled({"File", "Import...", "palette..."}, false);
		}
		displayPalEditor(object, gui);
		win->close();
	});
	cancel->connect("Clicked", [win]{
		win->close();
	});
}

void openPaletteFromFile(std::unique_ptr<EditableObject> &object, tgui::MenuBar::Ptr bar, tgui::Gui &gui)
{
	//TODO: Save last folder
	auto path = Utils::openFileDialog("Open palette file", ".", {{".*\\.pal", "Palette editor palette"}});

	if (path.empty())
		return;
	game->logger.info("Loading palette from file: " + path);

	auto entry = game->characterPaths[editSession.chr].palettes.find(path);
	ShadyCore::Palette *pal;

	if (entry == game->characterPaths[editSession.chr].palettes.end()) {
		std::ifstream stream(path, std::fstream::binary);

		if (stream.fail()) {
			Utils::dispMsg("Error", "Could not open " + path + ": " + strerror(errno), MB_ICONERROR);
			return;
		}
		pal = &game->characterPaths[editSession.chr].palettes[path];
		ShadyCore::getResourceReader({ShadyCore::FileType::TYPE_PALETTE, ShadyCore::FileType::PALETTE_PAL})(pal, stream);
	} else
		pal = &entry->second;

	for (auto &action : object->_moves)
		for (auto &block : action.second)
			for (auto &anim : block)
				anim.setPalette(*pal, path);
	editSession.palette = pal;
	editSession.palName = path;
	displayPalEditor(object, gui);
}

void openPaletteFromPackage(std::unique_ptr<EditableObject> &object, tgui::MenuBar::Ptr bar, tgui::Gui &gui)
{
	auto window = Utils::openWindowWithFocus(gui, 300, 300);
	std::vector<std::string> pals;
	tgui::ListBox::Ptr list = tgui::ListBox::create();

	for (auto &pal : game->characterPaths[editSession.chr].palettes)
		pals.push_back(pal.first);

	window->setTitle("Select character's palette to load");
	std::sort(pals.begin(), pals.end());
	list->connect("DoubleClicked", [&object, bar, &gui, window](std::string palette){
		game->logger.info("Loading palette from package: " + palette);

		auto &pal = game->characterPaths[editSession.chr].palettes[palette];

		for (auto &action : object->_moves)
			for (auto &block : action.second)
				for (auto &anim : block)
					anim.setPalette(pal, palette);
		editSession.palette = &pal;
		editSession.palName = palette;
		window->close();
		displayPalEditor(object, gui);
	});
	for (auto &pal : pals)
		list->addItem(pal);
	list->setSize("&.w", "&.h");
	list->setScrollbarValue(0);
	window->add(list);
}

void openPaletteFromPalEditor(std::unique_ptr<EditableObject> &object, tgui::MenuBar::Ptr bar, tgui::Gui &gui)
{
	//TODO: Save last folder
	auto path = Utils::openFileDialog("Open palette file", ".", {{".*\\.pal", "Palette editor palette"}});

	if (path.empty())
		return;
	game->logger.info("Loading palette from old pal editor file: " + path);

	struct stat s;

	if (stat(path.c_str(), &s) == -1) {
		Utils::dispMsg("Error", "Could not stat " + path + ": " + strerror(errno), MB_ICONERROR);
		return;
	}
	if (s.st_size < 1028) {
		Utils::dispMsg("Error", "File " + path + " is empty", MB_ICONERROR);
		return;
	}

	auto entry = game->characterPaths[editSession.chr].palettes.find(path);
	ShadyCore::Palette *pal;

	if (entry == game->characterPaths[editSession.chr].palettes.end()) {
		std::ifstream stream{path, std::ifstream::binary};

		if (stream.fail()) {
			Utils::dispMsg("Error", "Could not open file", MB_ICONERROR);
			return;
		}

		auto data = new uint32_t[256];
		auto metadata = new char[s.st_size - 1024];
		struct {
			const char *character;
			const char *name;
			const char *description;
			const char *author;
		} meta;

		stream.read((char *)data, 1024);
		stream.read(metadata, s.st_size - 1024);
		game->characterPaths[editSession.chr].palettes.erase(path);

		meta.character = metadata;
		game->logger.debug("Palette is meant for character " + std::string(meta.character));

		meta.name = meta.character + strlen(meta.character) + 1;
		game->logger.debug("  - Name " + std::string(meta.name));

		meta.description = meta.name + strlen(meta.name) + 1;
		game->logger.debug("  - Description " + std::string(meta.description));

		meta.author = meta.description + strlen(meta.description) + 1;
		game->logger.debug("  - Author " + std::string(meta.author));

		if (*meta.name || *meta.author || *meta.description)
			Utils::dispMsg("Metadata", "Palette " + std::string(meta.name) + " made by " + std::string(meta.author) + "\n\"" + meta.description + "\"\nPlease, be sure to credit the other when redistributing.", MB_ICONINFORMATION);
		pal = &game->characterPaths[editSession.chr].palettes[path];
		pal->initialize(16);

		auto palData = (uint16_t *)pal->data;

		memset(pal->data, 0, 512);
		for (int i = 0; i < 256; i++) {
			palData[i] |= (data[i] >> 19 & 0x1F) << 10;
			palData[i] |= (data[i] >> 11 & 0x1F) << 5;
			palData[i] |= (data[i] >> 3  & 0x1F) << 0;
			if (i)
				palData[i] |= 0x8000;
		}
		delete[] data;
		delete[] metadata;
	} else
		pal = &game->characterPaths[editSession.chr].palettes[path];

	for (auto &action : object->_moves)
		for (auto &block : action.second)
			for (auto &anim : block)
				anim.setPalette(*pal, path);
	editSession.palette = pal;
	editSession.palName = path;
	displayPalEditor(object, gui);
}

void saveFramedataToPackageCallback(std::unique_ptr<EditableObject> &object)
{
	//TODO: Save
	Utils::dispMsg("Error", "Not implemented yet", MB_ICONERROR);
}

bool saveFramedataToFileCallback(std::unique_ptr<EditableObject> &object)
{
	auto path = Utils::saveFileDialog(
		"Save pattern file",
		editSession.chr,
		{{".*\\.pat", "Pattern file"}, {".*\\.xml", "XML file"}}
	);

	if (path.empty())
		return false;

	std::string ext = path.substr(path.find_last_of('.') + 1);
	std::ofstream stream{path, std::fstream::binary};

	if (stream.fail()) {
		Utils::dispMsg("Error", "Could not open file " + path, MB_ICONERROR);
		return false;
	}
	ShadyCore::getResourceWriter({ShadyCore::FileType::TYPE_SCHEMA, ext == "xml" ? ShadyCore::FileType::SCHEMA_XML : ShadyCore::FileType::SCHEMA_GAME_PATTERN})(&tempSchema, stream);
	return true;
}

void savePaletteToFileCallback(std::unique_ptr<EditableObject> &object)
{
	auto path = Utils::saveFileDialog(
		"Save palette file",
		editSession.palName.substr(0, 5) == "data/" ? "." :
		editSession.palName,
		{{".*\\.pal", "Palette file"}}
	);

	if (path.empty())
		return;

	std::ofstream stream{path, std::fstream::binary};

	if (stream.fail()) {
		Utils::dispMsg("Error", "Could not open file " + path, MB_ICONERROR);
		return;
	}
	ShadyCore::getResourceWriter({ShadyCore::FileType::TYPE_PALETTE, ShadyCore::FileType::PALETTE_PAL})(editSession.palette, stream);
}

void savePaletteToPackageCallback(std::unique_ptr<EditableObject> &object)
{
	//TODO: Save
	Utils::dispMsg("Error", "Not implemented yet", MB_ICONERROR);
}

void	newFrameCallback(tgui::Gui &gui, std::unique_ptr<EditableObject> &object, tgui::Panel::Ptr panel)
{
	object->_moves.at(object->_action)[object->_actionBlock].insert(object->_moves.at(object->_action)[object->_actionBlock].begin() + object->_animation, object->_moves.at(object->_action)[object->_actionBlock][object->_animation]);

	auto anim = object->_animation + 1;
	auto oldBlock = object->_actionBlock;

	refreshRightPanel(gui, object, false);

	auto block = panel->get<tgui::SpinButton>("Block");
	auto frame = panel->get<tgui::Slider>("Progress");

	block->setValue(oldBlock);
	frame->setValue(anim);
}

void	newEndFrameCallback(tgui::Gui &gui, std::unique_ptr<EditableObject> &object, tgui::Panel::Ptr panel)
{
	object->_moves.at(object->_action)[object->_actionBlock].push_back(object->_moves.at(object->_action)[object->_actionBlock][object->_animation]);

	auto oldBlock = object->_actionBlock;

	refreshRightPanel(gui, object, false);

	auto block = panel->get<tgui::SpinButton>("Block");
	auto frame = panel->get<tgui::Slider>("Progress");

	block->setValue(oldBlock);
	frame->setValue(object->_moves.at(object->_action)[object->_actionBlock].size() - 1);
}

void	newAnimBlockCallback(tgui::Gui &gui, std::unique_ptr<EditableObject> &object, tgui::Panel::Ptr panel)
{
	auto newElem = new ShadyCore::Schema::Sequence::MoveFrame();

	tempSchema.objects.push_back(reinterpret_cast<ShadyCore::Schema::Object *const>(newElem));
	object->_actionBlock = object->_moves.at(object->_action).size();
	object->_moves.at(object->_action).emplace_back();
	object->_moves.at(object->_action).back().emplace_back(editSession.chr, tempSchema, *newElem, *editSession.palette, editSession.palName);
	refreshRightPanel(gui, object, false);

	auto block = panel->get<tgui::SpinButton>("Block");

	block->setValue(object->_moves.at(object->_action).size() - 1);
}

void	newHurtBoxCallback(std::unique_ptr<EditableObject> &object, tgui::Panel::Ptr boxes)
{
	object->_moves.at(object->_action)[object->_actionBlock][object->_animation].hBoxes.push_back({-10, 10, 10, -10});

	auto &box = object->_moves.at(object->_action)[object->_actionBlock][object->_animation].hBoxes.back();

	refreshBoxes(boxes, object->_moves.at(object->_action)[object->_actionBlock][object->_animation], object);
	selectBox(boxes->get<tgui::Button>("HurtBox" + std::to_string(object->_moves.at(object->_action)[object->_actionBlock][object->_animation].hBoxes.size() - 1)), &box);
}

void	newHitBoxCallback(std::unique_ptr<EditableObject> &object, tgui::Panel::Ptr boxes)
{
	object->_moves.at(object->_action)[object->_actionBlock][object->_animation].aBoxes.push_back({-10, 10, 10, -10});

	auto &box = object->_moves.at(object->_action)[object->_actionBlock][object->_animation].aBoxes.back();

	refreshBoxes(boxes, object->_moves.at(object->_action)[object->_actionBlock][object->_animation], object);
	selectBox(boxes->get<tgui::Button>("HitBox" + std::to_string(object->_moves.at(object->_action)[object->_actionBlock][object->_animation].aBoxes.size() - 1)), &box);
}

void	removeFrameCallback(std::unique_ptr<EditableObject> &object, tgui::Panel::Ptr boxes)
{
	auto &arr = object->_moves.at(object->_action)[object->_actionBlock];

	if (arr.size() == 1) {
		auto newElem = new ShadyCore::Schema::Sequence::MoveFrame();

		tempSchema.objects.push_back(reinterpret_cast<ShadyCore::Schema::Object *const>(newElem));
		arr.back() = FrameData(editSession.chr, tempSchema, *newElem, *editSession.palette, editSession.palName);
		refreshBoxes(boxes, arr.back(), object);
		selectBox(nullptr, nullptr);
		return;
	}
	arr.erase(arr.begin() + object->_animation);
	if (object->_animation == arr.size())
		object->_animation--;
	refreshBoxes(boxes, arr[object->_animation], object);
	selectBox(nullptr, nullptr);
}

void	removeAnimationBlockCallback(std::unique_ptr<EditableObject> &object)
{
	auto &arr = object->_moves.at(object->_action);

	if (arr.size() == 1) {
		auto newElem = new ShadyCore::Schema::Sequence::MoveFrame();

		tempSchema.objects.push_back(reinterpret_cast<ShadyCore::Schema::Object *const>(newElem));
		arr.back().clear();
		arr.back().emplace_back(editSession.chr, tempSchema, *newElem, *editSession.palette, editSession.palName);
		return;
	}
	arr.erase(arr.begin() + object->_actionBlock);
	if (object->_actionBlock == arr.size())
		object->_actionBlock--;
}

void	removeActionCallback(tgui::Gui &gui, std::unique_ptr<EditableObject> &object)
{
	if (object->_action == 0)
		return;

	auto it = object->_moves.find(object->_action);

	object->_moves.erase(it);
	refreshRightPanel(gui, object);
}

void	copyBoxesFromFrame(std::unique_ptr<EditableObject> &object, tgui::Panel::Ptr boxes, FrameData &other)
{
	auto &frame = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];

	frame.hBoxes = other.hBoxes;
	frame.aBoxes = other.aBoxes;
	refreshBoxes(boxes, frame, object);
}

void	copyBoxesFromLastFrame(std::unique_ptr<EditableObject> &object, tgui::Panel::Ptr boxes)
{
	if (!object->_animation)
		return;
	copyBoxesFromFrame(object, boxes, object->_moves.at(object->_action)[object->_actionBlock][object->_animation - 1]);
}

void	copyBoxesFromNextFrame(std::unique_ptr<EditableObject> &object, tgui::Panel::Ptr boxes)
{
	if (object->_animation >= object->_moves.at(object->_action)[object->_actionBlock].size() - 1)
		return;
	copyBoxesFromFrame(object, boxes, object->_moves.at(object->_action)[object->_actionBlock][object->_animation + 1]);
}

void	flattenCollisionBoxes(std::unique_ptr<EditableObject> &object, std::vector<std::vector<FrameData>> &action, FrameData *base)
{
	if (!base)
		for (auto &block : action)
			for (auto &frame : block)
				if (!frame.cBoxes.empty()) {
					base = &frame;
					goto allGood;
				}
	if (!base || base->cBoxes.empty())
		return;

allGood:
	for (auto &block : action)
		for (auto &frame : block)
			if (!frame.cBoxes.empty() && &frame != base) {
				frame.cBoxes.clear();
				frame.cBoxes.push_back(base->cBoxes.front());
			}
}

void	flattenAllCollisionBoxes(std::unique_ptr<EditableObject> &object, tgui::Panel::Ptr boxes)
{
	for (auto &[id, action] : object->_moves) {
		if (id < 100 && !action.front().front().cBoxes.empty() && id) {
			action.front().front().cBoxes.clear();
			action.front().front().cBoxes.push_back(object->_moves.at(0)[0][0].cBoxes.front());
		}
		flattenCollisionBoxes(object, action, nullptr);
	}
	refreshBoxes(std::move(boxes), object->_moves.at(object->_action)[object->_actionBlock][object->_animation], object);
}

void	flattenThisMoveCollisionBoxes(std::unique_ptr<EditableObject> &object, tgui::Panel::Ptr boxes)
{
	flattenCollisionBoxes(object, object->_moves.at(object->_action), &object->_moves.at(object->_action)[object->_actionBlock][object->_animation]);
	refreshBoxes(std::move(boxes), object->_moves.at(object->_action)[object->_actionBlock][object->_animation], object);
}

void	switchHitboxes(tgui::Panel::Ptr boxes)
{
	displayHitboxes = !displayHitboxes;
	boxes->setVisible(displayHitboxes);
}

void	displayPalEditorForce(std::unique_ptr<EditableObject> &object, tgui::Gui &gui)
{
	displayPalEditor(object, gui, true);
}

void	displayPalEditor(std::unique_ptr<EditableObject> &object, tgui::Gui &gui, bool force)
{
	auto f = std::make_shared<bool>(false);
	tgui::ChildWindow::Ptr window = gui.get<tgui::ChildWindow>("PaletteEditor");

	if (!window && !force)
		return;
	force = false;
	if (!window) {
		window = tgui::ChildWindow::create();
		window->setTitle("Palette editor");
		window->setPosition(200, 30);
		Utils::setRenderer(window);
		window->setSize(490, 450);
		force = true;
	}
	window->loadWidgetsFromFile("assets/gui/palEditor.gui");

	char buffer[8];
	auto pal = window->get<tgui::ComboBox>("Palettes");
	auto col = window->get<tgui::ScrollablePanel>("Colors");
	auto light = window->get<tgui::Slider>("Lightness");
	auto satHuePic = window->get<tgui::Picture>("SatHue");
	auto cross = window->get<tgui::Picture>("Cross");
	auto preview = window->get<tgui::TextBox>("Preview");
	auto hue = window->get<tgui::EditBox>("Hue");
	auto saturation = window->get<tgui::EditBox>("Sat");
	auto lightness = window->get<tgui::EditBox>("Light");
	auto edit = window->get<tgui::EditBox>("Edit");
	auto updatePalButton = [f, col, pal, &object](sf::Color bufferColor){
		if (*f)
			return;

		auto button = col->get<tgui::Button>("Color" + std::to_string(selectedColor));

		if (!button)
			return;
		if (!editSession.palette)
			return;

		auto renderer = button->getRenderer();
		auto &newpal = ((uint16_t*)editSession.palette->data)[selectedColor];

		newpal = 0;
		newpal |= (bufferColor.r >> 3 & 0x1F) << 10;
		newpal |= (bufferColor.g >> 3 & 0x1F) << 5;
		newpal |= (bufferColor.b >> 3  & 0x1F) << 0;
		if (selectedColor)
			newpal |= 0x8000;
		renderer->setBackgroundColor(bufferColor);
		renderer->setBackgroundColorDown(bufferColor);
		renderer->setBackgroundColorDisabled(bufferColor);
		renderer->setBackgroundColorFocused(bufferColor);
		renderer->setBackgroundColorHover(bufferColor);
		game->textureMgr.invalidatePalette(editSession.palName);
		for (auto &action : object->_moves)
			for (auto &block : action.second)
				for (auto &anim : block)
					anim.setPalette(*editSession.palette, editSession.palName);
	};
	auto updateTexture = [updatePalButton, light](Utils::HSLColor color, sf::Color bufferColor, bool modified) {
		sf::Image image;
		sf::Texture texture;

		image.create(light->getSize().x, light->getSize().y);

		auto size = image.getSize();

		for (unsigned y = 0; y < size.y; y++) {
			color.l = 240 - (240 * y / size.y);

			auto rgb = HSLtoRGB(color);
			sf::Color sf{rgb.r, rgb.g, rgb.b, 255};

			for (unsigned x = 0; x < size.x; x++)
				image.setPixel(x, y, sf);
		}
		texture.loadFromImage(image);
		light->getRenderer()->setTextureTrack({texture});
		if (modified)
			updatePalButton(bufferColor);
	};
	auto buttonCallBack = [edit, satHuePic, preview, light, hue, saturation, lightness, cross](tgui::Button::Ptr button){
		char buffer[8];
		auto c = button->getRenderer()->getBackgroundColor();
		sf::Color temp = {
			c.getRed(),
			c.getGreen(),
			c.getBlue()
		};
		Utils::HSLColor color = Utils::RGBtoHSL(temp);
		auto pos = satHuePic->getPosition();
		auto size = cross->getSize();

		sprintf(buffer, "#%02X%02X%02X", temp.r, temp.g, temp.b);
		light->setValue(color.l);
		hue->setText(std::to_string(color.h));
		saturation->setText(std::to_string(color.s));
		lightness->setText(std::to_string(color.l));
		cross->setPosition({
			(color.h * 200 / 240) + pos.x - size.x / 2,
			((240 - color.s) * 200 / 240) + pos.y - size.y / 2
		});
		edit->setText(buffer);
		preview->getRenderer()->setBackgroundColor(c);
	};
	auto sliderCallback = [updatePalButton, cross, light, lightness, satHuePic, hue, saturation, preview, edit]{
		char buffer[8];
		unsigned char h = (cross->getSize().x / 2 + cross->getPosition().x - satHuePic->getPosition().x) * 240 / 200;
		unsigned char s = 240 - (cross->getSize().y / 2 + cross->getPosition().y - satHuePic->getPosition().y) * 240 / 200;
		Utils::HSLColor color = {
			h,
			s,
			static_cast<unsigned char>(light->getValue())
		};
		sf::Color bufferColor = HSLtoRGB(color);

		sprintf(buffer, "#%02X%02X%02X", bufferColor.r, bufferColor.g, bufferColor.b);
		preview->getRenderer()->setBackgroundColor({bufferColor.r, bufferColor.g, bufferColor.b, 255});
		edit->setText(buffer);
		light->setValue(color.l);
		lightness->setText(std::to_string(color.l));
		updatePalButton(bufferColor);
	};

	for (auto &id : window->getWidgetNames())
		if (id.substring(0, strlen("Button")) == "Button") {
			auto button = window->get<tgui::Button>(id);

			button->connect("Clicked", buttonCallBack, button);
		}
	light->connect("ValueChanged", sliderCallback);
	edit->onReturnKeyPress.connect([f, cross, hue, saturation, light, lightness, satHuePic, edit, updateTexture]{
		std::string text = edit->getText();

		if (text.size() > 7) {
			edit->setText(text.substr(0, 7));
			return;
		} else if (text.size() != 7)
			return;

		tgui::Color color{edit->getText()};
		sf::Color bufferColor{
			color.getRed(),
			color.getGreen(),
			color.getBlue()
		};
		auto tmp = Utils::RGBtoHSL(bufferColor);
		auto pos = satHuePic->getPosition();
		auto size = cross->getSize();

		light->setValue(tmp.l);
		hue->setText(std::to_string(tmp.h));
		saturation->setText(std::to_string(tmp.s));
		lightness->setText(std::to_string(tmp.l));
		cross->setPosition({
			(tmp.h * 200 / 240.f) + pos.x - size.x / 2,
			((240 - tmp.s) * 200 / 240.f) + pos.y - size.y / 2
		});
		updateTexture(tmp, bufferColor, true);
	});
	hue->onReturnKeyPress.connect([cross, satHuePic, light, hue, saturation, lightness, edit, preview, updateTexture]{
		unsigned char h;

		try {
			auto nbr = std::stoul(hue->getText().toAnsiString());

			if (nbr > 240) {
				hue->setText("240");
				return;
			}
			h = nbr;
		} catch (...) { hue->setText("0"); return; }

		char buffer[8];
		unsigned char s = 240 - (cross->getSize().y / 2 + cross->getPosition().y - satHuePic->getPosition().y) * 240 / 200;
		Utils::HSLColor color = {
			h,
			s,
			static_cast<unsigned char>(light->getValue())
		};
		sf::Color temp = HSLtoRGB(color);
		auto pos = satHuePic->getPosition();
		auto size = cross->getSize();

		sprintf(buffer, "#%02X%02X%02X", temp.r, temp.g, temp.b);
		cross->setPosition({
			(h * 200 / 240) + pos.x - size.x / 2,
			cross->getPosition().y
		});
		edit->setText(buffer);
		preview->getRenderer()->setBackgroundColor({buffer});
		updateTexture(color, temp, true);
	});
	saturation->onReturnKeyPress.connect([cross, satHuePic, light, hue, saturation, lightness, edit, preview, updateTexture]{
		unsigned char s;

		try {
			auto nbr = std::stoul(saturation->getText().toAnsiString());

			if (nbr > 240) {
				saturation->setText("240");
				return;
			}
			s = nbr;
		} catch (...) { saturation->setText("0"); return; }

		char buffer[8];
		unsigned char h = (cross->getSize().x / 2 + cross->getPosition().x - satHuePic->getPosition().x) * 240 / 200;
		Utils::HSLColor color = {
			h,
			s,
			static_cast<unsigned char>(light->getValue())
		};
		sf::Color temp = HSLtoRGB(color);
		auto pos = satHuePic->getPosition();
		auto size = cross->getSize();

		sprintf(buffer, "#%02X%02X%02X", temp.r, temp.g, temp.b);
		cross->setPosition({
			(color.h * 200 / 240) + pos.x - size.x / 2,
			((240 - color.s) * 200 / 240) + pos.y - size.y / 2
		});
		edit->setText(buffer);
		preview->getRenderer()->setBackgroundColor({buffer});
		updateTexture(color, temp, true);
	});
	lightness->onReturnKeyPress.connect([updatePalButton, cross, satHuePic, light, hue, saturation, lightness, edit, preview]{
		unsigned char l;

		try {
			auto nbr = std::stoul(lightness->getText().toAnsiString());

			if (nbr > 240) {
				lightness->setText("0");
				return;
			}
			l = nbr;
		} catch (...) { lightness->setText("0"); return; }

		char buffer[8];
		unsigned char h = (cross->getSize().x / 2 + cross->getPosition().x - satHuePic->getPosition().x) * 240 / 200.;
		unsigned char s = 240 - (cross->getSize().y / 2 + cross->getPosition().y - satHuePic->getPosition().y) * 240 / 200;
		Utils::HSLColor color = {
			h,
			s,
			l
		};
		sf::Color temp = HSLtoRGB(color);
		tgui::Color tcolor{buffer};

		sprintf(buffer, "#%02X%02X%02X", temp.r, temp.g, temp.b);
		light->setValue(l);
		edit->setText(buffer);
		preview->getRenderer()->setBackgroundColor(tcolor);
		updatePalButton({
			tcolor.getRed(),
			tcolor.getGreen(),
			tcolor.getBlue(),
			tcolor.getAlpha()
		});
	});
	auto v = editSession.palette ? ((uint16_t *)editSession.palette->data)[selectedColor] : 0;
	sf::Color startColor{
		static_cast<sf::Uint8>((v & 0b0111110000000000) >> 7 | (v & 0b0111000000000000) >> 12),
		static_cast<sf::Uint8>((v & 0b0000001111100000) >> 2 | (v & 0b0000001110000000) >> 7),
		static_cast<sf::Uint8>((v & 0b0000000000011111) << 3 | (v & 0b0000000000011100) >> 2),
		static_cast<sf::Uint8>((v & 0x8000) ? 255 : 0)
	};
	Utils::HSLColor c = Utils::RGBtoHSL(startColor);
	auto pos = satHuePic->getPosition();
	auto size = cross->getSize();

	sprintf(buffer, "#%02X%02X%02X", startColor.r, startColor.g, startColor.b);
	light->setValue(c.l);
	hue->setText(std::to_string(c.h));
	saturation->setText(std::to_string(c.s));
	lightness->setText(std::to_string(c.l));
	cross->setPosition({
		(c.h * 200 / 240) + pos.x - size.x / 2,
		((240 - c.s) * 200 / 240) + pos.y - size.y / 2
	});
	edit->setText(buffer);
	preview->getRenderer()->setBackgroundColor({buffer});
	updateTexture(c, startColor, false);

	cross->ignoreMouseEvents();

	auto colorPickHandler = [cross, satHuePic, light, hue, saturation, edit, preview, updateTexture](tgui::Vector2f pos){
		char buffer[8];
		unsigned char h = pos.x * 240 / 200;
		unsigned char s = 240 - pos.y * 240 / 200;
		Utils::HSLColor color = {
			h,
			s,
			static_cast<unsigned char>(light->getValue())
		};
		sf::Color temp = HSLtoRGB(color);
		auto size = cross->getSize();

		sprintf(buffer, "#%02X%02X%02X", temp.r, temp.g, temp.b);
		hue->setText(std::to_string(color.h));
		saturation->setText(std::to_string(color.s));
		cross->setPosition({
			(color.h * 200 / 240) + satHuePic->getPosition().x - size.x / 2,
			((240 - color.s) * 200 / 240) + satHuePic->getPosition().y - size.y / 2
		});
		edit->setText(buffer);
		preview->getRenderer()->setBackgroundColor({buffer});
		updateTexture(color, temp, true);
	};

	satHuePic->onMousePress.connect(colorPickHandler);
	satHuePic->onMouseRelease.connect(colorPickHandler);

	col->removeAllWidgets();
	if (!editSession.palette) {
		gui.add(window, "PaletteEditor");
		pal->setEnabled(false);
		if (force)
			gui.add(window, "PaletteEditor");
		return;
	}

	auto lab = tgui::Label::create();

	lab->setPosition(0, 16 * 23);
	col->add(lab);
	for (auto &[name, _] : game->characterPaths[editSession.chr].palettes)
		pal->addItem(name);
	pal->setSelectedItem(editSession.palName);
	pal->connect("ItemSelected", [&object, &gui](const std::string &palette) {
		game->logger.info("Loading palette from package: " + palette);

		auto &pal = game->characterPaths[editSession.chr].palettes[palette];

		for (auto &action : object->_moves)
			for (auto &block : action.second)
				for (auto &anim : block)
					anim.setPalette(pal, palette);
		editSession.palette = &pal;
		editSession.palName = palette;
		displayPalEditor(object, gui);
	});
	for (int i = 0; i < 256; i++) {
		auto button = tgui::Button::create();
		auto renderer = button->getRenderer();
		auto val = ((uint16_t*)editSession.palette->data)[i];
		sf::Color color{
			static_cast<sf::Uint8>((val & 0b0111110000000000) >> 7 | (val & 0b0111000000000000) >> 12),
			static_cast<sf::Uint8>((val & 0b0000001111100000) >> 2 | (val & 0b0000001110000000) >> 7),
			static_cast<sf::Uint8>((val & 0b0000000000011111) << 3 | (val & 0b0000000000011100) >> 2),
			static_cast<sf::Uint8>((val & 0x8000) ? 255 : 0)
		};

		button->setSize(20, 20);
		button->setPosition(5 + (i % 16) * 29.5, 5 + (i / 16) * 23);
		//TODO: Fix memory leaks like this (col is captured by copy so they are never actually freed)
		button->connect("Clicked", [col, satHuePic, i, pal, light, hue, saturation, lightness, cross, edit, preview, updateTexture](std::weak_ptr<tgui::Button> ptr){
			col->get<tgui::Button>("Color" + std::to_string(selectedColor))->setFocused(false);
			selectedColor = i;

			char buffer[8];
			auto val = ((uint16_t*)editSession.palette->data)[i];
			sf::Color color{
				static_cast<sf::Uint8>((val & 0b0111110000000000) >> 7 | (val & 0b0111000000000000) >> 12),
				static_cast<sf::Uint8>((val & 0b0000001111100000) >> 2 | (val & 0b0000001110000000) >> 7),
				static_cast<sf::Uint8>((val & 0b0000000000011111) << 3 | (val & 0b0000000000011100) >> 2),
				static_cast<sf::Uint8>((val & 0x8000) ? 255 : 0)
			};
			Utils::HSLColor c = Utils::RGBtoHSL(color);
			auto pos = satHuePic->getPosition();
			auto size = cross->getSize();

			sprintf(buffer, "#%02X%02X%02X", color.r, color.g, color.b);
			light->onValueChange.setEnabled(false);
			light->setValue(c.l);
			light->onValueChange.setEnabled(true);
			hue->setText(std::to_string(c.h));
			saturation->setText(std::to_string(c.s));
			lightness->setText(std::to_string(c.l));
			cross->setPosition({
				(c.h * 200 / 240) + pos.x - size.x / 2,
				((240 - c.s) * 200 / 240) + pos.y - size.y / 2
			});
			edit->setText(buffer);
			preview->getRenderer()->setBackgroundColor({buffer});
			updateTexture(c, color, false);
			ptr.lock()->setFocused(true);
		}, std::weak_ptr(button));
		button->connect("RightClicked", [col, satHuePic, i, pal, light, hue, saturation, lightness, cross, edit, preview, updateTexture](std::weak_ptr<tgui::Button> ptr){
			if (i == selectedColor)
				return;

			char buffer[8];
			auto val = ((uint16_t*)editSession.palette->data)[i];
			sf::Color color{
				static_cast<sf::Uint8>((val & 0b0111110000000000) >> 7 | (val & 0b0111000000000000) >> 12),
				static_cast<sf::Uint8>((val & 0b0000001111100000) >> 2 | (val & 0b0000001110000000) >> 7),
				static_cast<sf::Uint8>((val & 0b0000000000011111) << 3 | (val & 0b0000000000011100) >> 2),
				static_cast<sf::Uint8>((val & 0x8000) ? 255 : 0)
			};
			Utils::HSLColor c = Utils::RGBtoHSL(color);
			auto pos = satHuePic->getPosition();
			auto size = cross->getSize();

			sprintf(buffer, "#%02X%02X%02X", color.r, color.g, color.b);
			light->setValue(c.l);
			hue->setText(std::to_string(c.h));
			saturation->setText(std::to_string(c.s));
			lightness->setText(std::to_string(c.l));
			cross->setPosition({
				(c.h * 200 / 240) + pos.x - size.x / 2,
				((240 - c.s) * 200 / 240) + pos.y - size.y / 2
			});
			edit->setText(buffer);
			preview->getRenderer()->setBackgroundColor({buffer});
			updateTexture(c, color, true);
			ptr.lock()->setFocused(false);
			col->get<tgui::Button>("Color" + std::to_string(selectedColor))->setFocused(true);
		}, std::weak_ptr(button));
		renderer->setBackgroundColor(color);
		renderer->setBackgroundColorDown(color);
		renderer->setBackgroundColorDisabled(color);
		renderer->setBackgroundColorFocused(color);
		renderer->setBackgroundColorHover(color);
		renderer->setBorderColorFocused(sf::Color::Red);
		button->setFocused(i == selectedColor);
		col->add(button, "Color" + std::to_string(i));
	}
	if (force)
		gui.add(window, "PaletteEditor");
}

void	displayBlendingOptions(tgui::Gui &gui)
{
	//TODO: make this a proper window
	Utils::dispMsg("Not implemented", "Blending options are not yet implemented", MB_ICONINFORMATION);
}

void	saveSettings()
{
	nlohmann::json json;

	json["swr"] = swr;
	json["soku"] = soku;
	json["soku2"] = soku2;
	json["bgColor"] = bgColor.toInteger();

	std::ofstream stream("assets/settings.json");

	stream << json;
}

void	displaySettings(tgui::Gui &gui, std::unique_ptr<EditableObject> &object, tgui::MenuBar::Ptr bar)
{
	auto newSoku = std::make_shared<std::string>(soku);
	auto newSwr = std::make_shared<std::string>(swr);
	auto newSoku2 = std::make_shared<std::string>(soku2);
	auto newBgColor = std::make_shared<sf::Color>(bgColor);
	auto window = Utils::openWindowWithFocus(gui, 500, 140);

	window->loadWidgetsFromFile("assets/gui/settings.gui");
	window->setTitle("Settings");

	auto sokuPath = window->get<tgui::EditBox>("SokuPath");
	auto swrPath = window->get<tgui::EditBox>("SWRPath");
	auto soku2Path = window->get<tgui::EditBox>("Soku2Path");
	auto sokuBrowse = window->get<tgui::Button>("SokuBrowse");
	auto swrBrowse = window->get<tgui::Button>("SWRBrowse");
	auto soku2Browse = window->get<tgui::Button>("Soku2Browse");
	auto bg = window->get<tgui::Button>("BG");
	auto save = window->get<tgui::Button>("Save");
	auto cancel = window->get<tgui::Button>("Cancel");
	auto renderer = bg->getRenderer();

	sokuPath->setText(soku);
	swrPath->setText(swr);
	soku2Path->setText(soku2);

	renderer->setBackgroundColor(bgColor);
	renderer->setBackgroundColorDown(bgColor);
	renderer->setBackgroundColorDisabled(bgColor);
	renderer->setBackgroundColorFocused(bgColor);
	renderer->setBackgroundColorHover(bgColor);

	sokuBrowse->connect("Clicked", [newSoku, sokuPath]{
		auto path = Utils::openFileDialog("Select Soku dat", ".", {{"th123.\\.dat", "Touhou 12.3 dat file"}});

		if (path.empty())
			return;

		path = std::filesystem::path(path).parent_path().string();
		sokuPath->setText(path);
	});
	swrBrowse->connect("Clicked", [newSwr, swrPath]{
		auto path = Utils::openFileDialog("Select SWR dat", ".", {{"th105.\\.dat", "Touhou 10.5 dat file"}});

		if (path.empty())
			return;

		path = std::filesystem::path(path).parent_path().string();
		swrPath->setText(path);
	});
	soku2Browse->connect("Clicked", [newSoku2, soku2Path]{
		auto path = Utils::openFileDialog("Select Soku2 folder", ".", {{"[Ss][Oo][Kk][Uu]2\\.dll", "Soku2 mod file"}});

		if (path.empty())
			return;

		path = (std::filesystem::path(path).parent_path() / "characters").string();
		if (!exists(path))
			Utils::dispMsg("Invalid Soku2 path", "Cannot access Soku2 characters folder. " + path + ": " + strerror(errno), MB_ICONEXCLAMATION);
		soku2Path->setText(path);
	});
	sokuPath->connect("TextChanged", [newSoku](const std::string &text){
		*newSoku = text;
	});
	swrPath->connect("TextChanged", [newSwr](const std::string &text){
		*newSwr = text;
	});
	soku2Path->connect("TextChanged", [newSoku2](const std::string &text){
		*newSoku2 = text;
	});
	bg->connect("Clicked", [&gui, newBgColor, renderer]{
		Utils::makeColorPickWindow(gui, [newBgColor, renderer](sf::Color color){
			*newBgColor = color;
			renderer->setBackgroundColor(color);
			renderer->setBackgroundColorDown(color);
			renderer->setBackgroundColorDisabled(color);
			renderer->setBackgroundColorFocused(color);
			renderer->setBackgroundColorHover(color);
		}, *newBgColor);
	});
	cancel->connect("Clicked", [](std::weak_ptr<tgui::ChildWindow> window){
		window.lock()->close();
	}, std::weak_ptr(window));
	save->connect("Clicked", [&gui, bar, &object, newSoku, newSwr, newSoku2, newBgColor](std::weak_ptr<tgui::ChildWindow> window){
		bgColor = *newBgColor;
		if (soku == *newSoku && swr == *newSwr && soku2 == *newSoku2) {
			saveSettings();
			window.lock()->close();
			return;
		}
		soku = *newSoku;
		swr = *newSwr;
		soku2 = *newSoku2;
		try {
			verifySettings();
		} catch (std::exception &e) {
			game->logger.error(e.what());
			return;
		}
		object.reset();
		loadedPath.clear();
		refreshRightPanel(gui, object);
		bar->setMenuEnabled({"New"}, false);
		bar->setMenuEnabled({"Remove"}, false);
		bar->setMenuEnabled({"Misc"}, false);
		bar->setMenuItemEnabled({"File", "Export..."}, false);
		bar->setMenuItemEnabled({"File", "Import...", "palette..."}, false);
		tempSchema.destroy();
		try {
			loadPackages();
		} catch (std::exception &e) {
			game->logger.error(e.what());
			Utils::dispMsg("Loading error", e.what(), MB_ICONERROR);
			return;
		}
		saveSettings();
		window.lock()->close();
	}, std::weak_ptr(window));
}

void	displayAbout(tgui::Gui &gui)
{
	auto window = Utils::openWindowWithFocus(gui, 470, 120);

	window->loadWidgetsFromFile("assets/gui/about.gui");
	window->setTitle("About FrameDataEditor");
	window->get<tgui::Label>("Version")->setText(VERSION_STR);
}

void	createPalette(tgui::Gui &gui)
{
	editSession.palName = "*" + editSession.palName;

	auto &pale = game->characterPaths[editSession.chr].palettes[editSession.palName];

	pale.initialize(editSession.palette->bitsPerPixel);
	memcpy(pale.data, editSession.palette->data, 512);
	editSession.palette = &game->characterPaths[editSession.chr].palettes[editSession.palName];

	tgui::ChildWindow::Ptr window = gui.get<tgui::ChildWindow>("PaletteEditor");

	if (!window)
		return;

	auto pal = window->get<tgui::ComboBox>("Palettes");

	pal->addItem(editSession.palName);
	pal->setSelectedItem(editSession.palName);
}

void	placeGuiHooks(tgui::Gui &gui, std::unique_ptr<EditableObject> &object)
{
	auto bar = gui.get<tgui::MenuBar>("main_bar");
	auto panel = gui.get<tgui::Panel>("Panel1");
	auto boxes = gui.get<tgui::Panel>("Boxes");

	game->logger.debug("Placing hooks");
	placeAnimPanelHooks(gui, panel, boxes, object);

	bar->setMenuEnabled({"New"}, false);
	bar->setMenuEnabled({"Remove"}, false);
	bar->setMenuEnabled({"Misc"}, false);
	bar->setMenuItemEnabled({"File", "Export..."}, false);
	bar->setMenuItemEnabled({"File", "Import...", "palette..."}, false);

	bar->connectMenuItem({"File", "Import...", "framedata...", "from file"}, openFramedataFromFile, std::ref(object), bar, std::ref(gui));
	bar->connectMenuItem({"File", "Import...", "framedata...", "from game package"}, openFramedataFromPackage, std::ref(object), bar, std::ref(gui));
	bar->connectMenuItem({"File", "Import...", "palette...", "from file"}, openPaletteFromFile, std::ref(object), bar, std::ref(gui));
	bar->connectMenuItem({"File", "Import...", "palette...", "from loaded palettes"}, openPaletteFromPackage, std::ref(object), bar, std::ref(gui));
	bar->connectMenuItem({"File", "Import...", "palette...", "from palette editor format"}, openPaletteFromPalEditor, std::ref(object), bar, std::ref(gui));
	bar->connectMenuItem({"File", "Export...", "framedata...", "to file"}, saveFramedataToFileCallback, std::ref(object));
	bar->connectMenuItem({"File", "Export...", "framedata...", "to game package"}, saveFramedataToPackageCallback, std::ref(object));
	bar->connectMenuItem({"File", "Export...", "palette...", "to file"}, savePaletteToFileCallback, std::ref(object));
	bar->connectMenuItem({"File", "Export...", "palette...", "to game package"}, savePaletteToPackageCallback, std::ref(object));
	bar->connectMenuItem({"File", "Settings"}, displaySettings, std::ref(gui), std::ref(object), bar);
	bar->connectMenuItem({"File", "Quit (Ctrl + Q)"}, quitCallback);
	bar->connectMenuItem({"File", "New framedata (Ctrl + N)"}, newFileCallback, std::ref(object), bar, std::ref(gui));

	bar->connectMenuItem({"New", "Palette"}, createPalette, std::ref(gui));
	bar->connectMenuItem({"New", "Frame (Ctrl + F)"}, newFrameCallback, std::ref(gui), std::ref(object), panel);
	bar->connectMenuItem({"New", "End frame (Ctrl + Shift + F)"}, newEndFrameCallback, std::ref(gui), std::ref(object), panel);
	bar->connectMenuItem({"New", "Animation block (Ctrl + B)"}, newAnimBlockCallback, std::ref(gui), std::ref(object), panel);
	bar->connectMenuItem({"New", "Hurt box (Ctrl + H)"}, newHurtBoxCallback, std::ref(object), boxes);
	bar->connectMenuItem({"New", "Hit box (Ctrl + Shift + H)"}, newHitBoxCallback, std::ref(object), boxes);

	bar->connectMenuItem({"Remove", "Frame (Ctrl + Shift + Del)"}, removeFrameCallback, std::ref(object), boxes);
	bar->connectMenuItem({"Remove", "Animation block (Shift + Del)"}, removeAnimationBlockCallback, std::ref(object));
	bar->connectMenuItem({"Remove", "Action (Ctrl + Del)"}, removeActionCallback, std::ref(gui), std::ref(object));
	bar->connectMenuItem({"Remove", "Selected box (Del)"}, removeBoxCallback, boxes, std::ref(object), panel);

	bar->connectMenuItem({"Misc", "Copy boxes from last frame"}, copyBoxesFromLastFrame, std::ref(object), boxes);
	bar->connectMenuItem({"Misc", "Copy boxes from next frame"}, copyBoxesFromNextFrame, std::ref(object), boxes);
	bar->connectMenuItem({"Misc", "Flatten all collision boxes"}, flattenAllCollisionBoxes, std::ref(object), boxes);
	bar->connectMenuItem({"Misc", "Flatten this move collision boxes"}, flattenThisMoveCollisionBoxes, std::ref(object), boxes);
	bar->connectMenuItem({"Misc", "Reload textures"}, [&object]{
		game->logger.debug("Reloading textures");
		for (auto &action : object->_moves)
			for (auto &block : action.second)
				for (auto &anim : block)
					anim.reloadTexture();
	});
	bar->connectMenuItem({"Misc", "Reload palettes"}, []{
		game->logger.debug("Reloading palettes");
		Utils::dispMsg("Not implemented", "Reloading palettes is not yet implemented", MB_ICONINFORMATION);
	});

	bar->connectMenuItem({"View", "Palette editor"}, displayPalEditorForce, std::ref(object), std::ref(gui));
	bar->connectMenuItem({"View", "Blending options"}, displayBlendingOptions, std::ref(gui));
	bar->connectMenuItem({"View", "Hitboxes (H)"}, switchHitboxes, boxes);

	bar->connectMenuItem({"Help", "About"}, displayAbout, std::ref(gui));

	for (unsigned i = 0; i < resizeButtons.size(); i++) {
		auto &resizeButton = resizeButtons[i];

		resizeButton = tgui::Button::create();
		resizeButton->setVisible(false);
		resizeButton->setSize(8, 8);
		resizeButton->getRenderer()->setBackgroundColor(tgui::Color{0xA0, 0xA0, 0xA0});
		resizeButton->getRenderer()->setBorderColor(tgui::Color::Red);
		resizeButton->connect("MousePressed", [i]{
			canDrag = true;
			dragUp = i < 3;
			dragDown = i > 4;
			dragLeft = i == 0 || i == 3 || i == 5;
			dragRight = i == 2 || i == 4 || i == 7;
		});
		gui.add(resizeButton);
	}
}

void	handleDrag(tgui::Gui &gui, std::unique_ptr<EditableObject> &object, int mouseX, int mouseY)
{
	static bool bbb = false;

	if (!object)
		return;
	if (!selectedBox && !spriteSelected)
		return;
	if (mouseStart.distance(Vector2i{mouseX, mouseY}) > 10)
		dragStart = true;
	if (!dragStart)
		return;
	if (!dragLeft && !dragRight && !dragUp && !dragDown) {
		if (spriteSelected) {/*
			auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];
			Vector2i diff = Vector2i{mouseX, mouseY} - lastMouse;

			diff.y *= -1;
			data.offsetX += diff.x;
			data.offsetY += diff.y;
			boxButton->setPosition("&.w / 2 + " + std::to_string(static_cast<int>(data.offsetX - (data.texWidth * data.blendOptions.scaleX) / 2)), "&.h / 2 + " + std::to_string(data.offsetY + 300));
			gui.get<tgui::EditBox>("Offset")->setText("(" + std::to_string(data.offsetX) + "," + std::to_string(data.offsetY) + ")");
			arrangeButtons(&*object);*/
		} else {
			Vector2i diff{mouseX, mouseY};

			diff -= lastMouse;
			selectedBox->left += diff.x;
			selectedBox->right += diff.x;
			selectedBox->down += diff.y;
			selectedBox->up += diff.y;
			boxButton->setPosition("&.w / 2 + " + std::to_string(selectedBox->left), "&.h / 2 + " + std::to_string(selectedBox->up + 300));
			arrangeButtons(&*object);
		}
		lastMouse = {mouseX, mouseY};
		return;
	}
	if (dragLeft) {
		auto diff = mouseX - lastMouse.x;

		if (spriteSelected) {/*
			auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];

			if (static_cast<int>(data.texWidth * data.blendOptions.scaleX) - diff < 10) {
				data.offsetX += data.texWidth * data.blendOptions.scaleX - 10;
				lastMouse.x += data.texWidth * data.blendOptions.scaleX - 10;
				data.blendOptions.scaleX = data.texWidth / 10;
			} else {
				data.offsetX += diff;
				bbb = !bbb;
				bbb &= diff % 2;
				data.size.x -= diff + copysign(bbb, diff);
				lastMouse.x = mouseX;
			}*/
		} else {
			/*if (static_cast<int>(selectedBox->size.x) - diff < 10) {
				selectedBox->pos.x += selectedBox->size.x - 10;
				lastMouse.x += selectedBox->size.x - 10;
				selectedBox->size.x = 10;
			} else {*/
			selectedBox->left += diff;
			//selectedBox->size.x -= diff;
			lastMouse.x = mouseX;
			//}
		}
	} else if (dragRight) {
		auto diff = mouseX - lastMouse.x;

		if (spriteSelected) {/*
			auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];

			if (static_cast<int>(data.size.x) + diff < 10) {
				lastMouse.x -= data.size.x - 10;
				data.offset.x += (data.size.x - 10) / 2;
				data.size.x = 10;
			} else {
				data.size.x += diff;
				bbb = !bbb;
				bbb &= diff % 2;
				data.offset.x += diff / 2 + copysign(bbb, diff);
				lastMouse.x = mouseX;
			}*/
		} else {
			/*if (static_cast<int>(selectedBox->size.x) + diff < 10) {
				lastMouse.x -= selectedBox->size.x - 10;
				selectedBox->size.x = 10;
			} else {*/
				//selectedBox->size.x += diff;
				selectedBox->right += diff;
				lastMouse.x = mouseX;
			//}
		}
	}
	if (dragUp) {
		auto diff = mouseY - lastMouse.y;

		if (spriteSelected) {/*
			auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];

			if (static_cast<int>(data.size.y) - diff < 10) {
				lastMouse.y += data.size.y - 10;
				data.size.y = 10;
			} else {
				data.size.y -= diff;
				lastMouse.y = mouseY;
			}*/
		} else {
			/*if (static_cast<int>(selectedBox->size.y) - diff < 10) {
				selectedBox->pos.y += selectedBox->size.y - 10;
				lastMouse.y += selectedBox->size.y - 10;
				selectedBox->size.y = 10;
			} else {*/
				//selectedBox->pos.y += diff;
				//selectedBox->size.y -= diff;
				selectedBox->up += diff;
				lastMouse.y = mouseY;
			//}
		}
	} else if (dragDown) {
		auto diff = mouseY - lastMouse.y;

		if (spriteSelected) {/*
			auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];

			if (static_cast<int>(data.size.y) + diff < 10) {
				data.offset.y -= data.size.y - 10;
				lastMouse.y -= data.size.y - 10;
				data.size.y = 10;
			} else {
				data.offset.y -= diff;
				data.size.y += diff;
				lastMouse.y = mouseY;
			}*/
		} else {
			/*if (static_cast<int>(selectedBox->size.y) + diff < 10) {
				lastMouse.y -= selectedBox->size.y - 10;
				selectedBox->size.y = 10;
			} else {*/
				//selectedBox->size.y += diff;
				selectedBox->down += diff;
				lastMouse.y = mouseY;
			//}
		}
	}
	if (spriteSelected) {/*
		auto &data = object->_moves.at(object->_action)[object->_actionBlock][object->_animation];

		boxButton->setPosition("&.w / 2 + " + std::to_string(static_cast<int>(data.offset.x - data.size.x / 2)), "&.h / 2 + " + std::to_string(data.offset.y + 300));
		boxButton->setSize(data.size.x, data.size.y);
		gui.get<tgui::EditBox>("Offset")->setText("(" + std::to_string(data.offset.x) + "," + std::to_string(data.offset.y) + ")");
		gui.get<tgui::EditBox>("Size")->setText("(" + std::to_string(data.size.x) + "," + std::to_string(data.size.y) + ")");
		arrangeButtons(&*object);*/
	} else {
		boxButton->setPosition("&.w / 2 + " + std::to_string(selectedBox->left), "&.h / 2 + " + std::to_string(selectedBox->up + 300));
		boxButton->setSize(selectedBox->right - selectedBox->left, selectedBox->down - selectedBox->up);
		arrangeButtons(&*object);
	}
}

void	handleKeyPress(sf::Event::KeyEvent event, std::unique_ptr<EditableObject> &object, tgui::Gui &gui)
{
	auto bar = gui.get<tgui::MenuBar>("main_bar");
	auto panel = gui.get<tgui::Panel>("Panel1");
	auto boxes = gui.get<tgui::Panel>("Boxes");

	if (event.code == sf::Keyboard::S) {
		if (event.control)
			saveFramedataToFileCallback(object);
	}
	if (event.code == sf::Keyboard::Q)
		quitCallback();
	if (event.code == sf::Keyboard::N && event.control)
		newFileCallback(object, bar, gui);
	if (event.code == sf::Keyboard::O && event.control)
		openFramedataFromPackage(object, bar, gui);

	if (object) {
		if (event.code == sf::Keyboard::F) {
			if (event.control && event.shift)
				newEndFrameCallback(gui, object, panel);
			else if (event.control)
				newFrameCallback(gui, object, panel);
		}
		if (event.code == sf::Keyboard::B && event.control)
			newAnimBlockCallback(gui, object, panel);
		if (event.code == sf::Keyboard::H) {
			if (event.control && event.shift)
				newHitBoxCallback(object, boxes);
			else if (event.control)
				newHurtBoxCallback(object, boxes);
			else
				switchHitboxes(boxes);
		}

		if (event.code == sf::Keyboard::Delete) {
			if (event.control && event.shift)
				removeFrameCallback(object, boxes);
			else if (event.control)
				removeActionCallback(gui, object);
			else if (event.shift)
				removeAnimationBlockCallback(object);
			else
				removeBoxCallback(boxes, object, panel);
		}
	}
}

void	loadSettings()
{
	game->logger.debug("Loading settings");

	std::ifstream file("assets/settings.json");
	nlohmann::json json;

	if (file.is_open()) {
		file >> json;
		file.close();

		swr = json["swr"];
		soku = json["soku"];
		soku2 = json["soku2"];
		bgColor = json.contains("bgColor") ? sf::Color(json["bgColor"]) : sf::Color::Black;
		bgColor.a = 255;
	}
	verifySettings();
	loadPackages();
}

std::filesystem::path cwd;

void	run()
{
	loadSettings();
	game->screen = std::make_unique<Screen>("Frame data editor version " VERSION_STR);

	std::unique_ptr<EditableObject> object;
	tgui::Gui gui{*game->screen};
	sf::Image icon;
	sf::Event event;
	sf::Texture stage;
	sf::Sprite sprite;

	stage.loadFromFile("assets/stages/14687.png");
	sprite.setTexture(stage, true);
	sprite.setPosition({stage.getSize().x * 1.f / -2.f, stage.getSize().y * 1.f / -1.4f});
	sprite.setScale(1, 1);
	if (icon.loadFromFile("assets/editorIcon.png"))
		game->screen->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	gui.loadWidgetsFromFile("assets/gui/editor.gui");

	bool dragging = false;
	auto panel = gui.get<tgui::Panel>("Panel1");
	auto progress = panel->get<tgui::Slider>("Progress");
	sf::View view;
	sf::View guiView{
		{
			0, 0,
			static_cast<float>(game->screen->getSize().x),
			static_cast<float>(game->screen->getSize().y)
		}
	};

	placeGuiHooks(gui, object);
	view.setCenter(panel->getSize().x / 2, -300);
	view.setSize(game->screen->getSize().x, game->screen->getSize().y);
	game->screen->setView(view);
	gui.setView(guiView);
	while (game->screen->isOpen()) {
		timer++;
		game->screen->clear(bgColor);
		game->screen->draw(sprite);
		if (object) {
			if (timer >= updateTimer || updateAnyway) {
				object->update();
				if (object->_animationCtr == 0)
					game->soundMgr.play(object->_moves.at(object->_action)[object->_actionBlock][object->_animation].hitSoundHandle);
				updateAnyway = false;
				progress->setValue(object->_animation);
				timer -= updateTimer;
			}
			object->render();
		}

		while (game->screen->pollEvent(event)) {
			if (cwd != std::filesystem::current_path()) {
				game->logger.warn("Current directory changed " + std::filesystem::current_path().string());
				std::filesystem::current_path(cwd);
			}
			gui.handleEvent(event);
			if (event.type == sf::Event::Closed) {
				quitRequest = true;
				continue;
			}
			if (event.type == sf::Event::KeyPressed)
				handleKeyPress(event.key, object, gui);
			if (event.type == sf::Event::Resized) {
				guiView.setSize(event.size.width, event.size.height);
				guiView.setCenter(event.size.width / 2, event.size.height / 2);
				gui.setView(guiView);

				view.setCenter(panel->getSize().x / 2, -300);
				view.setSize(event.size.width, event.size.height);
				game->screen->setView(view);
				continue;
			}
			dragging &= sf::Mouse::isButtonPressed(sf::Mouse::Left);
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				dragging = true;
				dragStart = false;
				mouseStart = {event.mouseButton.x, event.mouseButton.y};
				lastMouse = mouseStart;
			}
			dragUp &= dragging;
			dragDown &= dragging;
			dragLeft &= dragging;
			dragRight &= dragging;
			canDrag &= dragging;
			if (event.type == sf::Event::MouseMoved && dragging && canDrag)
				handleDrag(gui, object, event.mouseMove.x, event.mouseMove.y);
		}
		gui.draw();
		game->screen->display();
		if (quitRequest) {
			if (!object) {
				game->screen->close();
				continue;
			}
			quitRequest = false;
			if (gui.get<tgui::ChildWindow>("QuitConfirm"))
				continue;

			auto window = Utils::openWindowWithFocus(gui, 260, 90);

			window->loadWidgetsFromFile("assets/gui/quitConfirm.gui");
			window->get<tgui::Button>("Yes")->connect("Clicked", [&object](std::weak_ptr<tgui::ChildWindow> self){
				if (saveFramedataToFileCallback(object))
					game->screen->close();
			}, std::weak_ptr<tgui::ChildWindow>(window));
			window->get<tgui::Button>("No")->connect("Clicked", []{
				game->screen->close();
			});
			window->get<tgui::Button>("Cancel")->connect("Clicked", [](std::weak_ptr<tgui::ChildWindow> self){
				self.lock()->close();
			}, std::weak_ptr<tgui::ChildWindow>(window));
		}
	}
}

#ifdef _WIN32
std::string getLastError(int err = GetLastError())
{
	char *s = nullptr;
	std::string str;

	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&s, 0, nullptr
	);
	str = s;
	LocalFree(s);
	return str;
}

LONG WINAPI UnhandledExFilter(PEXCEPTION_POINTERS ExPtr)
{
	char buf[MAX_PATH], buf2[MAX_PATH];

	time_t timer;
	char timebuffer[26];
	struct tm* tm_info;

	time(&timer);
	tm_info = localtime(&timer);
	strftime(timebuffer, 26, "%Y%m%d%H%M%S", tm_info);
	sprintf(buf2, "crash_%s.dmp", timebuffer);

	HANDLE hFile = CreateFile(buf2, GENERIC_READ | GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		MINIDUMP_EXCEPTION_INFORMATION md;
		md.ThreadId = GetCurrentThreadId();
		md.ExceptionPointers = ExPtr;
		md.ClientPointers = FALSE;
		BOOL win = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &md, 0, 0);

		if (!win)
			sprintf(buf, "Fatal exception caught.\nMiniDumpWriteDump failed.\n%s: %s", getLastError().c_str(), buf2);
		else
			sprintf(buf, "Fatal exception caught.\nMinidump created %s", buf2);
		CloseHandle(hFile);
	} else
		sprintf(buf, "Fatal exception caught.\nCould not create file %s\n%s", buf2, getLastError().c_str());
	game->logger.fatal(buf);
	Utils::dispMsg("Fatal error", buf, MB_ICONERROR, &*game->screen);
	exit(EXIT_FAILURE);
}
#endif

int	main()
{
#ifdef _WIN32
	SetUnhandledExceptionFilter(UnhandledExFilter);
#endif
	cwd = std::filesystem::current_path();

	try {
		new Game("./editor.log");
		game->logger.info("Starting editor.");
		run();
		game->logger.info("Goodbye !");
	} catch (std::exception &e) {
		game->logger.fatal(e.what());
		Utils::dispMsg("Fatal error", e.what(), MB_ICONERROR, &*game->screen);
		delete game;
		return EXIT_FAILURE;
	}
	saveSettings();
	delete game;
	return EXIT_SUCCESS;
}
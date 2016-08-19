#include <iostream>
#include "ghCore.h"
#include "ghApplication.h"
#include "ghLoggerManager.h"
#include "ghFileLogger.h"
#include "ghConsoleLogger.h"
#include "ghInputManager.h"
#include "ghInputConfiguration.h"
#include "ghPlatform.h"
#include "ghHeaders.h"
#include "ghEvent.h"
#include "ghResource.h"
#include "ghConfiguration.h"

#include "ghMath.h"
#include <glm/glm.hpp>

#include "kzGameplay.h"

using namespace std;
using namespace glm;
using namespace ganeshEngine;


enum class kzItemType {
    BOSS_ITEM,
    REGULAR_ITEM
};


enum class kzGameplayState {
    LEVEL_BEGIN,
    LEVEL,
    LEVEL_END,
    ITEM_CHOICE,
    BOSS
};


class kzItem {
public:
    kzItemType m_type;

    bool activate_ship_field = false;
    float ship_speed_multiplier = 1.0f;
    float ship_speed_to_add = 0.0f;
    float fire_rate_multiplier = 1.0f;
    float fire_rate_to_add = 0.0f;
    float fire_spread_multiplier = 1.0f;
    float fire_spread_to_add = 0.0f;
    float fire_power_multiplier = 1.0f;
    float fire_power_to_add = 0.0f;
    int orbital_to_add = 0.0f;

    kzItem(kzItemType type) : m_type(type) {}

    static kzItem itemOne() {
        kzItem i = kzItem(kzItemType::BOSS_ITEM);
        i.fire_power_multiplier = 1.35f;
        return i;
    }

    static kzItem itemTwo() {
        kzItem i = kzItem(kzItemType::REGULAR_ITEM);
        i.fire_power_multiplier = 1.35f;
        return i;
    }
};

vector<kzItem> allItems{
        kzItem::itemOne(),
        kzItem::itemTwo()};

/*
 * 
kzItem i = kzItem(kzItemType::REGULAR_ITEM);
allItems.push_back(i);
*/
class kzPlayer {
public:
    /**
     * The ship kind defines the shoot style
     * 1: bullet
     * 2: laser
     * 3: orbital (no bullet fired from the ship)
     */
    int ship_kind;

    /**
     * Allows you to take one damage without dying
     */
    bool ship_field;

    /**
     * Value betweend 1 and X
     */
    float ship_speed;

    /**
     * Value betweend 1 and Y
     */
    float fire_rate;

    /**
     * Value betweend 1 and Z
     */
    float fire_spread;

    /**
     * Value betweend 1 and W
     */
    float fire_power;

    /**
     * Amount of orbital minion spinning around the player
     */
    int orbital_amount;

    list<kzItem> items_picked;

    /**
     * Used when the player pick up an item.
     * This method will recompute the player's statistics
     * 
     * @param item
     */
    void pickupItem(kzItem item);
};


class kzLevelPart {
public:
    int beginTimeMs;
    int durationMs;
};


class kzGameplay {
public:
    /**
     * Current multiplier, used to multiply point earned when catching power up
     * or killing enemies
     */
    int multiplier;

    /**
     * The amount of point earned by the player during a run
     * minimal value is 0
     */
    int score;

    U64 time;

    kzPlayer player;

    kzGameplayState state;

    /**
     * 1: first stage
     * 2: second stage
     * 3: third stage
     * 4: final boss stage
     */
    int current_level;

    list<kzItem> regularItemPool;

    list<kzItem> bossItemPool;

    /**
     * Composition of a level
     */
    list<kzLevelPart> level_parts;
};


/**
 * 
 */
int main() {
    LOG_CHANNEL channels = LOG_CHANNEL::RENDER | LOG_CHANNEL::DEFAULT | LOG_CHANNEL::INPUT;
    Configuration conf;
    conf.inputConfigurationFilename = "C:/Users/mickael.camier/workspace/ganeshEngine/ganeshEngineDemo/Resources/inputConfiguration.json";
    conf.resourceConfigurationFilename = "C:/Users/mickael.camier/workspace/ganeshEngine/ganeshEngineDemo/Resources/resourceConfiguration.json";
    conf.loggers.push_back(new ConsoleLogger(LOG_LEVEL::DEBUG, channels));
    conf.loggers.push_back(new FileLogger(LOG_LEVEL::DEBUG, channels, "C:/Users/mickael.camier/workspace/ganeshEngine/ganeshEngineDemo/Resources/log"));

    Application::Initialize(conf);
    /** After application initialization all singletons used by the engine
     *  are created and initialized, so all engine's customization, plugins
     *  addition should take place here, before the start of the main loop
     */
    Application::RunLoop();
    Application::Destroy();
    return 0;
}

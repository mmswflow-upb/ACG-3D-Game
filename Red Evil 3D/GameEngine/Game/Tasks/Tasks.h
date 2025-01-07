#pragma once
#include <string>

/// Enum class for Tasks
enum class Tasks {
    CollectItems,
    DefeatEnemies,
    EscortNPC,
    ExploreArea
};

/// Struct to Define Task Attributes
struct TaskAttributes {
    std::string description;   // Description of the task
    int difficultyLevel;       // Difficulty level (1-5)
    int reward;                // Reward points or items for completing the task
    std::string target;        // Target entity (e.g., "enemy", "area", "item")
};

inline TaskAttributes getTaskAttributes(Tasks task) {
    switch (task) {
    case Tasks::CollectItems:
        return { "Collect 10 rare items from the forest", 2, 100, "Item" };

    case Tasks::DefeatEnemies:
        return { "Defeat 5 bandits near the village", 3, 150, "Enemy" };

    case Tasks::EscortNPC:
        return { "Escort the merchant to the nearby town safely", 4, 200, "NPC" };

    case Tasks::ExploreArea:
        return { "Explore the abandoned castle ruins", 5, 300, "Area" };

    default:
        return { "", 0, 0, "" };
    }
}

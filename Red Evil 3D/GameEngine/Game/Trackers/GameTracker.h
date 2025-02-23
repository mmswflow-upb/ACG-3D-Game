#pragma once
#include <unordered_map>
#include "../Maps/Map.h"

struct Inventory {
    
    Gun* gun;// Pointer to the gun (nullptr if not picked up)
    int ammo;         // Total ammo count
    std::vector<Drop*> drops;

    Inventory() : gun(nullptr), ammo(0) {}
};

class GameTracker {
private:
    Inventory inventory;       // Inventory to store gun, ammo, and antidotes
    int currentTaskNumber;     // Current task number
    std::unordered_map<int, std::pair<std::string, std::string>> taskDescriptions; // Task title and description
    Gun initialGun;           // Pointer to the initial gun
    Drop ammo30, ammo60, medkit;
    Enemy iceDyno;            // Ice Dyno enemy
    Enemy fireDyno;           // Fire Dyno enemy
    Map* map;                  // Reference to the map object
    Main_Char* mainCharacter;
    Friend* friendCharacter;
	Animatable normalTree, burntTree, seaWater;
public:
    GameTracker(
        Map* gameMap,
        Main_Char* mc,
        Friend* fr,
        Gun gun,
        Drop ammo30,
        Drop ammo60,
        Drop medkit,
        Enemy ice,
        Enemy fire,
        Animatable normalTree,
        Animatable burntTree,
		Animatable seaWater
    ) : map(gameMap), initialGun(gun), ammo30(ammo30), ammo60(ammo60), medkit(medkit), iceDyno(ice), fireDyno(fire), currentTaskNumber(1), mainCharacter(mc), friendCharacter(fr) , normalTree(normalTree), burntTree(burntTree), seaWater(seaWater){
        // Initialize task descriptions
        taskDescriptions[1] = { "Pick up the Gun", "Collect the gun to proceed." };
        taskDescriptions[2] = { "Ammo Collection", "Pick up ammo from drops." };
        taskDescriptions[3] = { "Defeat the Ice Dyno", "Kill the Ice Dyno to proceed." };
        taskDescriptions[4] = { "Defeat the Fire Dyno", "Kill the Earth Dyno to proceed." };
        taskDescriptions[5] = { "The Cure", "Collect the HealthPack and Cure Layla." };
        
        setupTask1(); // Initial setup for the first task
    }

    /// Check if the character or friend is dead
    bool isMainCharacterOrFriendDead(Main_Char* mainCharacter, Friend* friendCharacter) {
        if (mainCharacter->getHealth() <= 0 || friendCharacter->getHealth() <= 0) {
            std::cout << "Game Over! A character has died.\n";
            return true;
        }
        return false;
    }

    /// Get the inventory by reference
    Inventory* getInventory() {
        return &inventory;
    }

    void addToInventory(Gun* newGun) {
        if (newGun == nullptr) return;

		cout << "Adding new gun to inventory: " << newGun->getName() <<"\n";
        inventory.gun = newGun;
    }

    void addToInventory(Drop* newDrop) {

        if (newDrop == nullptr) return;
        cout << "Adding new drop to inventory: " << newDrop->getName() << "\n";

        if (newDrop->getType() == DropType::Ammo_30) {

            inventory.ammo += 30;
        }
        else if (newDrop->getType() == DropType::Ammo_60) {
            inventory.ammo += 60;

        }
        else {

        }
    }


    

    /// Function to set the equipped item in the inventory
    void setEquipped(int indx) {
        


        Gun* gun = inventory.gun;
        std::vector<Drop*> drops = inventory.drops;

        // Unequip everything
        if (indx == -1) {
            // Unequip the gun if it exists
            if (gun != nullptr) {
                gun->setEquipped(false);
            }

            // Unequip all drops in the inventory
            for (size_t i = 0; i < drops.size(); ++i) {
                if (drops[i] != nullptr) {
                    drops[i]->setEquipped(false);
                }
            }
        }else if (indx == 1) {
            if (gun != nullptr) {
                gun->setEquipped(true); // Equip the gun
                // Unequip any currently equipped drops



                for (auto& drop : drops) {
                    if (drop != nullptr) {
                        drop->setEquipped(false); // Assuming Drop has setEquipped()
                    }
                }
            }
        }
        // Handle cases for indices corresponding to drops
        else if (indx >= 2) {
            int dropIndex = indx - 2; // Adjust index for the drops vector
            if (dropIndex < drops.size() && drops[dropIndex] != nullptr) {
                // Equip the selected drop
                drops[dropIndex]->setEquipped(true); // Assuming Drop has setEquipped()

                // Unequip the gun
                if (gun != nullptr) {
                    gun->setEquipped(false);
                }

                // Unequip other drops
                for (size_t i = 0; i < drops.size(); ++i) {
                    if (i != static_cast<size_t>(dropIndex) && drops[i] != nullptr) {
                        drops[i]->setEquipped(false);
                    }
                }
            }
        }
    }


    /// Set up task 1: Place the gun on the map and add trees in two different quadrants at height 20.5
    void setupTask1() {

        // Create the water
		seaWater.setPosition(glm::vec3(0.001f, -310.0f, 0.001f));
		map->addAnimatable(seaWater);


        // Place the initial gun
        initialGun.setPosition(glm::vec3(10.01f, 19.5f, 10.01f));
        map->setGunToBePickedUp(initialGun);
        std::cout << "Task 1 setup: Gun placed on the map.\n";

        // Seed the random number generator (if not already seeded elsewhere)
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        // Number of trees to spawn per type (adjust as necessary, e.g., use 30 for each)
        const int numTreesPerType = 20;

        // Define spread range parameters:
        const int spread = 140;  // Adjust this value to change how spread out the trees are

        // --- Spawn Normal Trees in the negative x and negative z quadrant ---
        for (int i = 0; i < numTreesPerType; ++i) {
            // Generate a random offset in the range [-spread, 0]
            float x = -static_cast<float>(std::rand() % spread);
            float z = -static_cast<float>(std::rand() % spread);
            glm::vec3 treePos(x, 20.5f, z);

            // Use normal tree for this quadrant
            Animatable tree = normalTree;
            tree.setPosition(treePos);
            map->addAnimatable(tree);

            std::cout << "Task 1 setup: Normal tree " << i << " placed at ("
                << treePos.x << ", " << treePos.y << ", " << treePos.z << ").\n";
        }

        // --- Spawn Burnt Trees in the positive x and positive z quadrant ---
        for (int i = 0; i < numTreesPerType; ++i) {
            // Generate a random offset in the range [0, spread]
            float x = static_cast<float>(std::rand() % spread);
            float z = static_cast<float>(std::rand() % spread);
            glm::vec3 treePos(x, 20.5f, z);

            // Use burnt tree for this quadrant
            Animatable tree = burntTree;
            tree.setPosition(treePos);
            map->addAnimatable(tree);

           
        }
    }





    /// Set up task 2: Place ammo drops on the map
    void setupTask2() {
		ammo30.setPosition(glm::vec3(20.0f, 18.5f, -20.0f));
        map->addDrop(&ammo30);
        map->removeGunToBePickedUp();
        std::cout << "Task 2 setup: Ammo drops placed on the map.\n";
    }

    /// Set up task 3: Place Ice Dyno on the map
    void setupTask3() {
		map->removeAmmoDrops();
		iceDyno.setPosition(glm::vec3(-40.0f, 19.5f, 40.0f));
        map->setEnemy(&iceDyno);
        std::cout << "Task 3 setup: Ice Dyno placed on the map.\n";
    }

    /// Set up task 4: Place Earth Dyno on the map
    void setupTask4() {
		fireDyno.setPosition(glm::vec3(60.0f, 19.5f, -60.0f));
        map->setEnemy(&fireDyno);

        std::cout << "Task 4 setup: Fire Dyno placed on the map.\n";
    }

    void setupTask5() {
		//add the cure to the map
		medkit.setPosition(glm::vec3(0.0f, 18.5f, 0.0f));
		map->addDrop(&medkit);
		std::cout << "Task 5 setup: Medkit placed on the map.\n";
    }

    /// Get the current task's title and description after calling update()
    std::pair<std::string, std::string> getCurrentTask(float deltaTime) {
        update();
        auto it = taskDescriptions.find(currentTaskNumber);
        if (it != taskDescriptions.end()) {
            return it->second;
        }
        return { "Unknown Task", "No description available." };
    }

    /// Function to get inventory items and their amounts
    std::map<std::string, std::string> getInventoryItemsAndAmounts() {
        std::map<std::string, std::string> itemsAndAmounts;

        // Add the gun to the map if it exists
        if (inventory.gun != nullptr) {
            std::string gunName = inventory.gun->getName(); // Assuming Gun has a getTypeName() method
            std::string ammoInfo = inventory.gun->getAmmoCount() + " / " +
                inventory.gun->getMaxAmmo(); // Assuming Gun has getAmmoCount() and getMaxAmmo()
            itemsAndAmounts["Gun"] = gunName + " (" + ammoInfo + ")";
        }

        // Add ammo to the map if any
        if (inventory.ammo > 0) {
            itemsAndAmounts["Ammo"] = std::to_string(inventory.ammo);
        }

        // Add items from drops to the map
        for (const auto& drop : inventory.drops) {
            if (drop != nullptr) {
                std::string dropName = drop->getName(); // Assuming Drop has a getTypeName() method
                std::string dropAmount = std::to_string(drop->getAmount()); // Assuming Drop has a getAmount() method
                if (itemsAndAmounts.find(dropName) != itemsAndAmounts.end()) {
                    // If the item already exists, update its amount
                    itemsAndAmounts[dropName] = std::to_string(std::stoi(itemsAndAmounts[dropName]) + drop->getAmount());
                }
                else {
                    // Otherwise, add the new item
                    itemsAndAmounts[dropName] = dropAmount;
                }
            }
        }

        return itemsAndAmounts;
    }

    /// Determines which tool is equipped and returns its details
    std::pair<std::string, std::string> getEquippedToolDetails() {
        // Check if a gun is equipped
        if (inventory.gun != nullptr && inventory.gun->isEquipped()) {
			std::string name = "Gun: " + inventory.gun->getName(); 
            std::string ammo = "Ammo: " + std::to_string(inventory.gun->getAmmoCount()) + " / " +
                std::to_string(inventory.gun->getMaxAmmo());
            return { name, ammo };
        }

        // Check if any drop is equipped
        for ( auto& drop : inventory.drops) {
            if (drop && drop->isEquipped()) {
                std::string name = "Drop: " + drop->getName(); // Assuming Drop has getTypeName()
                std::string amount = "Amount: " + std::to_string(drop->getAmount()); // Assuming Drop has getAmount()
                return { name, amount };
            }
        }

        // Default case: no tool equipped
        return { "No Tool Equipped", "" };
    }


    /// Update game logic based on the current task
    void update() {
        if (isMainCharacterOrFriendDead(mainCharacter, friendCharacter)) {
            currentTaskNumber = -1; // Game over
            return;
        }

        switch (currentTaskNumber) {
        case 1: { // Task 1: Pick up the Gun
            if (inventory.gun != nullptr && inventory.gun->getType() == GunPack::Pistol) { // Check if gun is picked up
                std::cout << "Gun picked up! Task 1 completed.\n";
                currentTaskNumber++;
                setupTask2(); // Set up next task
            }
            break;
        }

        case 2: { // Task 2: Pick up ammo
            auto drops = map->getDrops();
            
            if (inventory.ammo > 0) {
                currentTaskNumber++;
                setupTask3(); // Set up next task
            }
            break;
        }

        case 3: { // Task 3: Kill the Ice Dyno
            if (map->getEnemy() && map->getEnemy()->getType() == CharacterPack::Ice_Dyno) {
                if (map->getEnemy()->getHealth() <= 0) {
                    map->setEnemy(nullptr); // Remove enemy from map
                    std::cout << "Ice Dyno defeated! Task 3 completed.\n";
                    currentTaskNumber++;
                    setupTask4(); // Set up next task
                }
            }
            break;
        }

        case 4: { // Task 4: Kill the Fire Dyno
            if (map->getEnemy() && map->getEnemy()->getType() == CharacterPack::Fire_Dyno) {
                if (map->getEnemy()->getHealth() <= 0) {
                    map->setEnemy(nullptr); // Remove enemy from map
                    std::cout << "Fire Dyno defeated! Task 4 completed.\n";
                    currentTaskNumber++;
                    setupTask5(); // Set up next task
                }
            }
            break;
        }
              
        case 5: { // Task 5: Check for Medkit in Drops
            bool medkitFound = false;

            // Iterate through the drops on the map
            for (auto& drop : *map->getDrops()) {
                if (drop.getType() == DropType::HealthPack) { // Check if the drop is a medkit
                    medkitFound = true;
                    std::cout << "Medkit Found!\n";

                    // Remove the medkit from the map drops if necessary
                    map->removeDrop(drop);
                    currentTaskNumber++;
                    break; // Exit loop once medkit is found
                }
            }

            
            break;
        }

        default:
            std::cout << "All tasks completed!\n";
            break;
        }
    }
};

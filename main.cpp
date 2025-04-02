#include <iostream>
#include <random>
#include <string>

using namespace std;

void showStatus(int health, bool hasKey);
void leftPath(int& health, bool& hasKey);
void middlePath(int& health, bool& hasKey);
void rightPath(int& health, bool& hasKey, bool& isPlaying);

int main() {
    bool isPlaying = true;
    int health = 100;
    bool hasKey = false;
    int healthPotions = 2;  // Added health potions
    string choice;

    cout << "Welcome to 'Escape the Dungeon'\n";
    cout << "You find yourself trapped in a dark dungeon.\n";
    cout << "You have 2 health potions with you.\n";
    cout << "Your mission is to find a way out.\n\n";

    while (isPlaying) {
        cout << "\nYou are in a dimly lit room. There are three paths ahead:\n";
        cout << "1. Take the left path\n";
        cout << "2. Take the middle path\n";
        cout << "3. Take the right path\n";
        cout << "4. Check status\n";
        cout << "5. Use health potion\n";
        cout << "6. Quit game\n";

        cout << "\nWhat would you like to do? (1-6): ";
        getline(cin, choice);

        switch (choice[0]) {
            case '1':
                leftPath(health, hasKey);
                break;
            case '2':
                middlePath(health, hasKey);
                break;
            case '3':
                rightPath(health, hasKey, isPlaying);
                break;
            case '4':
                showStatus(health, hasKey);
                cout << "Health Potions: " << healthPotions << "\n";
                break;
            case '5':
                if (healthPotions > 0) {
                    health = min(100, health + 50);
                    healthPotions--;
                    cout << "You used a health potion. Health restored to " << health << "!\n";
                } else {
                    cout << "No health potions remaining!\n";
                }
                break;
            case '6':
                isPlaying = false;
                cout << "Thanks for playing!\n";
                break;
            default:
                cout << "Invalid choice. Please select 1-6.\n";
        }

        if (health <= 0) {
            cout << "\nGame Over! You have died.\n";
            isPlaying = false;
        }
    }

    return 0;
}

void leftPath(int& health, bool& hasKey) {
    string choice;
    cout << "\nYou venture down the left path...\n";
    cout << "You find a treasure chest!\n";
    cout << "1. Open the chest\n";
    cout << "2. Leave it alone\n";

    getline(cin, choice);

    if (choice == "1") {
        if (!hasKey) {
            cout << "You found a golden key! This might be useful later.\n";
            hasKey = true;
        }
        else {
            cout << "The chest is empty.\n";
        }
    }
    else if (choice == "2") {
        cout << "You decide to leave the chest alone and return to the main room.\n";
    }
    else {
        cout << "Invalid choice. You return to the main room.\n";
    }
}

void middlePath(int& health, bool& hasKey) {
    string choice;
    cout << "You take the middle path...\n";
    cout << "You encounter a monster!\n";
    cout << "1. Fight the monster\n";
    cout << "2. Try to run away\n";

    getline(cin, choice);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> damageDist(10, 30);
    uniform_int_distribution<> escapeDist(0, 1);

    if (choice == "1") {
        cout << "You engage in combat with the monster!\n";
        int damage = damageDist(gen);
        health -= damage;
        cout << "You took " << damage << " damage! Current health: " << health << "\n";
    }
    else if (choice == "2") {
        cout << "You attempt to run away...\n";
        if (escapeDist(gen) == 0) {
            cout << "You successfully escaped!\n";
        }
        else {
            int damage = damageDist(gen);
            health -= damage;
            cout << "The monster caught you! You took " << damage 
                 << " damage while escaping. Current health: " << health << "\n";
        }
    }
    else {
        cout << "Invalid choice. You return to the main room.\n";
    }
}

void rightPath(int& health, bool& hasKey, bool& isPlaying) {
    string choice;
    cout << "\nYou take the right path...\n";
    cout << "You find a large door with a keyhole!\n";
    cout << "1. Try to open the door\n";
    cout << "2. Go back\n";

    getline(cin, choice);

    if (choice == "1") {
        if (hasKey) {
            cout << "\nCongratulations! You used the key to unlock the door and escaped the dungeon!\n";
            cout << "You Win!\n";
            isPlaying = false;
        }
        else {
            cout << "The door is locked. You need to find a key.\n";
        }
    }
    else if (choice == "2") {
        cout << "You return to the main room.\n";
    }
    else {
        cout << "Invalid choice. You return to the main room.\n";
    }
}

void showStatus(int health, bool hasKey) {
    cout << "\nHealth: " << health << "\n";
    cout << "Key: " << (hasKey ? "Yes" : "No") << "\n";
}
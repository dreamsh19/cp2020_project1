#include "Backpack.h"
#include <iostream>
using namespace std;

Backpack::Backpack() {

}

void Backpack::assignMeals(CustomerRequirement customerRequirement) {

}

void Backpack::assignItem(CustomerRequirement customerRequirement) {

}

void Backpack::packBackpack() {

}

void Backpack::addItem(Item item) {

}

void Backpack::removeItem(int i) {

}

void Backpack::removeItem(Item item) {

}

void Backpack::print() {

}

Meal* Backpack::getMeals() {
    return meals;
}

void Backpack::setMeals(Meal* m) {
    meals = m;
}

int Backpack::getMealLength() {
    return meal_length;
}

Item* Backpack::getItems() {
    return items;
}

void Backpack::setItems(Item* it) {
    items = it;
}

int Backpack::getItemLength() {
    return item_length;
}

Item** Backpack::getZones() {
    return zones;
}

void Backpack::setZones(Item** z) {
    zones = z;
}

Item* Backpack::getStoreInventory() {
    return storeInventory;
}

void Backpack::setStoreInventory(Item* s) {
    storeInventory = s;
}

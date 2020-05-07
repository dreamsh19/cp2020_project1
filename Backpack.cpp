#include "Backpack.h"
#include <iostream>
using namespace std;

Backpack::Backpack() {
    StoreInventory store_inventory;
    storeInventory=store_inventory.item_list;

    zones = new Item*[5];

    // meals = NULL;
    // meal_length = 0;
    // items = NULL;
    // item_length = 0;
}

void Backpack::assignMeals(CustomerRequirement customerRequirement) {


    DaysOnCamp days_on_camp=customerRequirement.getDaysOnCamp();
    Weight prefered_meal_w = customerRequirement.getPreferredMealWeight();

    cout << days_on_camp << endl;
    meal_length = (2 * days_on_camp - 1) * 2;
    meals = new Meal[meal_length];
    for(Meal meal : meals){
        meal.weight = prefered_meal_w;
    }

    
}

void Backpack::assignItem(CustomerRequirement customerRequirement) {
    DaysOnCamp days_on_camp = customerRequirement.getDaysOnCamp();
    Weight prefered_item_w = customerRequirement.getPreferredItemWeight();
    Weight prefered_meal_w = customerRequirement.getPreferredMealWeight();
    int numItem = 4;
    if(days_on_camp == TWO || days_on_camp == THREE){
        numItem+=2;
        if(prefered_meal_w == HIGH) numItem++;
    }
    item_length = numItem;
    items = new Item[item_length];
    for(Item item : items){
        for(Item inv : storeInventory){
            if(item.equals(inv)){
                // I dont what to do
                break;
            }
        }
    }


}

void Backpack::packBackpack() {
    //zone에 배치
}

void Backpack::addItem(Item item) {
    item_length++;
    Item* items_new = new Item[item_length];
    int i;
    for(i=0;i<item_length-1;i++){
        items_new[i]=items[i];
    }
    items_new[i]=item;
    delete[] items;
    items=items_new;
}

void Backpack::removeItem(int i) {
    if(i>=item_length){
        cout << "Index out of range in removeItem int" << endl;
    }else{
        item_length--;
        for (int idx = i; idx < item_length; idx++)
        {
            items[idx] = items[idx + 1];
        }
        //delete the last item
    }
}

void Backpack::removeItem(Item item) {
    for(int i=0;i<item_length;i++){
        if(items[i].equals(item)){
            item_length--;
            for(int j=i;j<item_length;j++){
                items[j]=items[j+1];
            }
            //delete the last item

            break;
        }
    }
}

void Backpack::print() {
    for(int i=0;i<5;i++){
        cout << "Zone " << i << endl;
        for(Item i:zones[i]){
            i.print();
        }
    }
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

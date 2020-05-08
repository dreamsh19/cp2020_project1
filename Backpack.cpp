#include "Backpack.h"
#include <iostream>
#include <malloc.h>
using namespace std;

#define NUM_ZONES 5
#define ZONE_SIZE 2
#define INVENTORY_SIZE 42

Backpack::Backpack() {
    StoreInventory store_inventory;
    storeInventory=store_inventory.item_list;

    zones = new Item*[NUM_ZONES];
    for(int i=0;i<NUM_ZONES;i++){
        zones[i]=new Item[ZONE_SIZE];
    }
    meals = NULL;
    meal_length = 0;
    items = NULL;
    item_length = 0;
}

void Backpack::assignMeals(CustomerRequirement customerRequirement) {


    DaysOnCamp days_on_camp=customerRequirement.getDaysOnCamp();
    Weight prefered_meal_w = customerRequirement.getPreferredMealWeight();

    
    meal_length = (2 * days_on_camp + 1) * 2;
    meals = new Meal[meal_length];
    int i=0;
    for(int day=0;day<=days_on_camp;day++){
        meals[i++]=Meal(LUNCH,prefered_meal_w);
        meals[i++]=Meal(SNACK,prefered_meal_w);
    }
    for(int day=0;day<days_on_camp;day++){
        meals[i++]=Meal(BREAKFAST,prefered_meal_w);
        meals[i++]=Meal(DINNER,prefered_meal_w);
    }
    
}

void Backpack::assignItem(CustomerRequirement customerRequirement) {
    DaysOnCamp days_on_camp = customerRequirement.getDaysOnCamp();
    Weight prefered_item_w = customerRequirement.getPreferredItemWeight();
    Weight prefered_meal_w = customerRequirement.getPreferredMealWeight();

    item_length = 4;
    Item* temp_items = new Item[7];
    temp_items[0]=Item(CLOTHING,prefered_item_w);
    temp_items[1]=Item(FISHING_ROD,prefered_item_w);
    temp_items[2]=Item(LURE,prefered_item_w);
    temp_items[3]=Item(WATER,HIGH);
    if(days_on_camp == TWO || days_on_camp == THREE){
        item_length+=2;
        temp_items[4] = Item(SLEEPING_BAG, MEDIUM);
        temp_items[5] = Item(TENT, prefered_item_w);
        if(prefered_meal_w == HIGH){
            item_length++;
            temp_items[6] = Item(COOKING, prefered_item_w);
        }
    }

    items = new Item[item_length];
    for(int i=0;i<item_length;i++){
        for(int j=0;j<INVENTORY_SIZE;j++){
            if (temp_items[i].equals(storeInventory[j])){
                items[i]=storeInventory[j];
                break;
            }
        }   
    }

}

void Backpack::packBackpack() {

    for(int i=0;i<item_length;i++){
        ItemType itemType = items[i].getItemType();
        if(itemType==LURE) zones[0][0]=items[i];
        else if(itemType==FISHING_ROD) zones[1][0]=items[i];
        else if(itemType==CLOTHING) zones[2][0]=items[i];
        else if(itemType==COOKING) zones[3][0]=items[i];
        else if(itemType==WATER) zones[3][1]=items[i];
        else if(itemType==SLEEPING_BAG) zones[4][0]=items[i];
        else if(itemType==TENT) zones[4][1]=items[i];
    }
}

void Backpack::addItem(Item item) {
    Item* items_new = new Item[++item_length];
    int i;
    for(i=0;i<item_length-1;i++){
        items_new[i]=items[i];
    }
    items_new[i]=item;
    // delete[] items;
    items=items_new;
}

void Backpack::removeItem(int i) {
    if(i<item_length){
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
    Item item_null;
    for(int i=0;i<NUM_ZONES;i++){
        cout << "Zone " << i << endl;
        for(int j=0;j<ZONE_SIZE;j++){
            if(!zones[i][j].equals(item_null)){
                cout << '\t';
                zones[i][j].print();
            }
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

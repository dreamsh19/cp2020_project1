#include "Backpack.h"
#include <iostream>
#include <malloc.h>
using namespace std;

#define NUM_ZONES 5
#define ZONE_SIZE 2
#define INVENTORY_SIZE 42

// 1. StoreInventory의 default constructor를 이용해 StoreInventory.item_list를 
// storeInventory 멤버 변수로 가져온다.
// 2. NUM_ZONES(5) * ZONE_SIZE(2) 크기의 이차원 zones 배열을 초기화한다.
// default constructor로 생성된 item(SLEEPING_BAG, LOW)을 비어있음으로 간주.
// 3. 그 외의 멤버 변수 중 INT는 0으로, 포인터는 NULL로 초기화한다.
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

// DaysOnCamp enum의 실제 값이 ONE(0), TWO(1), THREE(2)인 것을 이용하여
// LUNCH, SNACK : (days_on_camp + 1)개 
// BREAKFAST, DINNER : days_on_camp개
// 총합 (4 * days_on_camp + 2)개 만큼 meal_length를 설정하고,
// 각각 prefered meal weight에 따라 meals 배열에 지정한다. 
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

// days_on_camp와 prefered_meal_weight 조건에 따라 item_length를 지정하고
// item들을 prefered item weight(단, SLEEPING BAG은 MEDIUM, WATER는 HIGH)에 따라 임시 temp_items 배열에 저장한다.
// temp_items배열을 순회하면서 storeInventory의 같은 item을 검색하여 일치하면 items 배열에 추가한다.
// 모두 추가한 후에 temp_items 배열 메모리 할당을 해제한다.
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
    delete[] temp_items;

}

// items 배열을 순회하며 각 item의 itemType에 따라 해당 zone에 배치한다. 
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

// item_length를 1 증가시켜 새로운 배열을 생성 후
// 원래의 items 배열을 새로운 배열에 복사하고 새로운 배열 가장 마지막에 item을 삽입한다.
// 이 새로운 배열을 items 배열로 지정하고 기존의 items 배열의 메모리를 해제한다.
void Backpack::addItem(Item item) {
    Item* items_new = new Item[++item_length];
    int i;
    for(i=0;i<item_length-1;i++){
        items_new[i]=items[i];
    }
    items_new[i]=item;
    delete[] items;
    items=items_new;
}

// i가 out of range index가 아닐 때,
// item_length를 1 감소시키고 i 이후의 item들을 앞으로 한 칸씩 옮긴다.
void Backpack::removeItem(int i) {
    if(i<item_length){
        item_length--;
        for (int idx = i; idx < item_length; idx++)
        {
            items[idx] = items[idx + 1];
        }
    }
}

// items 배열을 순회하면서 같은 item이 발견되면
// items_length를 1 감소시키고 그 이후의 item들을 앞으로 한 칸씩 옮긴다.
void Backpack::removeItem(Item item) {
    for(int i=0;i<item_length;i++){
        if(items[i].equals(item)){
            item_length--;
            for(int j=i;j<item_length;j++){
                items[j]=items[j+1];
            }
            break;
        }
    }
}

// 이차원 배열 zones를 순회하면서 default constructor로 생성된
// item(SLEEPING_BAG, LOW : 비어있는 것으로 간주)과 다를 때만 
// Item.print()를 이용하여 출력한다.
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

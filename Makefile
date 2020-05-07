CC = g++
CFLAGS = --std=c++17
TARGET = project1
OBJECTS = Backpack.o Meal.o Item.o StoreInventory.o CustomerRequirement.o main.o

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
clean :
	rm -f *.o
	rm -f $(TARGET)

Backpack.o : Backpack.cpp
	$(CC) $(CFLAGS) -c -o Backpack.o Backpack.cpp

Meal.o : Meal.cpp
	$(CC) $(CFLAGS) -c -o Meal.o Meal.cpp

Item.o : Item.cpp
	$(CC) $(CFLAGS) -c -o Item.o Item.cpp

StoreInventory.o : StoreInventory.cpp
	$(CC) $(CFLAGS) -c -o StoreInventory.o StoreInventory.cpp

CustomerRequirement.o : CustomerRequirement.cpp
	$(CC) $(CFLAGS) -c -o CustomerRequirement.o CustomerRequirement.cpp

main.o : main.cpp
	$(CC) -c -o main.o main.cpp   

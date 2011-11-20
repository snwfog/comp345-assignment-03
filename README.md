__Note: I STRONGLY suggest to review this project that is also availabe on [GitHub](https://github.com/snwfog/comp345-assignment-03).__

# COMP345 Assignment 3 README
## Map Builder Programming Pattern

### Requirement
- __ncurses 5.9 lib installed__

##### Note: I have completed all the 3 parts that were asked in assignment 3. You can choose to correct all of them, or you should correct the __MapEditor__ sections. The MapEditor section includes Map, MapBuilder, MapEditor, and you should comment out all the irrelevant "test" scenarios that I have included in the main.cpp.

### File Hierarchy
> Files are stored in their appropriate __virtual__ folders in my IDE. However, they are not placed in real folders. Here is the file hierarchy tree.
	
	comp345-assignment-03/
	+-main.cpp
	+-Function.h
	+-Function.cpp
	  +-Character
	  | +-Character.h
	  | +-Character.cpp
	  | +-CharacterBuilder.h
	  | +-CharacterBuilder.cpp
	  +-Map
	  | +-Map.h
	  | +-Map.cpp
	  | +-MapBuilder.h
	  | +-MapBuilder.cpp
 	  | +-MapEditor/
	  |   +-MapEditor.h
	  |   +-MapEditor.cpp
	  +-Item
	  | +-Item.h
	  | +-Item.cpp
	  | +-ItemBuilder.h
	  | +-ItemBuilder.cpp
	  +-Chest
	  | +-Chest.h
	  | +-Chest.cpp
	  | +-ChestBuilder.h
	  | +-ChestBuilder.cpp
	  	

### To Run
> You must compile all the provided .cpp files and additionally, you must link your compiler with the ncurses library using the command `-lnucrses`.
> Use this command to run the main.cpp
	./main



### Classes Explanation
#### MapBuilder
> These classes implement the MapBuilder class, as required from assignment 3. MapBuilder is the interface builder class, ArenaBuilder implements MapBuilder and place the corresponding map elements on the map to make the "arena". MapGenerator contains a MapBuilder and has the ability to generates different kind of map from its MapBuilder.

#### MapBuilder
> The map builder's interface, a map builder must implements this abstract class to construct map of different type.

#### ArenaBuilder
> ArenaBuilder, implements MapBuilder. Build a 9x9 arena map, as instructed by assignment 3, with a guardian, and a potentially random generated chest. ArenaBuilder implements the placeMapObject method of MapBuilder.For random generated chest, please see ChestBuilder.h and .cpp.

##### 		Arena Builder GUI

		8	####O####
		9	#		#
		10	#		#
		11	#		#
		12	#		#
		13	#		#
		14	#	x	#	
		15	#	n	#
		16	####@####
			890123456
	  	  	  |30

#### MapGenerator
> MapGenerator is the director of MapBuilders. Can construct different type of map by invoking the constructMap() method, which itself calls the overloaded methods from MapBuilders.

__Additional comments inside of class files.__


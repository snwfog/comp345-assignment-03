__Note: A version of this assignment is also available on [GitHub](https://github.com/snwfog/comp345-assignment-03).__

# COMP345 Assignment 3 README
## Map Builder Programming Pattern

### Requirement
- __ncurses 5.9 lib installed__


### Important Files
- Map.cpp & .h
- MapBuilder.cpp & .h
- Item.cpp & .h
- ItemBuilder.cpp & .h
- _Chest.cpp & .h (Not as part of assignment 3)_
- _ChestBuilder.cpp & .h (Not as part of assignment 3)_

### To Run
> Use this command in the terminal to compile and link the assignment
	g++ Map.cpp MapBuilder.cpp MapEditor.cpp main.cpp -o main
> Use this command to run the main.cpp
	./main



### Classes Explanation
#### MapBuilder
> These classes implement the MapBuilder class, as required from assignment 3. MapBuilder is the interface builder class, ArenaBuilder implements MapBuilder and place the corresponding map elements on the map to make the "arena". MapGenerator contains a MapBuilder and has the ability to generates different kind of map from its MapBuilder.

#### MapBuilder
> The map builder's interface, a map builder must implements this abstract class to construct map of different type.

#### ArenaBuilder
> ArenaBuilder, implements MapBuilder. Build a 9x9 arena map, as instructed by assignment 3, with a guardian, and a potentially random generated chest. ArenaBuilder implements the placeMapObject method of MapBuilder.For random generated chest, please see ChestBuilder.h and .cpp.

	##### Arena Builder GUI

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


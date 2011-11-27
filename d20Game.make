# COMP345 - Project Make File
all:
	g++ -lncurses Observer.h Character.cpp CharacterBuilder.cpp Map.cpp MapBuilder.cpp Item.cpp ItemBuilder.cpp Function.cpp d20GameBuilder.cpp d20Game.cpp ChestBuilder.cpp MerchantBuilder.cpp MapEditor.cpp main.cpp -o ./main
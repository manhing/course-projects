**Introduction:**
- Our group set out to create a futuristic spaceship text-based RPG using C++, in which the user traverses rooms, interacts with objects, completes game objectives and is able to see various visual animations on the screen. Some of the main objectives we accomplished in this game were to: have item storage and interaction, user movement through different rooms, user can encounter objects and interact with them, user can complete game objectives, purpose and ending to the game, animations using the UNIX curses library, various verbs the user can type that perform different actions, data from the game is loaded by individual files, the game takes over 20 minutes to complete by first time users, and it is fun to play. 

**Description of what the program does from the user’s perspective:**
- Our character wakes up from a long cryogenic sleep in the future. Many years have passed and his memory is hazy when he first wakes up. He wakes up to an abandoned spaceship. He must figure out who he is, why he is there, and complete objectives in order to navigate the ship back to his home planet. The user is prompted with an introduction and told they can type ‘help’ to see the list of available commands.
- User is able to navigate through rooms using the command line to achieve certain objectives by typing n,s,e,w. 
- User can encounter objects within the rooms and has the options to look at them, pick them up, or drop them. There is a max weight of items a player can hold.
- User can have a long-form description upon entering the room for the first time. A short-form description will appear each subsequent time he visits that particular room.
- Objects can interact with certain other objects.
- During object interactions and certain points in the game, there are animations to depict visually what is happening. 

**Instructions:**
- Type "make" to run the makefile.
- The executable program is named "game".
- After compiling, type "./game" to start the program.
- The introduction animation will run ("Omicron" was our group name) and then you can type "help" to view the various commands. 

[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/161P2Fwo)
# OOP_basic_design_worksheet

## Before you write any code, clone and run the project to ensure your computer is set-up correctly

## Instructions (Read all before writing code)

Practice your new found skills in Single responsibility & encapsulation

You are to write a simple "game" where you move a circle "Player" around the scene using the cursor keys. The circle should not leave the playarea (screen).

Your game will need at least 4 classes for 4 different responsibilities:

- [ ] Player class: responsibility of knowing how the player moves in the world (including keeping player on screen)

- [ ] PlayerRender class:  responsibility of drawing player at correct location on screen

- [ ] PlayerController class:  responsibility of converting keyboard input into Player movement instructions

- [ ] Boundary class:  responsibility of knowing if a point is inside a rectangle representing the playarea

### Notes

- The player class should not have *any* SFML dependencies, at all (no `sf::` anywhere in Player)!
- Write all the classes in the same file as main()
- No class is allowed to have a setter method (use the constructor)
- limit the getters as much as possible
- Use "Tell, don't ask" principle
- Watch out for Demeter violations
- It's ok for classes to contain other classes, but you don't have to.
- Put all decisions (`if` statements) in the class that has the responsibility of that decision

## Submission

Upload the `.cpp` file to the assignment on BB

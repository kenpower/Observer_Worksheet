# Worksheet: Refactoring to Observer Pattern

## Objective

Convert the existing game code to use the Observer Pattern, focusing on the interaction between Collectables (as the subject) and various observers (Inventory, SoundSystem, and Achievements) that react to the collection of items.

## Background

The Observer Pattern is a software design pattern that allows an object, known as the subject, to maintain a list of its dependents, called observers, and notify them of any state changes. This pattern is useful for creating a loosely coupled system where the subject and its observers can interact without being tightly linked.

In the provided game code, Collectables acts as a system that could benefit from implementing the Observer Pattern. **When a Collectable item is collected, several systems need to be notified: the player's inventory needs to be updated (Inventory), a sound should be played (SoundSystem), and achievements might be affected (Achievements)**.

## Task

Your task is to refactor the game code to implement the Observer Pattern. This involves creating a generic Observer interface, making Inventory, SoundSystem, and Achievements implement this interface, and modifying Collectables to notify these observers when an item is collected.

Note you should only modify code in the `Observer_Worksheet.cpp` file. Look for `Todo` comments for hints in the code.

**Other files do should not be modified**.

### Step 1: Define the Observer Interface

Create an Observer interface with a notification method that will be called when a Collectable is collected.

### Step 2: Make Inventory, SoundSystem, and Achievements Implement the Observer Interface

Modify the Inventory, SoundSystem, and Achievements classes to implement the Observer interface. The `onNotify()` method in each should contain the logic that was previously called directly in the `checkCollisionWith()`.

### Step 3: Refactor Collectables to Use Observers

Modify the Collectables class to maintain a list of Observer pointers. Add methods to attach observers. When a collectable is collected, iterate over the observers and notify them.

## Step 4: Connect the Observers
In your Game class setup method, attach the Inventory, SoundSystem, and Achievements instances as observers to the Collectables instance.

### Step 5: Test the Game
Ensure that the game functions as before, with Collectables notifying the observers whenever an item is collected.

## Deliverables

Modified game code implementing the Observer Pattern, all new code in in `Observer_Worksheet.cpp`.
Ensure that all changes preserve the game's original functionality.

### Evaluation Criteria

Correct implementation of the Observer Pattern.
Inventory, SoundSystem, and Achievements respond appropriately to collected items.
This worksheet provides a structured approach to refactoring an existing codebase using the Observer Pattern, fostering a deeper understanding of design patterns and their practical applications in game development.

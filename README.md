Hi! This is my implementation example of the test task!

Here I used GAS implementations of abilities.

Keybindings:
1 - Camera switch
Space - Jump
Shift - Run
LMB - Fire
Hold LMB - Fire energy weapon
F - Switch weapon
WASD - Movement
E - Interact

Project Structure Description:

1. AI – contains everything related to artificial intelligence in the project
  a. EQS – contains the Environment Query System for navigation
  b. Services – contains services used in the Behavior Tree
  c. Tasks – contains tasks executed by the AI, structured in the Behavior Tree
2. Animations – contains character animations
3. BaseAbilities – contains all base abilities for characters
4. Character – contains textures, materials, and the character's skeleton
5. Destructible – contains destructible objects
6. Input – input settings for the character
7. Interactibles – interactive objects (doors, terminals; terminals only replenish ammo)
8. Light – flashing light
9. Maps – the game map
10. Sound – weapon firing sounds
11. Spawner – AI spawner
12. UI – widgets
13. Weapons
  a. Energy Rifle – a rifle that charges a shot and fires a projectile that interacts with objects (including destructibles)
      Ability
      Effect applied to enemies
      Projectile
      Rifle asset
      Data asset containing pickup info for the rifle
  b. Assault Rifle – implemented via line trace, does not interact with destructible objects
      Ability
      Effect applied to enemies
      Rifle asset
      Data asset containing pickup info for the rifle


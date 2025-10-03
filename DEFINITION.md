# BulletJSON Definition

TODO
TEMP:

// TODO: add the entire bulletML definition here
// TODO: add extensions bellow to the definition
// TODO: add if/else actions
// TODO: add $repeatIndex variable
// TODO: add BOOLEAN_EXPRESSION, same as NUMBER_EXPRESSION, but for boolean (><, ==, (), variables, NUMBER_EXPRESSION, etc)
// TODO: add variables that can be access, for example $direction, $speed, etc (mostly for bullet and actions)
// TODO: add spriteRef bullet attribute, will be the name of a sprite
// TODO: add spriteRef variable to set the sprite direction (absolute, relative, sequence, sameAsBullet) (important for arrow like bullet sprites)
// TODO: add color var to bullet
// TODO: add changeColor action (useful for dancing bullets, can change the color with "acceleration" and sync the dance with the color change (and mostly with the music))
// TODO: add rotation attribute to bullet (self rotation, useful for arrow like bullets, also useful for make "sprite animation")
// TODO: add warn time to the laser (the time were it will draw a line to warn before spawn the laser, while in this state, any other action can take effect at the laser, it will apply to the warn line instead (devil blade like))
// TODO: add variable on bullet that indicates that if the sprite angle should match the bullet direction

- Pattern: A list of Bullet Managers

- Bullet Manager: A Bullet spawner/manager
  - bulletArray
  - vector2 position
  - bulletDefinitions // array of <bullet> definitions, can call by bulletRef like
  - fireDefinitions // array of <fire> definitions, can call by fireRef like
  - actions // list of actions, in sequence (top, top1, top2, ...)
  - actionsAll // perform normal actions, but for all bullets spawned by this manager, usually starts with a <wait> until finish all normal actions


- Actions
  - fire
    - bulletRef | bullet
    - offset
      - direction // relative, absolute, sequencial, aimed
      - distance // relative, absolute, sequencial. case 0 will spawn at same position of bullet manager
  - beforeVanish // can be used to do another actions before vanish when out of screen for example


- Bullet
  - vector2 position
  - float speed
  - float direction // in radians
  - ptr spriteRef
  - actionArray 


- Laser // think about laser specs (curvy lasers too)
// TODO: Curvy lasers are basically a string of bullets with a laser sprites (one bullet spawn a lot of pullets on its path to merge the sprites and create a laser, when the driver bullet vanish it will vanish all others spawned by the bullet)


- NUMBER: Mathematic Expression
- STRING: Alphanumeric string // no space, etc
- PARAM: NUMBER // can be relative, absolute, sequencial, aimed
- Label: STRING
- 
- [ ] Add a loading warn on HTML on web builds (it's slow to download .data and .wasm files from gh-pages)

- [ ] Editor
    - [ ] Save/Load patterns from json files
    - [ ] Import BulletML patterns
    - [ ] Slowdown features (when reach X bullets on screen, gradually reduce the deltaTimeScale to Y)
    - [ ] Pixel Perfect Collision check
    - [ ] Draw the pattern execution sequence in a small simplified indented graph (e.g: Action X -> Fire Y (Bullet Z) -> Fire A (Bullet B) -> End)

- [ ] Rename the project to BulletEML (Bullet Extended Markup Language)

- [ ] IMPORTANT: On bullet pool system, on VanishBullet(), instead of re-sort the array every time you vanish a bullet, store the ids in a list and resort only once in every 5 or 10 seconds
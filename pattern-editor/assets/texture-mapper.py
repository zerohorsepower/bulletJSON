import json
import os

script_path = os.path.dirname(os.path.realpath(__file__))
sprites = []

with open(str(script_path) + '/texture.json') as f:
    sprites = json.load(f)

sprites = sorted(sprites['frames'], key=lambda d: d['filename'])

for sprite in sprites:
    name = sprite['filename'].upper()
    x = str(sprite['frame']['x'])
    y = str(sprite['frame']['y'])
    w = str(sprite['frame']['w'])
    h = str(sprite['frame']['h'])

    print('    Global::sprites[Global::SPRITE_'+name+'] = Global::Sprite { '+x+', '+y+', '+w+', '+h+' };')
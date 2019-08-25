"""
Script to convert *.obj files to config.yaml
"""
import sys
import os

TEMPLATE = """
render_delay: 0
materials:
  -
    name: Red
    color: 0
  -
    name: Yellow
    color: 1
  -
    name: Green
    color: 2
  -
    name: Cyan
    color: 3
scene:
  width: 320
  height: 240
  title: Something
  background: blue
  edges: true
  objects:
{objects}
""".strip()


OBJECT_TEMPLATE = """
    -
      name: {name}
      type: triangle
      material: Red
      rotation:
        type: 0
        angle: 1
        axis: [1, 0, 0]
        apply_num: 360
      points:
        - [{p1[0]}, {p1[1]}, {p1[2]}]
        - [{p2[0]}, {p2[1]}, {p2[2]}]
        - [{p3[0]}, {p3[1]}, {p3[2]}]
"""

# HACK: to include only faces specified (for debug purposes)
#ONLY_FACES = [0, 2, 3, 4, 6, 8, 9, 10]
ONLY_FACES = []


def _get_raw(filename:str)->str:
    with open(filename, "r") as f:
        return f.read()


def _extract_vertexes(raw_data:str)->list:
    result = []

    for row in raw_data.split('\n'):
        if not row.startswith('v '):
            continue
        points = [float(f) for f in row.replace('v ', '').split(' ')]
        # NOTE: currently, the renderer supports only rendering from the origin means if the
        # object has value for Z >= 0 - the viewport will be inside of it. So we move the object
        # further away.
        points[-1] -= 1.5
        result.append(points)

    return result


def _extract_faces(raw_data:str)->list:
    return [
        # NOTE: in *.obj files indexes starts with 1 so we deduce 1 to make it easier to work with later
        [int(c)-1 for c in row.replace('f ', '').split(' ')]
        for row in raw_data.split('\n') if row.startswith('f ')
    ]


def _render_template(vertexes:list, faces:list)->str:
    objects = []

    for i, face in enumerate(faces):
        if ONLY_FACES and i not in ONLY_FACES:
            continue
        p1, p2, p3 = [vertexes[f] for f in face]
        name = f"t{i}"
        objects.append(OBJECT_TEMPLATE.format(name=name, p1=p1, p2=p2, p3=p3))

    return TEMPLATE.format(objects=''.join(objects))


def main(filename:str):
    raw_data = _get_raw(filename)
    vertexes = _extract_vertexes(raw_data)
    faces = _extract_faces(raw_data)
    output = _render_template(vertexes, faces)
    print(output)



if __name__ == "__main__":
    try:
        filename = sys.argv[1]
    except IndexError:
        print("Specify filename to convert")
        sys.exit(1)

    main(filename)

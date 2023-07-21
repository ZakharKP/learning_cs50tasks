from cs50 import get_int


def main():
    # take heigh
    h = get_heigh()
    draw_pirammide(h)

# take heigh


def get_heigh():
    while True:
        h = get_int("Heigh: ")
        if h > 0 and h < 9:
            break
    return h

# draw columns


def draw_columns(s, b):
    if s >= b:
        print((" " * (s - b)) + ("#" * b) + "  " + ("#" * b))
        draw_columns(s, b + 1)

# draw pirammide


def draw_pirammide(h):
    steps = h
    bricks = 1
    draw_columns(steps, bricks)


main()
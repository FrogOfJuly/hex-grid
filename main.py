import pygame
import random
import math
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

import hex_grid

gr = hex_grid.GlobeRenderer(
    glVertex3f,
    glColor3f,
    lambda: glBegin(GL_TRIANGLE_FAN),
    lambda: glEnable(GL_CULL_FACE),
    lambda: glFrontFace(GL_CCW),
    glLoadIdentity,
    glOrtho,
    glEnd
)

p = hex_grid.Planet()

init_colours = [hex_grid.Colour(random.random(), random.random(), random.random()) for c in p.init_colours()]

keymaping = {
    pygame.K_0: 0,
    pygame.K_1: 1,
    pygame.K_2: 2,
    pygame.K_3: 3,
    pygame.K_4: 4,
    pygame.K_5: 5,
    pygame.K_6: 6,
    pygame.K_7: 7,
    pygame.K_8: 8,
    pygame.K_9: 9,
}


def main():
    pygame.init()
    display = (600, 600)
    pygame.display.set_mode(display, DOUBLEBUF | OPENGL)
    pygame.display.set_caption('PyOpenGLobe')
    pygame.key.set_repeat(1, 10)  # allows press and hold of buttons
    gluPerspective(40, (display[0] / display[1]), 0.1, 50.0)
    glTranslatef(0.0, 0.0, -5)  # sets initial zoom so we can see globe
    last_pos_x = 0
    last_pos_y = 0
    colours = init_colours
    cur_grid_size = 0
    while True:
        for event in pygame.event.get():  # user avtivities are called events

            # Exit cleanly if user quits window
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

            # Rotation with arrow keys
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT:
                    glRotatef(1, 0, 1, 0)
                if event.key == pygame.K_RIGHT:
                    glRotatef(1, 0, -1, 0)
                if event.key == pygame.K_UP:
                    glRotatef(1, -1, 0, 0)
                if event.key == pygame.K_DOWN:
                    glRotatef(1, 1, 0, 0)
                if event.key in keymaping.keys() and cur_grid_size != keymaping[event.key]:
                    cur_grid_size = keymaping[event.key]
                    p.set_grid_size(cur_grid_size);
                    colours = [
                        hex_grid.Colour(random.random(), random.random(), random.random())
                        for _ in p.init_colours()
                    ]

            # Zoom in and out with mouse wheel
            if event.type == pygame.MOUSEBUTTONDOWN:
                if event.button == 4:  # wheel rolled up
                    glScaled(1.05, 1.05, 1.05)
                if event.button == 5:  # wheel rolled down
                    glScaled(0.95, 0.95, 0.95)

            # Rotate with mouse click and drag
            if event.type == pygame.MOUSEMOTION:
                x, y = event.pos
                dx = x - last_pos_x
                dy = y - last_pos_y
                mouseState = pygame.mouse.get_pressed()
                if mouseState[0]:
                    modelView = (GLfloat * 16)()
                    mvm = glGetFloatv(GL_MODELVIEW_MATRIX, modelView)

                    # To combine x-axis and y-axis rotation
                    temp = (GLfloat * 3)()
                    temp[0] = modelView[0] * dy + modelView[1] * dx
                    temp[1] = modelView[4] * dy + modelView[5] * dx
                    temp[2] = modelView[8] * dy + modelView[9] * dx
                    norm_xy = math.sqrt(temp[0] * temp[0] + temp[1]
                                        * temp[1] + temp[2] * temp[2])
                    glRotatef(math.sqrt(dx * dx + dy * dy),
                              temp[0] / norm_xy, temp[1] / norm_xy, temp[2] / norm_xy)

                last_pos_x = x
                last_pos_y = y

        # Creates Sphere and wraps texture
        glEnable(GL_DEPTH_TEST)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

        gr.draw_planet(p, colours)
        # Displays pygame window
        pygame.display.flip()
        pygame.time.wait(10)


if __name__ == "__main__":
    main()

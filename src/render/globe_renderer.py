from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *


class GlobeRenderer:
    default_size = 600

    def __init__(self, w=default_size, h=default_size):
        self.width = w
        self.height = h

    def set_matrix(self):
        glLoadIdentity()
        x = self.width / GlobeRenderer.default_size
        y = self.height / GlobeRenderer.default_size
        glOrtho(-x, x, -y, y, -2.0, 0.0)

    @staticmethod
    def draw_tile(tile, color):
        glColor3f(color)
        glBegin(GL_TRIANGLE_FAN)
        glVertex3f(tile.vector)
        for c in tile.corners:
            glVertex3f(c.vector)
        glVertex3f((tile.corners[0]).vector)
        glEnd()

    def draw_planet(self, planet, colors):
        self.set_matrix()
        glFrontFace(GL_CCW)
        glEnable(GL_CULL_FACE)
        for t in planet.tiles:
            GlobeRenderer.draw_tile(t, colors[t.id])

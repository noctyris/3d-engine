from ulab import numpy as np
from kandinsky import *
from math import *
from ion import *

HEIGHT,WIDTH=222,320
STEP=0.1

class Vec:
  def __init__(self,pos):
    self.pos=np.array(pos+(1,))
  def getSceenCoords(self,r=False):
    Vs=np.dot(comp,self.pos)
    self.pX,self.pY=(Vs[0]/Vs[3]+1)/2*WIDTH,(1-Vs[1]/Vs[3])/2*HEIGHT
    if r: self.pX,self.pY=round(self.pX),round(self.pY)

class Cam:
  def __init__(self,eye,tar,zlim,fov):
    self.eye=np.array(eye)
    self.tar=np.array(tar)
    self.zn,self.zf=sorted(zlim)
    self.fov=fov
  def projection_matrix(self):
    a,f,dz=HEIGHT/WIDTH,1/tan(self.fov/2),self.zf-self.zn
    return np.array([
      [a*f,0,0,0],
      [0,f,0,0],
      [0,0,self.zf/dz,-self.zf*self.zn/dz],
      [0,0,1,0]
    ])
  def view_matrix(self):
    norm=lambda u: u/np.linalg.norm(u)
    f=norm(self.tar-self.eye)
    r=norm(np.cross(np.array((0,1,0)),np.array(f)))
    u=np.cross(f,r)
    return np.array([
      [r[0],r[1],r[2],-np.dot(r,self.eye)],
      [u[0],u[1],u[2],-np.dot(u,self.eye)],
      [f[0],f[1],f[2],-np.dot(f,self.eye)],
      [0,0,0,1]
    ])

camera=Cam((6,3,2),(0,0,0),(.1,1000),pi/180*70)

def display(vectices):
  hasToBeDrawn=lambda v: v.pos[3]>camera.zn
  fill_rect(0,0,320,222,get_palette()["HomeBackground"])
  for i in range(len(vectices)):
    fill_circle(vectices[i].pX,vectices[i].pY,3,"white")
    for j in range(i+1,len(vectices)):
      if hasToBeDrawn(vectices[i]) and hasToBeDrawn(vectices[j]): draw_line(vectices[i].pX,vectices[i].pY,vectices[j].pX,vectices[j].pY,"white")

vectices=[
  Vec((-1, -1, -1)),
  Vec((-1, -1,  1)),
  Vec((-1,  1, -1)),
  Vec((-1,  1,  1)),
  Vec(( 1, -1, -1)),
  Vec(( 1, -1,  1)),
  Vec(( 1,  1, -1)),
  Vec(( 1,  1,  1))
]
M=np.eye(4)

def camMv(d):
  mv=lambda a: np.array((a[0],a[1],a[2]))+np.array(d)*STEP
  camera.eye=mv(camera.eye)
  camera.tar=mv(camera.tar)
  display(vectices)

comp=np.dot(np.dot(camera.projection_matrix(),camera.view_matrix()),M)
for i in vectices: i.getSceenCoords(True)
display(vectices)

while 1:
  if keydown(0):  camMv((0, 0, 1)) # Left
  if keydown(3):  camMv((0, 0,-1)) # Right
  if keydown(1):  camMv((0,-1, 0)) # Up
  if keydown(2):  camMv((0, 1, 0)) # Down
  if keydown(45): camMv((-1,0, 0)) # Far
  if keydown(46): camMv(( 1,0, 0)) # Near
  comp=np.dot(np.dot(camera.projection_matrix(),camera.view_matrix()),M)
  for i in vectices: i.getSceenCoords(True)
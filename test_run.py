from pybricks.hubs import PrimeHub
from pybricks.pupdevices import Motor, ColorSensor, UltrasonicSensor, ForceSensor
from pybricks.parameters import Button, Color, Direction, Port, Side, Stop
from pybricks.robotics import DriveBase
from pybricks.tools import wait, StopWatch

hub = PrimeHub()

# Setting up the wheels
left_wheel = Motor(Port.C, Direction.COUNTERCLOCKWISE) # Counter-clockwise for forward movement
right_wheel = Motor(Port.A) # Clockwise for forward movement

# Setting up the drive base 
drive_base = DriveBase(left_wheel, right_wheel, wheel_diameter=87.5, axle_track=178) 

# Instructions
drive_base.straight(1000)
drive_base.turn(-90)
drive_base.straight(500)
drive_base.turn(90)
drive_base.straight(300)
drive_base.turn(180)
drive_base.straight(500)
from pybricks.hubs import PrimeHub
from pybricks.pupdevices import Motor, ColorSensor, UltrasonicSensor, ForceSensor
from pybricks.parameters import Button, Color, Direction, Port, Side, Stop
from pybricks.robotics import DriveBase
from pybricks.tools import wait, StopWatch

hub = PrimeHub()
left_wheel = Motor(Port.C, Direction.COUNTERCLOCKWISE)
right_wheel = Motor(Port.A)

drive_base = DriveBase(left_wheel, right_wheel, wheel_diameter=87.5, axle_track=178)
drive_base.turn(90)


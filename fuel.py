from pybricks.hubs import PrimeHub
from pybricks.pupdevices import Motor, ColorSensor, UltrasonicSensor, ForceSensor
from pybricks.parameters import Button, Color, Direction, Port, Side, Stop
from pybricks.robotics import DriveBase
from pybricks.tools import wait, StopWatch

hub = PrimeHub()
left_wheel = Motor(Port.C, Direction.COUNTERCLOCKWISE)
right_wheel = Motor(Port.A)
motor = Motor(Port.B)

drive_base = DriveBase(left_wheel, right_wheel, wheel_diameter=87.5, axle_track=178)
drive_base.use_gyro(True)
drive_base.reset()

hub.display.text('9876543210', on=1000, off=0)
drive_base.straight(140)
motor.run_target(200, -90, then= Stop.HOLD, wait= True)
drive_base.straight(-45)
drive_base.turn(90)
drive_base.straight(1850)
motor.run_target(200, 0, then= Stop.HOLD, wait= True)
drive_base.straight(-1850)
from pybricks.hubs import PrimeHub
from pybricks.pupdevices import Motor, ColorSensor, UltrasonicSensor, ForceSensor
from pybricks.parameters import Button, Color, Direction, Port, Side, Stop
from pybricks.robotics import DriveBase
from pybricks.tools import wait, StopWatch

hub = PrimeHub()

def estimate_battery_percentage(voltage):
    return voltage*100/8

voltage = hub.battery.voltage() / 1000  # Pybricks gives voltage in mV
estimated_percentage = estimate_battery_percentage(voltage)

print("Battery Voltage:", voltage, "V")
print("Battery Percentage:", estimated_percentage, "%")


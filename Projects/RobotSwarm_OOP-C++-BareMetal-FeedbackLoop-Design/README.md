# Authors
Veselin Atanasov, Plamen Tsokov, Simeon Stoilov
# Context
A robot car which has a hc-sr04 ultrasonic sensor. Whenver the robot starts approaching the set point of 10cm, it needs to start slowing down, so the robot stops smootly. Once the robot stops at the setpoint, it has to rotate to a random side(left or right) with a random angle of the turn. The UML in the folder is the initial design which our code was based on. The abstract context diagram provides an overview of the system and its components.
# My contribution
Feedback loop system for steady stop(The working PID controller is in the main file not the PID.cpp file), UML, Abstract context diagram

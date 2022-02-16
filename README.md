# Solar-marine-db

# **INTRODUCTION**

To finish this second year of electronic maintenance we have had to continue with the project started last year, which consists of a boat powered by a solar panel. Apart from this, it should include an autopilot programmed with arduino and the solar panel should automatically orient itself towards the sun during the whole journey in order to achieve maximum performance. This project will participate in the tournament to be held on 18 June 2022 in Praia da Ribeira, Baiona.

# **Rules of the race**

Our project is a solar boat, and we have to take this project to the solar marine race. In order to participate in the project we have to fulfil a number of requirements and needs.

- The boat will be powered by a solar panel, only a solar panel, so no batteries can be used to store energy for when there is not so much light.
- The boat has to be controlled by a transmitter.
- The boat has to be driven by electric motors and more than one can be used.
- The boat can be built as we want and with the materials we want.
- We can only use batteries to power the boat's transmitter (radio control). Following these steps we will build our solar boat.


# **PROCEDURE**

To start with we had to see what condition the ship was in and what it needed. After the inspection we proceeded to do a project planning. This project mainly needed programming, a pcb and some improvements in the chassis. 

# **PARTS THAT MAKE UP THE PROJECT AND HOW IT WORKS**

The project is divided into 4 parts:

![490x_dia-mundial-agua-debajo-luz-azul-olas-brillo-getty-770x420](https://user-images.githubusercontent.com/96468247/154023383-b8c38dc0-6402-46eb-8655-49e07378b523.jpg)

# **ARDUINO**

The most important part of this project was the programming of an arduino nano to make the autopilot and the MPPT. For this we had to make two general programs and when we finished them we created a program called Solar Marine that put together the two previous programs.

**AUTOPILOT**

For the autopilot, we first had to get the motors to work with the controller. Secondly, we had to connect the teensy to the arduino nano via serial, as the teensy sends data to the bluetooth module via serial. When connecting them we had to make a program just to select the compass orientation. Finally having the two values we made a program that follows the direction that we assign with the remote control and makes corrections so that it does not deviate.
The following algorithm has been used to program the Autopilot code:

**MPPT**![Piloto automatico algoritmo](https://user-images.githubusercontent.com/99804190/154353780-bb3c349d-86fc-4285-abf0-5da22feb9144.PNG)

The MPPT is used to achieve the highest possible power at all times and to do this it varies the speed of the motors to increase or decrease the current. We had to program the MPPT with arduino. To do this, the first thing we had to do was to get the voltage and current we had. Then, we had to get the power and finally we made the program that varies the speed of the motors depending on the values we have.
The following algorithm has been used to program the MPPT code:

![MPPT algoritmo](https://user-images.githubusercontent.com/99804190/154353310-60933a73-43ca-4bd5-9331-0257c4e54f84.jpg)

# **MECHANICS** 

On the mechanical side we didn't have to do much, as almost everything was already done last year, we just added a few improvements. 

**STRIPS**

We added some wooden slats to reinforce the stability of the boat.

![1644829115268](https://user-images.githubusercontent.com/96468247/153832324-f5b47bdc-34f0-4172-8ef1-35426df3f29a.jpg)

**PANEL RUBBERS**

When we took delivery of the boat, the rubbers that hold the engine guides were in bad condition, so we selected a more resistant material and replaced it.
![1644831005396](https://user-images.githubusercontent.com/96468247/153837278-2c415607-8189-47f1-a397-191e0adfbcf5.jpg)

**WATERPROOFING**

For the waterproofing of the boat, we have replaced the casing covering the circuits with a new one and added cable glands for further waterproofing.

![1644831437435](https://user-images.githubusercontent.com/96468247/153838426-fdee1404-bff1-40a5-b1fb-7d1962980dff.jpg)


# **ELECTRONICS** 
In the project we had to make a PCB to put the electronic components together. This has been designed in Proteus and then milled with a LPKF.
In the following image we can see the design of the board: 

![pcb](https://user-images.githubusercontent.com/96468247/153840500-279f602c-aeee-4c96-9c1c-1baceb9a48c8.PNG)

And in the following image we can see the final result:

![1644832259025](https://user-images.githubusercontent.com/96468247/153840832-f83742b2-d365-4516-96bd-5b9d06a57b08.jpg)

# **SUPPLY** 
For powering the boat we use the HQST-100DB solar panel which provides us with a maximum power of 100W, a maximum voltage of 21.7V and a maximum current of 6.1 Amps.

![1644832649844](https://user-images.githubusercontent.com/96468247/153860980-17192ad2-77d9-4fa3-9d87-7f672da59693.jpg)

But this voltage is too high for the ESCs, so we use Step-Downs to lower the voltage to 16V to power the ESCs that control the motors.

![1644840467964](https://user-images.githubusercontent.com/96468247/153862948-881a197c-f783-4474-bf1a-ff32fdf410ca.jpg)

# **OPERATION OF THE BOAT** 

In the following image we have the electrical diagram of the project. First we can see how the board feeds two ammeters that are between the step down and the board. These send the current to the arduino. To get the voltage we have two resistors in series to create a voltage divider that goes to the arduino. 
After lowering the voltage to 16V we feed the ESCs that power the arduino and are controlled by the arduino. With the ESCs we control the motors. For the program that controls the ESCs we need information for this we have connected a radio control. Finally we have connected the arduino with the teensy to know the position of the compass that is connected to it.

![Captura](https://user-images.githubusercontent.com/96468247/154062460-d0ea52d9-f697-4e18-9102-274636bf4b02.PNG)


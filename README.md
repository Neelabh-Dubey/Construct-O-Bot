Project Name- Contruct-O-Bot

Objective- To construct a bot which can traverse on a given predefined map.

Use Case- After any natural calamities, mass restoration and reconstruction work happens. This need a lot of human effort and it has serious risk
            of life the person involved in the work due to uneven terrain and mobility issues for humans. This bot was designed so that it can carry goods, raw material form one place to another place following shortest path.

Hardware Requirements-
        1)-Four Wheels
        2)-Chasis
        3)-Bot's body material(styrene sheets)
        4)-4 DC Motors
        5)-Motor Encoders
        6)-AVR development board
        7)-Programmer Kit
        8)-Power Source- LiPo battery
        9)-Sharp Sensors
        10)-Ultrasonic Sensors
        11)-Line Array Sensor
        other utility components like chargers, buzzer, jumpers, jacks, voltage convertors, etc.

Software Requirement-
        1)-V-rep
        2)-Any code editor for cpp programming
        3)-Arduino IDE

Our Work-
    Hardware-
        We constructed bot that can traverse paths following black lines, side walls. Bot was capable of traversing shortest path on a given map. Sensors like Sharp IR, Ultrasonics sensors were used to take data from ground surface and side walls and these data are processed as per our desigend algo to generate shortest path between source and destination. Bot has block picking mechanism.
        Overall, it was like self-driving JCB prototype but with limited setup and constraints.

    Software- 
        We designed our algo (based single-shortest-path-following-algos like Dijkstra) which process input data based on bot location (mapped coordinates) and destination location to generate shortest path between them. We were given a map representing different paths, halting points, picking stations, destination points, etc. Our algo proudce final shortest path available for any two node on the map.

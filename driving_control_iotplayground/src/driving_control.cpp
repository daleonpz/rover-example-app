/*
 * Copyright (c) 2019 FH Dortmund and others
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Description:
 *    Rover driving control example
 *
 * Author:
 *    Daniel Paredes - daleonpz@gmail.com 
 *
 */

#include <stdio.h>

//Basis Include
#include <roverapi/rover_api.hpp>

//Driving Include
#include <roverapi/rover_driving.hpp>

//Using rover namespace from Rover API
using namespace rover;

typedef enum
{
    forward,
    backward,
    turnright, 
    turnleft,
    idle,

}roverStates;

int main (){
    printf("Started roverapp driving example.\n");
    RoverBase r_base = RoverBase();
    r_base.initialize();
    
    // Driving with rover
    RoverDriving r_driving = RoverDriving();
    r_driving.initialize();
    r_driving.setSpeed(HIGHEST_SPEED);

    // Modify here to add more steps 
    roverStates steps[] = {forward, 
                backward, 
                turnleft, 
                idle};

    int moves = (int)( sizeof(steps) / sizeof(steps[0]));

    for( int i=0; i<moves; i++){
        switch( steps[i] ){
            case forward:
                r_driving.goForward();
                break;
            case backward:
                r_driving.goBackward();
                break; 
            case turnright:
                r_driving.turnRight();
                break;
            case turnleft:
                r_driving.turnLeft();
                break;
            case idle: 
            default:
                r_driving.stopRover();
                break; 
        }
        r_base.sleep (1500);
        printf("states: %i \n", steps[i]);
    }
    
    printf("Exiting.\n");
    return 0;
}

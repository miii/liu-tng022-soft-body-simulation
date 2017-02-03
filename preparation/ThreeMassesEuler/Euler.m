function [ position, velocity ] = Euler( i,j, mass, h, force, velocity, position )
%Euler Function for one mass in a string damper system
%   i = iteration 
%   j = massNumber 
%   mass = mass of object
%   h = step size
%   force = difEquation of force
%   position = position of object

    velocity(i+1,j) = velocity(i,j) + h*force/mass; 
    position(i+1,j) = position(i,j) + h*velocity(i+1,j); 

end


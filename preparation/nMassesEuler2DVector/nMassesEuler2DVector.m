clc
clear all
close all

m = 2; % mass 
k = 50; % spring constant
d = 2; % damper constant
r = 0.9; % rest length
h = 0.01; % step size
samples = 1000;

% initial state
masses = [0 0; 1 0; 2 1];
velocity = [0 0; 0 0; 0 0];

[pos vel] = createMSDVector2D(masses, velocity, m, k, d, r, h, samples);

% pos(sample, mass, axis)
x = pos(:, :, 1);
y = pos(:, :, 2);

%plot(y)

%plot(x', y', 'O')
visualize2D(x, y, 0.001)
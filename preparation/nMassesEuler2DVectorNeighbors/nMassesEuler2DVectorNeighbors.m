clc
clear all
close all

m = 2; % mass 
k = 40; % spring constant
d = 2; % damper constant
r = 0.8; % rest length
h = 0.01; % step size
samples = 1000;

% initial state
masses = [0 0; 1 0; 1.2 1.2; 0 1];
velocity = [0 0; 0 0; 0 0; 0 0];

% connections(mass, neighbor)
connections = [4 2 3; 1 3 4; 2 4 1; 3 1 2];
connecitons = cleanConnections(connections, samples, m);

[pos vel] = createMSDVector2DNeighbors(masses, velocity, connections, m, k, d, r, h, samples);

% pos(sample, mass, axis)
x = pos(:, :, 1);
y = pos(:, :, 2);

%plot(y)

%plot(x', y', 'O')
visualize2D(x, y);
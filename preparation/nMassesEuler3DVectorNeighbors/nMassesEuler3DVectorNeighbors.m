clc
clear
close all

m = 1; % mass 
k = 20; % spring constant
d = 5; % damper constant
r = 0.5; % rest length
h = 0.01; % step size
samples = 2000;

%[masses, connections] = genMasses(2);
%masses
%connections

% initial state
%masses = [0 0 0; 1 0 0; 0 1 0; 1 1 0; 0 0 1; 1 0 1; 0 1 1; 1 1 1]; % pos
%velocity = [0 0 0; 0 0 0; 0 0 0; 0 0 0; 0 0 0; 0 0 0; 0 0 0; 0 0 0];
masses = [0 0 0; 1 0 0; 2 0 0; 0 1 0; 1 1 0; 2 1 0; 0 2 0; 1 2 0; 2 2 0];
%masses = [0 0 0; 1 0 0; 0 1 0; 1 1 0];
%masses = [0 0 0; 0 1 0; 1 0 0];
velocity = zeros(size(masses));

% connections(mass, neighbor)
%connections = [5 2 3; 1 4 6; 1 4 7; 3 2 8; 6 7 1; 8 5 2; 3 5 8; 7 6 4];
%connections = [5 2 3 6 4 7; 1 4 6 5 8 3; 1 4 7 8 2 5; 3 2 8 1 7 6; 6 7 1 2 8 3; 8 5 2 7 4 1; 3 5 8 4 6 1; 7 6 4 3 2 5];
connections = [2 5 4 0 0 0 0 0; 1 4 5 6 3 0 0 0; 2 5 6 0 0 0 0 0; 1 2 5 8 7 0 0 0; 1 2 3 4 6 7 8 9; 3 2 5 8 9 0 0 0; 4 5 8 0 0 0 0 0; 7 4 5 6 9 0 0 0; 6 5 8 0 0 0 0 0];
%connections = [2 3 4; 1 3 4; 1 2 4; 1 2 3];
%connections = [2 3; 1 3; 1 2];
connecitons = cleanConnections(connections, samples, m);

[pos vel] = createMSDVector3DNeighbors(masses, velocity, connections, m, k, d, r, h, samples);

% pos(sample, mass, axis)
x = pos(:, :, 1);
y = pos(:, :, 2);
z = pos(:, :, 3);

%plot(z)

%plot(y)

%plot(x', y', 'O')
visualize3D(x, y, z, connections);

%line(x, y, z)
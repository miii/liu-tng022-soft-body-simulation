clc
clear all
close all

m = 2; % mass 
k = 20; % spring constant
d = 0.4; % damper constant
r = 0.5; % rest length

h = 0.01; % step size
samples = 2000;

n = 5; % number of masses
% initial state
x(1,1:n) = [-2 -1 0 1 2 ];   
v(1,1:n) = [0 0 0 0 0];

[x, v] = create_MSD(x, v, samples, n, m, k, d, r, h);

figure(1);
plot(x)

%visualize2D(x, 0, [-2 2], [-1 1]);
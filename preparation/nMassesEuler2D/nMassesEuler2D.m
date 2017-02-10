clc
clear all
close all

m = 2; % mass 
k = 20; % spring constant
d = 5; % damper constant
r = 0.5; % rest length

h = 0.01; % step size
samples = 20 / h;

n = 3; % number of masses
% initial state
x(1,1:n) = [-1 0 1];   
vx(1,1:n) = [0 0 0];

y(1,1:n) = [0 1 0];   
vy(1,1:n) = [0 0 0];

[xa, vxx] = create_MSD(x, vx, samples, n, m, k, d, r, h);
[ya, vyy] = create_MSD(y, vy, samples, n, m, k, d, r, h);

%figure(1);
%plot(xa)

%figure(2);
%plot(ya)

visualize2D(xa, ya)
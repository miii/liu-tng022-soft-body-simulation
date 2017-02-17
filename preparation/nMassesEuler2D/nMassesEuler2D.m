clc
clear all
close all

m = 2; % mass 
k = 50; % spring constant
d = 20; % damper constant
r = 0.8; % rest length

h = 0.01; % step size
samples = 10 / h;

% initial state
x(1,:) = [-1 0 1];   
vx(1,:) = [0 0 0];

y(1,:) = [0 1 0];   
vy(1,:) = [0 0 0];

n = length(x);

[xa, vxx] = create_MSD(x, vx, samples, n, m, k, d, r, h);
[ya, vyy] = create_MSD(y, vy, samples, n, m, k, d, r, h);

%figure(1);
%plot(xa)

% figure(2);
% plot(ya(:, 1:2))
% figure(3);
% plot(ya(:, 2:3))
% figure(4)
% plot(ya)

visualize2D(xa, ya)
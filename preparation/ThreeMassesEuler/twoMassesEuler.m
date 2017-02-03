clear all
close all

m = 2; % mass 
k = 20; % spring
d = 0.4; % damper
r = 0.5; % rest length

h = 0.01; % step size
samp = 2000;

% initial state
x(1,1) = -1;
x(1,2) = 0;
v(1,1) = 0;
v(1,2) = 0;


for i=1:samp
    
    absx = abs(x(i,1)-x(i,2));

    
    [xab1, xab2] = create_direction(x, i, 1, 2);
    f1 = -(k*( absx - r)*xab1 + d*(v(i,1)-v(i,2)));

    f2 = -(k*( absx - r)*xab2 + d*(v(i,2)-v(i,1)));

    
    %Euler
    v(i+1,1) = v(i,1) + h*f1/m; 
    x(i+1,1) = x(i,1) + h*v(i+1,1); 
    v(i+1,2) = v(i,2) + h*f2/m;
    x(i+1,2) = x(i,2) + h*v(i+1,2);
    
end
figure(1);
plot(x)


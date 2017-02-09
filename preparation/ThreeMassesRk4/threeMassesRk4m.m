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
x(1,3) = 1;
v(1,1) = 0;
v(1,2) = 0;
v(1,3) = 0;

for i=1:samp
    
    absx12 = abs(x(i,1)-x(i,2));
    absx23 = abs(x(i,2)-x(i,3));
    x12 = create_direction(x, i, 1, 2);
    x23 = create_direction(x, i, 2, 3);
    
    f1 = -(k*( absx12 - r)*x12 + d*(v(i,1)-v(i,2)));
    f2 = -f1 -(k*( absx23 - r)*x23 + d*(v(i,2)-v(i,3)));
    f3 = k*( absx23 - r)*x23 + d*(v(i,2)-v(i,3));v(i+1,2) = v(i,2) + h*f2/m;
    x(i+1,2) = x(i,2) + h*v(i+1,2);
    
    % Runge Kutta 4th order (funkar inte exakt som den ska)
    [x,v]=rk4(i,1,m,h,f1,v,x); 
    [x,v]=rk4(i,2,m,h,f2,v,x); 
    [x,v]=rk4(i,3,m,h,f3,v,x); 
    
    
end

figure(1);
plot(x)


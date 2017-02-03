function [ direction_ab, direction_ba ] = create_direction( x, i, a, b )
% This function will generate the direction
% x is the incoming vector
% (i,a) is the first point
% (i,b) is the second point
    absx = abs(x(i,a)-x(i,b)); 
    direction_ab = (x(i,a)-x(i,b))/absx;
    direction_ba = (x(i,b)-x(i,a))/absx;  
end


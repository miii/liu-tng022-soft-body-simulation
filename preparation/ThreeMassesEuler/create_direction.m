function direction = create_direction( x, i, a, b )
% This function will generate the direction
% x is the incoming vector
% (i,a) is the first point
% (i,b) is the second point
    absx = abs(x(i,a)-x(i,b)); 
    direction = (x(i,a)-x(i,b))/absx;
end


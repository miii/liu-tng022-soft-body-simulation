function [masses, connections] = genMasses(s)
    masses = zeros(s^3, 3);
    connections = zeros(s^3, 6);
    
    l = 1;
    for i = 1:s
        for j = 1:s
            for k = 1:s
                masses(l, :) = [i-1 j-1 k-1];
                
                if i > 1
                    connections(l, 1) = (i-2)*s + (j-1)*s + (k-1);
                end
                if i < s
                    connections(l, 2) = (i)*s + (j-1)*s + (k-1);
                end
                if j > 1
                    connections(l, 3) = (i-1)*s + (j-2)*s + (k-1);
                end
                if j < s
                    connections(l, 4) = (i-1)*s + (j)*s + (k-1);
                end
                if k > 1
                    connections(l, 5) = (i-1)*s + (j-1)*s + (k-2);
                end
                if j < s
                    connections(l, 3) = (i-1)*s + (j-2)*s + (k);
                end
                
                l = l + 1;
            end
        end
    end
end


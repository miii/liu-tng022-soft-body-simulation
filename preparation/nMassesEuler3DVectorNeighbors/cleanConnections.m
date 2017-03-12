function connections = cleanConnections(connections, samples, m)
%connections = cleanConnections(connections, samples, m)
%   Remove duplicates from connections (only one-way connections are allowed)

     % Loop through all samples
    for i = 2:samples
        
        % Loop through all masses
        for j = 1:m
            
            % Get number of neighbor masses
            kk = length(connections(j, :));
            
            % Loop through all neighbors of current mass
            for k = 1:kk
                
                % Get neighbor index
                ni = connections(j, k);
                
                % Zero value can be seen as NULL
                if ni == 0
                   continue;
                end
        
                % Remove connection if given by other mass too.
                % This is to avoid spring from being calculated multiple
                % times in the same frame.
                [~, fcm] = size(connections);
                for l = 1:fcm
                    
                    if connections(ni, l) == j
                        connections(ni, l) = 0;
                        break;
                    end
                end
                
            end
            
        end
        
    end
end


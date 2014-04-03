function [ direct, scatterd] = illumination(full, pattern1, pattern2)
%ILLUMINATION Summary of this function goes here
%   Detailed explanation goes here
    [x, y, d] =size(full);
    direct = pattern1;
    scatterd = pattern2;
    for i=1:1:x
        for j=1:1:y
            for k=1:1:d
                l_plus = 0;
                l_minus = 0;
                if (pattern1(i, j, k) > pattern2(i,j,k))
                    l_plus = pattern1(i,j,k);
                    l_minus = pattern2(i,j,k);
                else
                    l_plus = pattern2(i,j,k);
                    l_minus = pattern1(i,j,k);
                end
                scatterd(i,j,k) = 2*l_minus;
                direct(i,j,k) = l_plus - l_minus;
            end
        end
    end
   
end


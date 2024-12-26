N = 8;
C = round(dctmtx(N) * 2^14.5);

fileID = fopen('dct_coeff_table.txt', 'w');

for i = 1:N
    fprintf(fileID, '{ ');
    fprintf(fileID, '%d', C(i, 1));
    
    for j = 2:N
        fprintf(fileID, ', %d', C(i, j));
    end
    
    if i == N
        fprintf(fileID, ' }\n');
    else
        fprintf(fileID, ' },\n');
    end
end
fclose(fileID);

N = 512;
image = imread('lena_gray.bmp');
block = double(image(1:N, 1:N)); 

fileID = fopen('input.dat', 'w');

for i = 1:N
    fprintf(fileID, '%d ', block(i, :)); 
    fprintf(fileID, '\n');               
end

fclose(fileID);

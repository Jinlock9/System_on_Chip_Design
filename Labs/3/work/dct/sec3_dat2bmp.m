N = 512;
fileID = fopen('output.dat', 'r');

block = fscanf(fileID, '%d', [N, N]);
block = block';                       

fclose(fileID);

block_image = uint8(block);

imwrite(block_image, 'recovered_image.bmp');

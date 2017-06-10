close all;clear all;clc;

files = dir('E:\FaceRecognition\face\*.BMP');
len = size(files,1);
for i = 1:len
    fileName = files(i).name;
    % Rename the file
    newName = ['face','_',num2str(i)];
    movefile(['E:\FaceRecognition\face\',fileName],['E:\FaceRecognition\face\',newName,'.bmp']);
end
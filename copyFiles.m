close all;clear all;clc;

path = 'E:\FaceRecognition\test\';
% 遍历test文件夹下的所有子文件夹。
subFolders = dir(path);
foldersLen = size(subFolders,1);
for i = 3:foldersLen
    subFolder = [path,subFolders(i).name];
    disp(['----------',subFolder,'----------'])
    %     遍历子文件夹下的所有文件。
    files = dir(subFolder);
    copyfile([subFolder,'\',files(4).name],['E:\FaceRecognition\train\train_',subFolders(i).name,'.bmp']);
end
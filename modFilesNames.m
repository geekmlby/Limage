close all;clear all;clc;

path = 'E:\FaceRecognition\test\';
% 遍历test文件夹下的所有子文件夹。
subFolders = dir(path);
foldersLen = size(subFolders,1);
for i = 3:foldersLen
    subFolder = [path,subFolders(i).name];
    disp(['----------',subFolder,'----------'])
%     遍历子文件夹下的所有文件。
    files = dir([subFolder,'\*.BMP']);
    filesLen = size(files,1);
    for j = 1:filesLen
        disp(['----------',files(j).name,'----------'])
%         截取文件名(除去文件扩展名)。
        fileFullName = files(j).name;
        fileNameIndex = strfind(fileFullName,'.');
        fileName = fileFullName(1:fileNameIndex - 1);
%         重命名文件。
        movefile([subFolder,'\',fileFullName],[subFolder,'\','test_',fileName,'.bmp']);
    end
end







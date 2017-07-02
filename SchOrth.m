% Schmidt orthogonalization
function SchOrthMat = SchOrth(BaseMat)

[rNum,cNum] = size(BaseMat);
SchOrthMat = zeros(rNum,cNum);
for i = 1 : cNum
    if i == 1
        SchOrthMat(:,i) = BaseMat(:,i);
    else
        for j = 1 : i
            if j == 1
                SchOrthMat(:,i) = BaseMat(:,i);
            else
                up = 0;
                down = 0;
                for w = 1 : rNum
                    up = up + SchOrthMat(w,j) * BaseMat(w,i);
                    down = down + SchOrthMat(w,j) * SchOrthMat(w,j);
                    tmp = up / down;
                end
                SchOrthMat(:,i) = tmp * BaseMat(:,j - 1);
            end
        end
    end
end

for i = 1 : cNum
    sum = 0;
    for j = 1 : rNum
        sum = sum + SchOrthMat(j,i) * SchOrthMat(j,i);
    end
    sum = sqrt(sum);
    SchOrthMat(:,i) = sum * SchOrthMat(:,i);
end
















function pro = calDotPro(Vec1,Vec2)

if (size(Vec1,1) ~= size(Vec2,1)) || size(Vec1,2) ~= 1 || size(Vec2,2) ~= 1
    error('The input parameters are wrong!');
end

pro = 0;
for i = 1 : size(Vec1,1)
    pro = pro + Vec1(i) * Vec2(i);
end


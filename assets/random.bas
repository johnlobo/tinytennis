10 mode 1
20 defint A-Z
30 c=1
40 RANDOMIZE TIME
50 s=RND*1024+1
70 i=1023
80 while i>0
90 i=i-1
100 if s<1001 then p=s-1
110 x=p mod 40+1
120 y= p\40+1
130 pen c
140 locate x,y:print ("#");
160 c=(c mod 3)+1
170 l=s and 1
180 s=s\2
190 s=s XOR &240*l
200 wend
210 call&BB18

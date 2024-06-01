// Bonus 

//A 

0: CP 200 90    
1: CP 201 100  
2: CP 50 60     
3: BZJi 64 0     
4: CP 75 202     
5: CP 147 75    
6: CP 148 100   
7: CP 50 61 
8: BZJi 146 0     
9: CP 76 149     

//B 

10: CP 200 91    
11: CP 201 130   
12: CP 50 62     
13: BZJi 64 0    
14: CP 77 202    
15: CP 147 77   
16: CP 148 130  
17: CP 50 63    
18: BZJi 146 0    
19: CP 78 149    
20: BZJi 21 0    

21: 20          


// Sum
36: CPi 51 0       
37: CPi 203 0      

38: CP 204 200      
39: ADD 204 51      
40: CPI  205 204    
41: ADD 203 205     
42: ADDi 51 1       
43: CP 206 201      
44: LT 206 51       
45: BZJ 65 206     
46: CP 202 203    
47: BZJi 50 0    


50: 0             // stack pointer

// BZJ Pointers
60: 4            
61: 9           
62: 14           
63: 19            
64: 36            
65: 38            

75: 0    // sum of array 1
76: 0    // mean of array 1
77: 0    // sum of array 2
78: 0    // mean of array 2

90: 101  // array 1 start index
91: 131  // array 2 start index

100: 20  // SIZE of section A
101: 9   // first grade of Section A
102: 1   
103: 2
104: 2
105: 5
106: 7
107: 10
108: 7
109: 8
110: 6
111: 9
112: 4   
113: 2
114: 4
115: 3
116: 7
117: 10
118: 0
119: 8
120: 6   // last grade of Section A

130: 12  // SIZE of section B
131: 9   // first grade of Section B
132: 1   
133: 2
134: 4
135: 3
136: 7
137: 2
138: 0
139: 8
140: 5
141: 8
142: 1   // last grade of Section B   

146: 150 // divider start address , divider function
147: 0   // operand 1
148: 0   // operand 2
149: 0   // result
150: CPi 149 0
151: CP 173 147
152: CP 172 173
153: LT 172 148
154: LTi 172 1
155: BZJ 50 172
156: ADDi 149 1
157: CP 171 148
158: NAND 171 171
159: ADDi 171 1
160: ADD 173 171
161: BZJi 169 152  
169: 0 
170: 0 // temp
171: 0 // temp2
172: 0 // temp3
173: 0 // temp4                      , end of divider 
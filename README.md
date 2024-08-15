single flag solution 
not good as it busy waiting
![image](https://github.com/user-attachments/assets/a7f0ea10-33ea-4fb4-a9db-2607c589ff32)


peterson's solution
only applicable to two threads with single resources
![image](https://github.com/user-attachments/assets/a6e6d821-a81d-42b3-8879-cf8d7b27d7f9)


conditional variable
no busy waiting
still for single resource
![image](https://github.com/user-attachments/assets/f9603816-a333-472d-a6ee-1ab6e56f1d4a)


semaphore 
for multiple resources instances
for 3
![image](https://github.com/user-attachments/assets/604ae3ed-d7f4-4823-a578-a6a6b75b41b3)

![image](https://github.com/user-attachments/assets/88fa3603-d18b-4180-90f4-e8090aaaf1b8)
![image](https://github.com/user-attachments/assets/053994c0-6e58-4bbc-b47c-06391b56548e)


producer consumer problem
here the buffer is shared so we must have synchronization 
which can be obtained by conditional varible  
![image](https://github.com/user-attachments/assets/30165ebb-3bc6-442f-abd0-848e382470ea)
because its a finite buffer we have these problems

![image](https://github.com/user-attachments/assets/6d79c893-7483-4412-8748-8ad6a33cc3ca)


how to solve these
with mutex we can have mutual exclusion

![image](https://github.com/user-attachments/assets/2cfcd7e1-a2dd-4406-aac8-d37af351885e)

another probelm is reader writer problem 
here two reader can come but if their si one writer than no reader can come
![image](https://github.com/user-attachments/assets/60b06171-76c2-47ce-b032-d79c56ed01cf)



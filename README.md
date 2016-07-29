# Quantum-Tic-Tac-Toe




User defined m*n sized Quantum generalization of Tic-Tac-Toe. User plays at two different places in same move and one of which will be finalised when entanglement occurs. ( See how_to_play.pdf to see entire description of rules )

Implemented in C++ using Simplecpp Graphics Library developed by Prof. Abhiram Ranade, IIT Bombay.









### How to run code :


1. You must have Simplecpp Graphics Library which can be downloaded from [here](https://www.cse.iitb.ac.in/~ranade/simplecpp/).
2. Compile main.cpp and you can start playing !!!!
  
For linux you can also compile in the following way.
Let Path1 be path to folder where s++ is genereted in step1 and Path2 be path to folder containing main.cpp
   
Compile and run main.cpp using following command.
  ```
   	$ Path1/s++ -o Quantum_Tic_Tac_Toe Path2/main.cpp 
  ``` 
  
  
  
  ```
   	$ ./Quantum_Tic_Tac_Toe
   ```
  


### Extention of Rule of Game :

There are standard rules for 3x3 sized Quantum Tic Tac Toe but not for m*n sized, so rules are extended to make game interesting in bigger size. ( Modification is compatible with rules of 3x3 version )

1. Players can choose how many boxes should be there in a line to win.
2. In a situation of tie if number of empty boxes are greater than or equal to number of boxes required to win in a line, then game continues.

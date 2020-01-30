# Milestone2

## Table of contents
* Background
* Goal
* Preparations
* How to get started
* How does it work?
* GitHub Link

## Background
This project was done as an assignment for our programming course - Advanced Programming 1. It shows the following skills -
streaming data, parallel programming, client-server Architecture, templates, design patterns and so on. This is the second part of the project.

## Goal
The purpose of this part of the project is to find the best solution for a given problem. In our case, the problem is finding the best path between two given locations. It will be represented as a matrix, and the solution will be represented as a string of directions from the beginning point to the ending point- {Up, Down, Left, Right}. 

## Preparations
For running our project, you should make the following preparations:
* The project uses Threads, therefore it is very recommended to use a Linux workspace.
* You should have a matrix represented the following way:
    - each row contains numbers separated by a comma.
    - each row has the same amount of values as expected from a matrix.
    - each row will be separated by a new line.
* You need to know the location of your starting point in the matrix. Same for the ending point. it will be represented as a pair of numbers separated by a comma. 
notice!- the value first in the first row is in location 0,0.

## How to get started
After all our preparations are complete, it is time to solve our problem.
First, we need to create our server so we will be able to connect to it as a client. For that, we need to run our program as follows:
* open a terminal and write the command - g++ -std=c++14 *.cpp -o a.out -pthread
* then the following command will run the program - ./a.out

you may add a port number to that command, but it is not mandatory. The default port number is 5600.
Now, our server is ready and waiting for a client.
the next step will be to connect to the server. Open the terminal and write the following, followed by a port number of your choosing: telnet 127.0.0.1
Now, all you need to do is to enter your matrix followed by your starting point and ending point (in that exact order). At last, after all the information was sent, send the word "end" to announce the termination of your input.
Your solution to the problem will be presented to you :)

## How does it work?
So how the problem is being solved?
The server gets the client's input and checks if a solution to the problem already exists. If so, returns the solution. Otherwise transforms it into a searchable object. Then, via the A* algorithm, the problem is solved and it's solution saved. At last, the solution is being sent to the client.
Note :
At the begining we mentioned parallel programming. In this program, we use a parallel server that can handle up to ten clients at a time.

## GitHub Link
https://github.com/topStud/Milestone2

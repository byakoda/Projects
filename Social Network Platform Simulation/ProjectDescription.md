# Simple Social Network Simulation

This project is a simulation of basic functionalities of a simple social network platform using C programming. The key features include following users, liking posts, and implementing a cache to optimize data retrieval. This project not only allowed me to apply my theoretical knowledge but also provided practical experience with C programming, linked lists, and cache management.

## About the Developer
Hello! I’m Emre Akoda, a student at Middle East Technical University currently pursuing a degree in Computer Engineering.

I have a keen interest in programming and enjoy tackling challenges related to memory management, data structures, and system design. This project not only allowed me to apply my theoretical knowledge but also provided practical experience with C programming, linked lists, and cache management.

Feel free to reach out if you have any questions or feedback regarding this project!

### Contact
You can contact me via:

- Email: eakoda10@gmail.com
- LinkedIn: [Emre Akoda](https://www.linkedin.com/in/emre-akoda-b07b36248)

## Table of Contents
- [Objectives](#objectives)
- [Specifications](#specifications)
- [Structures](#structures)
- [Input File](#input-file)
- [Usage](#usage)
- [Compilation and Execution](#compilation-and-execution)

## Objectives
The main objectives of this project are to:
1. Simulate basic functionalities of a simple social network platform.
2. Implement a caching mechanism to speed up data access.
3. Gain hands-on experience with memory allocation, structs, linked lists, and strings in C.

## Specifications
The project simulates a social network with the following features:
1. A global struct `db` to store user and post data.
2. Two global structs `UserCache` and `PostCache` to store recently accessed users and posts.
3. Linked list operations for managing cache entries.
4. Implementations of follow and like functionalities with cache handling.
5. Printing cache entries and followers as specified.

### Functional Requirements
- **User Follow**: When a user follows another user, both users are fetched from the cache or database and the follower information is updated.
- **Post Like**: When a user likes a post, both the user and the post are fetched from the cache or database and their like counts are updated.
- **Cache Management**: The caches have limited capacities and follow an eviction policy to manage entries.

## Structures
The main structures used in this project are:

### User
```c
typedef struct User {
    int userId;
    char *username;
    Date *birthday;
    Node *followers_head;
    Node *followers_tail;
    int numOfFollowers;
    int numOfFollowing;
    int liked;
} User;
```


### Post
```c
typedef struct Post {
    int postId;
    char *content;
    User *Author;
    int likes;
} Post;
```
### Node
```c
typedef struct Node {
    void *data;
    struct Node *next;
    struct Node *prev;
} Node;
```
### Cache
```c
typedef struct Cache {
    int capacity;
    int size;
    Node *head;
    Node *tail;
} Cache;
```
## Input File
The input file is structured as follows:

1. Cache capacities for UserCache and PostCache.
2. Number of users followed by user details.
3. Number of posts followed by post details.
4. Number of actions followed by action details (follow or like).

### Example Input
- 10 20
- 2
- 3 eminem 17 10 1972
- 5 tupac 16 6 1971
- 1
- 6 5 107
- 4
- F 1 4
- F 5 2
- L 6 1
- L 7 2

## Usage
To use this project:

1. Compile the code using the provided Makefile.
2. Run the executable with the input file containing the required data.

## Compilation and Execution
### Compilation
Use the provided Makefile to compile the project:

```bash
make
```

### Execution
Run the compiled executable with the input file:

```bash
./socialnetwork < input.txt
```

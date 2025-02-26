#include "socialmedia.h"

#include <stdlib.h>

Database db;
Cache userCache;
Cache postCache;

void printUser(User *user) {
  printf("User: %d, Username: %s, Followers: %d, Following: %d, Liked: %d\n",
         user->userId, user->username, user->numOfFollowers,
         user->numOfFollowing, user->liked);
}

void printPost(Post *post) {
  printf("Post: %d, Author: %s, Likes: %d\n", post->postId,
         post->author->username, post->likes);
}

void printUserCache() {
  Node *current = userCache.head;
  printf("UserCache:\n");
  while(current != NULL){
    printUser((User*)current -> data);
    current = current -> next;
  }
}

void printPostCache() {
  Node *current = postCache.tail;
  printf("PostCache:\n");
  while(current != NULL){
    printPost((Post*)current -> data);
    current = current -> prev;
  }
}

Node *createNode(void *data) {
  Node *new_node = (Node*)malloc(sizeof(Node));
  new_node -> data = data;
  new_node -> next = NULL;
  new_node -> prev = NULL;
  return new_node;
}

void appendToCache(Cache *cache, void *data) {
  Node *for_control = createNode(data);
  if(cache -> size == cache -> capacity){
    removeLast(cache);
  }
  if(cache -> head != NULL){
    for_control -> next = cache -> head;
    cache -> head -> prev = for_control;
  }
  else{
    cache -> tail = for_control;
  }
  cache -> head = for_control;
  cache -> size++;
}

void moveToFront(Cache *cache, Node *node) {
  if(cache -> tail == node){
    cache -> tail = node -> prev;
  }
  if(cache -> head == node){
    return;
  }
  if(node -> prev != NULL || node -> next != NULL){
    node -> prev -> next = node -> next;
  }
  node -> next = cache -> head;
  if(cache -> head != NULL){
    cache -> head -> prev = node;
  }
  cache -> head = node;
  node -> prev = NULL;
}

void removeLast(Cache *cache) {
  if(cache -> tail -> prev != NULL){
    cache -> tail -> prev -> next = NULL;
  }
  else if( cache -> tail -> prev == NULL){
    cache -> head = NULL;
  }
  cache -> tail = cache -> tail -> prev;
}

User *fetchUser(int userId) {
  User *person = &db.users[userId];
  Node *current = userCache.head;
  while(current != NULL){
    User *person_2 = (User*)current -> data;
    if(person -> userId == userId){
      moveToFront(&userCache, current);
      return person_2;
    }
    current = current -> next;
  }
  appendToCache(&userCache, person);
  return person;
}

Post *fetchPost(int postId) {
  Node *current = postCache.head;
  Post *story = &db.posts[postId];
  while(current != NULL){
    Post *story_2 = (Post*)current -> data;
    if(story -> postId == postId){
      moveToFront(&postCache, current);
      return story_2;
    }
    current = current -> next;
  }
  appendToCache(&postCache, story);
  return story;
}

void followUser(int followerId, int followedId) {
  User *follower = fetchUser(followerId);
  User *followed = fetchUser(followedId);
  Node *new_person = createNode(follower);
  if(followed -> followers_head != NULL){
    followed -> followers_tail -> next = new_person;
    new_person -> prev = followed -> followers_tail;
  }
  else{
    followed -> followers_head = new_person;
  }
  followed -> followers_tail = new_person;
  follower -> numOfFollowing++;
  followed -> numOfFollowers++;
}

void likePost(int userId, int postId) {
  User *person = fetchUser(userId);
  Post *story = fetchPost(postId);
  person -> liked++;
  story -> likes++;
}

void printFollowersInReverse() {
  Node *current = userCache.head;
  printf("Followers of all users in UserCache in reverse:\n");
  while(current != NULL){
    User *person = (User*)current -> data;
    Node *current_2 = person -> followers_tail;
    printf("Followers of user with id %d in reverse:\n", person -> userId);
    while(current_2 != NULL){
      User *followers = (User*)current_2 -> data;
      printf("[%d] ", followers -> userId);
      current_2 = current_2 -> prev;
    }
    current = current -> next;
  }
}

void freeLinkedList(Node *head) {
  Node *current = head;
  while(current != NULL){
    Node *next_one = current -> next;
    free(current);
    current = next_one;
  }
}